#include <string>

#ifndef CONNECT_4
#define CONNECT_4
#include "connect4.h"
#endif

class connect4_helper {

public:
    static std::string getInputText ();
    static std::string printGameState (connect4 *game);

};