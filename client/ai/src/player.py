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
        self.player_ready = 1
        self.action = 0
        self.team_mates = 0
        self.mtopt = False
        self.mode: Player.Mode = Player.Mode.EXPEDITION
        self.nbr_connect = 0
        self.broadcasts = []
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


    class Mode:
        SURVIVAL = 0
        WAITING = 1
        EXPEDITION = 2


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


    ##IPC functions

    def receive(self, checks: bool = True) -> str:
        msg = self.socket.recv(1024).decode()
        if not msg.endswith("\n"):
            msg += self.receive()
        if checks:
            if "message" in msg:
                self.broadcasts.append(msg)
                return self.receive()
            if "dead" in msg:
                self.disconnect(0)
        return msg


    def forward(self) -> None:
        '''move forward'''
        print(bcolors.OKGREEN + "Player is moving forward" + bcolors.ENDC)
        self.socket.sendall("Forward\n".encode())
        ok = self.receive()


    def right(self) -> None:
        '''turn right'''
        print(bcolors.OKGREEN + "Player is turning right" + bcolors.ENDC)
        self.socket.sendall("Right\n".encode())
        ok = self.receive()


    def left(self) -> None:
        '''turn left'''
        print(bcolors.OKGREEN + "Player is turning left" + bcolors.ENDC)
        self.socket.sendall("Left\n".encode())
        ok = self.receive()


    def take(self, object : str) -> None:
        '''take object'''
        self.socket.sendall(f"Take {object}\n".encode())
        ok = self.receive()
        self.get_inventory()


    def look(self) -> None:
        '''look around the player'''
        self.socket.sendall("Look\n".encode())
        res = self.receive()
        response = res[1:-1]
        response = response.split(',')
        response = [cell.strip() for cell in response]
        self.looked = [cell.split(' ') for cell in response]


    def incantation(self) -> None:
        '''incantation'''
        self.socket.sendall("Incantation\n".encode())
        res = self.receive()
        if "Elevation underway" in res:
            res = self.receive()
            if "Current level" in res:
                self.level += 1
                self.mode = self.Mode.EXPEDITION
        else:
            return


    def broadcast(self, message : str) -> None:
        '''broadcast a message'''
        self.socket.sendall(f"Broadcast {message}\n".encode())
        ok = self.receive()


    def connect_nbr(self) -> int:
        '''connect the player'''
        self.socket.sendall("Connect_nbr\n".encode())
        ok: str = self.receive()
        if not ok.isnumeric():
            return -1
        return int(ok)


    def fork(self) -> None:
        '''fork the player'''
        self.socket.sendall("Fork\n".encode())
        ok = self.receive()


    def eject(self) -> None:
        '''eject the player'''
        self.socket.sendall("Eject\n".encode())
        ok = self.receive()


    def set_object(self, object : str) -> None:
        '''set object'''
        self.socket.sendall(f"Set {object}\n".encode())
        ok = self.receive()
        self.get_inventory()


    def get_inventory(self) -> None:
        '''get the inventory'''
        self.socket.sendall("Inventory\n".encode())
        res = self.receive().strip()
        res = res[1:-1]
        res = ' '.join(res.split())
        res = res.replace(" ,", ",").replace(", ", ",")
        res = res.replace(" ", "=")
        self.inventory.update(eval(f"dict({res})"))


    ##AI functions

    def go_to_direction(self, direction : int) -> None:
        '''go to the direction given in parameter'''
        print(bcolors.OKGREEN + f"Player {self.team} is going to direction {direction}" + bcolors.ENDC)
        if direction < 0 or direction > 8:
            return
        if direction == 0:
            self.broadcast(self.team + ":chui;pret;mon;gars??" + str(self.level))
            self.mode = self.Mode.WAITING
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
        print(bcolors.OKGREEN + f"Player is looking for f{self.looked}" + bcolors.ENDC)
        self.look()
        correct_tile = self.get_correct_tile(searching_item)
        if correct_tile:
            self.go_to(correct_tile[1], self.get_pos(correct_tile[0]), searching_item)
        else:
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
        self.get_inventory()
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
        if self.inventory['food'] < 6:
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
        self.get_inventory()
        if self.inventory['food'] < 6:
            self.mode = self.Mode.SURVIVAL
        if self.mode == self.Mode.SURVIVAL:
            if self.inventory['food'] >= 15:
                self.mode = self.Mode.EXPEDITION
            print(bcolors.FAIL + "Player is starving" + bcolors.ENDC)
            self.search_object(['food'])
            return
        if self.mode == self.Mode.EXPEDITION:
            self.action = self.check_requirements(self.LEVEL_REQUIREMENTS[self.level])
            self.incantation_gestion()


    def run(self) -> None:
        '''run the player'''
        while True:
            print(bcolors.OKBLUE + f"Player {self.team} is lvl {self.level}" + bcolors.ENDC)
            if self.socket.fileno() == -1:
                self.disconnect(2)
            self.get_action()


    def connect(self) -> None:
        '''connect the player'''
        try:
            self.socket.connect((self.machine, int(self.port)))
        except socket.error as e:
            return
        reponsed = self.receive(False)
        print(bcolors.OKBLUE + f"Received message: {reponsed}" + bcolors.ENDC)
        while True:
            self.socket.sendall((self.team + "\n").encode())
            response = self.receive(False)
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
