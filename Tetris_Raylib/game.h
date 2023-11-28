#pragma once
#include "grid.h"
#include "blocks.cpp"
#include "save.h"

class Game
{
public:
	Game();
	void Draw();
	void HandleInput();
	void MoveBlockDown();
	int score;
	int hightScore;
	bool GameOver;

private:
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void MoveBlockLeft();
	void MoveBlockRight();
	bool IsBlockOutside();
	void RotateBlock();
	void LockBlock();
	bool BlockFits();
	void Reset();
	void UpdateScore(int linesCleared, int moveDownPoints);
	std::vector<Block> blocks;
	Block curentBlock;
	Block nextBlock;
	Grid grid;
	Save save;
};