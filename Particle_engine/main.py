from display import Display
from particle import Particle
import random

RES_X = 40
RES_Y = 40
display = Display(RES_X, RES_Y)

particles = [Particle(random.randint(0, RES_X), random.randint(0, RES_Y), display, random.randint(2, 10)) for _ in range(0,random.randint(5, 200))]
particles1 = [Particle(random.randint(0, RES_X), random.randint(0, RES_Y), display, 0) for _ in range(0, 300)]

def main():
    display.run(60, particles1)

if __name__ == "__main__":
    main()