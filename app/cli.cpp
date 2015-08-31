#include <iostream>
#include <string>

#ifndef CONNECT_4
#define CONNECT_4
#include "connect4.h"
#endif

#include "connect4_helper.h"


connect4 game(2);
bool wantQuit = false;


int main (int argc, char *argv[]) {

    printf("Welcome to Connect4!\n");

    while (!wantQuit) {

        std::string state = connect4_helper::printGameState(&game);
        printf("%s", state.c_str());

        int currentPlayer = game.getCurrentPlayer();

        printf("Player %d, what's your move? (Enter a column between 1 and 7)\n", currentPlayer);
        std::string input = connect4_helper::getInputText();

        if (input.compare("quit") == 0) {
            wantQuit = true;
        } else {

            int col = atoi(input.c_str());
            game.makePlay(currentPlayer, col);

            if (game.isGameOver()) {

                std::string state = connect4_helper::printGameState(&game);
                printf("%s", state.c_str());

                int winner = game.getWinner();
                printf("Congratulations, player %d wins!\n", winner);
                wantQuit = true;

            }

        }

    }

    return 0;

}
