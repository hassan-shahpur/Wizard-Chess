//
// Created by Owner on 2023-02-18.
//

#include <string>
#include <iostream>
#include "lichess_api.hpp"

void stream_moves(){

    std::string url = "https://lichess.org/lichess_api/board/game/stream/jmglk03q";
//    request r(url, false);

    lichess_api a(true);
    a.set_game_id("jmglk03q");

    a.start_polling();

}