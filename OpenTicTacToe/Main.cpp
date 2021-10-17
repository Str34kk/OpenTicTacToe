#include <SFML/Graphics.hpp>

#include "SFWindow.h"

int main()
{
    GameLogic gameLogic;
    SFWindow sFWindow(gameLogic);

    while (sFWindow.getWindowIsOpen())
    {
        sFWindow.update();
        sFWindow.render();
    }
    return 0;
}