import lexer
import scrytree

    
if __name__ == "__main__":
    query = "name:regi spd>100"
    tokens = lexer.tokenize(query)
    classified_tokens = lexer.classify_tokens(tokens)
    print(query)
    for token in classified_tokens:
        print(f"\t{token}")
        