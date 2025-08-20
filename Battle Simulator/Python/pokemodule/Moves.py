from .Types import Type

class Move:
    def __init__(self):
        self.move_type = Type.NORMAL
        self.category = "Physical"
        self.name = "Struggle"
        self.current_pp = 1
        self.max_pp = 1
        self.power = 50
        self.accuracy = -1 # -1 means it does not check for accuracy, always hits
        self.tags = ["contact", "king's rock"]
    
    
    def __str__(self):
        return f"{self.name} ({self.category} {self.power} {self.move_type.name}) {self.current_pp}/{self.max_pp}"
    
    def __repr__(self):
        return f"{self.name}"