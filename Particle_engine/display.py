import time
import os
from particle import Particle
from typing import List

class Display:
    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y
        self._default_values = '.'
        self.canvas = [[self._default_values for _ in range(self.x)] for _ in range(self.y)]

    def update(self, x: int, y: int, value: str):
        if 0<=x<self.x and 0<=y<self.y:
            self.canvas[y][x] = value

    def display(self):
        for row in self.canvas:
            print(' '.join(row))

    def clear(self):
        self.canvas = [[self._default_values for _ in range(self.x)] for _ in range(self.y)]
        os.system('cls' if os.name == 'nt' else 'clear')

    def run(self, fps: int, particles: List[Particle]):
        while True:
            self.clear()
            for particle in particles:
                particle.move()
                particle.check_collisions()
                particle.update()
            self.display()
            time.sleep(1/fps)

            # self.clear()
            # particle.move()
            # particle.update()
            # self.display()
            # time.sleep(1/fps)
