/**
 * @brief Board class, deals with the movement of the pieces, gets valid moves, verifies starting position of the chess board.
 * @details Does all activities related to the board, board states and moves. Uses functions from thc.cpp to complete chess functions.
 * @authors Jarvis, Rustam, Owen, Hassan, Dayton
*/

#ifndef WIZARD_CHESS_BOARD_HPP
#define WIZARD_CHESS_BOARD_HPP

#include <iostream>
#include "thc.h"
#include "board_sensors.hpp"

class board {

private:

    bool verbose;

    std::string last_move;

    char prev_state[65];

    thc::ChessRules cr;

public:

    //should init in constructor
    board_sensors board_magnet_sensors = board_sensors(false);

    explicit board(bool verbose);

    bool make_move(std::string);

    std::string get_user_move();

    void print_valid_moves();

    void print_board_state();

    bool verify_starting_position(std::vector<std::vector<bool>> custom_state = {});

    bool is_valid_move(std::string move);

    bool is_checkmate();

    std::string identify_user_move(std::vector<std::vector<bool>> middle, std::vector<std::vector<bool>> final);

    void set_board_state(std::vector<bool>);

};


#endif //WIZARD_CHESS_BOARD_HPP
