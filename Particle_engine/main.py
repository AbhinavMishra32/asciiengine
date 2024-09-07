from display import Display
from particle import Particle
import random

RES_X = 20
RES_Y = 20
display = Display(RES_X, RES_Y)

particles = [Particle(random.randint(0, RES_X), random.randint(0, RES_Y), display) for _ in range(0,random.randint(5, 20))]

def main():
    particle = Particle(1, 4, 10, display)
    display.run(60, particle)

if __name__ == "__main__":
    main()