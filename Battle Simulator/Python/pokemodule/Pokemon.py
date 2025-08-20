from __future__ import annotations
from random import randint
from . import Types, Moves, Abilities, Items

def round_half_down(num: float) -> int:
    return int(num) if ((num - int(num)) <= 0.5) else int(num) + 1


class Pokemon:
    def __init__(self):
    # Generic data
        self.nickname = ""
        self.form_name = ""
        self.name = ""
        self.dex_number = 0
        self.is_shiny = False
        
        # Battle-related data
        self.level = 0
        self.gender = ""
        self.happiness = 0
        self.tera_type = Types.Type.NONE
        self.ability = None
        self.held_item = None
        self.type_1 = None
        self.type_2 = None
        
        ## Moves
        self.move_1 = Moves.Move()
        self.move_2 = Moves.Move()
        self.move_3 = Moves.Move()
        self.move_4 = Moves.Move()
        
        ## Baase stats
        self.base_stat_hp = 0
        self.base_stat_attack = 0
        self.base_stat_defense = 0
        self.base_stat_special_attack = 0
        self.base_stat_special_defense = 0
        self.base_stat_speed = 0
        
        ## IV's
        self.iv_stat_hp = 0
        self.iv_stat_attack = 0
        self.iv_stat_defense = 0
        self.iv_stat_special_attack = 0
        self.iv_stat_special_defense = 0
        self.iv_stat_speed = 0
        
        ## EV's
        self.ev_stat_hp = 0
        self.ev_stat_attack = 0
        self.ev_stat_defense = 0
        self.ev_stat_special_attack = 0
        self.ev_stat_special_defense = 0
        self.ev_stat_speed = 0
    
    def attack_pokemon(self, move: Moves.Move, other: Pokemon):
        if (move.category == "Physical"): 
            attack = self.base_stat_attack + ( self.ev_stat_attack // 4) + self.iv_stat_attack
            defense = self.base_stat_defense + ( self.ev_stat_defense // 4) + self.iv_stat_defense
        elif (move.category == "Special"): 
            attack = self.base_stat_special_attack + ( self.ev_stat_special_attack // 4) + self.iv_stat_special_attack
            defense = self.base_stat_special_defense + ( self.ev_stat_special_defense // 4) + self.iv_stat_special_defense
        else: exit("What")
        
        mult_target = 1 # 0.75 if battle royale and attack has more than 1 target, otherwise 1
        mult_pb = 1 # 0.25 if move is second strike of Parent Bond ability, otherwise 1
        mult_weather = 1 # 1.5 if Water during rain or Fire (Hydro Steam move) during harsh sunlight. 0.5 if Water (except Hydro Steam) in harsh sunlight or fire during rain. 1 otherwise, or if any Pokemon has Cloud Nine or Air Lock ability
        mult_glaive_rush = 1 # 2 if target used Glaive Rush previous turn, otherwise 1
        mult_crit = 1 # 1.5 if a critical hit, 1 otherwise. Always 1 if target ability is Battle Armor or Shell armor
        mult_random = randint(85, 100) / 100 # Random integer between 85 and 100 (inclusive), divided by 100. 
        if (move.move_type in [self.type_1, self.type_2]): mult_stab = 2 if self.ability.name == "Adaptability" else 1.5 # I'll deal with tera later
        else: mult_stab = 1
        
        mult_type_effect = Types.get_effectiveness(self, move.move_type, other)
        mult_burn = 1 # 0.5 if user is burned, ability is NOT Guts, and the move is Physical, otherwise 1
        mult_other = 1 # 1 in most cases. Look at wiki, I'll implement this later
        mult_zmove = 1
        mult_terashield = 1

        
        dmg = ((2 * self.level) / 5) + 2
        dmg *= move.power * (attack / defense)
        dmg = (dmg / 50) + 2
        dmg *= mult_target * mult_pb * mult_weather * mult_glaive_rush * mult_crit * mult_random * mult_stab * mult_type_effect * mult_burn * mult_other * mult_zmove * mult_terashield
        
        return dmg