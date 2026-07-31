TOKEN_WORDS = ["t", "type", "n", "name", "gen", "game", "hp", "atk", "attack", "spatk", "specialattack", "defense", "def", "spdef", "specialdef", "speed", "spd", "bst", "total", "region"] # to be expanded on
OPERATOR_WORDS = ["not", "and", "or"]

class InvalidKeywordException(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__(self.message)
    def __str__(self): return self.message

class InvalidQueryException(Exception):
    def __init__(self, message):
        self.message = message
        super().__init__(self.message)
    def __str__(self): return self.message

def strip(s: str) -> str:
    """strips a string, as well as leading and ending quotes

    Args:
        s (str): the string to strip

    Returns:
        str: the stripped string
    """
    if not s: return ""
    s = s.strip()  # remove whitespace
    if (s[0] in ("'", '"')): s = s[1:]
    if (s and s[-1] in ("'", '"')): s = s[:-1] # check s again
    return s

def tokenize(query: str) -> list[tuple]:
    """turns a search query into individual tokens in a list

    Args:
        query (str): search query

    Returns:
        list: a list
    """
    
    tokens = []
    curr_token = ""
    in_quotes = False
    
    index = 0
    while (index < len(query)):
        char = query[index]

        # Quotes
        if (char in "\"'"): in_quotes = not in_quotes

        # Spaces
        if (char == " " and not in_quotes):
            tokens.append(curr_token)
            curr_token = ""
        
        # Parenthesis
        elif ((char == "(" or char == ")") and not in_quotes):
            if (curr_token): # parenthesis and curr_token is not empty (i.e. the ) in '(atk>45)')
                tokens.append(curr_token)
                tokens.append(char)
                curr_token = ""
                
            else: # parenthesis and curr_token is empty (i.e. the ( in '(atk>45)')
                tokens.append(char)

        # NOT
        elif (char == "-" and not in_quotes):
            if (curr_token):
                tokens.append(curr_token)
                tokens.append(char)
                curr_token = ""
                
            else:
                tokens.append(char)

        else:
            curr_token += char
        
        index += 1

    tokens.append(curr_token)
    return tokens

def classify_tokens(tokens: list) -> list:
    """Returns a list of the tokens in a query, classified by their query type

    Args:
        tokens (list): a list of tokens (str)

    Returns:
        list: a list of tuples of token and their classifications
    """
    classified_tokens = []
    for token in tokens:
        # Empty token
        if (token == ""): continue
        
        # Parenthesis
        elif (token == ")" or token == "("):
            classified_tokens.append(("paren", token))
            continue
        
        elif (token[0] == "-"): 
            classified_tokens.append(("bool", "not"))
            continue
        
        # Get the type of token comparison
        if ("<=" in token): comp_type = "<="
        elif ("<" in token): comp_type = "<"
        elif (">=" in token): comp_type = ">="
        elif (">" in token): comp_type = ">"
        elif ("==" in token): comp_type = "=="
        elif ("!=" in token): comp_type = "!="
        elif ("=" in token): comp_type = ":"
        else: comp_type = ":"
        split_token = token.split(comp_type, 1)
        
        # Either a bool word or name
        if (len(split_token) == 1): # Could be a bool token, or a name
            if (token not in OPERATOR_WORDS): 
                bool_type = "=="
                classified_tokens.append(("name", token, bool_type)) # Name token
            else: 
                classified_tokens.append(("bool", token)) # Bool token
        
        # Some type of attribute to query
        elif (len(split_token) == 2): # Attribute token
            # Error checking
            if (split_token[0] not in TOKEN_WORDS): raise InvalidKeywordException(f"{split_token[0]} not a valid keyword")
            
            token_type = split_token[0]
            token_value = strip(split_token[1])

            if (token_type in ["type", "t"]): token_type = "type"
            elif (token_type in ["name", "n"]): token_type = "name"
            elif (token_type in ["gen", "generation"]): token_type = "generation"
            elif (token_type in ["game"]): token_type = "game"
            elif (token_type in ["hp"]): token_type = "hp"
            elif (token_type in ["atk", "attack"]): token_type = "atk"
            elif (token_type in ["spatk", "specialattack"]): token_type = "spatk"
            elif (token_type in ["def", "defense"]): token_type = "def"
            elif (token_type in ["spdef", "specialdefense"]): token_type = "spdef"
            elif (token_type in ["spd", "speed"]): token_type = "spd"
            elif (token_type in ["bst", "total"]): token_type = "bst"
            elif (token_type in ["region"]): token_type = "region"
            
            if (comp_type == ":" or comp_type == "="): comp_type = ":"
            token_tuple = (token_type, token_value, comp_type) # ex: ("hp", "50", "<=")
            
            classified_tokens.append(token_tuple)

    return post_process_tokens(classified_tokens)

def post_process_tokens(tokens: list[tuple]) -> list[tuple]:
    """Adds boolean tokens in between tokens where they belong, adds missing trailing ending parenthesis, and removes empty tokens

    Args:
        tokens (list[tuple]): a list of tokens

    Returns:
        list[tuple]: a list of tokens
    """
    if (len(tokens) == 0): raise InvalidQueryException(f"Query cannot be empty")

    index = 1
    new_tokens = [tokens[0]]
    open_groups = 0
    while (index < len(tokens)):
        previous_token = tokens[index - 1]
        current_token = tokens[index]
        if (previous_token[1] == "("): open_groups += 1
        elif (previous_token[1] == ")" and open_groups == 0): raise InvalidQueryException("Query contains unclosed parenthesis")
        elif (previous_token[1] == ")"): open_groups -= 1
        
        # Previous token not bool/() and current is not bool/()
        # Adds implied AND, "args AND args"
        if (previous_token[0] not in ["bool", "paren"] and current_token[0] not in ["bool", "paren"]):
            new_tokens.append(("bool", "and"))

        # Previous token not bool/() and current is not negation
        # Adds implied AND, "args AND NOT args"
        elif (previous_token[0] not in ["bool", "paren"] and current_token[1] == "not"):
            new_tokens.append(("bool", "and"))
        
        # Prevuious token is ) and current is not )/bool
        # Adds implied AND, "(args) AND args"
        elif (previous_token[1] == ")" and current_token[1] != ")" and current_token[0] != "bool"):
            new_tokens.append(("bool", "and"))
        
        new_tokens.append(current_token)
        index += 1
    
    # Checks for missing parenthesis
    if (tokens[index - 1][1] == ")"): open_groups -= 1 # Above loop does not check the last index for parenthesis
    if (open_groups):
        raise InvalidQueryException("Query contains unclosed parenthesis")
    
    return new_tokens

if __name__ == "__main__":
    # raw query -> tokenize -> classify_tokens
    #queries = ["((t:ghost -spd>80) or (spatk<=45 atk<=45)) -t:fire"]
    # queries = ["type:fire hp>=100 or name:pikachu", "t:fire -mega", "t:fire -t:ghost", "(-(t:ghost -spd>80) or (spatk<=45 atk<=45)) -t:fire"]
    queries = ["(t:fire or t:water) atk>=100"]
    for query in queries:
        print(f"{query = }")
        query_tokens = tokenize(query)
        print(f"{query_tokens = }")
        query_classified_tokens = classify_tokens(query_tokens)
        print(f"query_classified_tokens")
        for token in query_classified_tokens:
            print(f"\t{token}")
        
        
        
        print()