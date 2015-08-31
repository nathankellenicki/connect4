#include <string>

class connect4 {

    private:
        int numPlayers;
        int currentPlayer;
        bool gameOver;

        int boardState[7][6];
        int rowCounter[7];

        bool checkForWin (int player, int col, int row);
        bool checkDirection (int player, int col, int row, int moveCol, int moveRow);

    public:
        connect4 (int numPlayers = 2);
        void reset ();
        int getStateAtPosition (int col, int row);
        int getCurrentPlayer ();
        int getWinner ();
        bool isGameOver ();
        void makePlay (int player, int col);

};