#------------------------------
# Rain.py
# Author: Zach H
# Date: 06/18/2019
#
# a simple program that uses pygame
# to create rain and some umbrellas
# that can move through it
#------------------------------
import numpy as np
import random
import time
import pygame
from umbrella import umbrella

pygame.init()

blue = (0,0,255)
black = (0,0,0)
display_height = 1000
display_width = 1800

screen = pygame.display.set_mode((display_width, display_height))
clock = pygame.time.Clock()

#create umbrella object, imported from a seperate class file
umbrella1 = umbrella(0, 4)

def droplets(droplet_x, droplet_y, droplet_w, droplet_h, color):
    pygame.draw.rect(screen, color, [droplet_x, droplet_y, droplet_w, droplet_h])

def rain_loop():
    GameExit = False
    num_of_droplets = 128
    # droplets all have slighty varying speeds by .2 pixels/s
    droplet_speed = np.arange(15,(num_of_droplets), .2)
    droplet_start_y = np.empty(num_of_droplets)
    # droplets all start at the same y position at -600 pixels
    droplet_start_y.fill(-600)
    droplet_start_x = np.empty(num_of_droplets)
    # droplets all have random x values at start
    droplet_start_x.fill(random.randint(0, display_width))
    droplet_width = 5
    droplet_height = 5

    while not GameExit:
        screen.fill(black)

        umbrella1.x += umbrella1.x_change

        # if the umbrellas go off screen, reset their positions
        if umbrella1.x > display_width:
            umbrella1.x = -300

        # draw the individual droplets for the number of droplets that you want
        for i in range(num_of_droplets):
            droplets(droplet_start_x[i], droplet_start_y[i], droplet_width, droplet_height, blue)
            droplet_start_y[i] += droplet_speed[i]

            # if the droplets hit the umbrella they reset, hence not going through the umbrella
            # or the droplets hit the bottom of the screen, then they reset
            if droplet_start_x[i] > umbrella1.x and droplet_start_x[i] < (umbrella1.x + umbrella1.umbrella_width) and droplet_start_y[i] > umbrella1.y:
                droplet_start_y[i] = -600
                droplet_start_x[i] = random.randrange(0,display_width)

            elif droplet_start_y[i] > display_height:
                droplet_start_y[i] = 0 - droplet_height
                droplet_start_x[i] = random.randrange(0,display_width)

        # blit the umbrella to the screen (function from class)
        umbrella1.blit_to_screen(screen,umbrella1.x,umbrella1.y)

        # handles Escape key as exit
        events = pygame.event.get()
        for event in events:
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    GameExit = True

        pygame.display.update()
        # run at 60fpss
        clock.tick(60)

rain_loop()

pygame.quit()
quit()
