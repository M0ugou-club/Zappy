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
        self.survival = True
        self.is_incanting = False


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
            print("ko")
            self.survival = False
        pass


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
        pass


    def look(self) -> list:
        '''look around the player'''
        self.socket.sendall("Look\n".encode())
        response = self.socket.recv(1024).decode()
        if response != "ko\n":
            response = self.interpret_look(response)
            return response
        else:
            self.survival = False
        pass


    def incantation(self) -> None:
        '''incantation'''
        self.socket.sendall("Incantation\n".encode())
        response = self.socket.recv(1024).decode()
        if response != "ko\n":
            self.level += 1


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
            inventory[response[i][0]] = int(response[i][1])
        return inventory


    def get_inventory(self) -> dict:
        '''get the inventory of the player'''
        self.socket.sendall("Inventory\n".encode())
        response = self.socket.recv(1024).decode()
        if response == "ko\n":
            self.survival = False
        response = self.interpret_inventory(response)
        print(response)
        return response


    ##AI functions

    def go_to_direction(self, direction : int) -> None:
        '''go to the direction given in parameter'''
        self.MOUVEMENTS_DIRECTION[direction](self)


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


    def receive_broadcast(self) -> str:
        '''recieve a broadcast'''
        pass


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


    def search_object(self, looked: list, searching_item : list) -> None:
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
            test = self.get_inventory()
            print(test['food'])
            self.search_object(self.look(), ['food'])


    def expedition(self) -> None:
        '''expeditions'''
        print("Expedition")
        self.search_object(self.look(), ['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame'])


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
            if key == 'player':
                if self.count_player(look[0]) < requirements[key]:
                    return 2
            elif inventory[key] < requirements[key]:
                return 1
        return 0


    def what_i_need(self, requirements: dict) -> list:
        '''return list of which item i need to search for'''
        inventory = self.get_inventory()
        needed = []
        for key in requirements:
            if inventory[key] < requirements[key]:
                needed.append(key)
        return needed


    def receive_broadcast(self) -> None:
        '''receive the broadcast'''
        response = self.fd.recv(1024).decode()
        if response == "ko\n" or response.startswith("message") == False:
            return
        direction = response.split(", ")[0].split(" ")[1]
        message = response.split(", ")[1]
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


    def try_incantation(self) -> None:
        '''try the incantation'''
        inventory = self.get_inventory()
        if inventory['food'] < 5:
            return
        requirements = self.LEVEL_REQUIREMENTS[self.level]
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
            print("MY LEVEL IS : ", self.level)
            self.fork()
            inventory = self.get_inventory()
            if inventory['food'] < 5:
                self.survive()
            self.recieve_broadcast()
            if not self.is_incanting :
                self.try_incantation()
            self.expedition()

    def disconnect(self) -> None:
        '''disconnect the player'''
        if (self.fd != 0):
            self.socket.close()