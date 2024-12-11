
from stockfish import Stockfish

stockfish = Stockfish(path="/opt/homebrew/bin/stockfish")


def main():

    s = Stockfish()

    # print(s.get_evaluation())

    s.set_fen_position("rnbqkbnr/pppppppp/8/8/8/8/PP5P/RNBQKBNR w KQkq - 0 1")
    print(s.get_board_visual())

    print(s.get_best_move())





if __name__ == "__main__":
    main()
