#ifndef POKEMON_PLAYER_H
#define POKEMON_PLAYER_H

#include "old_pokemon.h"

#define MAX_POKEMON_PARTY 6

class Player {
private:
    std::string name;
    std::array<Pokemon, MAX_POKEMON_PARTY> party;
    Pokemon *current_pokemon;

public:
    // Methods
    void switch_pokemon(int switch_out, int switch_in);
};

void Player::switch_pokemon(int switch_out, int switch_in) {

}



#endif