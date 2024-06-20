import random
import socket
import subprocess
import select
import asyncio
import sys
import logging

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    OKPINK = '\033[95m'
    OKWHITE = '\033[97m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

class Player:
    def __init__(self, team, machine, port):
        self.team = team
        self.level = 1
        self.fd = 0
        self.machine = machine
        self.port = port
        self.socket = socket.socket()
        self.survival = True
        self.is_incanting = False
        self.player_ready = 1
        self.team_mates = 0
        self.MTopt = False
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

    ##SELECT FUNCTIONS


    def handle_server_response(self) -> str:
        '''Handle incoming server messages'''
        response = self.socket.recv(1024).decode()
        responses = response.split("\n")
        for reponse in responses:
            if reponse.startswith("dead"):
                print(bcolors.FAIL + "Player is dead" + bcolors.ENDC)
                self.disconnect(int(42))
            elif reponse.startswith("[ food"):
                self.interpret_inventory(reponse)
            elif reponse.startswith("[ player"):
                self.interpret_look(reponse)
            elif reponse.startswith("message "):
                self.receive_broadcast(reponse)
            elif reponse.isnumeric():
                self.nbr_connect = int(reponse)
            elif reponse.startswith("Current level: "):
                print(reponse)
                self.interpret_incantation(reponse)


    def select_gestion(self, message_to_send : str) -> str:
        '''select the function to call'''
        if self.socket.fileno() == -1:
            self.disconnect(2)
        if self.is_incanting:
            print(bcolors.FAIL + "Player is incanting" + bcolors.ENDC)
        print(bcolors.OKWHITE + f"Sending message: {message_to_send}" + bcolors.ENDC)
        _, ready_to_write, _ = select.select([], [self.socket], [], 1)
        if ready_to_write:
            self.socket.sendall(message_to_send.encode())
        return self.handle_server_response()


    ##IPC functions

    def forward(self) -> None:
        '''move forward'''
        self.select_gestion("Forward\n")


    def right(self) -> None:
        '''turn right'''
        self.select_gestion("Right\n")

    def left(self) -> None:
        '''turn left'''
        self.select_gestion("Left\n")

    def take(self, object : str) -> None:
        '''take object'''
        self.select_gestion(f"Take {object}\n")

    def interpret_look(self, response : str) -> list:
        '''interpret the look response'''
        print("interpret look")
        response = response[1:-1]
        response = response.split(',')
        for i in range(len(response)):
            if (response[i][0] == ' '):
                response[i] = response[i][1:]
            response[i] = response[i].split(' ')
        for i in range(len(response)):
            if response[i] == ['']:
                response[i] = []
        self.looked = response
        return response


    def look(self) -> list:
        '''look around the player'''
        response = self.select_gestion("Look\n")
        return response


    def interpret_incantation(self, response : str) -> None:
        '''interpret the incantation response'''
        print("interpret incantation")
        print(response)
        response = response.split(": ")
        self.is_incanting = False
        self.level = int(response[1])
        self.player_ready = 1


    def incantation(self) -> None:
        '''incantation'''
        self.select_gestion("Incantation\n")
        self.connect_nbr()
        if (self.nbr_connect == 0):
            self.fork()


    def broadcast(self, message : str) -> None:
        '''broadcast a message'''
        self.select_gestion(f"Broadcast {message}\n")

    def connect_nbr(self) -> None:
        '''connect the player'''
        self.select_gestion("Connect_nbr\n")

    def fork(self) -> None:
        '''fork the player'''
        self.select_gestion("Fork\n")

    def eject(self) -> None:
        '''eject the player'''
        self.select_gestion("Eject\n")

    def set_object(self, object : str) -> None:
        '''set object'''
        self.select_gestion(f"Set {object}\n")

    def check_dict_inventory(self, key : str) -> bool:
        '''check the inventory'''
        return key in [
            "food",
            "linemate",
            "deraumere",
            "sibur",
            "mendiane",
            "phiras",
            "thystame"
        ]

    def interpret_inventory(self, response : str) -> dict:
        '''interpret the inventory response'''
        print("interpret inventory")
        response = response[1:-2]
        response = response.split(',')
        for i in range(len(response) - 1):
            if (response[i][0] == ' '):
                response[i] = response[i][1:]
        inventory = {}
        for i in range(len(response) - 1):
            response[i] = response[i].split(' ')
            if self.check_dict_inventory(response[i][0]):
                inventory[response[i][0]] = int(response[i][1])
            else:
                key = response[i][0]
                inventory[key[3:]] = int(response[i][1])
        self.inventory.update(inventory)
        return inventory


    def get_inventory(self) -> None:
        '''get the inventory'''
        self.select_gestion("Inventory\n")

    ##AI functions


    def go_to_direction(self, direction : int) -> None:
        '''go to the direction given in parameter'''
        print("go to direction")
        if direction < 0 or direction > 8:
            return
        if direction == 0:
            print("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")
            self.broadcast(self.team + ":chui;pret;mon;gars??" + str(self.level))
            self.is_incanting = True
            while self.is_incanting:
                self.get_inventory()
                if self.inventory['food'] < 5:
                    self.survive()
                    break
            return
        self.MOVEMENTS_DIRECTION[direction - 1](self)


    def go_to(self, tile : list, pos : tuple, searching_item : list) -> None:
        '''go to the tile given in parameter'''
        print("go to")
        for _ in range(pos[1]):
            self.forward()
        if pos[0] > 0:
            self.right()
        elif pos[0] < 0:
            self.left()
        for _ in range(abs(pos[0])):
            self.forward()
        self.get_object(tile, searching_item)


    def get_object(self, tile : list , searching_item : list) -> None:
        print("get object")
        '''take the item in the tile'''
        for item in searching_item:
            if item in tile:
                print(bcolors.OKCYAN + f"Player {self.team} is taking {item}" + bcolors.ENDC)
                self.take(item)


    def get_correct_tile(self, searching_item : list) -> tuple[int, list]:
        '''get the correct tile'''
        print("get correct tile")
        for i in range(len(self.looked)):
            for j in range(len(searching_item)):
                if searching_item[j] in self.looked[i]:
                    return i, self.looked[i]
        return None


    def get_pos(self, tile: int) -> tuple[int, int]:
        '''set the coord of the tile'''
        print("get pos")
        index = 0
        for y in range(self.level + 1) :
            for x in range(-y, y + 1) :
                if index == tile:
                    return x, y
                index += 1
        return 0, 0


    def  search_object(self, searching_item : list) -> None:
        '''search the object in the tile'''
        print("search object")
        correct_tile = self.get_correct_tile(searching_item)
        if correct_tile:
            self.go_to(correct_tile[1], self.get_pos(correct_tile[0]), searching_item)
        else :
            self.go_to_direction(random.randint(1, 8))


    def survive(self) -> None:
        '''survive'''
        print("survive")
        while self.inventory['food'] < 15:
            self.look()
            self.search_object(['food'])
            self.get_inventory()


    def expedition(self) -> None:
        '''expeditions'''
        print("expedition")
        self.search_object(['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame'])


    def count_player(self, looked: list) -> int:
        '''count the player in the tile'''
        print("count player")
        count = 0
        for i in range(len(looked)):
            if looked[i] == 'player':
                count += 1
        return count


    def check_requirements(self, requirements: dict) -> bool:
        '''check the requirements'''
        print("check requirements")
        self.get_inventory()
        self.look()
        look = self.looked
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
        print("what i need")
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
        print("receive broadcast")
        direction = message_received.split(", ")[0].split(" ")[1]
        message = message_received.split(", ")[1]
        if not message.startswith(self.team):
            return
        ordre = message.split(":")[1]
        lvl = int(message.split("??")[1])
        if ordre.startswith("ON;EVOLUE;OUUU;??") and lvl == self.level:
            if self.inventory['food'] < 5:
                self.survive()
            print(bcolors.OKGREEN + f"Player {self.team} is going to direction {direction}" + bcolors.ENDC)
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
        print("put requirements")
        for key in requirements:
            if key != 'player':
                for _ in range(requirements[key]):
                    self.set_object(key)

##faire un truc avec des id pour s'arreter
    def try_incantation(self) -> None:
        '''try the incantation'''
        print("try incantation")
        self.get_inventory()
        if self.inventory['food'] < 5:
            return
        requirements = self.LEVEL_REQUIREMENTS[self.level]
        requirements_checked = self.check_requirements(requirements)
        count_call = 0
        while requirements_checked != 0:
            if requirements_checked == 1:
                if self.inventory['food'] < 5:
                    return
                self.look()
                self.search_object(self.what_i_need(requirements))
            else:
                if count_call == 0:
                    self.call_teammates()
                count_call += 1
                if count_call == 4:
                    count_call = 0
                self.get_inventory()
                if self.inventory['food'] < 5:
                    return
            requirements_checked = self.check_requirements(requirements)
        self.put_requirements(requirements)
        print(bcolors.WARNING + "INCANTATION" + bcolors.ENDC)
        self.incantation()


    def run(self) -> None:
        '''run the player'''
        while (True):
            print(bcolors.OKBLUE + f"Player {self.team} is lvl {self.level}" + bcolors.ENDC)
            if self.inventory['food'] < 15:
                print(bcolors.WARNING + "A L'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAIDE" + bcolors.ENDC)
                self.survive()
            if not self.is_incanting :
                self.try_incantation()


    def connect(self) -> None:
        '''connect the player'''
        try:
            self.socket.connect((self.machine, int(self.port)))
        except socket.error as e:
            return
        print(self.socket.recv(1024).decode())
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
