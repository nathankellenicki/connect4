#ifndef CONNECT_4
#define CONNECT_4
#include "connect4.h"
#endif

#include <algorithm>


connect4::connect4 (int numPlayers) {

    this->numPlayers = numPlayers;
    this->reset();

}


void connect4::reset () {

    this->currentPlayer = 1;
    this->gameOver = false;

    std::fill(this->rowCounter, this->rowCounter + 7, 0);

    for (int i = 0; i < 7; i++) {
        std::fill(this->boardState[i], this->boardState[i] + 6, 0);
    }

}


int connect4::getStateAtPosition (int col, int row) {
    return this->boardState[col][row];
}


int connect4::getCurrentPlayer () {
    return this->currentPlayer;
}


bool connect4::isGameOver () {
    return this->gameOver;
}


int connect4::getWinner () {

    if (!this->isGameOver()) {
        return 0; // Game isn't over yet (TODO: Throw)
    }

    return this->currentPlayer;
}


void connect4::makePlay (int player, int col) {

    col--;

    if (this->isGameOver()) {
        return; // Game is over (TODO: Throw)
    }

    if (player > this->numPlayers) {
        return; // Invalid player (TODO: Throw)
    }

    if (player != this->getCurrentPlayer()) {
        return; // Not current player (TODO: Throw)
    }

    if (col > 6) {
        return; // Invalid column (TODO: Throw)
    }

    int *row = &this->rowCounter[col];

    if (*row >= 6) {
        return; // Already reached the top (TODO: Throw)
    }

    this->boardState[col][*row] = player;

    bool hasWon = this->checkForWin(player, col, *row);

    if (hasWon) {

        this->gameOver = true;
        return;

    }

    (*row)++;
    this->currentPlayer++;

    if (this->currentPlayer > numPlayers) {
        this->currentPlayer = 1;
    }

    return;

}


bool connect4::checkDirection (int player, int col, int row, int colIncr, int rowIncr) {

    if ((col + (3 * colIncr)) < 0 || (row + (3 * rowIncr)) < 0) { // Check bounds
        return false;
    }

    int colPos = col;
    int rowPos = row;

    for (int i = 0; i < 4; i++) {

        if (this->boardState[colPos][rowPos] != player) {
            return false;
        } else {

            colPos = colPos + colIncr;
            rowPos = rowPos + rowIncr;

        }

    }

    return true;

}


bool connect4::checkForWin (int player, int col, int row) {

    for (int colIncr = -1; colIncr <= 1; colIncr++) {
        for (int rowIncr = -1; rowIncr <= 1; rowIncr++) {

            if (!(colIncr == 0 && rowIncr == 0)) {

                bool hasWon = this->checkDirection(player, col, row, colIncr, rowIncr);

                if (hasWon) {
                    return true;
                }

            }

        }
    }

    return false;

}