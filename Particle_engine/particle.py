import random

class Particle():
    def __init__(self, x, y, mass =0, display: 'display'): #type: ignore
        self.x = x
        self.y = y
        self.dx =  random.uniform(-1, 1)/10
        self.dy = random.uniform(-1, 1)/10
        self.mass = mass
        self.damping = 0.65
        self.display = display
        self.char = 'X'
        self.gravity = 0.1
        self.friction = 0.99

    def move(self):
        self.x += self.dx
        self.y += self.dy
        self.dy += self.gravity

        self.dx *= self.friction
        self.dy *= self.friction

        if self.x <0:
            self.x = 0
            self.dx = -self.dx * self.damping

        if self.y <0:
            self.y =0
            self.dy = -self.dy * self.damping

        if self.x >= self.display.x:
            self.x = self.display.x
            self.dx = -self.dx * self.damping
        
        if self.y >= self.display.y:
            self.y = self.display.y
            self.dy = -self.dy * self.damping
    
        #debug
    def update(self):
        self.display.update(int(self.x), int(self.y), self.char)

    def check_collision(self):
        global particles
        for other in particles:
