from pokemodule import *


pokemon = Pokemon()
pokemon.name = "What"

for i in pokemon.__dict__:
    print(i, pokemon.__dict__[i])