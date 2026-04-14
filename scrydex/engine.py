from dataclasses import dataclass
from pokemon import Pokemon, create_database_from_csv
import lexer

def get_pokemon_from_query(database: list[Pokemon], query: str) -> list[Pokemon]:
    valid_pokemon = database[:]
    tokens = lexer.tokenize(query)
    classified_tokens = lexer.classify_tokens(tokens)
    
    for token in classified_tokens:
        if (token[0] == "bool" or token[0] == "paren"): continue
        valid_pokemon = lexer.get_valid_pokemon(valid_pokemon, token)
        if (len(valid_pokemon) == 0): break
    
    
    return valid_pokemon


if __name__ == "__main__":
    pokemon_db = create_database_from_csv()
    valid = get_pokemon_from_query(pokemon_db, "hp>100 atk<20")