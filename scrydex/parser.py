from __future__ import annotations
from dataclasses import dataclass, field
from typing import Any

@dataclass
class Node:
    type: str
    left: Node | None = None
    right: Node | None = None
    value: Any = None

    
if __name__ == "__main__":
    # 't:fire -t:ghost'
    # ("type", "fire", "==")
    # ("bool", "and")
    # ("bool", "not")
    # ("type", "ghost", "==")

    ast = Node(
        type = "and",
        left = Node(
            type = "compare",
            value = ("type", "==", "fire")
        ),
        right = Node(
            type = "not",
            left = Node(
                type = "compare",
                value = ("type", "==", "ghost")
            )
        )
    )
    print(ast)