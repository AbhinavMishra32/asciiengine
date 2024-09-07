from display import Display
from particle import Particle

def main():
    display = Display(10, 10)
    particle = Particle(1, 4, 10, display)
    display.run(10, particle)

if __name__ == "__main__":
    main()