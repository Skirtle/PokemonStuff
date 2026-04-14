from __future__ import annotations
from dataclasses import dataclass, field
from typing import Any

import lexer

@dataclass
class Node:
    type: str
    left: Node | None = None
    right: Node | None = None
    value: Any = None

def create_ast(tokens: list[tuple[str, str, str] | tuple[str, str]]) -> Node:
    paren_count = 0
    for index,token in enumerate(tokens):
        print(f"\t{index} {token}")
        if (token[0] == "paren"):
            paren_count += 1 if token[1] == "(" else -1
        print(f"\t\t{paren_count = }")
        

    return Node("empty")
    
if __name__ == "__main__":
    query = "-(t:fire atk>50) or (spd>100 -(t:ghost t:fire))"
    tokens = lexer.tokenize(query)
    classified_tokens = lexer.classify_tokens(tokens)
    print(query)
    for token in tokens:
        print(f"\t{token}")
    for token in classified_tokens:
        print(f"\t\t{token}")
    
    ast = create_ast(classified_tokens)
    print(ast)