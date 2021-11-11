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

SFWindow::SFWindow(GameLogic& _gameLogic, Net& _neuralNet) : neuralNet(topology)
{
	initVeriables();
	initWindow();

    gameLogic = _gameLogic;
    neuralNet = _neuralNet;

    std::cout << "Net recent average error: " << neuralNet.getRecentAverageError() << std::endl;
}

SFWindow::~SFWindow()
{
	delete window;
}

void SFWindow::render()
{
    window->clear();
    window->draw(table);
    int posiotionInGrid;
    for (int i = 0; i < gameLogic.gridSize; i++)
    {
        for (int j = 0; j < gameLogic.gridSize; j++)
        {
            posiotionInGrid = i * gameLogic.gridSize + j;
            if (gameLogic.gameScore[posiotionInGrid] == 1)
            {
                x[0].setPosition((i * 200), (j * 200));
                window->draw(x[0]);
            }
            else if (gameLogic.gameScore[posiotionInGrid] == -1)
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

void SFWindow::AIMove()
{
    std::vector<double> inputVals, targetVals, resultVals;
    neuralNet.feedForward(gameLogic.gameScore);
    neuralNet.getResults(resultVals);

    int AIChoice = helpers.largest_element_index(resultVals, gameLogic.gameScore);
    helpers.showVectorVals("resultVals: ", resultVals);

    gameLogic.updateTableScore(AIChoice);
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

        if (!gameLogic.endGame && gameLogic.gameScore.back() == 1)
        {
            AIMove();
            if (gameLogic.moveNumber > 4) gameLogic.checkForWinner();
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            int posiotionInGrid;
            for (int i = 0; i < gameLogic.gridSize; i++)
            {
                for (int j = 0; j < gameLogic.gridSize; j++)
                {
                    posiotionInGrid = i * gameLogic.gridSize + j;
                    if (!gameLogic.endGame &&
                        gameLogic.gameScore.back() == 1 &&
                        gameLogic.gameScore[posiotionInGrid] == 0 &&
                        mousePosition.x > (i * 200) &&
                        mousePosition.x < 200 + (i * 200) &&
                        mousePosition.y >(j * 200) &&
                        mousePosition.y < 200 + (j * 200))
                    {
                        gameLogic.updateTableScore(posiotionInGrid);
                        if (gameLogic.moveNumber > 4) gameLogic.checkForWinner();
                    }
                    else if (!gameLogic.endGame &&
                        gameLogic.gameScore.back() == -1 &&
                        gameLogic.gameScore[posiotionInGrid] == 0 &&
                        mousePosition.x > (i * 200) &&
                        mousePosition.x < 200 + (i * 200) &&
                        mousePosition.y >(j * 200) &&
                        mousePosition.y < 200 + (j * 200))
                    {
                        gameLogic.updateTableScore(posiotionInGrid);
                        if (gameLogic.moveNumber > 4) gameLogic.checkForWinner();
                    }
                }
            }
        }
    }
}