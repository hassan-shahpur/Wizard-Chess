/**
 * @brief Controls the movement of the gantry
 * @details Methods that move the gantry in different amounts to the necessasry squares
 * @authors
*/

#ifndef WIZARD_CHESS_STEPPERS_HPP
#define WIZARD_CHESS_STEPPERS_HPP

#include <string>
#include <tuple>

class steppers {

private:

    int BOARD_WIDTH = 0;
    int BOARD_HEIGHT = 0;

    int current_x = 1100;
    int current_y = 1100;

    void tick_x(int direction);
    void tick_y(int direction);

    void set_stepper(int value, int motor);

    


public:

    steppers(bool verbose);

    void zero_steppers();

    void move_to(int x_dist, int y_dist);
    
    bool make_move(std::string move);

    std::tuple<int, int> get_servo_angle();

    void test();

};


#endif //WIZARD_CHESS_STEPPERS_HPP
