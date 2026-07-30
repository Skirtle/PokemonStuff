from pokemon import Pokemon

def get_valid_pokemon(database: list[Pokemon], token: tuple[str, str, str], negate: bool = False) -> list[Pokemon]:
    new_database: list[Pokemon] = []
    for pokemon in database:
        token_type = token[0]
        token_value = token[1]
        compare_type = token[2]

        if (token_type == "name"):
            token_value = token_value.replace(" ", "")
            if (compare_type == "!=" and token_value not in pokemon.normalized_name): new_database.append(pokemon)
            elif (token_value in pokemon.normalized_name): new_database.append(pokemon)
        
        elif (token_type == "type"):
            if (compare_type == "!=" and token_value not in pokemon.types): new_database.append(pokemon)
            elif (compare_type == "==" and token_value in pokemon.types): new_database.append(pokemon)
        
        elif (token_type == "generation"):
            token_value = int(token_value)
            if (token_value in pokemon.generation): new_database.append(pokemon)
        
        elif (token_type == "game"):
            if (compare_type == "!=" and token_value not in pokemon.games): new_database.append(pokemon)
            elif (token_value in pokemon.games): new_database.append(pokemon)
        
        elif (token_type == "region"):
            if (compare_type == "!=" and token_value not in pokemon.region.lower()): new_database.append(pokemon)
            elif (token_value in pokemon.region.lower()): new_database.append(pokemon)
        
        elif (token_type == "hp"):
            token_value = int(token_value)
            eval_exp = f"{pokemon.stats[0]} {compare_type} {token_value}"
            if (eval(eval_exp)): new_database.append(pokemon)
        
        elif (token_type == "atk"):
            token_value = int(token_value)
            eval_exp = f"{pokemon.stats[1]} {compare_type} {token_value}"
            if (eval(eval_exp)): new_database.append(pokemon)
        
        elif (token_type == "def"):
            token_value = int(token_value)
            eval_exp = f"{pokemon.stats[2]} {compare_type} {token_value}"
            if (eval(eval_exp)): new_database.append(pokemon)
        
        elif (token_type == "spatk"):
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