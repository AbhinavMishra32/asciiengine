import random

class Particle():
    def __init__(self, x, y, mass, display: 'display'): #type: ignore
        self.x = x
        self.y = y
        self.dx =  random.uniform(-1, 1)/10
        self.dy = random.uniform(-1, 1)/10
        self.mass = mass
        self.damping = 0.65
        self.display = display
        self.char = 'X'
        self.velchar = {
            ()
        }
    
    def move(self):
        self.x += self.dx
        self.y += self.dy
        self.dy += 0.1

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
        print('x: ', self.x, 'y:', self.y, 'dx:',self.dx,'dy:', self.dy)

    def update_char(self):
        pass

    def update(self):
        self.display.update(int(self.x), int(self.y), self.char)