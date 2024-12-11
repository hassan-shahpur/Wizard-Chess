
#include <string>
#include "game.hpp"
#include <iostream>

#include "test_api.cpp"

#include "lichess_api.hpp"


using namespace std;

int main(){

    game g(true);
    cout << "Starting game..." << endl;

    g.start_game();

    cout << "Done game! \n Here are the stats:" << endl;
    cout << "Number of moves" << g.get_number_of_moves() << endl;

//    stream_moves();

}