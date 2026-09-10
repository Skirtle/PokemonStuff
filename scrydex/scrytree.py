from dataclasses import dataclass
from abc import ABC, abstractmethod
from pokemon import Pokemon, STAT_INDEX, create_database_from_csv
from lexer import TOKEN_WORDS, OPERATOR_WORDS
import operator

BINARY_EXPRESSIONS = OPERATOR_WORDS
FILTER_EXPRESSIONS = TOKEN_WORDS
BASE_DB = create_database_from_csv()

@dataclass
class Expression(ABC):
    @abstractmethod
    def evaluate(self): 
        raise NotImplementedError

@dataclass
class Literal(Expression):
    value: int | str
    
    def evaluate(self) -> int | str:
        return self.value
    
@dataclass
class BinaryOperator(Expression):
    left: Expression
    op: str
    right: Expression
    
    def evaluate(self) -> list[Pokemon]:
        left_value = self.left.evaluate()
        right_value = self.right.evaluate()
        
        if (self.op == "and"): return [p for p in left_value if p in right_value]
        elif (self.op == "or"): return list(set(left_value + right_value))
        raise ValueError(f"Unsupported operator {self.op}")
    
@dataclass
class Filter(Expression):
    field: str
    op: str
    value: Expression
    
    def evaluate(self) -> list[Pokemon]:
        all_pokemon: list[Pokemon] = BASE_DB[:]
        
        if (self.field == "type"): 
            if (self.op == "!="):
                return [p for p in all_pokemon if self.value.evaluate() not in p.types]
            elif (self.op == "=" or self.op == ":"):
                return [p for p in all_pokemon if self.value.evaluate() in p.types]
            elif (self.op == "=="):
                return [p for p in all_pokemon if self.value.evaluate() == p.types[0] and len(p.types) == 1]
            
        if (self.field == "name"): 
            if (self.op == "!="):
                return [p for p in all_pokemon if self.value.evaluate().lower() not in p.name.lower()]
            elif (self.op == "=" or self.op == ":"):
                return [p for p in all_pokemon if self.value.evaluate().lower() in p.name.lower()]
            elif (self.op == "=="):
                return [p for p in all_pokemon if self.value.evaluate().lower() == p.name.lower()]
            
        
        # Compare numerical stats
        stat_fields = {
            "hp": STAT_INDEX.HP.value,
            "atk": STAT_INDEX.ATTACK.value,
            "spatk": STAT_INDEX.SPECIAL_ATTACK.value,
            "def": STAT_INDEX.DEFENSE.value,
            "spdef": STAT_INDEX.SPECIAL_DEFENSE.value,
            "spd": STAT_INDEX.SPEED.value
        }
        pokemon_stat_index = stat_fields[self.field]
        
        operators = {
            "!=": operator.ne,
            ":": operator.eq,
            ">": operator.gt,
            ">=": operator.ge,
            "<=": operator.le,
            "<": operator.lt,
        }
        compare = operators[self.op]
        
        value = self.value.evaluate()
        return [p for p in all_pokemon if compare(p.stats[pokemon_stat_index], value)]
    
    
if __name__ == "__main__":
    import parser
    import lexer
    query = "t:fire spd>100"
    tokens = lexer.classify_tokens(lexer.tokenize(query)) # [('type', 'fire', ':'), ('bool', 'and'), ('spd', '100', '>')]
    tree = BinaryOperator(Filter("type", "==", Literal("fire")), "and", Filter("spd", ">=", Literal(100)))
    print(tree.evaluate())