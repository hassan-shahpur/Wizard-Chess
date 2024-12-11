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

// Entry point for stockfish bot program
int main() {
    // set depth to 5
    stockfish_bot bot("./stockfish", 5);
    bot.start();
    std::vector<std::string> output;
    // Some preliminary commands to setup the engine
    bot.sendCommand("isready\n");
    bot.sendCommand("uci\n");

    int baudRate = 115200;
    int fd;                             
    // Open port to controller 
    fd = open("/dev/tty.usbserial-0001", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        std::cout << "Device cannot be opened.\n";
        return -1;                     
    }
    struct termios options;

    // fcntl(fd, F_SETFL, FNDELAY);                    // Open the device in nonblocking mode

    // Set parameters
    tcgetattr(fd, &options);                        // Get the current options of the port
    bzero(&options, sizeof(options));               // Clear all the options
    speed_t Speed;
    switch (baudRate)                               // Set the speed (baudRate)
    {
        case 110  :     Speed=B110; break;
        case 300  :     Speed=B300; break;
        case 600  :     Speed=B600; break;
        case 1200 :     Speed=B1200; break;
        case 2400 :     Speed=B2400; break;
        case 4800 :     Speed=B4800; break;
        case 9600 :     Speed=B9600; break;
        case 19200 :    Speed=B19200; break;
        case 38400 :    Speed=B38400; break;
        case 57600 :    Speed=B57600; break;
        case 115200 :   Speed=B115200; break;
        default : std::cout << "Invalid baud rate.\n"; return -1;
    }
    cfsetispeed(&options, Speed);                   // Set the baud rate
    cfsetospeed(&options, Speed);
    options.c_cflag |= ( CLOCAL | CREAD |  CS8);    // Configure the device : 8 bits, no parity, no control
    options.c_iflag |= ( IGNPAR | IGNBRK );
    options.c_cc[VTIME]=0;                          // Timer unused
    options.c_cc[VMIN]=0;                           // At least one character before satisfy reading
    tcsetattr(fd, TCSANOW, &options);               // Activate the settings

    char buffer[256];
    std::string line;

    std::string bot_move = "";
    std::string user_move = ""; 
    std::string analyze_cmd = "go depth " + std::to_string(bot.getDepth()) + "\n";

    while (true) {
        sleep(1);
        ssize_t count = read(fd, buffer, sizeof(buffer));
        for (int i = 0; i < count; i++) {
            char c = buffer[i];
            if (c == '\n') {
                // If newline is encountered, print the line and clear it
                // std::cout << line << std::endl;
                if (line.rfind("fish", 0) == 0) {
                    user_move = line.substr(5);
                    // std::cout << user_move << std::endl;
                }
                line.clear();
            } else {
                // Otherwise, add the character to the line
                line += c;
            }
        }

        if (count > 0) {
            if (user_move != "") {
                // std::cout << "User: " << user_move << std::endl;
                // User made a move, add it
                bot.addMove(user_move);
                // Needed to set the stockfish engine board state
                std::string command = "position startpos moves";
                // Sync the stockfish board state with internal board state (from the controller)
                std::vector<std::string> move_sequence = bot.getMoveSequence();
                for (std::string move : move_sequence) {
                    command += " " + move;
                }
                bot.sendCommand(command + '\n');
                // get the next best move
                bot_move = bot.sendCommand(analyze_cmd)[0];
                bot.addMove(bot_move);
                // std::cout << "Bot: " << bot_move << std::endl;
                // Send the next move to the controller
                write(fd, bot_move.c_str(), sizeof(output[output.size()-1].c_str()));
            }
            // Clear buffer
            memset(buffer, '\0', sizeof(buffer));
            user_move = "";
        }
    }
  

    // Close the serial connection 
    close(fd);
    // Stop bot
    bot.stop();
    return 0;
}