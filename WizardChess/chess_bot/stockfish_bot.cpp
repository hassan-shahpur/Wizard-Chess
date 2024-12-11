#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "stockfish_bot.hpp"

#define BUFFER_SIZE 4096

using namespace std;

/**
 * @brief Stockfish bot constructor
 * @details  Sets up the path for the stockfish executable
 * Stockfish is an open source UCI chess engine https://github.com/official-stockfish/Stockfish
 * Bot is initially in the off state
 * @param filePath Path to the stockfish executable
 * @param newDepth Depth of the bot. Represents difficulty (e.g. elo rating in chess)
*/
stockfish_bot::stockfish_bot(string filePath, int newDepth) {
    stockfishPath = filePath;
    isRunning = false;
    depth = newDepth;
}

/**
 * @brief Stockfish bot destructor
*/
stockfish_bot::~stockfish_bot() {}


/**
 * @brief   Starts the bot
 * @details Communication is performed through Unix pipes. 
 * Processor is forked to execute the stockfish binary.
 * First pipe used to send data from chess board to the bot.
 * Second pipe used to send data from bot to chess board.
 * @return  State of the bot (running/not running)
*/ 
bool stockfish_bot::start() {
    if(isRunning) {
        return true;
    }

    int fdin[2], fdout[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    if(pipe(fdin) == -1) {
        cerr << "Failed to create input pipe." << endl;
        return false;
    }

    if(pipe(fdout) == -1) {
        cerr << "Failed to create output pipe." << endl;
        return false;
    }

    pid = fork();

    if(pid == -1) {
        cerr << "Failed to create child process." << endl;
        return false;
    // Child process 
    } else if (pid == 0) {
        close(fdin[1]);
        close(fdout[0]);
        // stdin is read from the pipe
        dup2(fdin[0], STDIN_FILENO);
        // stdout is written to the pipe
        dup2(fdout[1], STDOUT_FILENO);
        execl(stockfishPath.c_str(), "stockfish", (char*)0);
        exit(1);
    // Parent process
    } else {
        close(fdin[0]);
        close(fdout[1]);
        fcntl(fdout[0], F_SETFL, O_NONBLOCK);
        stockfishPID = pid;
        inputFd = fdin[1];
        outputFd = fdout[0];
        isRunning = true;
        return true;
    }
}

/**
 * @brief   Stops the bot
 * @details Close all pipes. Kill the stockfish process. Set bot to not running
*/
void stockfish_bot::stop() {
    if(!isRunning) {
        return;
    }
    close(inputFd);
    close(outputFd);
    kill(stockfishPID, SIGKILL);
    waitpid(stockfishPID, NULL, 0);
    isRunning = false;
    stockfishPID = -1;
}

/**
 * @brief Sends a command to the stockfish chess engine
 * @param command The command to be sent to the engine
 * @return Output from stockfish after executing the command
*/
vector<string> stockfish_bot::sendCommand(string command) {
    write(inputFd, command.c_str(), command.size());
    char buffer[BUFFER_SIZE];
    int bytesRead = 0;
    memset(buffer, 0, sizeof(buffer));
    // wait for stockfish to process command
    usleep(100000);
    vector<string> output = {};
    bytesRead = read(outputFd, buffer, BUFFER_SIZE); 
    stringstream ss(buffer);
    string token;
    while (std::getline(ss, token, '\n')) {
        output.push_back(token);
    }
    // 'go' means to analyze for best move, just return the best move
    if (command.rfind("go", 0) == 0) {
        string lline = output[output.size()-1];
        string bestMove = "";
        for (int i = 9; i < lline.length(); i++) {
            if (lline[i] == ' ') break;
            bestMove += lline[i];
        }
        return {bestMove};
    }
    return output;
}

/**
 * @brief   Get the depth for move analysis
 * @details Depth indicates the number of moves the engine has looked ahead
 * @return  Bot's analysis depth
*/
int stockfish_bot::getDepth() {
    return depth;
}

/**
 * @brief   Returns the current move sequence
 * @details Since stockfish does not keep state between calls, need to get the entire board state every call
 * @return  Ordered sequence of moves made so far 
*/
std::vector<std::string> stockfish_bot::getMoveSequence() {
    return move_sequence;
}

/**
 * @brief   Adds a newly made move to the move sequence
 * @details Since stockfish does not keep state between calls, need to set the entire board state every call 
 * @param   move Newly made move 
*/
void stockfish_bot::addMove(std::string move) {
    move_sequence.push_back(move);
}

