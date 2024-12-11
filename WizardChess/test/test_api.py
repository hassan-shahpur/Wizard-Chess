# This is a program to test the chess lichess_api and see if we can get the right information
# Edit: We can! lichess has great resources
from pprint import pprint
from time import sleep

import requests as requests
import json

import ndjson

from pprint import pprint

PLAYER = 'Player 1'

def main():

    stream_game()


def stream_game():
    s = requests.Session()
    url = f'https://lichess.org/api/board/game/stream/Qz4a9crrKUsS'
    headers = {"Authorization": 'Bearer lip_SiW11uHl5R4z2voZpm3h', "Accept": "application/x-ldjson"}
    with s.get(url, headers=headers, stream=True) as resp:

        for line in resp.iter_lines():

            if line:
                pprint(line)
                j = line.decode('utf8')
                j = json.loads(j)
                if j["type"] == "gameState":
                    moves = str(j["moves"]).split(" ")
                    print(moves[-1])
                elif j["type"] == "gameFull":
                    print(j["white"])
                    print(j["black"])
                else:
                    print("J: ", j)


                # print(j)

    # list_resp = response.text.splitlines()
    # json_resp = list(map(lambda x: json.loads(x), list_resp))
    # print(r.status_code)
    # print("Got r")
    # # j = r.json()
    # print(items)

def print_opponent_move(move):
    print(move)


def get_last_archive():

    url = f'https://api.chess.com/pub/player/{PLAYER}/games/archives'
    r = requests.get(url, auth=('user', 'pass'))
    print(r.status_code)
    print("Got the archives")
    j = r.json()
    last_archive = j['archives'][-1]
    print(f"Last archive is [{last_archive}]")

    r = requests.get(last_archive, auth=('user', 'pass'))

    j = r.json()

    return j

def get_last_game():

    archive = get_last_archive()

    return archive['games'][-1]

if __name__ == '__main__':
    main()
