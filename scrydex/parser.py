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

class EmptyQueryException(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__(self.message)
    def __str__(self): return self.message

def strip(s: str) -> str:
    """strips a string, as well as leading and ending quotes

    Args:
        s (str): the string to strip

    Returns:
        str: the stripped string
    """
    if not s:
        return ""
    s = s.strip()  # remove whitespace
    if (s[0] in ("'", '"')):
        s = s[1:]
    if (s and s[-1] in ("'", '"')):  # check s again
        s = s[:-1]
    return s.strip()

def tokenize(query: str) -> list:
    """turns a search query into individual tokens in a list

    Args:
        query (str): search query

    Returns:
        list: a list
    """
    
    tokens = []
    curr_token = ""
    in_quotes = False
    
    index = 0
    while (index < len(query)):
        char = query[index]

        if (char in "\"'"): in_quotes = not in_quotes

        if char == " " and not in_quotes:
            tokens.append(curr_token)
            curr_token = ""
        else:
            curr_token += char
        
        index += 1

    tokens.append(curr_token)
    return tokens

def post_process_tokens(tokens: list[tuple]) -> list[tuple]:
    """Adds boolean tokens in between tokens where they belong

    Args:
        tokens (list[tuple]): a list of tokens

    Returns:
        list[tuple]: a list of tokens
    """
    if (len(tokens) == 0): raise EmptyQueryException(f"Query cannot be empty")

    index = 1
    new_tokens = [tokens[0]]
    while (index < len(tokens)):

        if (tokens[index - 1][0] != "bool" and tokens[index][0] != "bool"):
            new_tokens.append(("bool", "and"))
        new_tokens.append(tokens[index])
        index += 1


    return new_tokens

def classify_tokens(tokens: list) -> list:
    """Returns a list of the tokens in a query, classified by their query type

    Args:
        tokens (list): a list of tokens (str)

    Returns:
        list: a list of tuples of token and their classifications
    """
    classified_tokens = []
    for token in tokens:
        # Get the type of token comparison
        if ("<=" in token): comp_type = "<="
        elif ("<" in token): comp_type = "<"
        elif (">=" in token): comp_type = ">="
        elif (">" in token): comp_type = ">"
        elif ("=" in token): comp_type = "="
        else: comp_type = ":"
        split_token = token.split(comp_type, 1)
        
        # Either a bool word or name
        if (len(split_token) == 1): # Could be a bool token, or a name
            if (token not in Token.BOOL_WORDS): classified_tokens.append(("name", token, "==")) # Name token
            else: classified_tokens.append(("bool", token)) # Bool token
        
        # Some type of attribute to query
        elif (len(split_token) == 2): # Attribute token
            # Error checking
            if (split_token[0] not in Token.TOKEN_WORDS): raise InvalidKeywordException(f"{split_token[0]} not a valid keyword")
            
            token_type = split_token[0]
            token_value = strip(split_token[1])

            if (token_type in ["type", "t"]): token_type = "type"
            elif (token_type in ["name", "n"]): token_type = "name"
            elif (token_type in ["gen", "generation"]): token_type = "generation"
            elif (token_type in ["game"]): token_type = "game"
            elif (token_type in ["hp"]): token_type = "hp"
            elif (token_type in ["atk", "attack"]): token_type = "atk"
            elif (token_type in ["spatk", "specialattack"]): token_type = "spatk"
            elif (token_type in ["def", "defense"]): token_type = "def"
            elif (token_type in ["spdef", "specialdefense"]): token_type = "spdef"
            elif (token_type in ["spd", "speed"]): token_type = "spd"
            elif (token_type in ["bst", "total"]): token_type = "bst"
            elif (token_type in ["region"]): token_type = "region"
            
            if (comp_type == ":" or comp_type == "="): comp_type = "=="
            token_tuple = (token_type, token_value, comp_type)
            
            classified_tokens.append(token_tuple)
            
        else: raise Exception(f"split too many times, {split_token}") # Error

    return post_process_tokens(classified_tokens)

def get_valid_pokemon(database: list[Pokemon], token: tuple[str, str, str]) -> list:
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
        compare_type = token[2]

        if (token_type == "name"):
            token_value = token_value.replace(" ", "")
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
            token_value = int(token_value)
            eval_exp = f"{pokemon.stats[0]} {compare_type} {token_value}"
            if (eval(eval_exp)): new_database.append(pokemon)
        
        elif (token_type == "atk"):
            token_value = int(token_value)
            eval_exp = f"{pokemon.stats[1]} {compare_type} {token_value}"
            if (eval(eval_exp)): new_database.append(pokemon)
        
        elif (token_type == "spatk"):
            token_value = int(token_value)
            eval_exp = f"{pokemon.stats[2]} {compare_type} {token_value}"
            if (eval(eval_exp)): new_database.append(pokemon)

        elif (token_type == "def"):
            token_value = int(token_value)
            eval_exp = f"{pokemon.stats[3]} {compare_type} {token_value}"
            if (eval(eval_exp)): new_database.append(pokemon)

        elif (token_type == "spdef"):
            token_value = int(token_value)
            eval_exp = f"{pokemon.stats[4]} {compare_type} {token_value}"
            if (eval(eval_exp)): new_database.append(pokemon)

        elif (token_type == "spd"):
            token_value = int(token_value)
            eval_exp = f"{pokemon.stats[5]} {compare_type} {token_value}"
            if (eval(eval_exp)): new_database.append(pokemon)

        elif (token_type == "bst"):
            token_value = int(token_value)
            if (token_value == pokemon.base_total): new_database.append(pokemon)
    
    
    return new_database


if __name__ == "__main__":
    queries = ["name=\"type: null\"", "name:\"type: null\"", "name=\"ghastly\"", "name:\"ghastly\"", "name:ghastly", "name=ghastly"]
    for query in queries:
        try:
            raw_tokens = tokenize(query)
            process_tokens = post_process_tokens(raw_tokens)
            classified_tokens = classify_tokens(process_tokens)
            print(f"{query = }\n\t{raw_tokens}\n\t{process_tokens}\n\t{classified_tokens}")
        except Exception as e:
            print(f"Error on {query = }:\n\t{type(e).__name__}, {e}")