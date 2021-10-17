#include "GameLogic.h"

void GameLogic::initVeriables()
{
	this->turnX = true;
	this->endGame = false;
}

GameLogic::GameLogic()
{
	this->initVeriables();
}

GameLogic::~GameLogic()
{
}
