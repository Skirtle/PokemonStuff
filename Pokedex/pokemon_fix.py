# import matplotlib.pyplot as plt

class Pokemon:
    def __init__(self, form_name = "", number = 0, name = "", type_1 = None, type_2 = None, total = 0, hp = 0, attack = 0, defense = 0, special_attack = 0, special_defense = 0, speed = 0):
        self.number = number
        self.name = name
        self.form_name = form_name
        self.type_1 = type_1
        self.type_2 = type_2
        self.total = total
        self.hp = hp
        self.attack = attack
        self.defense = defense
        self.special_attack = special_attack
        self.special_defense = special_defense
        self.speed = speed
        
        self._set_generation()
        
    def __str__(self):
        types = f"({self.type_1}" + (f", {self.type_2}" if self.type_2 != None else "") + ")"
        return f"#{self.number} {self.form_name} {types}, [{self.hp}, {self.attack}, {self.defense}, {self.special_attack}, {self.special_defense}, {self.speed}] ({self.total}) [Gen {self.generation_number}, {self.region_name}]"
    
    def __repr__(self):
        return f"{self.name}"
    
    def _set_generation(self):
        # Generation 1, Kanto
        if (self.number in range(1, 151 + 1) and self.name == self.form_name): 
            self.generation_number = 1
            self.region_name = "Kanto"
        
        # Generation 2, Johto
        if (self.number in range(152, 251 + 1) and self.name == self.form_name): 
            self.generation_number = 2
            self.region_name = "Johto"
        
        # Generation 3, Hoenn
        if (self.number in range(252, 386 + 1) or self.name in ["Castform", "Deoxys"]): 
            self.generation_number = 3
            self.region_name = "Hoenn"
        
        # Generation 4, Sinnoh
        if (self.number in range(387, 493 + 1) or self.name in ["Burmy", "Wormadam", "Rotom", "Giratina", "Shaymin"]): 
            self.generation_number = 4
            self.region_name = "Sinnoh"
        
        # Generation 5,Unova
        if (self.number in range(494, 649 + 1) or self.name in ["Basculin", "Darmanitan", "Tornadus", "Thunderus", "Landorus", "Kyurem", "Keldeo", "Meloetta"]): 
            self.generation_number = 5
            self.region_name = "Unova"
        
        # Generation 6, Kalos
        if (self.number in range(650, 721 + 1) or
              (f"Mega {self.name}" in self.form_name) or 
              (f"Primal {self.name}" == self.form_name) or
              self.name in ["Aegislash", "Pumpkaboo", "Gourgeist", "Hoopa"] or 
              (self.name == "Zygarde" and "50" in self.form_name)):
                self.generation_number = 6
                self.region_name = "Kalos"
        
        # Generation 7, Alola
        if (self.number in range(722, 809 + 1) or 
            "Alolan " in self.form_name or 
            "Partner " in self.form_name or
            self.form_name in ["Greninja (Ash-Greninja)", "Zygarde (Complete Forme)"] or
            (self.name == "Zygarde" and "10" in self.form_name)): 
                self.generation_number = 7
                self.region_name = "Alola"
        
        # Generation 8, Galar
        if (self.number in range(810, 905 + 1) or
            "Galarian" in self.form_name or
            "Hisuian" in self.form_name or
            self.form_name in ["Dialga (Origin Forme)", "Palkia (Origin Forme)", "Basculin (White-Striped Form)"]):
            self.generation_number = 8
            if ("Hisuian" in self.form_name): 
                self.region_name = "Hisui"
            else: 
                self.region_name = "Galar"
                
        
        # Generation 9, Paldea
        if (self.number in range(906, 1025 + 1) or
            "Breed" in self.form_name or
            "Paldean" in self.form_name or
            "Bloodmoon" in self.form_name): 
            self.generation_number = 9
            self.region_name = "Paldea"
        

input_filename = "all_pokemon.txt"
output_filename = "pokemon.csv"
pokemon = []

with open(input_filename, "r") as file:
    line = file.readline().strip()
    
    while (line != ""):
        new_mon = Pokemon()
        new_mon.form_name = line
        new_mon.number = int(file.readline().strip())
        new_mon.name = file.readline().strip()
        new_mon.type_1 = file.readline().strip()
        
        next_line = file.readline().strip()
        
        if (next_line.isalpha()): # Pokemon has two types
            new_mon.type_2 = next_line
            new_mon.total = file.readline().strip()
        else: 
            new_mon.type_2 = None
            new_mon.total = next_line
        
        new_mon.hp = int(file.readline().strip())
        new_mon.attack = int(file.readline().strip())
        new_mon.defense = int(file.readline().strip())
        new_mon.special_attack = int(file.readline().strip())
        new_mon.special_defense = int(file.readline().strip())
        new_mon.speed = int(file.readline().strip())
        
        new_mon._set_generation()
        
        pokemon.append(new_mon)
        line = file.readline().strip()



with open(output_filename, "w") as file:
    args = [key for key in pokemon[0].__dict__]
    header = ",".join([key for key in pokemon[0].__dict__]) + "\n"
    file.write(header)
    
    print(args)
    for p in pokemon:
        
        line = ",".join([str(p.__dict__[arg]) for arg in args]) + "\n"
        file.write(line)
