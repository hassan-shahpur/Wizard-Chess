/**
 * @brief Board class, deals with the movement of the pieces, gets valid moves, verifies starting position of the chess board.
 * @details all activities related to the board, board states and moves. Uses functions from thc.cpp to complete chess functions.
 * @authors Jarvis, Rustam, Owen, Hassan, Dayton
*/


#include <iostream>
#include <stdlib.h>
#include <vector>
#include "board_sensors.hpp"
#include "thc.h"
#include "board.hpp"

/**
 * @brief Board constructor
 * @details Sets verbose to the supplied value from the call, sets last move to empty to define it, and fill the board
 * 
 * @param verbose for debugging, prints additional information to the console
*/
board::board(bool verbose) {
    this->verbose = verbose;
    this->last_move = "";
    strncpy(this->prev_state, this->cr.squares, 65);
    // bot plays black by default
}

/**
 * @brief the board board state to console
 * @details Uses the ToDebugStr in tch.cpp to display all squares and pieces on the chess board
*/
void board::print_board_state() {
//    this.&cr
//    const std::string &description
//    std::string fen = this->cr.ForsythPublish();
    std::string s = this->cr.ToDebugStr();

//    printf( "%s\n", description.c_str() );
//    printf( "FEN (Forsyth Edwards Notation) = %s\n", fen.c_str() );
    printf( "%s\n", s.c_str() );
}

/**
 * @brief Displays all valid moves available on the current board state
 * @details Uses GenLegalMoveList to find all possible moves that the player can legally play on the current turn.
*/
void board::print_valid_moves() {
    thc::Move mv;
//    printf( "List of all legal moves in the current position\n" );
    std::vector<thc::Move> moves;
    std::vector<bool> check;
    std::vector<bool> mate;
    std::vector<bool> stalemate;
    this->cr.GenLegalMoveList(  moves, check, mate, stalemate );
    unsigned int len = moves.size();
    for( unsigned int i=0; i<len; i++ )
    {
        mv = moves[i];
        std::string mv_txt = mv.NaturalOut(&cr);
        const char *suffix="";
        if( check[i] )
            suffix = " (note '+' indicates check)";
        else if( mate[i] )
            suffix = " (note '#' indicates mate)";
        printf( "%d. %s%s\n", i+1, mv_txt.c_str(), suffix );
    }

}

/**
 * @brief Attempt to make a move
 * @details Given a move as a string, checks if it is valid, then changes the board state if the move is valid and returns true. If it is an 
 * invalid move this returns false
 * @param String move to be taken by current player
 * @returns Returns true if successful and valid move, returns false if invalid move.
*/
bool board::make_move(std::string move) {
//    Returns true if the move was a valid move
    thc::Move mv;
    mv.TerseIn( &cr, move.c_str() );

    if(this->is_valid_move(move)){
        this->last_move = move;
        strncpy(this->prev_state, this->cr.squares, 65);
        cr.PlayMove(mv);
        // std::cout << this->prev_state << "\n";
        // std::cout << this->cr.squares << "\n";
        return true;
    } else {
        return false;
    }

    return true;
}

/**
 * @brief Gets user's move from input
 * @details Asks for player's move and receives it through input after displaying a list of valid moves
 * @returns User's move as a string
*/
std::string board::get_user_move() {

    if(this->verbose){
        std::cout << "Waiting for next move... Here are the legal moves you can play" << std::endl;
        this->print_valid_moves();
    }

    std::string move;
    std::cin >> move;
    return move;
}

/**
 * @brief Verifies board is in correct starting position
 * @details Compares supplied game state to the expected back two files for both sides being filled and if so returns true.
 * @param Vector current board state
 * @returns True or false depending on board state
*/

bool board::verify_starting_position(std::vector<std::vector<bool>> custom_state) {

    std::vector<std::vector<bool>> state = board_magnet_sensors.get_board_state();
    if (custom_state.size() > 0) {
        state = custom_state;
    } 

    std::vector<std::vector<bool>> expected_state = {{true,true,true,true,true,true,true,true},
                                                    {true,true,true,true,true,true,true,true},
                                                    {false,false,false,false,false,false,false,false},                    
                                                    {false,false,false,false,false,false,false,false}, 
                                                    {false,false,false,false,false,false,false,false}, 
                                                    {false,false,false,false,false,false,false,false}, 
                                                    {true,true,true,true,true,true,true,true},
                                                    {true,true,true,true,true,true,true,true}};

    if (state == expected_state) return true;
    return false;
}

/**
 * @brief Check if move supplied is a valid move on the board state
 * @details Uses the generated valid move list to compare if given move is valid, and legal
 * @param String move supplied to be checked
 * @returns True if move is legal, false if illegal
*/
bool board::is_valid_move(std::string move) {

    thc::Move mv;
    std::vector<thc::Move> moves;
    std::vector<bool> check;
    std::vector<bool> mate;
    std::vector<bool> stalemate;
    this->cr.GenLegalMoveList(  moves, check, mate, stalemate );
    unsigned int len = moves.size();
    for( unsigned int i=0; i<len; i++ )
    {
        mv = moves[i];
        std::string mv_txt = mv.TerseOut();
        if (mv_txt == move){
            std::cout << "HIT: " << mv_txt << std::endl;
            return true;
        }
//        const char *suffix="";
//        if( check[i] )
//            suffix = " (note '+' indicates check)";
//        else if( mate[i] )
//            suffix = " (note '#' indicates mate)";
//        printf( "%d. %s%s\n", i+1, mv_txt.c_str(), suffix );
    }

    return false;
}

/**
 * @brief check if there is a checkmate on the board
 * @details Checks the board state to see if the board position has a checkmate
 * @returns Returns true if there is a checkmate, false otherwise
*/
bool board::is_checkmate() {
//    TODO Check if a position is checkmate
    thc::TERMINAL eval_final_position;
    bool legal = cr.Evaluate( eval_final_position );
    bool mate = (eval_final_position == thc::TERMINAL_WCHECKMATE);
    if (mate) return true;
    return false;
}

/**
 * @brief Calculates what move the user chose
 * @details Identify a move that was made by the player in algebraic notation
 * i.e. [old_position][new_position]
 * @param vector original board state
 * @param vector Final board state
 * @returns the move user chose
*/
std::string board::identify_user_move(std::vector<std::vector<bool>> middle, std::vector<std::vector<bool>> final) {

    // check the number of pieces 
    int count = 0;
    char moved_piece;
    char files[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    std::string new_pos;
    std::string old_pos;
    std::string move;
    // white castles king side
    if (this->prev_state[7*8+4] == 'K' && final[7][6] == 'K') return "O-O";
    // white castles queen side
    if (this->prev_state[7*8+4] == 'K' && final[7][2] == 'K') return "O-O-O";
    // black castles king side
    if (this->prev_state[4] == 'k' && final[0][6] == 'k') return "o-o";
    // black castles queen side
    if (this->prev_state[4] == 'k' && final[0][2] == 'K') return "o-o-o";

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (final[row][col] != false) {
                count++;
            }
            if (this->prev_state[row*8+col] != ' ') {
                count--;
            }
            // regular move
            if (middle == final) {
                if (this->prev_state[row*8+col] != ' ' && final[row][col] == false) {
                // rows in array ascend from top to bottom, opposite for chessboard
                old_pos = files[col] + std::to_string(8-row);
                moved_piece = this->prev_state[row*8+col];
                }
                if (this->prev_state[row*8+col] == ' ' && final[row][col] == true) {
                    new_pos = files[col] + std::to_string(8-row);
                }
            // take move
            } else {
                if (this->prev_state[row*8+col] != ' ' && middle[row][col] == false) {
                    new_pos = files[col] + std::to_string(8-row);
                } 
                if (this->prev_state[row*8+col] != ' ' && final[row][col] == false) {
                    old_pos = files[col] + std::to_string(8-row);
                }
            } 
            
        }
    }
    move = moved_piece + old_pos + new_pos; 
    
    return move;
}