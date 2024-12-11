/**
 * @brief Controls and starts the game
 * @details Initialize the game and stats related to it, starts the game and start and register both players moves
 * @authors 
*/
#ifndef WIZARD_CHESS_GAME_HPP
#define WIZARD_CHESS_GAME_HPP

#include <vector>
#include <string>
#include "board.hpp"
#include "steppers.hpp"

class game {
private:

    bool verbose;

    bool player_is_white{};
    // instantiate in game.cpp instead
    board chess_board = board(true);

    int move_number;

    steppers stepper = steppers(false);

    std::vector<std::string> move_sequence;

    // 0 - White's turn
    // 1 - Black's turn
    int turn;


public:

    game(bool verbose);

    ~game();

    int start_game();

    int get_number_of_moves() const;



};


#endif //WIZARD_CHESS_GAME_HPP
