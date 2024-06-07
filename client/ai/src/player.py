import random
import socket

level_requirements = {
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

    ##IPC functions

    def forward(self) -> None:
        '''move forward'''
        self.socket.sendall("Forward\n".encode())
        response = self.socket.recv(1024).decode()
        if response == "ko\n":
            self.survival = False
        pass


    def right(self) -> None:
        '''turn right'''
        self.socket.sendall("Right\n".encode())
        response = self.socket.recv(1024).decode()
        if response == "ko\n":
            self.survival = False
        pass


    def left(self) -> None:
        '''turn left'''
        self.socket.sendall("Left\n".encode())
        response = self.socket.recv(1024).decode()
        if response == "ko\n":
            self.survival = False
        pass


    def take(self, object : str) -> None:
        '''take the object in the tile'''
        self.socket.sendall(f"Take {object}\n".encode())
        response = self.socket.recv(1024).decode()
        if response == "ko\n":
            self.survival = False
        pass


    def interpretlook(self, response : str) -> list:
        '''interpret the look response'''
        print(response, end="")
        response = response[1:-2]
        response = response.split(',')
        for i in range(len(response)):
            response[i] = response[i].split(' ')
        return response
        pass


    def look(self) -> list:
        '''look around the player'''
        self.socket.sendall("Look\n".encode())
        response = self.socket.recv(1024).decode()
        if response != "ko\n":
            print(f"Around -> {self.interpretlook(response)}")
            return response
        else:
            self.survival = False
        pass


    def incantation(self) -> None:
        '''incantation'''
        self.socket.sendall("Incantation\n".encode())
        response = self.socket.recv(1024).decode()
        pass


    def broadcast(self, message : str) -> None:
        '''broadcast a message'''
        self.socket.sendall(f"Broadcast {message}\n".encode())
        response = self.socket.recv(1024).decode()
        if response == "ko\n":
            self.survival = False
        pass


    def connect_nbr(self) -> None:
        '''connect the player'''
        self.socket.sendall("Connect_nbr\n".encode())
        pass


    def fork(self) -> None:
        '''fork the player'''
        self.socket.sendall("Fork\n".encode())
        response = self.socket.recv(1024).decode()
        if response == "ko\n":
            self.survival = False
        pass


    def eject(self) -> None:
        '''eject the player'''
        self.socket.sendall("Eject\n".encode())
        response = self.socket.recv(1024).decode()
        if response == "ko\n":
            self.survival = False
        pass


    def set_object(self, object : str) -> None:
        '''set object down'''
        self.socket.sendall(f"Set {object}\n".encode())
        response = self.socket.recv(1024).decode()
        if response == "ko\n":
            self.survival = False
        pass


    def get_inventory(self) -> None:
        '''get the inventory of the player'''
        self.socket.sendall("Inventory\n".encode())
        response = self.socket.recv(1024).decode()
        if response == "ko\n":
            self.survival = False
        print(f"Inventory -> {response}", end="")
        pass


    ##AI functions

    def go_to(self, tile : list, pos : tuple, searching_item : list) -> None:
        '''go to the tile given in parameter'''
        for _ in range(pos.y):
            self.forward()
        if pos.x > 0:
            self.right()
        elif pos.x < 0:
            self.left()
        for _ in range(abs(pos.x)):
            self.forward()
        self.get_object(tile, searching_item)


    def get_object(self, tile : list , searching_item : list) -> None:
        '''take the item in the tile'''
        for item in searching_item:
            if item in tile:
                self.take(item)


    def go_to_direction(self, direction : int) -> None:
        '''go to the direction given in parameter'''
        if direction == 1:
            self.forward()
        elif direction == 2:
            self.left()
            self.forward()
            self.right()
            self.forward()
        elif direction == 3:
            self.left()
            self.forward()
        elif direction == 4:
            self.left()
            self.forward()
            self.left()
            self.forward()
        elif direction == 5:
            self.left()
            self.left()
            self.forward()
        elif direction == 6:
            self.right()
            self.forward()
            self.right()
            self.forward()
        elif direction == 7:
            self.right()
            self.forward()
        elif direction == 8:
            self.right()
            self.forward()
            self.left()
            self.forward()


    def receive_broadcast(self) -> str:
        '''recieve a broadcast'''
        pass


    def get_correct_tile(looked: list,  searching_item : list) -> tuple[int, list]:
        '''get the correct tile'''
        for i in range(len(looked)):
            for j in range(len(searching_item)):
                if j in looked[i]:
                    return i, looked[i]
        return None


    def get_pos(self, tile: int) -> tuple[int, int]:
        '''set the coord of the tile'''
        index = 0
        for y in range(self.level + 1) :
            for x in range(-y, y + 1) :
                if index == tile:
                    return x, y
        return 0, 0


    def search_object(self, looked: list, searching_item : list) -> None:
        '''search the object in the tile'''
        correct_tile = self.get_correct_tile(looked, searching_item)
        if correct_tile:
            self.go_to(correct_tile[1], self.get_pos(correct_tile[0]), searching_item)
        else :
            self.go_to_direction(random.randint(1, 3))


    def survive(self) -> None:
        '''survive'''
        inventory = self.get_inventory()
        while inventory['food'] < 10:
            self.search_object(self.look(), ['food'])


    def expedition(self) -> None:
        '''expeditions'''
        self.search_object(self.look(), ['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame'])


    def check_requirements(self, requirements: dict) -> bool:
        '''check the requirements'''
        inventory = self.get_inventory()
        look = self.look()
        for key in requirements:
            if inventory[key] < requirements[key]:
                return 1
            if key == 'player':
                if look[0] < requirements[key]:
                    return 2
        return 0


    def what_i_need(self, requirements: dict) -> list:
        '''return list of which item i need to search for'''
        inventory = self.get_inventory()
        needed = []
        for key in requirements:
            if inventory[key] < requirements[key]:
                needed.append(key)
        return needed


    def call_teammates(self) -> None:
        '''call the teammates'''
        self.broadcast(self.team + ": ON EVOLUE OUUU ??" + str(self.level))
        return


    def try_incantation(self) -> None:
        '''try the incantation'''
        inventory = self.get_inventory()
        if inventory['food'] < 10:
            return
        requirements = level_requirements[self.level - 1]
        requirements_checked = self.check_requirements(requirements)
        if requirements_checked == 0:
            self.incantation()
        else:
            while requirements_checked != 0:
                if requirements_checked == 1:
                    self.search_object(self.look(), self.what_i_need(requirements))
                else:
                    self.call_teammates()
                requirements_checked = self.check_requirements(requirements)
            self.incantation()
            self.is_incanting = True
            pass


    def run(self) -> None:
        '''run the player'''
        self.socket.connect((self.machine, int(self.port)))
        self.socket.sendall("\n".encode())
        while True:
            self.socket.sendall((self.team + "\n").encode())
            if self.socket.recv(1024).decode() == "ko\n":
                break

        while (True):
            inventory = self.get_inventory()
            if inventory['food'] < 10:
                self.survive()
            else:
                self.expedition()
            ##self.recieve_broadcast()
            if not self.incantation :
                self.try_incantation()

    def disconnect(self) -> None:
        '''disconnect the player'''
        if (self.fd != 0):
            self.socket.close()