#include <iostream>
#include <string>

#ifndef CONNECT_4
#define CONNECT_4
#include "Connect4.h"
#endif

#include "C4CmdLine.h"


Connect4 game(2);
bool wantQuit = false;


int main (int argc, char *argv[]) {

    printf("Welcome to Connect4!\n");

    while (!wantQuit) {

        C4CmdLine::printGameState(&game);

        int currentPlayer = game.getCurrentPlayer();

        printf("Player %d, what's your move? (Enter a column between 1 and 7)\n", currentPlayer);
        std::string input = C4CmdLine::getInputText();

        if (input.compare("quit") == 0) {
            wantQuit = true;
        } else {

            int col = atoi(input.c_str());
            game.makePlay(currentPlayer, col);

            if (game.isGameOver()) {

                C4CmdLine::printGameState(&game);

                int winner = game.getWinner();
                printf("Congratulations, player %d wins!\n", winner);
                wantQuit = true;

            }

        }

    }

    return 0;

}
