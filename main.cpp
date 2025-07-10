#include <iostream>
#include <cassert>
#include "pokemon.h"
#include <array>
#include "pokemon_move_class.h"


int main() {
    std::cout << "Pokemon game!\n";
    // Base, iv, ev, generate pokemon, set types, give moves


    


    std::array<Pokemon, 6> team1 = {};
    std::array<Pokemon, 6> team2 = {};

    int team1_index = 0;
    int team2_index = 0;
    int turn = 0;

    Pokemon *team1_current = &team1[0];
    Pokemon *team2_current = &team2[0];


    // Print teams
    std::cout << "Team 1:\n";
    for (int i = 0; i < team1.size(); i++) {
        std::cout << "\t" << team1[i] << "\n";
    }

    std::cout << "Team 2:\n";
    for (int i = 0; i < team2.size(); i++) {
        std::cout << "\t" << team2[i] << "\n";
    }

    // Battle until one teeam is empty
    std::cout << "Begin!";
    while (team1_index < team1.size() && team2_index < team2.size()) {
        // Upkeep
        // Uptick turn count
        // Check the moves both Pokemon are using for priority, switching out, etc
        // Check if move is usable
        turn++;
        std::cout << "\nTurn " << turn << "\n";



        // Check speeds
        Pokemon *first_pokemon, *second_pokemon;
        int team1_priority = team1_current->get_move(0).get_priority();
        int team2_priority = team2_current->get_move(0).get_priority();
        if (team1_priority == team2_priority) {
            if (team1_current->get_speed() == team2_current->get_speed()) {
                int random_number = std::rand() % 2;
                if (random_number) {
                    first_pokemon = team1_current; 
                    second_pokemon = team2_current;
                }
                else {
                    first_pokemon = team2_current; 
                    second_pokemon = team1_current;
                }
            }
            else {
                first_pokemon = (team1_current->get_speed() >= team2_current->get_speed()) ? team1_current : team2_current;
                second_pokemon = (team1_current == first_pokemon) ? team2_current : team1_current;
            }
        } else if (team1_priority > team2_priority) {
            first_pokemon = team1_current;
            second_pokemon = team2_current;
        } else if (team1_priority < team2_priority) {
            first_pokemon = team2_current;
            second_pokemon = team1_current;
        }



        // Perform first attack
        Move first_move = (first_pokemon->get_move(0));
        first_pokemon->attack_target(second_pokemon, &first_move);
        // std::cout << "\t" << first_pokemon->get_name() << " used " << first_move.get_name() << " against " << second_pokemon->get_name() << " for " << dmg << "!\n";

        // Check if slower Pokemon lived
        if (second_pokemon->get_hp() <= 0) {
            second_pokemon->set_hp(0);
            // Fainted
            std::cout << "\t" << second_pokemon->get_name() << " fainted!";

            // Check the team
            if (second_pokemon == team1_current) {
                team1_index++;
                // Team 1's Pokemon fainted
                // Check if anymore Pokemon
                if (team1_index >= team1.max_size()) {
                    // No more Pokemon
                    std::cout << " Team 1 has run out of Pokemon!\n";
                    break;
                }
                else {
                    // Still more Pokemon
                    team1_current = &team1[team1_index];
                    std::cout << " Switching out for " << team1_current->get_name() << "!\n";
                }
            }
            else {
                // Team 2's Pokemon fainted
                team2_index++;
                // Check if anymore Pokemon
                if (team2_index >= team2.max_size()) {
                    // No more Pokemon
                    std::cout << " Team 2 has run out of Pokemon!\n";
                    break;
                }
                else {
                    // Still more Pokemon
                    team2_current = &team2[team2_index];
                    std::cout << " Switching out for " << team2_current->get_name() << "!\n";
                }
            }
            // Next turn
            continue;
        }



        // Perform second attack
        Move second_move = (second_pokemon->get_move(0));
        second_pokemon->attack_target(first_pokemon, &second_move);
        //std::cout << "\t" << second_pokemon->get_name() << " used " << second_move.get_name() << " against " << first_pokemon->get_name() << " for " << dmg << "!\n";

        // Check if faster Pokemon lived
         if (first_pokemon->get_hp() <= 0) {
            first_pokemon->set_hp(0);
            // Fainted
            std::cout << "\t" << first_pokemon->get_name() << " fainted!";

            // Check the team
            if (first_pokemon == team1_current) {
                team1_index++;
                // Team 1's Pokemon fainted
                // Check if anymore Pokemon
                if (team1_index >= team1.max_size()) {
                    // No more Pokemon
                    std::cout << " Team 1 has run out of Pokemon!\n";
                    break;
                }
                else {
                    // Still more Pokemon
                    team1_current = &team1[team1_index];
                    std::cout << " Switching out for " << team1_current->get_name() << "\n";
                }
            }
            else {
                // Team 2's Pokemon fainted
                team2_index++;
                // Check if anymore Pokemon
                if (team2_index >= team2.max_size()) {
                    // No more Pokemon
                    std::cout << " Team 2 has run out of Pokemon!\n";
                    break;
                }
                else {
                    // Still more Pokemon
                    team2_current = &team2[team2_index];
                    std::cout << " Switching out for " << team2_current->get_name() << "!\n";
                }
            }
            // Next turn
            continue;
        }


        // Cleanup step

    }

    return 0;
}