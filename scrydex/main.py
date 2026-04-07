import parser
from pokemon import Pokemon

if __name__ == "__main__":
    houndour = Pokemon("Houndour", ["dark", "fire"])
    houndoom = Pokemon("Houndoom", ["dark", "fire"])
    mega_houndoom = Pokemon("Mega Houndoom", ["dark", "fire"])
    chiyu = Pokemon("Chi-Yu", ["dark", "fire"])
    incineroar = Pokemon("Incinerorar", ["fire", "dark"])
    charmander = Pokemon("Charmander", ["fire"])
    absol = Pokemon("absol", ["dark"])
    houndstone = Pokemon("Houndstone", ["ghost"])
    pokemon_database = [houndour, houndoom, mega_houndoom, chiyu, incineroar, charmander, absol, houndstone]
    
    
    while (query:=input("Query: ").strip()):
        query_tokens = parser.tokenize(query)
        classfied_tokens = parser.classify_tokens(query_tokens)
        
        print(query)    
        valid_pokemon = pokemon_database[:]
        
        for token in classfied_tokens:
            if (token[0] == "bool"): continue
            valid_pokemon = parser.get_valid_pokemon(valid_pokemon, token)
            if (len(valid_pokemon) == 0): break
            
        print(valid_pokemon)
    