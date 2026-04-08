import parser
from pokemon import Pokemon
import csv

if __name__ == "__main__":
    pokemon_database = []
    with open(f"pokemon.csv", "r") as file:
        reader = csv.reader(file)
        for pokemon in reader:
            if (pokemon[0] == "number"): continue
            number = int(pokemon[0])
            name = pokemon[2]
            type_1 = pokemon[3]
            type_2 = pokemon[4]
            stats = pokemon[6:12]
            gen = int(pokemon[12])
            region = pokemon[13]
            
            types = [type_1.lower()]
            if (type_2 != 'None'): types.append(type_2.lower())
            stats_int = [int(stat) for stat in stats]
            
            pokemon = Pokemon(name, number, region, types, [gen], [], stats_int)
            pokemon_database.append(pokemon)
    
    
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
    