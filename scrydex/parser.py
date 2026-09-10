from lexer import tokenize, classify_tokens
from scrytree import Expression, Literal, BinaryOperator, Filter, BINARY_EXPRESSIONS, FILTER_EXPRESSIONS

def token_to_expression(token: tuple) -> Expression:
    if (token[0] in FILTER_EXPRESSIONS): return Filter(token[0], token[2], Literal(token[1]))
    raise NotImplementedError(f"Haven't added things yet for {token = }")

def create_tree(tokens: list[tuple]) -> Expression:
    expressions: list[Expression] = []
    
    index = 0
    while index < len(tokens):
        token = tokens[index]
        
        if (token[0] in FILTER_EXPRESSIONS): expressions.append(token_to_expression(token))
        elif (token[1] in BINARY_EXPRESSIONS): expressions.append(token[1])
        else: raise NotImplementedError(f"No expression type can be found for '{token[1]}'")
        
        index += 1
        
        
    index = 1
    while index < len(expressions) - 1:
        if (expressions[index] == "and"):
            left = expressions[index - 1]
            right = expressions[index + 1]
            expressions[index - 1:index + 2] = [BinaryOperator(left, "and", right)]
        
        else: index += 1
        
    index = 1
    while index < len(expressions) - 1:
        if (expressions[index] == "or"):
            left = expressions[index - 1]
            right = expressions[index + 1]
            expressions[index - 1:index + 2] = [BinaryOperator(left, "or", right)]
        
        else: index += 1

    return expressions[0]

if __name__ == "__main__":
    query = "(name:regi spd>100) or (t=fire atk<50)"
    query = "name:regi spd>=100 or t=fire atk<=50 hp<=40"
    tokens = tokenize(query)
    classified_tokens = classify_tokens(tokens)
    tree = create_tree(classified_tokens)
    print(query)
    print(tree.evaluate())
        