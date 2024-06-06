import random
import socket

class Player:
    def __init__(self, team, machine, port):
        self.team = team
        self.level = 1
        self.fd = 0
        self.machine = machine
        self.port = port
        self.socket = socket.socket()
        self.inventory = {
            'food': 1,
            'linemate': 0,
            'deraumere': 0,
            'sibur': 0,
            'mendiane': 0,
            'phiras': 0,
            'thystame': 0
        }
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

    def look(self) -> list:
        '''look around the player'''
        self.socket.sendall("Look\n".encode())
        response = self.socket.recv(1024).decode()
        if response == "ko\n":
            self.survival = False
        print(f"Around -> {response}", end="")
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
        correct_tile = self.get_correct_tile(self.looked, searching_item)
        if correct_tile:
            self.go_to(correct_tile[1], self.get_pos(correct_tile[0]), searching_item)
        else :
            self.go_to_direction(random.randint(1, 3))


    def survive(self) -> None:
        '''survive'''
        self.search_object(self.look(), ['food'])


    def expedition(self) -> None:
        '''expeditions'''
        self.search_object(self.look(), ['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame'])


    def run(self) -> None:
        '''run the player'''
        self.socket.connect((self.machine, int(self.port)))
        self.socket.sendall("\n".encode())
        while True:
            self.socket.sendall((self.team + "\n").encode())
            if self.socket.recv(1024).decode() == "ko\n":
                break

        while (True):
            self.forward()
            self.get_inventory()
            self.look()
            if self.inventory['food'] < 10:
                self.survive()
            else:
                self.expedition()
            self.recieve_broadcast()

    def disconnect(self) -> None:
        '''disconnect the player'''
        if (self.fd != 0):
            self.socket.close()