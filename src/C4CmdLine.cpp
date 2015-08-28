#include "C4CmdLine.h"
#include <iostream>
#include <string>

#ifndef CONNECT_4
#define CONNECT_4
#include "Connect4.h"
#endif

std::string C4CmdLine::getInputText () {

    char input[256];

    scanf("%256s", input);

    return std::string(input);

}


void C4CmdLine::printGameState (Connect4 *game) {

    printf("\n---------\n");

    for (int row = 5; row >= 0; row--) {

        printf("|");

        for (int col = 0; col < 7; col++) {
            printf("%d", game->getStateAtPosition(col, row));
        }

        printf("|\n");

    }

    printf("---------\n\n");

}