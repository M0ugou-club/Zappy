class Player:
    def __init__(self, team):
        self.team = team
        self.level = 1
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


    def go_to(self, tile, searching_item : list) -> None:
        '''go to the tile given in parameter'''
        x, y = tile.get_coord
        for _ in range(y):
            self.forward()
        if x > 0:
            self.right()
        elif x < 0:
            self.left()
        for _ in range(abs(x)):
            self.forward()
        self.get_object(tile, searching_item)


    def forward(self) -> None:
        '''move forward'''
        pass


    def right(self) -> None:
        '''turn right'''
        pass


    def left(self) -> None:
        '''turn left'''
        pass


    def take(self) -> None:
        '''take the object in the tile'''
        pass


    def get_object(self, tile : list , items : list) -> None:
        '''take the item in the tile'''
        for item in items:
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


    def look(self) -> list:
        '''look around the player'''
        pass


    def incantation(self) -> None:
        '''incantation'''
        pass


    def broadcast(self, message : str) -> None:
        '''broadcast a message'''
        pass


    def connect_nbr(self) -> None:
        '''connect the player'''
        pass


    def fork(self) -> None:
        '''fork the player'''
        pass


    def eject(self) -> None:
        '''eject the player'''
        pass


    def set_object(self, object : str) -> None:
        '''set the object in the tile'''
        pass


    def inventory(self) -> None:
        '''get the inventory of the player'''
        pass


    def survive(self) -> None:
        '''survive'''
        pass

    def expedition(self) -> None:
        '''expeditions'''
        pass
