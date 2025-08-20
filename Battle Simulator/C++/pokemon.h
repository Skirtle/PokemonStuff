#ifndef POKEMON_H
#define POKEMON_H

#include "pokemon_type.h"
#include "pokemon_move_class.h"
#include "pokemon_nature.h"

#include <string>
#include <array>
#include <random>


class Pokemon {
private:
    std::string name;
    int level;
    int hp, attack, defense, special_attack, special_defense, speed;
    Type type1, type2;
    Move move;
    std::array<Move, 4> move_set;
    Nature nature;


public:
    // Non-volatile statuses (not removed when switched out)
    bool is_burnt = false;
    bool is_paralyzed = false;
    bool is_asleep = false;
    bool is_frozen = false;
    bool is_poisoned = false;
    bool is_badly_poisoned = false;

    // Volatile statuses (removed when switched out)
    bool is_confused = false;

    // Constructors
    Pokemon() {
        Pokemon("null", 0, 0, 0, 0, 0, 0, 0, Nature::HARDY);
        this->set_types(Type::NONE, Type::NONE);
        this->move = Move();
    }
    Pokemon(std::string n, int l, int h, int a, int d, int sa, int sd, int s, Nature na) {
        this->set_name(n);
        this->set_level(l);
        this->set_hp(h);
        this->set_attack(a);
        this->set_defense(d);
        this->set_sp_attack(sa);
        this->set_sp_defense(sd);
        this->set_speed(s);
        this->set_types(Type::NONE, Type::NONE);
        this->set_nature(na);
    }
    Pokemon(std::string n, int l, std::array<int, 6> base, std::array<int, 6> iv, std::array<int, 6> ev, Nature na) {
        this->set_name(n);
        this->set_nature(na);
        this->calculate_stats(l, base, iv, ev);
        this->set_types(Type::NONE, Type::NONE);
    }

    // Getters
    std::string get_name() { return this->name; }
    int get_hp( ) { return this->hp; }
    int get_attack() { return this->attack; }
    int get_defense(){ return this->defense; }
    int get_sp_attack(){ return this->special_attack; }
    int get_sp_defense(){ return this->special_defense; }
    int get_speed(){ return this->speed; }
    int get_level() { return this->level; }
    Type get_type1() { return this->type1; }
    Type get_type2() { return this->type2; }
    Move get_move(int i) { return this->move_set[i]; }
    std::array<Move, 4> get_move_set() { return this->move_set; }
    Nature get_nature() { return this->nature; }

    // Setters
    void set_name(std::string n) { this->name = n; };
    void set_hp(int h ) { this->hp = h; }
    void set_attack(int a) { this->attack = a; }
    void set_defense(int d){ this->defense = d; }
    void set_sp_attack(int sa){ this->special_attack = sa; }
    void set_sp_defense(int sd){ this->special_defense = sd; }
    void set_speed(int s){ this->speed = s; }
    void set_level(int l) { this->level = l; }
    void set_types(Type t1, Type t2) { this->type1 = t1; this->type2 = t2; }
    void set_move(Move m, int i) { this->move_set[i] = m; }
    void set_move_set(std::array<Move, 4> ms) { this->move_set = ms;}
    void set_nature (Nature nat) { this->nature = nat; }

    // Methods
    void attack_target(Pokemon *defender, Move* move) {
        // Randomness
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> random_chance(85, 100);
        std::uniform_int_distribution<> crit_chance(1, 24);

        // Multipliers
        double A = (move->get_category() == Category::PHYSICAL) ? this->get_attack() : this->get_sp_attack(); // Attack stat of attacking Pokemon
        double D = (move->get_category() == Category::PHYSICAL) ? defender->get_defense() : defender->get_sp_defense(); // Defense stat of defending Pokemon
        double power = move->get_power(); // This will become the power of the move used, default for now is 100
        double targets = 1; // 0.75 if move has multiple targets, otherwise 1
        double pb = 1; // Parental bond, 0.25 (0.5 in gen VI), if move is second strike of Parent Bond, otherwise 1
        double weather = 1; // 1.5 if Water in rain, Fire/Hydro Steam in harsh sunlight, 0.5 (except Hydro Steam) if Water in harsh sunlight, 0.5 if Fire in rain. Otherwise 1, or 1 if Cloun Nine or Air Lock ability 
        double glaive_rush = 1; // 2 if target used Glaive Rush last turn, otherwise 1
        double critical = (crit_chance(gen) <= 1) ? 1.5 : 1; // Critical hit
        double random = random_chance(gen) / 100.0; // A random number between (and including) 80 and 100, then divided by 100
        double stab = (move->get_type() == this->get_type1() || move->get_type() == this->get_type2() ) ? 1.5 : 1.0; // 1.5 if used move matches a type of the attacker, 2 if previous and has Adaptability, otherwise 1. More rules for Terastaize
        double type = get_attack_multiplier(move->get_type(), defender->get_type1(), defender->get_type2()); // Effectiveness
        double burn = (this->is_burnt && move->get_category() == Category::PHYSICAL) ? 0.5 : 1.0; // 0.5 if the attacker is burned, its Ability is not Guts, and the used move is a physical move, otherwise 1
        double other = 1; // 1 in most cases
        double zmove = 1; // 0.25 if zmove used and defender is protecting, otherwise 1

        // Calculate damage
        double dmg_ratio = (double) A / (double) D;
        double base_dmg = (2 * this->get_level()) / 5.0 + 2;
        base_dmg *= power;
        base_dmg *= dmg_ratio;
        base_dmg /= 50;
        base_dmg += 2;
        base_dmg = base_dmg * targets * pb * weather * glaive_rush * critical * stab * type * burn * other * zmove * random;
        // Round to closest (0.5 -> down)
        if ((base_dmg - (int) base_dmg) <= 0.5) base_dmg = (int) base_dmg;
        else base_dmg = (int) (base_dmg + 1);

        // Change the defender's HP
        defender->set_hp(defender->get_hp() - base_dmg);

        // Print the attack
        std::cout << "\t" << this->get_name() << " used " << move->get_name() << "!";
        if (type >= 2) std::cout << " It was super effective!";
        else if (type < 1) std::cout << " It wasn't very effective!";
        if (critical > 1) std::cout << " Critical hit!";
        std::cout << " " << defender->get_name() << " took " << base_dmg << " damage!\n";

        // Use move's PP
        move->set_current_pp(move->get_current_pp() - 1);
    }

    void calculate_stats(int level, std::array<int, 6> base, std::array<int, 6> iv, std::array<int, 6> ev) {
        // Pokemon does not have full stats, not good!
        if (base.size() != 6 || iv.size() != 6 || ev.size() != 6) {
            this->set_level(0);
            this->set_stats({0, 0, 0, 0, 0, 0});
            return;
        }

        std::array<int, 6> new_stats;
        std::array<double, 6> nature_stats = get_nature_mults(this->nature);

        for (int i = 0; i < 6; i++) {
            int base_num = (2 * base[i]) + iv[i] + (ev[i] / 4);
            base_num *= ((double) level / 100);
            
            if (i == 0) { base_num += level + 10; } // Stat is HP
            else { 
                base_num += 5;
                double nature_mult = nature_stats[i];
                base_num *= nature_mult;
            } // Not HP
            new_stats[i] = base_num;
        }

        this->set_stats(new_stats);
        this->set_level(level);
    }

    void set_stats(std::array<int, 6> stats) {
        this->set_hp(stats[0]);
        this->set_attack(stats[1]);
        this->set_defense(stats[2]);
        this->set_sp_attack(stats[3]);
        this->set_sp_defense(stats[4]);
        this->set_speed(stats[5]);
    }

    // Overloads
    friend std::ostream& operator<<(std::ostream& os, const Pokemon& self) {
        os << self.name << " (" << self.level << ") [HP: " << self.hp << ", ATK: " << self.attack << ", DEF: " << self.defense;
        os << ", SP. ATK: " << self.special_attack << ", SP. DEF: " << self.special_defense << ", SPD: " << self.speed << "]";
        return os; // Return the stream to allow chaining
    }

};



#endif