import lexer


    
if __name__ == "__main__":
    query = "-(t:fire atk>50) or (spd>100 -(t:ghost t:fire))"
    tokens = lexer.tokenize(query)
    classified_tokens = lexer.classify_tokens(tokens)
    print(query)
    for token in classified_tokens:
        print(f"\t{token}")
        