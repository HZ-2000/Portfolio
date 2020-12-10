#------------------------------
# Umbrella class
# Author: Zach H
# Date: 06/18/2019
#------------------------------
import pygame

class umbrella:
    def __init__(self, x, x_change):
        display_height = 1000
        display_width = 1800
        self.umbrella_width = 195
        self.umbrella_height = 210
        self.umbrella_img = pygame.image.load("umbrella.png")
        self.x = x
        self.y = (display_height * 0.75)
        self.x_change = x_change

    def blit_to_screen(self,screen,x,y):
        screen.blit(self.umbrella_img,(x, y))
