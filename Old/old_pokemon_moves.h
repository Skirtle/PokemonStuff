#ifndef POKEMON_MOVES_H
#define POKEMON_MOVES_H

#include "old_pokemon_type.h"
#include "old_pokemon_move_class.h"

// Move::Move(std::string t_name, Type t_type, MoveType t_move_type, int t_power , int t_accuracy, int t_base_priority, int t_pp) {

Move shadow_ball = Move("Shadow Ball", Type::GHOST, MoveType::SPECIAL, 80, 100, 0, 15);
Move icy_wind = Move("Icy Wind", Type::ICE, MoveType::SPECIAL, 55, 95, 0, 15);
Move knock_off = Move("Knock Off", Type::DARK, MoveType::PHYSICAL, 65, 100, 0, 20);
Move focus_punch = Move("Focus Punch", Type::FIGHTING, MoveType::PHYSICAL, 150, 100, -3, 20);

Move blizzard = Move("Blizzard", Type::ICE, MoveType::SPECIAL, 110, 70, 0, 5);
Move draining_kiss = Move("Draining Kiss", Type::FAIRY, MoveType::SPECIAL, 50, 100, 0, 10);
Move thunderbolt = Move("Thunderbolt", Type::ELECTRIC, MoveType::SPECIAL, 90, 100, 0, 15);
Move giga_impact = Move("Giga Impact", Type::NORMAL, MoveType::PHYSICAL, 150, 90, 0, 5);

#endif