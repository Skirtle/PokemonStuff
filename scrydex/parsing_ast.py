from dataclasses import dataclass, field

@dataclass
class Tree:
    text: str
    
    
if __name__ == "__main__":
    print(Tree("text"))