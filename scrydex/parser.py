from __future__ import annotations
from dataclasses import dataclass, field
from typing import Any
from abc import ABC

import lexer

@dataclass
class Node(ABC): pass

@dataclass
class BoolNode(Node):
    left: Node | None
    right: Node | None

@dataclass
class AttributeNode(Node):
    value: Any = None

@dataclass
class UnaryNode(Node):
    value: Any = None

def token_to_node(token: tuple[str, str, str] | tuple[str, str]) -> Node:
    return Node()

def create_ast(head: Node) -> Node:
    # Base case
    if (isinstance(head, AttributeNode)):
        ... 

    return Node()
    
if __name__ == "__main__":
    query = "-(t:fire atk>50) or (spd>100 -(t:ghost t:fire))"
    tokens = lexer.tokenize(query)
    classified_tokens = lexer.classify_tokens(tokens)
    print(query)
    for token in classified_tokens:
        print(f"\t{token}")
    
    ast = create_ast(classified_tokens)
    print(ast)