#-----------------------------
# CubePlayer.py
# Author: Zach H
# Date: 5/29/2020
#-----------------------------

class Player:
    x = 900
    y = 500
    speed = 7
    direction = 0

    def move_left(self):
        self.x += self.speed
        self.direction = 1

    def move_right(self):
        self.x -= self.speed
        self.direction = 3

    def move_down(self):
        self.y += self.speed
        self.direction = 0

    def move_up(self):
        self.y -= self.speed
        self.direction = 2
