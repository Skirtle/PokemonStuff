from dataclasses import dataclass, field
from csv import reader as csvreader
from enum import Enum
import json
from pathlib import Path

class STAT_INDEX(Enum):
    HP = 0
    ATTACK = 1
    DEFENSE = 2
    SPECIAL_ATTACK = 3
    SPECIAL_DEFENSE = 4
    SPEED = 5

@dataclass
class Pokemon:
    base_name: str
    name: str
    dex_number: int
    region: str
    types: list[str] = field(default_factory = list)
    generation: list[int] = field(default_factory = list)
    games: list[str] = field(default_factory = list)
    stats: list[int] = field(default_factory = list)
    
    def __post_init__(self) -> None:
        self.normalized_name = self.name.replace(" ", "").strip().lower()
        self.initial_game = self.games[0] if len(self.games) > 0 else None
        self.base_total = sum(self.stats)
    
    def __str__(self) -> str: return self.name
    def __repr__(self) -> str: return self.name

    def serialized(self) -> dict:
        if self.name == self.base_name:
            image_dir = f"/images/{self.dex_number}/{self.dex_number}.png"
        else:
            form_ids_path = Path(f"./pokedex/{self.dex_number}/form_ids.json")

            with open(form_ids_path, "r", encoding="utf-8") as f:
                form_ids = json.load(f)

            form_id = form_ids[self.name]
            image_dir = f"/images/{self.dex_number}/{form_id}.png"

        return {
            "base_name": self.base_name,
            "name": self.name,
            "dex_number": self.dex_number,
            "region": self.region,
            "types": self.types,
            "generation": self.generation,
            "games": self.games,
            "stats": self.stats,
            "normalized_name": self.normalized_name,
            "initial_game": self.initial_game,
            "base_total": self.base_total,
            "image": image_dir
        }

    def __hash__(self) -> int:
        return self.normalized_name.__hash__()
    
    
def create_database_from_csv(filename: str = "pokemon.csv") -> list[Pokemon]:
    """Create a list of Pokemon based on the .csv file given

    Args:
        filename (str, optional): the filepath to the csv of pokemon. Defaults to "pokemon.csv".

    Returns:
        list[Pokemon]: a list of Pokemon
    """
    pokemon_database = []
    with open(f"pokemon.csv", "r", encoding = "utf-8") as file:
        reader = csvreader(file)
        for pokemon in reader:
            if (pokemon[0] == "number"): continue
            number = int(pokemon[0])
            base_name = pokemon[1]
            name = pokemon[2]
            type_1 = pokemon[3]
            type_2 = pokemon[4]
            stats = pokemon[6:12]
            gen = int(pokemon[12])
            region = pokemon[13]
            
            types = [type_1.lower()]
            if (type_2 != 'None'): types.append(type_2.lower())
            stats_int = [int(stat) for stat in stats]
            
            pokemon = Pokemon(base_name, name, number, region, types, [gen], [], stats_int)
            pokemon_database.append(pokemon)
    return pokemon_database
