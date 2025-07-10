#ifndef POKEMON_MOVE_CLASS_H
#define POKEMON_MOVE_CLASS_H

#include <string>
#include "pokemon_type.h"

enum class Category {
    PHYSICAL, SPECIAL, STATUS
};

class Move {
private:
    std::string name;
    int power, accuracy, current_pp, max_pp, priority;
    bool makes_contact;
    Type type;
    Category category;

public:
    // Constructors
    Move(std::string n = "Struggle", int p = 1, int a = 100, int cp = 1, int mp = 1, bool contact = true, Type t = Type::NORMAL, int pr = 0, Category c = Category::PHYSICAL) {
        this->set_name(n);
        this->set_power(p);
        this->set_accuracy(a);
        this->set_current_pp(cp);
        this->set_max_pp(mp);
        this->set_makes_contact(contact);
        this->set_type(t);
        this->set_priority(pr);
        this->set_category(c);
    }

    // Setters
    void set_name(std::string n){ this->name = n;}
    void set_power(int p){ this->power = p;}
    void set_accuracy(int a){ this->accuracy = a;}
    void set_current_pp(int cp){ this->current_pp = cp;}
    void set_max_pp(int mp){ this->max_pp = mp;}
    void set_makes_contact(bool contact){ this->makes_contact = contact;}
    void set_type(Type t){ this->type = t;}
    void set_priority(int pr) {this->priority = pr; }
    void set_category(Category c) { this->category = c; }

    // Getters
    std::string get_name() { return this->name; }
    int get_power( ) { return this->power; }
    int get_accuracy( ) { return this->accuracy; }
    int get_current_pp( ) { return this->current_pp; }
    int get_max_pp( ) { return this->max_pp; }
    bool get_makes_contact( ) { return this->makes_contact; }
    Type get_type( ) { return this->type; }
    int get_priority() { return this->priority; }
    Category get_category() { return this->category; }
};

#endif