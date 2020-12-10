#-----------------------------
# CubeEnemies.py
# Author: Zach H
# Date: 5/29/2020
#-----------------------------

from random import randrange

class Enemies:
    enemy_speed = 7
    enemy_x = 0
    enemy_y = 0
    enemy_width = 100
    direction = 0
    dodged = 0

    def __init__(self, windowHeight, windowWidth):
        # on creation each cube has a different driection
        # and starting position
        self.direction = randrange(4)
        if self.direction == 0:
            self.enemy_x = -90
            self.enemy_y = randrange(windowHeight - 90)

        if self.direction == 1:
            self.enemy_x = windowWidth + 90
            self.enemy_y = randrange(windowHeight - 90)

        if self.direction == 2:
            self.enemy_x = randrange(windowWidth - 90)
            self.enemy_y = -90

        if self.direction == 3:
            self.enemy_x = randrange(windowWidth - 90)
            self.enemy_y = windowHeight + 12

    def move_enemy(self):
        if self.direction == 0:
            self.enemy_x += self.enemy_speed

        if self.direction == 1:
            self.enemy_x -= self.enemy_speed

        if self.direction == 2:
            self.enemy_y += self.enemy_speed

        if self.direction == 3:
            self.enemy_y -= self.enemy_speed

    def check_position(self):
        if self.enemy_x < -90:
            self.enemy_x = 1890
            self.dodged += 1
            return True

        elif self.enemy_x > 1890:
            self.enemy_x = -90
            self.dodged += 1
            return True

        elif self.enemy_y < -90:
            self.enemy_y = 1090
            self.dodged += 1
            return True

        elif self.enemy_y > 1090:
            self.enemy_y = -90
            self.dodged += 1
            return True

        else:
            return False
        
        
        
        
