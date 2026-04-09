from dataclasses import dataclass, field
from csv import reader as csvreader


@dataclass
class Pokemon:
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
        return {
            "name": self.name,
            "dex_number": self.dex_number,
            "region": self.region,
            "types": self.types,
            "xx": self.generation,
            "xx": self.games,
            "stats": self.stats,
            "normalized_name": self.normalized_name,
            "initial_game": self.initial_game,
            "base_total": self.base_total
    }
    
    
def create_database_from_csv(filename: str = "pokemon.csv") -> list[Pokemon]:
    """Create a list of Pokemon based on the .csv file given

    Args:
        filename (str, optional): the filepath to the csv of pokemon. Defaults to "pokemon.csv".

    Returns:
        list[Pokemon]: a list of Pokemon
    """
    pokemon_database = []
    with open(f"pokemon.csv", "r") as file:
        reader = csvreader(file)
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
    return pokemon_database
