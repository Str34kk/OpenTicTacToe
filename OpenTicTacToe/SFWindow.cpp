#include "SFWindow.h"

void SFWindow::initVeriables()
{
	window = nullptr;
    tablet.loadFromFile("Sprites/table.png");
    sprite.loadFromFile("Sprites/sprite.png");
    table.setTexture(tablet);

    x1.setTexture(sprite);
    x2.setTexture(sprite);
    x3.setTexture(sprite);
    o1.setTexture(sprite);
    o2.setTexture(sprite);
    o3.setTexture(sprite);
    x1.setTextureRect(sf::IntRect(0, 0, 200, 200));
    x2.setTextureRect(sf::IntRect(200, 0, 200, 200));
    x3.setTextureRect(sf::IntRect(400, 0, 200, 200));
    o1.setTextureRect(sf::IntRect(0, 200, 200, 200));
    o2.setTextureRect(sf::IntRect(200, 200, 200, 200));
    o3.setTextureRect(sf::IntRect(400, 200, 200, 200));

    o = { o1, o2, o3 };
    x = { x1, x2, x3 };
}

void SFWindow::initWindow()
{
	videoMode.width = 600;
	videoMode.height = 600;
	window = new sf::RenderWindow(videoMode, "Open Tic Tac Toe");
	window->setFramerateLimit(25);
}

SFWindow::SFWindow(GameLogic _gameLogic)
{
	initVeriables();
	initWindow();

    gameLogic = _gameLogic;
}

SFWindow::~SFWindow()
{
	delete window;
}

void SFWindow::render()
{
    window->clear();
    window->draw(table);
    for (int i = 0; i < gameLogic.gridSize; i++)
    {
        for (int j = 0; j < gameLogic.gridSize; j++)
        {
            if (gameLogic.gameScore[i][j] == 1)
            {
                x[0].setPosition((i * 200), (j * 200));
                window->draw(x[0]);
            }
            else if (gameLogic.gameScore[i][j] == -1)
            {
                o[0].setPosition((i * 200), (j * 200));
                window->draw(o[0]);
            }
        }
    }
    window->display();
}

void SFWindow::update()
{
    updateEvents();
}

const bool SFWindow::getWindowIsOpen() const
{
    return window->isOpen();
}

void SFWindow::updateEvents()
{
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();

        if (event.type == sf::Event::MouseMoved)
        {
            mousePosition.x = event.mouseMove.x;
            mousePosition.y = event.mouseMove.y;
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            for (int i = 0; i < gameLogic.gridSize; i++)
            {
                for (int j = 0; j < gameLogic.gridSize; j++)
                {
                    if (!gameLogic.endGame &&
                        gameLogic.turnX &&
                        gameLogic.gameScore[i][j] == 0 &&
                        mousePosition.x > (i * 200) &&
                        mousePosition.x < 200 + (i * 200) &&
                        mousePosition.y >(j * 200) &&
                        mousePosition.y < 200 + (j * 200))
                    {
                        gameLogic.gameScore[i][j] = 1;
                        gameLogic.updateTableScore(i, j, 1);
                        gameLogic.moveNumber += 1;
                        if (gameLogic.moveNumber > 4) gameLogic.checkForWinner();
                        gameLogic.turnX = false;
                    }
                    else if (!gameLogic.endGame &&
                        !gameLogic.turnX &&
                        gameLogic.gameScore[i][j] == 0 &&
                        mousePosition.x > (i * 200) &&
                        mousePosition.x < 200 + (i * 200) &&
                        mousePosition.y >(j * 200) &&
                        mousePosition.y < 200 + (j * 200))
                    {
                        gameLogic.gameScore[i][j] = -1;
                        gameLogic.updateTableScore(i, j, -1);
                        gameLogic.moveNumber += 1;
                        if (gameLogic.moveNumber > 4) gameLogic.checkForWinner();
                        gameLogic.turnX = true;
                    }
                }
            }
        }
    }
}