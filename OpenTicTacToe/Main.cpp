#include <SFML/Graphics.hpp>
#include <iostream>

int clickx = 0, clicky = 0, moveNumber = 0;
int gridSize = 3;
int gameScore[3][3];
int tableScore[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
bool turnX = true, endGame = false;

void checkForWinner() {
    for (int i = 0; i < gridSize+2;i++)
    {
        if (tableScore[i] == gridSize)
        {
            std::cout << "X win";
            endGame = true;
            break;
        }else if (tableScore[i] == -gridSize)
        {
            std::cout << "O win";
            endGame = true;
            break;
        }
    }
}
void updateTableScore(int col, int row, int score) {
    tableScore[col] += score;
    tableScore[gridSize + row] += score;
    if (row == col) tableScore[2 * gridSize] += score;
    if (gridSize - 1 - col == row) tableScore[2 * gridSize + 1] += score;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "Open Tic Tac Toe");
    window.setFramerateLimit(25);
    sf::Texture tablet;
    sf::Texture sprite;
    tablet.loadFromFile("Sprites/table.png");
    sprite.loadFromFile("Sprites/sprite.png");
    sf::Sprite table(tablet);
    sf::Sprite x1(sprite), x2(sprite), x3(sprite), o1(sprite), o2(sprite), o3(sprite);

    x1.setTextureRect(sf::IntRect(0, 0, 200, 200));
    x2.setTextureRect(sf::IntRect(200, 0, 200, 200));
    x3.setTextureRect(sf::IntRect(400, 0, 200, 200));
    o1.setTextureRect(sf::IntRect(0, 200, 200, 200));
    o2.setTextureRect(sf::IntRect(200, 200, 200, 200));
    o3.setTextureRect(sf::IntRect(400, 200, 200, 200));
    
    sf::Sprite o[3] = { o1, o2, o3 };
    sf::Sprite x[3] = { x1, x2, x3 };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
            {
                clickx = event.mouseMove.x;
                clicky = event.mouseMove.y;
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                for (int i = 0; i < gridSize; i++)
                {
                    for (int j = 0; j < gridSize; j++)
                    {
                        if (!endGame &&
                            turnX && 
                            gameScore[i][j] == 0 && 
                            clickx > (i * 200) && 
                            clickx < 200 + (i * 200) && 
                            clicky > (j * 200) && 
                            clicky < 200 + (j * 200))
                        {
                            gameScore[i][j] = 1;
                            updateTableScore(i, j, 1);
                            moveNumber += 1;
                            if (moveNumber > 4) checkForWinner();
                            turnX = false;
                        }
                        else if (!endGame &&
                            !turnX &&
                            gameScore[i][j] == 0 &&
                            clickx > (i * 200) &&
                            clickx < 200 + (i * 200) &&
                            clicky >(j * 200) &&
                            clicky < 200 + (j * 200))
                        {
                            gameScore[i][j] = -1;
                            updateTableScore(i, j, -1);
                            moveNumber += 1;
                            if (moveNumber > 4) checkForWinner();
                            turnX = true;
                        }
                    }
                }
            }
        }
         
        window.clear();
        window.draw(table);
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                if (gameScore[i][j] == 1 )
                {
                    x[0].setPosition((i * 200), (j * 200));
                    window.draw(x[0]);
                } else if (gameScore[i][j] == -1)
                {
                    o[0].setPosition((i * 200), (j * 200));
                    window.draw(o[0]);
                }
            }
        }
        window.display();
    }

    return 0;
}