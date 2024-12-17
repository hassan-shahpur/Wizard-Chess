## Wizard Chess

This is a group project developped for an Object Oriented Design Course

Wizard Chess is an interactive chessboard that combines human gameplay with automated opponent movements. Players manually move their own pieces, while the computer-controlled opponent’s pieces are moved autonomously using a gantry system powered by electromagnets.

## Hardware and Technology

This project was developped entirely in C++

The project utilized a gantry system constructed from 20x20 aluminum extrusions, timing belts, stepper motors, and custom 3D-printed parts. Hall sensors were integrated to detect the positions of the chess pieces, while an Arduino microcontroller controlled the stepper motors and electromagnets responsible for automated movements. Inspired by Greg06’s Automated Chessboard.

Here are some of the videos showcasing the project:

[![Moving a Piece](https://img.youtube.com/vi/tppY0oy66Ag/0.jpg)](https://youtu.be/tppY0oy66Ag)
[![Testing the Gantry](https://img.youtube.com/vi/x6VtnNcSBzg/0.jpg)](https://youtu.be/x6VtnNcSBzg)

## Tests

How to run acceptance tests:

Detect if all pieces are in the correct starting position and Move Identification given new state:

1. cd into test folder under src
2. run the following command: g++ -std=c++11 test_board.cpp ../board/board.cpp ../board_sensors/board_sensors.cpp ../board/thc.cpp -I ../board/ -I ../board_sensors/
3. run the executable (./test_board)

Test folder:
In the test directory there is a variety of tests that have been created:
led_test.ino: this tests LED and arduino control over hardware
test_api.cpp: This sets up the lichess API and sets the game ID of a game
lichess_api.py: Python testing script to see what information can be pulled from the Lichess API
test_stockfish.py: Set a position for the chess game and test the stockfish AI functionality by asking its best move
