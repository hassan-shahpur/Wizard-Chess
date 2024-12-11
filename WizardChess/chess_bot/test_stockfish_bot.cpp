#include "stockfish_bot.hpp"
#include <iostream>

int main() {
    stockfish_bot bot("./stockfish", 1);
    bool start = bot.start();
    if (!start) {
        std::cout << "Error starting bot\n";
    }
    std::cout << "Bot started\n";

    std::vector<std::string> output;
    // Some preliminary commands to setup the engine
    output = bot.sendCommand("isready\n");
    if (output[output.size()-1] != "readyok") {
        std::cout << "Failed to initialize engine\n";
    }
    std::cout << "Engine started\n";

    bot.sendCommand("uci\n");

    // Send White's move
    bot.sendCommand("postion startpos moves e2e4\n");

    // Get best move
    output = bot.sendCommand("go depth 5\n");
    
    if (output[0].length() != 4) {
        std::cout << "Error analyzing best move\n";
    }
    std::cout << "Best move: " << output[0] << "\n";
    bot.stop();
    std::cout << "Bot stopped\n";
    return 0;
}