# Scrydex

## Pipeline
### Query
### Lexer
### Parser
### Validator
### Evaluator
### Result


## Syntax 
### Loose names: '{name}'
This results in Pokemon with {name} anywhere in the name. 'name:charm' would result in Charmander and Charmeleon. Alias: 'name:{name}'

### Exact names: '!"{name}"'
This results in Pokemon with the exact name given, not a loose comparison. '!"Regi"' would have zero reuslts, but '!"Regigigas"' would result in exactly one result. Alias: 'name={name}'

### Attributes: '{atribute}{operator}{value}'
* Attributes
    * Takes names as inputs
        * type, t
        * name, n
        * game
        * region, foundin, nativeto, found, native
    * Takes numbers as inputs
        * generation, gen
        * hp
        * attack, atk
        * specialattack, spatk
        * defense, def
        * specialdefense, spdef
        * speed, spd
        * basestattotal, bst, total
* Operators
    * :
        * When used with numbers, used as 'exactly equal to'
        * When used with names, used as a "found in." See [loose names](#loose-names-name)
    * =
        * When used with numbers, used as 'exactly equal to'
        * When used with names, used as an "exactly equal to." See [exact names](#exact-names-name)
    * \>
    * \>=
    * <
    * <=
    * !=
* Values
    * Names: used for type, name, generation, game, and region
    * Numbers: used for generation, attack, specialattack, defense, specialdefense, speed, basetstattotal
* Examples
    * type:fire results in all Pokemon that have the Fire type
    * type=fire results in all Pokemon that are only Fire type
    * generation: