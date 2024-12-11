/**
 * @brief Controls and starts the game
 * @details Initialize the game and stats related to it, starts the game and start and register both players moves
 * @authors 
*/
#include <iostream>
#include <unistd.h>
#include <thread>
#include <Arduino.h>
#include "definitions.hpp"

#include "game.hpp"
#include "board.hpp"


/**
 * @brief Creates and initalize game object
 * @details Sets verbose, which side player is on, the sequence of moves, the move counter, and turn counter.
 * @param Bool verbose, for debugging, displays additional information
*/
game::game(bool verbose) {

    this->verbose = verbose;
    this->player_is_white = true;
    this->move_number = 0;
    this->turn = 0;
}

/**
 * @brief starts the game
 * @details Starts the game by settung the game id, verify starting position, make both players moves.
 * @returns 1
*/
int game::start_game() {

//    Set up some variables
    bool checkmate = false;
    // std::string game_id = "I3va3U9X";

    // std::string move;

    stepper.zero_steppers();

    //stepper.move_to(0, 0);
    
    while(1){
        delay(1000);
        Serial.println("HEHE");
    }

    

//     player_is_white = true;
//     std::string user_move = "e2e4";
//     std::string bot_move;

// //    Make sure the board is set up correctly
//     // while(!chess_board.verify_starting_position()){
//     //     std::cout << "Please set up board correctly" << std::endl;
//     //     sleep(1);
//     // }
//     // while(!chess_board.verify_starting_position()){
//     //     std::cout << "Please set up board correctly" << std::endl;
//     //     sleep(1);
//     // }


// //  TODO If the player is black, get a bot move first
// //  move = lichess_api.get_bot_move();
// //  chess_board.make_move(move);
//     if(!player_is_white){
//         // move = lichess_api.last_bot_move();
//         chess_board.make_move(std::string(bot_move.c_str()));
//     }


//     while (true) {

// //         this->move_number += 1;
// //         if(this->verbose){
// //             std::cout << "Move " << this->move_number<< std::endl;
// //         }


// // //      ===== Get the users move =====
//         // if(this->verbose){
//         //     std::cout << "Getting the users move." << std::endl;
//         //     // chess_board.print_board_state();
//         // }
        
//         // user_move = chess_board.get_user_move();
//         // user_move = chess_board.identify_user_move();

//         int touch_sensit = 100;
        
        
        do{
            
            // Wait for the user to press the button
            std::cout << "Waiting for move confirmation..." << std::endl;
            while(analogRead(PIN_BUTTON) > 1000){
                //std::cout << "..." << std::endl;
                delay(100);
            }

            delay(2000);
            std::vector<std::vector<bool>> middle_state = chess_board.board_magnet_sensors.get_board_state();
            
            // Wait for the user to press the button again
            while(analogRead(PIN_BUTTON) > 1000){
                //std::cout << "..." << std::endl;
                delay(100);
            }

            std::vector<std::vector<bool>> final_state = chess_board.board_magnet_sensors.get_board_state();

            user_move = chess_board.identify_user_move(middle_state, final_state);

            if(chess_board.make_move(user_move)){
                // A move has been sucsessfully made. Exit
                break;
            }

//             // std::cout << "That is not a valid move. Please try again. Remember this is case-sensitive" << std::endl;
//             chess_board.print_board_state();

// //         }while (1);

// //      ===== Play the users move =====
//         chess_board.make_move(user_move);
//         stepper.make_move(user_move);
//         move_sequence.push_back(std::string(user_move.c_str()));            
            

//         if (chess_board.is_checkmate())
//             break;


// //      ===== Get the bots move =====
//         // prefix 'fish' is for identifying a move message
//         Serial.println(("fish " + user_move).c_str());
//         while(Serial.available() == 0) {}
//         bot_move = std::string(Serial.readString().c_str());
//         move_sequence.push_back(std::string(bot_move.c_str()));   

// //      Wait some time to let the bot make a move on the server
//         // chess_board.print_board_state();
//         // sleep(2);
        
//         // send signal to stockfish bot on the computer and read the output from the computer
//         // move = lichess_api.last_bot_move();


// //      ===== Play the bots move =====
//         chess_board.make_move(bot_move);

       
//     }

    return 1;


}

/**
 * @brief number of moves getter
 * @details Gives number of moves
 * @returns Number of moves
*/
int game::get_number_of_moves() const {
    return this->move_number;
}

game::~game() {

}
