import random
import socket
import subprocess
import select
import asyncio

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
        self.team_mates = 0
        self.MTopt = False


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
        print("Received:", response)
        if response:
            if response.startswith("dead"):
                print("Player is dead")
                self.disconnect()
            if response.startswith("[food"):
                return self.interpret_inventory(response)
            elif response.startswith("[player"):
                return self.interpret_look(response)
            if response.startswith("message "):
                print("Received broadcast")
                return self.handle_server_response()
                self.receive_broadcast(response)
            else:
                return response


    def select_gestion(self, message_to_send : str) -> str:
        '''select the function to call'''
        _, ready_to_write, _ = select.select([], [self.socket], [], 1)
        if ready_to_write:
            print("Sending:", message_to_send)
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
        response = response[1:-2]
        response = response.split(',')
        for i in range(len(response)):
            if (response[i][0] == ' '):
                response[i] = response[i][1:]
            response[i] = response[i].split(' ')
        for i in range(len(response)):
            if response[i] == ['']:
                response[i] = []
        return response


    def look(self) -> list:
        '''look around the player'''
        response = self.select_gestion("Look\n")
        return response

    def incantation(self) -> None:
        '''incantation'''
        if self.select_gestion("Incantation\n") != "ko\n":
            self.level += 1
            self.is_incanting = True


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
        return inventory


    def get_inventory(self) -> dict:
        '''get the inventory'''
        reponse = self.select_gestion("Inventory\n")
        return reponse

    ##AI functions


    def go_to_direction(self, direction : int) -> None:
        '''go to the direction given in parameter'''
        print(direction)
        self.MOVEMENTS_DIRECTION[direction](self)


    def go_to(self, tile : list, pos : tuple, searching_item : list) -> None:
        '''go to the tile given in parameter'''
        print(f"{pos=}")
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
        '''take the item in the tile'''
        for item in searching_item:
            if item in tile:
                print("Item found")
                print(item)
                self.take(item)


    def get_correct_tile(self, looked: list,  searching_item : list) -> tuple[int, list]:
        '''get the correct tile'''
        for i in range(len(looked)):
            for j in range(len(searching_item)):
                if searching_item[j] in looked[i]:
                    return i, looked[i]
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


    def  search_object(self, looked: list, searching_item : list) -> None:
        '''search the object in the tile'''
        correct_tile = self.get_correct_tile(looked, searching_item)
        if correct_tile:
            self.go_to(correct_tile[1], self.get_pos(correct_tile[0]), searching_item)
        else :
            print("Item not found")
            self.go_to_direction(random.randint(1, 3))


    def survive(self) -> None:
        '''survive'''
        while self.get_inventory()['food'] < 15:
            self.search_object(self.look(), ['food'])


    def expedition(self) -> None:
        '''expeditions'''
        self.search_object(['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame'])


    def count_player(self, looked: list) -> int:
        '''count the player in the tile'''
        count = 0
        for i in range(len(looked)):
            if looked[i] == 'player':
                count += 1
        return count


    def check_requirements(self, requirements: dict) -> bool:
        '''check the requirements'''
        inventory = self.get_inventory()
        look = self.look()
        for key in requirements:
            if key != 'player' and inventory[key] < requirements[key]:
                return 1
        for player in requirements:
            if player == 'player':
                if self.count_player(look[0]) < requirements[player]:
                    return 2
        return 0


    def what_i_need(self, requirements: dict) -> list:
        '''return list of which item i need to search for'''
        inventory = self.get_inventory()
        needed = []
        for key in requirements:
            print(key)
            if key == 'player':
                continue
            if inventory[key] < requirements[key]:
                needed.append(key)
        print(needed)
        return needed


    def receive_broadcast(self, message_received) -> None:
        '''receive the broadcast'''
        direction = message_received.split(", ")[0].split(" ")[1]
        message = message_received.split(", ")[1]
        if not message.startswith(self.team):
            return
        ordre = message.split(": ")[1]
        lvl = int(message.split("?")[1])
        if ordre == "ON EVOLUE OUUU ??" and lvl == self.level:
            self.go_to_direction(int(direction))
        return

    def call_teammates(self) -> None:
        '''call the teammates'''
        self.broadcast(self.team + ": ON EVOLUE OUUU ??" + str(self.level))
        return


    def put_requirements(self, requirements: dict) -> None:
        '''put the requirements'''
        for key in requirements:
            if key != 'player':
                for _ in range(requirements[key]):
                    self.set_object(key)


    def try_incantation(self) -> None:
        '''try the incantation'''
        inventory = self.get_inventory()
        if inventory['food'] < 5:
            return
        requirements = self.LEVEL_REQUIREMENTS[self.level]
        requirements_checked = self.check_requirements(requirements)
        while requirements_checked != 0:
            if requirements_checked == 1:
                print("searching for items")
                self.search_object(self.look(), self.what_i_need(requirements))
            else:
                print("calling teammates")
                self.call_teammates()
                if self.get_inventory()['food'] < 5:
                    return
            requirements_checked = self.check_requirements(requirements)
        self.put_requirements(requirements)
        self.incantation()


    def run(self) -> None:
        '''run the player'''
        while (True):
            print("MY LEVEL IS : ", self.level)
            inventory = self.get_inventory()
            if inventory != {}:
                if inventory['food'] < 5:
                    self.survive()
            if not self.is_incanting :
                self.try_incantation()

    def connect(self) -> None:
        '''connect the player'''
        try:
            self.socket.connect((self.machine, int(self.port)))
        except socket.error as e:
            print(f"Socket error: {e}")
            return
        self.socket.sendall("\n".encode())
        while True:
            print("Sending team")
            self.socket.sendall((self.team + "\n").encode())
            response = self.socket.recv(1024).decode()
            print("Received:", response)
            if response == "ko\n":
                break


    def disconnect(self) -> None:
        '''disconnect the player'''
        self.socket.close()
        pass