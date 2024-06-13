import random
import socket
import subprocess
import select

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
        self.inventory = {}
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

    ##SELECT FUNCTIONS


    def send_message(self, message : str) -> None:
        '''send the message'''
        print("Sending messages")
        self.socket.sendall(message.encode())


    def handle_server_response(self) -> None:
        '''Handle incoming server messages'''
        print("receive messages")
        response = self.socket.recv(1024).decode()
        print("Received:", response)
        if response:
            if response.startswith("[food"):
                self.inventory = self.interpret_inventory(response)
            elif response.startswith("[player"):
                self.looked = self.interpret_look(response)
            if response.startswith("message "):
                print("Received broadcast")
                self.receive_broadcast(response)
            else:
                pass


    async def select_gestion(self) -> None:
        '''select the function to call'''
        while self.messages_queue:
            message = self.messages_queue.pop(0)
            print("Message:", message)
            _, ready_to_write, _ = select.select([], [self.socket], [], 1)
            if ready_to_write:
                self.send_message(message)
            self.handle_server_response()


    ##IPC functions

    def forward(self) -> None:
        '''move forward'''
        self.messages_queue.append("Forward\n")


    def right(self) -> None:
        '''turn right'''
        self.messages_queue.append("Right\n")


    def left(self) -> None:
        '''turn left'''
        self.messages_queue.append("Left\n")


    def take(self, object : str) -> None:
        '''take object'''
        self.messages_queue.append(f"Take {object}\n")


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
        self.messages_queue.append("Look\n")


    def incantation(self) -> None:
        '''incantation'''
        self.messages_queue.append("Incantation\n")
        #if ready_to_read:
        #    response = self.socket.recv(1024).decode()
        #    print("Incantation:" + response)
        #    if response != "ko\n":
        #        self.level += 1
        #        self.is_incanting = True


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


    def get_inventory(self) -> None:
        '''get the inventory'''
        self.messages_queue.append("Inventory\n")


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


    def get_correct_tile(self, searching_item : list) -> tuple[int, list]:
        '''get the correct tile'''
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
        correct_tile = self.get_correct_tile(searching_item)
        if correct_tile:
            self.go_to(correct_tile[1], self.get_pos(correct_tile[0]), searching_item)
        else :
            print("Item not found")
            self.go_to_direction(random.randint(1, 3))


    def survive(self) -> None:
        '''survive'''
        while self.inventory['food'] < 15:
            self.get_inventory()
            self.search_object(['food'])


    def expedition(self) -> None:
        '''expeditions'''
        print("Expedition")
        self.search_object(['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame'])


    def count_player(self, ) -> int:
        '''count the player in the tile'''
        count = 0
        for i in range(len(self.looked)):
            if self.looked[i] == 'player':
                count += 1
        return count


    def check_requirements(self, requirements: dict) -> bool:
        '''check the requirements'''
        for key in requirements:
            self.get_inventory()
            if key != 'player' and self.inventory[key] < requirements[key]:
                return 1
        for player in requirements:
            self.get_inventory()
            if player == 'player':
                if self.count_player(self.look[0]) < requirements[player]:
                    return 2
        return 0


    def what_i_need(self, requirements: dict) -> list:
        '''return list of which item i need to search for'''
        needed = []
        for key in requirements:
            print(key)
            if key == 'player':
                continue
            self.get_inventory()
            if self.inventory[key] < requirements[key]:
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
        self.get_inventory()
        if self.inventory['food'] < 5:
            return
        requirements = self.LEVEL_REQUIREMENTS[self.level]
        requirements_checked = self.check_requirements(requirements)
        while requirements_checked != 0:
            if requirements_checked == 1:
                print("searching for items")
                self.search_object(self.what_i_need(requirements))
            else:
                print("calling teammates")
                self.call_teammates()
                self.get_inventory()
                if self.inventory['food'] < 5:
                    return
            requirements_checked = self.check_requirements(requirements)
        self.put_requirements(requirements)
        self.incantation()


    def run(self) -> None:
        '''run the player'''
        try:
            self.socket.connect((self.machine, int(self.port)))
        except socket.error as e:
            print(f"Socket error: {e}")
            return
        self.socket.sendall("\n".encode())
        while True:
            self.socket.sendall((self.team + "\n").encode())
            if self.socket.recv(1024).decode() == "ko\n":
                break

        while True:
            # self.socket.sendall("Broadcast Salut !\n".encode())
            print("MY LEVEL IS : ", self.level)
            self.get_inventory()
            if self.inventory['food'] < 5:
                self.survive()
            if not self.is_incanting:
                self.try_incantation()
            self.select_gestion()


    def disconnect(self) -> None:
        '''disconnect the player'''
        self.socket.close()
        pass