''' AI for the Zappy project '''

import random
import socket
import subprocess
import select
import asyncio
import sys
import logging
from time import sleep

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    OKPINK = '\033[95m'
    OKYELLOW = '\033[93m'
    OKWHITE = '\033[97m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

class Player:
    '''Player class'''
    def __init__(self, team, machine, port):
        self.team = team
        self.level = 1
        self.fd = 0
        self.machine = machine
        self.port = port
        self.socket = socket.socket()
        self.survival = False
        self.is_incanting = False
        self.player_ready = 1
        self.receive_inventory = False
        self.receive_look = False
        self.is_doing_action = False
        self.action = 0
        self.team_mates = 0
        self.mtopt = False
        self.nbr_connect = 0
        self.inventory = {
            'food': 10,
            'linemate': 0,
            'deraumere': 0,
            'sibur': 0,
            'mendiane': 0,
            'phiras': 0,
            'thystame': 0
        }
        self.looked = []


    LEVEL_REQUIREMENTS = {
        1: {
            'player': 1,
            'linemate': 1
        },
        2: {
            'player': 2,
            'linemate': 1,
            'deraumere': 1,
            'sibur': 1
        },
        3: {
            'player': 2,
            'linemate': 2,
            'sibur': 1,
            'phiras': 2
        },
        4: {
            'player': 4,
            'linemate': 1,
            'deraumere': 1,
            'sibur': 2,
            'phiras': 1
        },
        5: {
            'player': 4,
            'linemate': 1,
            'deraumere': 2,
            'sibur': 1,
            'mendiane': 3
        },
        6: {
            'player': 6,
            'linemate': 1,
            'deraumere': 2,
            'sibur': 3,
            'phiras': 1
        },
        7: {
            'player': 6,
            'linemate': 2,
            'deraumere': 2,
            'sibur': 2,
            'phiras': 2,
            'mendiane': 2,
            'thystame': 1
        }
    }


    MOVEMENTS_DIRECTION = [
        lambda self: (self.forward()),
        lambda self: (self.left(), self.forward(), self.right(), self.forward()),
        lambda self: (self.left(), self.forward()),
        lambda self: (self.left(), self.forward(), self.left(), self.forward()),
        lambda self: (self.left(), self.left(), self.forward()),
        lambda self: (self.right(), self.forward(), self.right(), self.forward()),
        lambda self: (self.right(), self.forward()),
        lambda self: (self.right(), self.forward(), self.left(), self.forward())
    ]

    messages_queue = []


    ##IPC functions

    def forward(self) -> None:
        '''move forward'''
        print(bcolors.OKGREEN + "Player is moving forward" + bcolors.ENDC)
        self.messages_queue.append("Forward\n")


    def right(self) -> None:
        '''turn right'''
        print(bcolors.OKGREEN + "Player is turning right" + bcolors.ENDC)
        self.messages_queue.append("Right\n")


    def left(self) -> None:
        '''turn left'''
        print(bcolors.OKGREEN + "Player is turning left" + bcolors.ENDC)
        self.messages_queue.append("Left\n")


    def take(self, object : str) -> None:
        '''take object'''
        self.messages_queue.append(f"Take {object}\n")


    def interpret_look(self, response : str) -> None:
        '''interpret the look response'''
        response = response[1:-1]
        response = response.split(',')
        response = [cell.strip() for cell in response]
        self.looked = [cell.split(' ') for cell in response]
        self.receive_look = True

    def look(self) -> None:
        '''look around the player'''
        response = self.messages_queue.append("Look\n")


    def interpret_incantation(self, response : str) -> None:
        '''interpret the incantation response'''
        print(bcolors.WARNING + "GG MON GRAS !!!" + bcolors.ENDC)
        response = response.split(": ")
        self.is_incanting = False
        self.level = int(response[1])
        self.player_ready = 1
        #if self.nbr_connect == 0:
        #    self.fork()


    def incantation(self) -> None:
        '''incantation'''
        self.messages_queue.append("Incantation\n")
        self.connect_nbr()


    def broadcast(self, message : str) -> None:
        '''broadcast a message'''
        self.messages_queue.append(f"Broadcast {message}\n")


    def connect_nbr(self) -> None:
        '''connect the player'''
        self.messages_queue.append("Connect_nbr\n")


    def fork(self) -> None:
        '''fork the player'''
        self.messages_queue.append("Fork\n")


    def eject(self) -> None:
        '''eject the player'''
        self.messages_queue.append("Eject\n")


    def set_object(self, object : str) -> None:
        '''set object'''
        self.messages_queue.append(f"Set {object}\n")


    def interpret_inventory(self, response : str) -> None:
        '''interpret the inventory response'''
        response = response[1:-1]
        response = ' '.join(response.split())
        response = response.replace(" ,", ",").replace(", ", ",")
        response = response.replace(" ", "=")
        self.inventory.update(eval(f"dict({response})"))
        self.receive_inventory = True

    def get_inventory(self) -> None:
        '''get the inventory'''
        self.messages_queue.append("Inventory\n")


    ##AI functions

    def go_to_direction(self, direction : int) -> None:
        '''go to the direction given in parameter'''
        print(bcolors.OKGREEN + f"Player {self.team} is going to direction {direction}" + bcolors.ENDC)
        if direction < 0 or direction > 8:
            return
        if direction == 0:
            self.broadcast(self.team + ":chui;pret;mon;gars??" + str(self.level))
            self.is_incanting = True
            return
        self.MOVEMENTS_DIRECTION[direction - 1](self)


    def go_to(self, tile : list, pos : tuple, searching_item : list) -> None:
        '''go to the tile given in parameter'''
        for _ in range(pos[1]):
            self.forward()
        if pos[0] > 0:
            self.right()
        elif pos[0] < 0:
            self.left()
        for _ in range(abs(pos[0])):
            self.forward()
        self.get_object(tile, searching_item)


    def count_item(self, tile : list, item : str) -> int:
        '''count the item in the tile'''
        count = 0
        for i in range(len(tile)):
            if tile[i] == item:
                count += 1
        return count


    def get_object(self, tile : list , searching_item : list) -> None:
        '''take the item in the tile'''
        for item in searching_item:
            nbr = self.count_item(tile, item)
            if item in tile:
                for _ in range(nbr):
                    print(bcolors.OKCYAN + f"Player {self.team} is taking {item}" + bcolors.ENDC)
                    self.take(item)


    def get_correct_tile(self, searching_item : list) -> tuple[int, list]:
        '''get the correct tile'''
        if "food" in searching_item:
            food_count = 0
            index = 0
            for i in range(len(self.looked)):
                if self.count_item(self.looked[i], "food") > food_count:
                    food_count = self.count_item(self.looked[i], "food")
                    index = i
            if food_count > 0:
                return index, self.looked[index]
        else:
            for i in range(len(self.looked)):
                for j in range(len(searching_item)):
                    if searching_item[j] in self.looked[i]:
                        return i, self.looked[i]
        return None


    def get_pos(self, tile: int) -> tuple[int, int]:
        '''set the coord of the tile'''
        index = 0
        for y in range(self.level + 1) :
            for x in range(-y, y + 1) :
                if index == tile:
                    return x, y
                index += 1
        return 0, 0


    def search_object(self, searching_item : list) -> None:
        '''search the object in the tile'''
        print(bcolors.OKGREEN + f"Player is looking to f{self.looked}" + bcolors.ENDC)
        correct_tile = self.get_correct_tile(searching_item)
        print(bcolors.OKGREEN + f"i find this tile: {correct_tile}" + bcolors.ENDC)
        if correct_tile:
            self.go_to(correct_tile[1], self.get_pos(correct_tile[0]), searching_item)
        else :
            self.go_to_direction(random.randint(1, 8))


    def check_requirements(self, requirements: dict) -> int:
        '''check the requirements'''
        for key in requirements:
            if key != 'player' and self.inventory[key] < requirements[key]:
                return 1
        for player in requirements:
            if player == 'player':
                if self.player_ready < requirements[player]:
                    return 2
        return 0


    def what_i_need(self, requirements: dict) -> list:
        '''return list of which item i need to search for'''
        needed = []
        for key in requirements:
            if key == 'player':
                continue
            if self.inventory[key] < requirements[key]:
                needed.append(key)
        return needed


    def receive_broadcast(self, message_received) -> None:
        '''receive the broadcast'''
        if self.survival:
            return
        direction = message_received.split(", ")[0].split(" ")[1]
        message = message_received.split(", ")[1]
        if not message.startswith(self.team):
            return
        ordre = message.split(":")[1]
        lvl = int(message.split("??")[1])
        if ordre.startswith("ON;EVOLUE;OUUU;??") and lvl == self.level:
            self.messages_queue = []
            self.go_to_direction(int(direction))
        if ordre.startswith("chui;pret;mon;gars??") and lvl == self.level:
            self.player_ready += 1


    def call_teammates(self) -> None:
        '''call the teammates'''
        print(bcolors.WARNING + "CALLING TEAMMATES" + bcolors.ENDC)
        self.broadcast(self.team + ":ON;EVOLUE;OUUU;??" + str(self.level))
        return


    def put_requirements(self, requirements: dict) -> None:
        '''put the requirements'''
        for key in requirements:
            if key != 'player':
                for _ in range(requirements[key]):
                    self.set_object(key)


    def incantation_gestion(self) -> None:
        '''incantation gestion'''
        if self.action == 0:
            print(bcolors.WARNING + "INCANTATION" + bcolors.ENDC)
            self.put_requirements(self.LEVEL_REQUIREMENTS[self.level])
            self.incantation()
            return
        elif self.action == 1:
            self.search_object(self.what_i_need(self.LEVEL_REQUIREMENTS[self.level]))
            return
        elif self.action == 2:
            self.call_teammates()
            return

    def get_action(self) -> None:
        '''get the action'''
        if self.inventory['food'] < 6:
            self.survival = True
        if self.survival:
            if self.inventory['food'] >= 15:
                self.survival = False
            print(bcolors.FAIL + "Player is starving" + bcolors.ENDC)
            self.is_incanting = False
            self.search_object(['food'])
            return
        if self.is_incanting:
            print(bcolors.FAIL + "PAULO EST TROP BO" + bcolors.ENDC)
            self.messages_queue = []
            return
        else:
            self.action = self.check_requirements(self.LEVEL_REQUIREMENTS[self.level])
            self.incantation_gestion()
            return


    def handle_server_response(self) -> None:
        '''Handle incoming server messages'''
        response = self.socket.recv(1024).decode()
        responses = response.split("\n")
        for reponse in responses:
            if reponse.startswith("dead"):
                print(bcolors.FAIL + "Player is dead" + bcolors.ENDC)
                self.disconnect(int(42))
            elif reponse.startswith("[ food") or reponse.startswith("[food"):
                print(bcolors.OKPINK + "Player have inventory" + bcolors.ENDC)
                self.interpret_inventory(reponse)
            elif reponse.startswith("[ player") or reponse.startswith("[player"):
                print(bcolors.OKPINK + "Player is looking to ta grosse mere la pute" + bcolors.ENDC)
                self.interpret_look(reponse)
            elif reponse.startswith("message "):
                self.receive_broadcast(reponse)
            elif reponse.isnumeric():
                self.nbr_connect = int(reponse)
            elif reponse.startswith("Current level: "):
                self.interpret_incantation(reponse)
            elif reponse.startswith("ko"):
                print(bcolors.FAIL + "MANGE MOI LE BOU DU GLAND SALE FILS DE PUTE" + bcolors.ENDC)
                self.is_incanting = False


    def handle_server_sending(self) -> None:
        '''Handle sending messages to the server'''
        if self.messages_queue:
            print(bcolors.FAIL + self.messages_queue[0] + bcolors.ENDC)
            self.socket.sendall(self.messages_queue[0].encode())
            self.messages_queue.pop(0)
            self.is_doing_action = False
            self.receive_look = False
            self.receive_inventory = False
            return
        if self.receive_inventory == False:
            print(bcolors.OKCYAN + "CACA INVENTORY" + bcolors.ENDC)
            self.socket.sendall("Inventory\n".encode())
            return
        if self.receive_look == False:
            print(bcolors.OKCYAN + "CACA look" + bcolors.ENDC)
            self.socket.sendall("Look\n".encode())
            return
        if self.receive_inventory and self.receive_look:
            self.get_action()
            self.is_doing_action = True


    def run(self) -> None:
        '''run the player'''
        while True:
            print(bcolors.OKBLUE + f"Player {self.team} is lvl {self.level}" + bcolors.ENDC)
            if self.socket.fileno() == -1:
                self.disconnect(2)
            _, ready_to_write, _ = select.select([], [self.socket], [], 1)
            if ready_to_write:
                self.handle_server_sending()
            if not self.is_doing_action:
                print("LEO LE RIGOLO")
                self.handle_server_response()


    def connect(self) -> None:
        '''connect the player'''
        try:
            self.socket.connect((self.machine, int(self.port)))
        except socket.error as e:
            return
        reponsed = self.socket.recv(1024).decode()
        print(bcolors.OKBLUE + f"Received message: {reponsed}" + bcolors.ENDC)
        while True:
            self.socket.sendall((self.team + "\n").encode())
            response = self.socket.recv(1024).decode()
            print(bcolors.OKBLUE + f"Received message: {response}" + bcolors.ENDC)
            if not response:
                continue
            if response == "ko\n":
                self.disconnect(6)
                break
            elif response[0].isnumeric():
                break


    def disconnect(self, error : int) -> None:
        '''disconnect the player'''
        self.socket.close()
        sys.exit(error)
