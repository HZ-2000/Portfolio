#-----------------------------
# cude_dodge.py
# Author: Zach H
# Date: May 29, 2020
#
# Cube dodge game, dodge the
# cubes for as long as you can.
# The higher the time the better!
#-----------------------------
from pygame.locals import *
from time import sleep
import math
import pygame
# local files
from CubeEnemies import Enemies
from CubePlayer import Player

class App:
    windowWidth = 1800
    windowHeight = 1000
    player = 0
    enemies = []

    def __init__(self):
        self.running = True
        self.player = Player()
        self.display = None # display object
        self.enemies.append(Enemies(self.windowHeight,self.windowWidth))
        self.time = pygame.time.Clock()
        self.paused = False

    def on_init(self):
        pygame.init()
        self.display = pygame.display.set_mode((self.windowWidth,self.windowHeight), pygame.HWSURFACE)
        pygame.display.set_caption("Ball Dodge")
        self.running = True

    def on_event(self):
        if event.type == QUIT:
            self.running = False

    def on_render(self, start_time):
        self.display.fill((0,0,0))
        # player render
        pygame.draw.rect(self.display, (25,25,255), [self.player.x,self.player.y, 90, 90])
        # enemies render
        for i in range(len(self.enemies)):
            if self.enemies[i].check_position():
                self.enemies.append(Enemies(self.windowHeight,self.windowWidth))
            self.enemies[i].move_enemy()
            pygame.draw.rect(self.display, (255,255,255), [self.enemies[i].enemy_x,self.enemies[i].enemy_y, 90, 90])
        # compatibility for pause function
        if not self.paused:
            counting_time = pygame.time.get_ticks() - start_time
            self.display_time(counting_time)

        pygame.display.flip()
        sleep(0.03)

    def display_time(self, counting_time):
        font = pygame.font.Font("freesansbold.ttf", 105)
        # zfill fills the string with 0s until reaching the
        # specified length
        counting_minutes = str(counting_time/60000).zfill(2)
        counting_seconds = str((counting_time%60000)/1000).zfill(2)

        counting_string = "%s:%s" % (counting_minutes, counting_seconds)

        counting_text = font.render(str(counting_string), True, (255,0,0))
        counting_rect = counting_text.get_rect()
        counting_rect.center = (150,50)

        self.display.blit(counting_text, counting_rect)
        pygame.display.update()

    def death_message(self):
        self.message_display("Game Over")
        sleep(2)

    def text_objects(self,text,font):
        textSurface = font.render(text, True, (255,0,0))
        return textSurface, textSurface.get_rect()

    def message_display(self,text):
        largeText = pygame.font.Font("freesansbold.ttf",115)
        TextSurf, TextRect = self.text_objects(text, largeText)
        TextRect.center = ((self.windowWidth/2),(self.windowHeight/2))
        self.display.blit(TextSurf,TextRect)

        pygame.display.update()

    def death(self):
        # for loop checks every enemy on screen
        for i in range(len(self.enemies)):
            y_bound = self.enemies[i].enemy_y + 90
            x_bound = self.enemies[i].enemy_x + 90
            player_x_bound = self.player.x + 90
            player_y_bound = self.player.y + 90

            # each if compares a corner of the player square
            # since the enemies are the same size they cant slip between corners
            if self.player.x in range(self.enemies[i].enemy_x, x_bound) and self.player.y in range(self.enemies[i].enemy_y, y_bound):
                return True

            if player_x_bound in range(self.enemies[i].enemy_x, x_bound) and self.player.y in range(self.enemies[i].enemy_y, y_bound):
                return True

            if self.player.x in range(self.enemies[i].enemy_x, x_bound) and player_y_bound in range(self.enemies[i].enemy_y, y_bound):
                return True

            if player_x_bound in range(self.enemies[i].enemy_x, x_bound) and player_y_bound in range(self.enemies[i].enemy_y, y_bound):
                return True

    def on_cleanup(self):
        pygame.quit()

    def on_execute(self):
        if self.on_init() == False:
            self.running = False

        # start main game loop
        start_time = pygame.time.get_ticks()
        while( self.running ):
            pygame.event.pump()
            keys = pygame.key.get_pressed()

            if (keys[K_a]):
                self.player.move_right()

            if (keys[K_d]):
                self.player.move_left()

            if (keys[K_w]):
                self.player.move_up()

            if (keys[K_s]):
                self.player.move_down()

            if (keys[K_ESCAPE]):
                self.running = False

            if (keys[K_SPACE]):
                self.paused = not self.paused

            if self.death():
                self.running = False

            self.time.tick(60)
            self.on_render(start_time)
        self.death_message()
        self.on_cleanup()

if __name__ == "__main__" :
    theApp = App()
    theApp.on_execute()
