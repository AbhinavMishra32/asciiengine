# import Math

class Particle():
    def __init__(self, x, y, mass, display: 'Display'):
        self.x = x
        self.y = y
        self.dx = 0
        self.dy = 0
        self.mass = mass
        # self.id = Math.random(0, 1000000)
        self.display = display
        self.char = 'X'
    
    def move(self):
        self.x += self.dx
        self.y += self.dy
        self.dy += 0.1

        if self.x < 0: self.x =0
        if self.y <0: self.y = 0
        if self.x >= self.display.x: self.x = self.display.x -1
        if self.y >= self.display.y: self.y = self.display.y -1

    def update(self):
        self.display.update(int(self.x), int(self.y), self.char)