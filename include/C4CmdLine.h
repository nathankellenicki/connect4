#include <string>

#ifndef CONNECT_4
#define CONNECT_4
#include "Connect4.h"
#endif

class C4CmdLine {

public:
    static std::string getInputText ();
    static void printGameState (Connect4 *game);

};