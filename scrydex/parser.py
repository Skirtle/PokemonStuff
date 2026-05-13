from __future__ import annotations
from dataclasses import dataclass, field
from typing import Any
from abc import ABC, abstractmethod

import lexer

@dataclass
class Node(ABC):
    type: str

    @abstractmethod
    def evaluate(self): pass

@dataclass
class UnaryNode(Node):
    ...
    
if __name__ == "__main__":
    query = "-(t:fire atk>50) or (spd>100 -(t:ghost t:fire))"
    tokens = lexer.tokenize(query)
    classified_tokens = lexer.classify_tokens(tokens)
    print(query)
    for token in classified_tokens:
        print(f"\t{token}")
        