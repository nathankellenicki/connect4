#include "connect4_helper.h"
#include <iostream>
#include <string>
#include <sstream>

#ifndef CONNECT_4
#define CONNECT_4
#include "connect4.h"
#endif

std::string connect4_helper::getInputText () {

    char input[256];

    scanf("%256s", input);

    return std::string(input);

}


std::string connect4_helper::printGameState (connect4 *game) {

    std::stringstream output;

    output << "\n-----------------\n";

    for (int row = 5; row >= 0; row--) {

        output << "| ";

        for (int col = 0; col < 7; col++) {

            int player = game->getStateAtPosition(col, row);

            if (player == 0) {
                output << " ";
            } else {
                output << player;
            }

            output << " ";

        }

        output << "|\n";

    }

    output << "-----------------\n";
    output << "  1 2 3 4 5 6 7  \n\n";

    return output.str();

}