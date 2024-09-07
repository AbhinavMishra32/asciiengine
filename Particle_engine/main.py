from display import Display
from particle import Particle

def main():
    display = Display(20, 20)
    particle = Particle(1, 4, 10, display)
    display.run(60, particle)

if __name__ == "__main__":
    main()