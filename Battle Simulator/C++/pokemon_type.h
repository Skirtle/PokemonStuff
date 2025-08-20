#ifndef POKEMON_TYPE_H
#define POKEMON_TYPE_H

#include <unordered_map>

enum class Type {
    NORMAL, FIRE, WATER, ELECTRIC,
    GRASS, ICE, FIGHTING, POISON,
    GROUND, FLYING, PSYCHIC, BUG,
    ROCK, GHOST, DRAGON, DARK,
    STEEL, FAIRY, NONE
};

static std::unordered_map<Type, std::unordered_map<Type, double>> effectivenessChart = {
    {Type::NORMAL, {{Type::NORMAL, 1.0}, {Type::FIRE, 1.0}, {Type::WATER, 1.0}, {Type::ELECTRIC, 1.0},  {Type::GRASS, 1.0}, {Type::ICE, 1.0}, {Type::FIGHTING, 1.0}, {Type::POISON, 1.0}, {Type::GROUND, 1.0}, 
    {Type::FLYING, 1.0}, {Type::PSYCHIC, 1.0}, {Type::BUG, 1.0}, {Type::ROCK, 0.5}, {Type::GHOST, 0.0}, {Type::DRAGON, 1.0}, {Type::DARK, 1.0}, {Type::STEEL, 0.5}, {Type::FAIRY, 1.0}}},
    
    {Type::FIRE, {{Type::NORMAL, 1.0}, {Type::FIRE, 0.5}, {Type::WATER, 0.5}, {Type::ELECTRIC, 1.0},  {Type::GRASS, 2.0}, {Type::ICE, 2.0}, {Type::FIGHTING, 1.0}, {Type::POISON, 1.0}, {Type::GROUND, 1.0}, 
    {Type::FLYING, 1.0}, {Type::PSYCHIC, 1.0}, {Type::BUG, 2.0}, {Type::ROCK, 0.5}, {Type::GHOST, 1.0}, {Type::DRAGON, 0.5}, {Type::DARK, 1.0}, {Type::STEEL, 2.0}, {Type::FAIRY, 1.0}}},
    
    {Type::WATER, {{Type::NORMAL, 1.0}, {Type::FIRE, 2.0}, {Type::WATER, 0.5}, {Type::ELECTRIC, 1.0},  {Type::GRASS, 0.5}, {Type::ICE, 1.0}, {Type::FIGHTING, 1.0}, {Type::POISON, 1.0}, {Type::GROUND, 2.0}, 
    {Type::FLYING, 1.0}, {Type::PSYCHIC, 1.0}, {Type::BUG, 1.0}, {Type::ROCK, 2.0}, {Type::GHOST, 1.0}, {Type::DRAGON, 0.5}, {Type::DARK, 1.0}, {Type::STEEL, 1.0}, {Type::FAIRY, 1.0}}},
    
    {Type::ELECTRIC, {{Type::NORMAL, 1.0}, {Type::FIRE, 1.0}, {Type::WATER, 2.0}, {Type::ELECTRIC, 0.5},  {Type::GRASS, 0.5}, {Type::ICE, 1.0}, {Type::FIGHTING, 1.0}, {Type::POISON, 1.0}, {Type::GROUND, 0.0}, 
    {Type::FLYING, 2.0}, {Type::PSYCHIC, 1.0}, {Type::BUG, 1.0}, {Type::ROCK, 1.0}, {Type::GHOST, 1.0}, {Type::DRAGON, 0.5}, {Type::DARK, 1.0}, {Type::STEEL, 1.0}, {Type::FAIRY, 1.0}}},
    
    {Type::GRASS, {{Type::NORMAL, 1.0}, {Type::FIRE, 0.5}, {Type::WATER, 2.0}, {Type::ELECTRIC, 1.0},  {Type::GRASS, 0.5}, {Type::ICE, 1.0}, {Type::FIGHTING, 1.0}, {Type::POISON, 0.5}, {Type::GROUND, 2.0}, 
    {Type::FLYING, 0.5}, {Type::PSYCHIC, 1.0}, {Type::BUG, 0.5}, {Type::ROCK, 2.0}, {Type::GHOST, 1.0}, {Type::DRAGON, 0.5}, {Type::DARK, 1.0}, {Type::STEEL, 0.5}, {Type::FAIRY, 1.0}}},
    
    {Type::ICE, {{Type::NORMAL, 1.0}, {Type::FIRE, 0.5}, {Type::WATER, 0.5}, {Type::ELECTRIC, 1.0},  {Type::GRASS, 2.0}, {Type::ICE, 0.5}, {Type::FIGHTING, 1.0}, {Type::POISON, 1.0}, {Type::GROUND, 2.0}, 
    {Type::FLYING, 2.0}, {Type::PSYCHIC, 1.0}, {Type::BUG, 1.0}, {Type::ROCK, 1.0}, {Type::GHOST, 1.0}, {Type::DRAGON, 2.0}, {Type::DARK, 1.0}, {Type::STEEL, 0.5}, {Type::FAIRY, 1.0}}},
    
    {Type::FIGHTING, {{Type::NORMAL, 2.0}, {Type::FIRE, 1.0}, {Type::WATER, 1.0}, {Type::ELECTRIC, 1.0},  {Type::GRASS, 1.0}, {Type::ICE, 2.0}, {Type::FIGHTING, 1.0}, {Type::POISON, 0.5}, {Type::GROUND, 1.0}, 
    {Type::FLYING, 0.5}, {Type::PSYCHIC, 0.5}, {Type::BUG, 0.5}, {Type::ROCK, 2.0}, {Type::GHOST, 0.0}, {Type::DRAGON, 1.0}, {Type::DARK, 2.0}, {Type::STEEL, 2.0}, {Type::FAIRY, 0.5}}},
    
    {Type::POISON, {{Type::NORMAL, 1.0}, {Type::FIRE, 1.0}, {Type::WATER, 1.0}, {Type::ELECTRIC, 1.0},  {Type::GRASS, 2.0}, {Type::ICE, 1.0}, {Type::FIGHTING, 1.0}, {Type::POISON, 0.5}, {Type::GROUND, 0.5}, 
    {Type::FLYING, 1.0}, {Type::PSYCHIC, 1.0}, {Type::BUG, 1.0}, {Type::ROCK, 0.5}, {Type::GHOST, 0.5}, {Type::DRAGON, 1.0}, {Type::DARK, 1.0}, {Type::STEEL, 0.0}, {Type::FAIRY, 2.0}}},
    
    {Type::GROUND, {{Type::NORMAL, 1.0}, {Type::FIRE, 2.0}, {Type::WATER, 1.0}, {Type::ELECTRIC, 2.0},  {Type::GRASS, 0.5}, {Type::ICE, 1.0}, {Type::FIGHTING, 1.0}, {Type::POISON, 2.0}, {Type::GROUND, 1.0}, 
    {Type::FLYING, 0.0}, {Type::PSYCHIC, 1.0}, {Type::BUG, 0.5}, {Type::ROCK, 2.0}, {Type::GHOST, 1.0}, {Type::DRAGON, 1.0}, {Type::DARK, 1.0}, {Type::STEEL, 2.0}, {Type::FAIRY, 1.0}}},
    
    {Type::FLYING, {{Type::NORMAL, 1.0}, {Type::FIRE, 1.0}, {Type::WATER, 1.0}, {Type::ELECTRIC, 0.5},  {Type::GRASS, 2.0}, {Type::ICE, 1.0}, {Type::FIGHTING, 2.0}, {Type::POISON, 1.0}, {Type::GROUND, 1.0}, 
    {Type::FLYING, 1.0}, {Type::PSYCHIC, 1.0}, {Type::BUG, 2.0}, {Type::ROCK, 0.5}, {Type::GHOST, 1.0}, {Type::DRAGON, 1.0}, {Type::DARK, 1.0}, {Type::STEEL, 0.5}, {Type::FAIRY, 1.0}}},
    
    {Type::PSYCHIC, {{Type::NORMAL, 1.0}, {Type::FIRE, 1.0}, {Type::WATER, 1.0}, {Type::ELECTRIC, 1.0},  {Type::GRASS, 1.0}, {Type::ICE, 1.0}, {Type::FIGHTING, 2.0}, {Type::POISON, 2.0}, {Type::GROUND, 1.0}, 
    {Type::FLYING, 1.0}, {Type::PSYCHIC, 0.5}, {Type::BUG, 1.0}, {Type::ROCK, 1.0}, {Type::GHOST, 1.0}, {Type::DRAGON, 1.0}, {Type::DARK, 0.0}, {Type::STEEL, 0.5}, {Type::FAIRY, 1.0}}},
    
    {Type::BUG, {{Type::NORMAL, 1.0}, {Type::FIRE, 0.5}, {Type::WATER, 1.0}, {Type::ELECTRIC, 1.0},  {Type::GRASS, 2.0}, {Type::ICE, 1.0}, {Type::FIGHTING, 0.5}, {Type::POISON, 0.5}, {Type::GROUND, 1.0}, 
    {Type::FLYING, 0.5}, {Type::PSYCHIC, 2.0}, {Type::BUG, 1.0}, {Type::ROCK, 1.0}, {Type::GHOST, 0.5}, {Type::DRAGON, 1.0}, {Type::DARK, 2.0}, {Type::STEEL, 0.5}, {Type::FAIRY, 0.5}}},
    
    {Type::ROCK, {{Type::NORMAL, 1.0}, {Type::FIRE, 2.0}, {Type::WATER, 1.0}, {Type::ELECTRIC, 1.0},  {Type::GRASS, 1.0}, {Type::ICE, 2.0}, {Type::FIGHTING, 0.5}, {Type::POISON, 1.0}, {Type::GROUND, 0.5}, 
    {Type::FLYING, 2.0}, {Type::PSYCHIC, 1.0}, {Type::BUG, 2.0}, {Type::ROCK, 1.0}, {Type::GHOST, 1.0}, {Type::DRAGON, 1.0}, {Type::DARK, 1.0}, {Type::STEEL, 0.5}, {Type::FAIRY, 1.0}}},
    
    {Type::GHOST, {{Type::NORMAL, 0.0}, {Type::FIRE, 1.0}, {Type::WATER, 1.0}, {Type::ELECTRIC, 1.0},  {Type::GRASS, 1.0}, {Type::ICE, 1.0}, {Type::FIGHTING, 1.0}, {Type::POISON, 1.0}, {Type::GROUND, 1.0}, 
    {Type::FLYING, 1.0}, {Type::PSYCHIC, 2.0}, {Type::BUG, 1.0}, {Type::ROCK, 1.0}, {Type::GHOST, 2.0}, {Type::DRAGON, 1.0}, {Type::DARK, 0.5}, {Type::STEEL, 1.0}, {Type::FAIRY, 1.0}}},
    
    {Type::DRAGON, {{Type::NORMAL, 1.0}, {Type::FIRE, 1.0}, {Type::WATER, 1.0}, {Type::ELECTRIC, 1.0},  {Type::GRASS, 1.0}, {Type::ICE, 1.0}, {Type::FIGHTING, 1.0}, {Type::POISON, 1.0}, {Type::GROUND, 1.0}, 
    {Type::FLYING, 1.0}, {Type::PSYCHIC, 1.0}, {Type::BUG, 1.0}, {Type::ROCK, 1.0}, {Type::GHOST, 1.0}, {Type::DRAGON, 2.0}, {Type::DARK, 1.0}, {Type::STEEL, 0.5}, {Type::FAIRY, 0.0}}},
    
    {Type::DARK, {{Type::NORMAL, 1.0}, {Type::FIRE, 1.0}, {Type::WATER, 1.0}, {Type::ELECTRIC, 1.0},  {Type::GRASS, 1.0}, {Type::ICE, 1.0}, {Type::FIGHTING, 0.5}, {Type::POISON, 1.0}, {Type::GROUND, 1.0}, 
    {Type::FLYING, 1.0}, {Type::PSYCHIC, 2.0}, {Type::BUG, 1.0}, {Type::ROCK, 1.0}, {Type::GHOST, 2.0}, {Type::DRAGON, 1.0}, {Type::DARK, 0.5}, {Type::STEEL, 1.0}, {Type::FAIRY, 0.5}}},
    
    {Type::STEEL, {{Type::NORMAL, 1.0}, {Type::FIRE, 0.5}, {Type::WATER, 0.5}, {Type::ELECTRIC, 0.5},  {Type::GRASS, 1.0}, {Type::ICE, 2.0}, {Type::FIGHTING, 1.0}, {Type::POISON, 1.0}, {Type::GROUND, 1.0}, 
    {Type::FLYING, 1.0}, {Type::PSYCHIC, 1.0}, {Type::BUG, 1.0}, {Type::ROCK, 2.0}, {Type::GHOST, 1.0}, {Type::DRAGON, 1.0}, {Type::DARK, 1.0}, {Type::STEEL, 0.5}, {Type::FAIRY, 2.0}}},
    
    {Type::FAIRY, {{Type::NORMAL, 1.0}, {Type::FIRE, 0.5}, {Type::WATER, 1.0}, {Type::ELECTRIC, 1.0},  {Type::GRASS, 1.0}, {Type::ICE, 1.0}, {Type::FIGHTING, 2.0}, {Type::POISON, 0.5}, {Type::GROUND, 1.0}, 
    {Type::FLYING, 1.0}, {Type::PSYCHIC, 1.0}, {Type::BUG, 1.0}, {Type::ROCK, 1.0}, {Type::GHOST, 1.0}, {Type::DRAGON, 2.0}, {Type::DARK, 2.0}, {Type::STEEL, 0.5}, {Type::FAIRY, 1.0}}},
    
};

double get_attack_multiplier(Type attack_type, Type def_type1, Type def_type2 = Type::NONE) {
    if (attack_type == Type::NONE || def_type1 == Type::NONE) return 1.0; // Protects against NONE typing

    double mult1 = effectivenessChart[attack_type][def_type1];
    double mult2 = (def_type2 != Type::NONE) ? effectivenessChart[attack_type][def_type2] : 1;
    return mult1 * mult2;
}


#endif