#ifndef POKEMON_NATURE_H
#define POKEMON_NATURE_H

#include <string>
#include <array>
#include "pokemon_nature.h"

enum class Nature {
    HARDY, LONELY, BRAVE, ADAMANT, NAUGHTY,
    BOLD, DOCILE, RELAXED, IMPISH, LAX, TIMID,
    HASTY, SERIOUS, JOLLY, NAIVE, MODEST,
    MILD, QUIET, BASHFUL, RASH, CALM,
    GENTLE, SASSY, CAREFUL, QUIRKY
};

 enum class Stat {
    HP, ATTACK, DEFENSE, SPEED, SP_ATTACK, SP_DEFENSE
};

inline std::array<Nature, 25> natures = {Nature::HARDY, Nature::LONELY, Nature::BRAVE, Nature::ADAMANT, Nature::NAUGHTY, 
    Nature::BOLD,Nature:: DOCILE, Nature::RELAXED, Nature::IMPISH, Nature::LAX, 
    Nature::TIMID, Nature::HASTY, Nature::SERIOUS, Nature::JOLLY, Nature::NAIVE, 
    Nature::MODEST, Nature::MILD, Nature::QUIET, Nature::BASHFUL, Nature::RASH, 
    Nature::CALM, Nature::GENTLE, Nature::SASSY, Nature::CAREFUL, Nature::QUIRKY};

inline std::array<std::string, 25> nature_names = {"HARDY", "LONELY", "BRAVE", "ADAMANT", "NAUGHTY", 
    "BOLD", "DOCILE", "RELAXED", "IMPISH", "LAX", 
    "TIMID", "HASTY", "SERIOUS", "JOLLY", "NAIVE", 
    "MODEST", "MILD", "QUIET", "BASHFUL", "RASH", 
    "CALM", "GENTLE", "SASSY", "CAREFUL", "QUIRKY"};

inline std::array<Stat, 6> stats = {Stat::HP, Stat::ATTACK, Stat::DEFENSE, Stat::SPEED, Stat::SP_ATTACK, Stat::SP_DEFENSE};

// Functions
inline std::pair<Stat, Stat> get_nature_stats(Nature nature) { return std::pair<Stat, Stat>(stats[(int) nature / 5], stats[(int) nature % 5]); }
inline std::pair<Stat, Stat> get_nature_stats(int nature_int) { return std::pair<Stat, Stat>(stats[nature_int / 5], stats[nature_int % 5]); }
inline std::string get_nature_name(Nature nature) { return nature_names[(int) nature]; }
inline std::string get_nature_name(int nature_int) { return nature_names[nature_int]; }


std::array<double, 6> get_nature_mults(Nature nature) {
    std::array<double, 6> base ={1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

    std::pair<Stat, Stat> stat_pair = get_nature_stats(nature);
    Stat pos_stat = stat_pair.first;
    Stat neg_stat = stat_pair.second;
    if (pos_stat == neg_stat) return base;
    // Add 1 to index to take into account HP is not affected by nature
    base[(int) pos_stat + 1] = 1.1;
    base[(int) neg_stat + 1] = 0.9;

    return base;

}

#endif