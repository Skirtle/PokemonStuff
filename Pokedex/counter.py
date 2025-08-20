import csv

def get_pokemon(filename: str = "pokemon.csv"):
    pokemon = []
    with open(filename, "r") as file:
        reader = csv.reader(file)
        for row in reader:
            pokemon.append(row)
    
    return pokemon

def choose_loop(pokemon_list):
    number = 1
    for pokemon in pokemon_list:
        name = pokemon[0]
        count = pokemon[1]
        game = pokemon[2]
        
        if (name == "Pokemon"): continue
        print(f"{number}. {name} ({count}, {game})")
    
    ans = input("\tChoose a Pokemon: ")
    if (ans.isdigit()): return int(ans)
    else:
        # Assuming the input is the Pokemon name
        for index,value in enumerate(pokemon_list):
            if (value[0].lower() == ans.lower()): return index
    
    return None

def counter_loop(pokemon_list, index, filename = "pokemon.csv"):
    print(f"You're now hunting for {pokemon_list[index][0]} and starting at {pokemon_list[index][1]} tries")
    
    while (True):
        tries = int(pokemon_list[index][1])
        a = input(f"You are at {tries} tries. Press enter to add 1. ")
        if (a == ""): tries += 1
        pokemon_list[index][1] = tries
        
        update_csv(filename, index, tries)
        
        if (a != ""): break
        
def update_csv(filename, index, new_tries):
    old = get_pokemon(filename)
    old[index][1] = str(new_tries)
    
    with open(filename, "w", newline='') as file:
        writer = csv.writer(file)
        writer.writerows(old)

if __name__=="__main__":
    counters = get_pokemon()
    ind = choose_loop(counters)
    counter_loop(counters, ind)