from . import Moves, Pokemon

from enum import Enum

class Type(Enum):
    NORMAL = 1
    FIRE = 2
    WATER = 3
    ELECTRIC = 4
    GRASS = 5
    ICE = 6
    FIGHTING = 7
    POISON = 8
    GROUND = 9
    FLYING = 10
    PSYCHIC = 11
    BUG = 12
    ROCK = 13
    GHOST = 14
    DRAGON = 15
    DARK = 16
    STEEL = 71
    FAIRY = 18
    NONE = -1
    
    
def get_effectiveness(attacker: Pokemon, move: Moves.Move, defender: Pokemon) -> float:
    multiplier = 1
    
    
    return multiplier