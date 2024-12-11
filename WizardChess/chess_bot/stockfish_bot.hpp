#ifndef STOCKFISH_BOT_H
#define STOCKFISH_BOT_H
#include <string>
#include <vector>
#include <sys/types.h>

/**
 * @brief   Chess board's API to the stockfish chess engine.
 * @author  Rustam Mamedov
 * @details The chess board requires access to a chess engine in order to make decisions on the next move. 
 * The class provides an API between the chess board and the stockfish binary, with bidirectional communication.
 * The communication is established using the Unix fork and pipe. 
*/

class stockfish_bot {

private:

    std::string stockfishPath;
    int depth;
    int inputFd;
    int outputFd;
    pid_t stockfishPID;
    bool isRunning;
    std::vector<std::string> move_sequence;

public:
    
    stockfish_bot(std::string path, int depth);

    bool start();

    void stop();

    std::vector<std::string> sendCommand(std::string command);

    int getDepth();

    std::vector<std::string> getMoveSequence();

    void addMove(std::string move);

    ~stockfish_bot();

};


#endif 
