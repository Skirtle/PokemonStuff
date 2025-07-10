#ifndef POKEMON_MOVE_CLASS_H
#define POKEMON_MOVE_CLASS_H

#include <string>
#include "old_pokemon_type.h"

enum class MoveType {
    PHYSICAL, SPECIAL, STATUS
};

class Move {
private:
    std::string name;
    Type type;
    MoveType move_type;
    int base_power, base_accuracy, base_priority, base_pp, current_pp;
public:
    Type get_type();
    std::string get_name();
    Move(std::string t_name, Type t_type, MoveType t_move_type, int t_power, int t_accuracy, int t_base_priority, int t_base_pp);
    Move();
};

Move::Move(std::string t_name, Type t_type, MoveType t_move_type, int t_power , int t_accuracy, int t_base_priority, int t_pp) {
    this->name = t_name;
    this->type = t_type;
    this->move_type = t_move_type;
    this->base_power = t_power;
    this->base_accuracy = t_accuracy;
    this->base_pp = t_pp;
    this->current_pp = t_pp;
}
Move::Move() {
    this->name = "Struggle";
    this->type = Type::NORMAL;
    this->move_type = MoveType::PHYSICAL;
    this->base_power = 60;
    this->base_accuracy = 100;
    this->base_pp = 1;
    this->current_pp = 1;
}

Type Move::get_type() { return this->type; }
std::string Move::get_name() { return this->name; }

#endif