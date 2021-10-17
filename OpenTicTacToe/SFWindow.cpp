#include "SFWindow.h"

void SFWindow::initVeriables()
{
	this->window = nullptr;
}

void SFWindow::initWindow()
{
	this->videoMode.width = 600;
	this->videoMode.height = 600;
	this->window = new sf::RenderWindow(this->videoMode, "Open Tic Tac Toe");
	this->window->setFramerateLimit(25);
}

SFWindow::SFWindow()
{
	this->initVeriables();
	this->initWindow();
}

SFWindow::~SFWindow()
{
	delete this->window;
}

void SFWindow::render()
{
    this->window->clear();
    this->window->draw(table);
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (gameScore[i][j] == 1)
            {
                x[0].setPosition((i * 200), (j * 200));
                this->window->draw(x[0]);
            }
            else if (gameScore[i][j] == -1)
            {
                o[0].setPosition((i * 200), (j * 200));
                this->window->draw(o[0]);
            }
        }
    }
    this->window->display();
}

void SFWindow::update()
{
}

void SFWindow::updateEvents()
{
}
