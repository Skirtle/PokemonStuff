from pokemon import Pokemon
from dataclasses import dataclass, field

@dataclass
class Token:
    TOKEN_WORDS = ["t", "type", "n", "name", "gen", "game", "hp", "atk", "attack", "spatk", "specialattack", "defense", "def", "spdef", "specialdef", "speed", "spd", "bst", "total", "region"] # to be expanded on
    BOOL_WORDS = ["not", "and", "or"]

class InvalidKeywordException(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__(self.message)
        
    def __str__(self): return self.message

def tokenize(query: str) -> list:
    """turns a search query into individual tokens in a list

    Args:
        query (str): search query

    Returns:
        list: a list
    """
    
    tokens = []
    curr_token = ""
    
    for char in query:
        if (char == " "): 
            tokens.append(curr_token)
            tokens.append("and")
            curr_token = ""
        
        else: curr_token += char
    
    else: tokens.append(curr_token)
    
    return tokens

def classify_tokens(tokens: list) -> list:
    """Returns a list of the tokens in a query, classified by their query type

    Args:
        tokens (list): a list of tokens (str)

    Returns:
        list: a list of tuples of token and their classifications
    """
    classified_tokens = []
    for token in tokens:
        split_token = token.split(":")
        
        if (len(split_token) == 1): # Could be a bool token, or a name
            if (token not in Token.BOOL_WORDS): classified_tokens.append(("name", token)) # Name token
            else: classified_tokens.append(("bool", token)) # Bool token
        
        
        elif (len(split_token) == 2): # Attribute token
            # Error checking
            if (split_token[0] not in Token.TOKEN_WORDS): raise InvalidKeywordException(f"{split_token[0]} not a valid keyword")
            
            token_type = split_token[0]
            if (token_type in ["type", "t"]): token_type = "type"
            elif (token_type in ["name", "n"]): token_type = "name"
            elif (token_type in ["gen", "generation"]): token_type = "generation"
            elif (token_type in ["game"]): token_type = "game"
            elif (token_type in ["hp"]): token_type = "hp"
            elif (token_type in ["atk", "attack"]): token_type = "atk"
            elif (token_type in ["spatk", "specialattack"]): token_type = "spatk"
            elif (token_type in ["def", "defense"]): token_type = "def"
            elif (token_type in ["spdef", "specialattack"]): token_type = "spdef"
            elif (token_type in ["spd", "speed"]): token_type = "spd"
            elif (token_type in ["bst", "total"]): token_type = "bst"
            elif (token_type in ["region"]): token_type = "region"
            
            token_tuple = (token_type, split_token[1])
            
            classified_tokens.append(token_tuple)
            
        else: # What
            exit("you fucked up, a a ron") # Error
        
        
    return classified_tokens

def get_valid_pokemon(database: list[Pokemon], token: tuple[str, str]) -> list:
    """Given a list of Pokemon, return a new list of the Pokemon that satisfy the token

    Args:
        database (list[Pokemon]): a list of Pokemon
        token (tuple[str, str]): the token

    Returns:
        list: a list of Pokemon
    """
    new_database = []
    
    for pokemon in database:
        token_type = token[0]
        token_value = token[1]
        if (token_type == "name"): 
            if (token_value in pokemon.normalized_name): new_database.append(pokemon)
        elif (token_type == "type"):
            if (token_value in pokemon.types): new_database.append(pokemon)
        elif (token_type == "generation"):
            token_value = int(token_value)
            if (token_value in pokemon.generation): new_database.append(pokemon)
        elif (token_type == "game"):
            if (token_value in pokemon.game): new_database.append(pokemon)
        elif (token_type == "region"):
            if (token_value in pokemon.region.lower()): new_database.append(pokemon)
        elif (token_type == "hp"):
            if (token_value == pokemon.stats[0]): new_database.append(pokemon)
        elif (token_type == "atk"):
            token_value = int(token_value)
            if (token_value == pokemon.stats[1]): new_database.append(pokemon)
        elif (token_type == "spatk"):
            token_value = int(token_value)
            if (token_value == pokemon.stats[2]): new_database.append(pokemon)
        elif (token_type == "def"):
            token_value = int(token_value)
            if (token_value == pokemon.stats[3]): new_database.append(pokemon)
        elif (token_type == "spdef"):
            token_value = int(token_value)
            if (token_value == pokemon.stats[4]): new_database.append(pokemon)
        elif (token_type == "spd"):
            token_value = int(token_value)
            if (token_value == pokemon.stats[5]): new_database.append(pokemon)
        elif (token_type == "bst"):
            token_value = int(token_value)
            if (token_value == pokemon.base_total): new_database.append(pokemon)
    
    
    return new_database