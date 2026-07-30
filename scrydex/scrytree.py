from dataclasses import dataclass
from typing import Any
from abc import ABC, abstractmethod

@dataclass
class Expression(ABC):
    @abstractmethod
    def evaluate(self): 
        raise NotImplementedError

@dataclass
class Literal(Expression):
    value: int | str
    
    def evaluate(self) -> Any:
        return self.value
    
@dataclass
class BinaryOperator(Expression):
    left: Expression
    op: str
    right: Expression
    
    def evaluate(self) -> Any:
        left_value = self.left.evaluate()
        right_value = self.right.evaluate()
        
        if (self.op == "+"): return left_value + right_value
        elif (self.op == "*"): return left_value * right_value
        raise ValueError(f"Unsupported operator {self.op}")
    
@dataclass
class UnaryOperator(Expression):
    op: str
    value: Expression
    
    def evaluate(self) -> Any:
        if (self.op == "not"): return NotImplemented # fix later
    
    
if __name__ == "__main__":
    tree = BinaryOperator(BinaryOperator(Literal(5), "+", Literal(7)), "*", BinaryOperator(Literal(2), "*", Literal(7)))
    print(tree.evaluate())