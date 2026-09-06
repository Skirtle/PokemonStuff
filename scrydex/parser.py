from lexer import tokenize, classify_tokens
from scrytree import Expression, Literal, BinaryOperator, Filter, BINARY_EXPRESSIONS, FILTER_EXPRESSIONS

def token_to_expression(token: tuple) -> Expression:
    if (token[0] in FILTER_EXPRESSIONS):
        return Filter(token[0], token[2], token[2])
    
    raise NotImplementedError(f"Haven't added things yet for {token = }")

def create_tree(tokens: list[tuple]) -> Expression:
    expressions: list[Expression] = []
    for index,token in enumerate(tokens):
        print(f"Parsing {token = }")
        expressions.append(token_to_expression(token))
        
        
    print(f"{expressions = }")
    return Literal(4)

if __name__ == "__main__":
    query = "(name:regi spd>100) or (t=fire atk<50)"
    tokens = tokenize(query)
    classified_tokens = classify_tokens(tokens)
    print(query)
    for token in classified_tokens:
        print(f"\t{token}")
    
    print("\n")
    tree = create_tree(classified_tokens)
    print(tree.evaluate())
        