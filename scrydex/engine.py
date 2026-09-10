from dataclasses import dataclass
from pokemon import Pokemon, create_database_from_csv
from parser import create_tree
import lexer

def get_pokemon_from_query(database: list[Pokemon], query: str) -> list[Pokemon]:
    valid_pokemon = database[:]
    tokens = lexer.tokenize(query)
    classified_tokens = lexer.classify_tokens(tokens)
    
    valid_pokemon = create_tree(classified_tokens).evaluate()
    
    return valid_pokemon


if __name__ == "__main__":
    pokemon_db = create_database_from_csv()
    valid = get_pokemon_from_query(pokemon_db, "hp>100 atk<20")
    
    normal = get_pokemon_from_query(pokemon_db, "t:normal")
    ghost = get_pokemon_from_query(pokemon_db, "t:ghost")
    
    both = normal + ghost
    both.sort(key = lambda x: x.name)
    for p in both:
        print(p)