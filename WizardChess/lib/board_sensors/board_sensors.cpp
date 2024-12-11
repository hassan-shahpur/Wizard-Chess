/**
 * @brief Uses board sensors to set up the board state for use throught the code
 * @details Initializes board sensors, uses them to detect where each piece is and store in a board vector, as well as checking
 * individual squares and printing the board state.
 * @author Jarvis
*/

#include "board_sensors.hpp"
#include <iostream>
#include <vector>
#include <Arduino.h>
#include "definitions.hpp"


/**
 * @brief Board sensor constructor to initialize board sensors
 * @details Initializes board sensors for use of reading board states using hall effect sensor input
 * @param Boolean verbose, used for deugging to print additional info
*/
board_sensors::board_sensors(bool verbose) {
    this->verbose = verbose;
    std::cout << "Initializing board_sensors" << std::endl;
}

/**
 * @brief Check the state of all squares on the board
 * @details Moves around and checks the state of the board using hall effect sensor outputs
 * @returns The board state
*/
std::vector<std::vector<bool>> board_sensors::get_board_state() {

    if (this->verbose)
        std::cout << "Getting the board state" << std::endl;

//    Create a 2d array to store board sensor values
    std::vector<std::vector<bool>> board( 8 , std::vector<bool> (8, false));

//        For each row
    for(int i = 0; i < 8; i++){

            int x = i &= 0x1;
            int y = i &= 0x2;
            int z = i &= 0x4;
            digitalWrite(PIN_SELECT1, x);
            digitalWrite(PIN_SELECT2, y);
            digitalWrite(PIN_SELECT3, z);

            board.at(i).at(0) = get_square_state(0);
            board.at(i).at(1) = get_square_state(1);
            board.at(i).at(2) = get_square_state(2);
            board.at(i).at(3) = get_square_state(3);
            board.at(i).at(4) = get_square_state(4);
            board.at(i).at(5) = get_square_state(5);
            board.at(i).at(6) = get_square_state(6);
            board.at(i).at(7) = get_square_state(7);
            board.at(i).at(8) = get_square_state(8);
        
    }

    if (this->verbose) {
        std::cout << "Done getting board state. Here is the " << std::endl;
        this->print_board_state(board);
    }
    
    return board;
}

/**
 * @brief returns the board state of specific square
 * @details Given the square supplied by the x and y parameters, use the hall effect sensor to check if the square is occupied or not
 * @param int x position of desired square
 * @returns true if piece is on that square and false if the square is empty
*/
bool board_sensors::get_square_state(int x) {

//    TODO Get the state of one square by setting the right bits, and checking the output
//        Right now we are just returning the identity matrix
    if(x == 0){
        digitalRead(PIN_QUERY1);
    }else if(x == 1){
        digitalRead(PIN_QUERY2);
    }else if(x == 2){
        digitalRead(PIN_QUERY3);
    }else if(x == 3){
        digitalRead(PIN_QUERY4);
    }else if(x == 4){
        digitalRead(PIN_QUERY5);
    }else if(x == 5){
        digitalRead(PIN_QUERY6);
    }else if(x == 6){
        digitalRead(PIN_QUERY7);
    }else if(x == 7){
        digitalRead(PIN_QUERY8);
    }
    

}

/**
 * @brief Prints current board state
 * @details Cycles through each square and prints the value of that square
 * @param boardState current board state
 */
void board_sensors::print_board_state(std::vector<std::vector<bool>> state) {

//    Doing a lot of printing in this function, so use the std namespace
    using namespace std;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            cout << state.at(i).at(j) << " ";
        }
        cout << endl;
    }
}



