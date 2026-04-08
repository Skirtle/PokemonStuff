from dataclasses import dataclass, field


@dataclass
class Pokemon:
    name: str
    dex_number: int
    region: str
    types: list[str] = field(default_factory = list)
    generation: list[int] = field(default_factory = list)
    game: list[str] = field(default_factory = list)
    stats: list[int] = field(default_factory = list)
    
    def __post_init__(self) -> None:
        self.normalized_name = self.name.replace(" ", "").strip().lower()
        self.initial_game = self.game[0] if len(self.game) > 0 else None
        self.base_total = sum(self.stats)
    
    def __str__(self) -> str: return self.name
    def __repr__(self) -> str: return self.name