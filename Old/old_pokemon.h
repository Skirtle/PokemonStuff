#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <string>
#include <array>
#include "old_pokemon_type.h"
#include "old_pokemon_move_class.h"
#include "old_pokemon_moves.h"
#include "old_pokemon_nature.h"
#include "old_pokemon_ability_class.h"

// Classes
class Pokemon {
private:
    int level;
    int max_hp;
    int current_hp;

    std::array<int, 6> base_stats;
    std::array<int, 6> iv_stats;
    std::array<int, 6> ev_stats;
    std::array<int, 6> final_stats;
    std::array<Move, 4> moves;

    std::string name;

    Type type1, type2;

    Nature nature;

public:
    Pokemon(std::string name, Type type1, Type type2, int level, Nature nature);

    // Setters
    void set_level(int lev);
    void set_name(std::string new_name);
    void set_types(Type new_type1, Type new_type2);
    void set_moves(Move move1, Move move2, Move move3, Move move4);
    void set_hp_stats();
    void set_stat_values(std::array<int, 6> base, std::array<int, 6> iv, std::array<int, 6> ev);
    void set_nature(Nature nature);

    // Getters
    Type get_type1();
    Type get_type2();
    std::array<Move, 4> get_moves();
    std::string get_name();
    std::array<int, 6> get_final_stats();
    int get_current_hp();
    int get_level();

    void attack(Move move, Pokemon defender);
    void attack(int move_num, Pokemon defender);
    void calculate_stats();
};

// Setters
// Set Pokemon information
void Pokemon::set_name(std::string new_name) { this->name = new_name; }
void Pokemon::set_types(Type new_type1, Type new_type2) {  this->type1 = new_type1; this->type2 = new_type2; }
void Pokemon::set_moves(Move move1, Move move2, Move move3, Move move4) {this->moves = {move1, move2, move3, move4}; }

// Set Pokemon stats
void Pokemon::set_level(int lev) { this->level = lev; }
void Pokemon::set_hp_stats() {
    int hp1 = ((2 * this->base_stats[0]) + this->iv_stats[0] + int((double) ev_stats[0] / 4));
    int hp2 = hp1 * this->level;

    this->max_hp = ((int) hp2 / 100) + this->level + 10;
    this->current_hp = this->max_hp;
    this->final_stats[0] = this->max_hp;
}
void Pokemon::set_stat_values(std::array<int, 6> base, std::array<int, 6> iv, std::array<int, 6> ev) {
        this->base_stats = base;
        this->iv_stats = iv;
        this->ev_stats = ev;
        this->set_hp_stats();
        this->calculate_stats();
    }
void Pokemon::set_nature(Nature nature) { this->nature = nature; }

// Getters
Type Pokemon::get_type1() { return this->type1; }
Type Pokemon::get_type2() {  return this->type2; }
std::array<Move, 4> Pokemon::get_moves() { return this->moves; }
std::string Pokemon::get_name() { return this->name; }
int Pokemon::get_current_hp() { return this->current_hp; }
std::array<int, 6> Pokemon::get_final_stats() {  return this->final_stats; }
int Pokemon::get_level() { return this->level; }


// Constructors
Pokemon::Pokemon(std::string name, Type type1, Type type2, int level = 100, Nature nature = Nature::HARDY) {
    this->set_level(level);
    this->set_name(name);
    this->set_types(type1, type2);
    this->set_nature(nature);
}

// Methods
void Pokemon::attack(Move move, Pokemon defender) {
    std::cout << this->get_name() << " used " << move.get_name() << "!\n";
    std::string eff_words;
    int efficiency = get_attack_multiplier(move.get_type(), defender.get_type1(), defender.get_type2());

    if (efficiency == 0) eff_words = "It had no effect!\n\n";
    else if (efficiency < 1) eff_words = "It was not very effective!\n\n";
    else if (efficiency == 1) eff_words = "\n";
    else eff_words = "It was super effective!\n\n";

    std::cout << eff_words;
}

void Pokemon::attack(int move_num, Pokemon defender) {
    this->attack(this->get_moves()[move_num], defender);
}

void Pokemon::calculate_stats() {
    std::array<double, 6> mults = get_nature_mults(this->nature);
    for (int i = 1; i < 6; i++) {
        double nature_mult = mults[i];

        int base = this->base_stats[i];
        int iv = this->iv_stats[i];
        int ev = this->ev_stats[i];

        int twice_base = 2 * base;
        int fourth_ev = (int) ev / 4;
        int numerator = (twice_base + iv + fourth_ev) * level;
        int final_stat = (int) ((((int) (numerator / 100)) + 5) * nature_mult);

        this->final_stats[i] = final_stat;
    }
}

#endif