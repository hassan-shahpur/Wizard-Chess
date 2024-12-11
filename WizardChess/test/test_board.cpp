#include "board.hpp"
#include <iostream>
#include <stdlib.h>
#include <vector>

int main() {
    board* b = new board(true);

    // testing starting position verification
    bool result;
    std::vector<std::vector<bool>> bad_state = {{false,true,true,true,true,true,true,true},
                                                {true,true,true,true,true,true,true,true},
                                                {false,false,false,false,false,false,false,false},                    
                                                {false,false,false,false,false,false,false,false}, 
                                                {false,false,false,false,false,false,false,false}, 
                                                {false,false,false,false,false,false,false,false}, 
                                                {true,true,true,true,true,true,true,true},
                                                {true,true,true,true,true,true,true,true}};
    result = b->verify_starting_position(bad_state); // should output 0
    std::cout << result << std::endl;
    std::vector<std::vector<bool>> good_state = {{true,true,true,true,true,true,true,true},
                                                {true,true,true,true,true,true,true,true},
                                                {false,false,false,false,false,false,false,false},                    
                                                {false,false,false,false,false,false,false,false}, 
                                                {false,false,false,false,false,false,false,false}, 
                                                {false,false,false,false,false,false,false,false}, 
                                                {true,true,true,true,true,true,true,true},
                                                {true,true,true,true,true,true,true,true}};
    result = b->verify_starting_position(good_state); //should output 1
    std::cout << result << std::endl;

    // testing move identification, should print Pe2e4 (white pawn from e2 to e4)
    std::vector<std::vector<bool>> e2e4 = {{true,true,true,true,true,true,true,true},
                                            {true,true,true,true,true,true,true,true},
                                            {false,false,false,false,false,false,false,false},                    
                                            {false,false,false,false,false,false,false,false}, 
                                            {false,false,false,false,true,false,false,false}, 
                                            {false,false,false,false,false,false,false,false}, 
                                            {true,true,true,true,false,true,true,true},
                                            {true,true,true,true,true,true,true,true}};
    std::string move = b->identify_user_move(e2e4);
    std::cout << move << std::endl;
    // testing checkmate
    b->make_move("f2f3");
    b->make_move("e7e5");
    b->make_move("g2g4");
    b->make_move("d8h4");
    std::cout << b->is_checkmate() << std::endl;
    delete b;
    return 0;
}

