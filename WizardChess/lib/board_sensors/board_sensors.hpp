/**
 * @brief Uses board sensors to set up the board state for use throught the code
 * @details Initializes board sensors, uses them to detect where each piece is and store in a board vector, as well as checking
 * individual squares and printing the board state.
 * @author Jarvis
*/

#ifndef WIZARD_CHESS_BOARD_SENSORS_HPP
#define WIZARD_CHESS_BOARD_SENSORS_HPP

#include <vector>

class board_sensors {

private:

    bool verbose;

    bool get_square_state(int x);

    static void print_board_state(std::vector<std::vector<bool>> state);

public:

    board_sensors(bool verbose);

    std::vector<std::vector<bool>> get_board_state();

};


#endif //WIZARD_CHESS_BOARD_SENSORS_HPP
