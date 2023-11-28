#include "game.h"
#include <random>

Game::Game()
{
	grid = Grid();
	blocks = GetAllBlocks();
	curentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	GameOver = false;
	score = 0;
	save = Save();
	hightScore = save.GetHighScore();
}

Block Game::GetRandomBlock()
{
	if (blocks.size() == 0)
	{
		blocks = GetAllBlocks();
	}
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	
	return block;
}

std::vector<Block> Game::GetAllBlocks()
{
	return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void Game::Draw()
{
	grid.Draw();
	curentBlock.Draw(11, 11);
	switch (nextBlock.id)
	{
		case 3:
		{
			nextBlock.Draw(255, 340);
		}break;
		case 4:
		{
			nextBlock.Draw(255, 330);
		}break;
		default:
		{
			nextBlock.Draw(270, 320);
		}break;
	}
	
}

void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();
	if (GameOver && keyPressed != 0)
	{
		Reset();
		return;
	}

	switch (keyPressed)
	{
	case KEY_A:
	case KEY_LEFT:
	{
		MoveBlockLeft();
	}break;
	case KEY_D:
	case KEY_RIGHT:
	{
		MoveBlockRight();
	}break;
	case KEY_S:
	case KEY_DOWN:
	{
		MoveBlockDown();
		UpdateScore(0, 1);
	}break;
	case KEY_W:
	case KEY_UP:
	{
		RotateBlock();
	}break;
	default:
		break;
	}
}

void Game::MoveBlockLeft()
{
	if (GameOver)
		return;
	curentBlock.Move(0, -1);
	if (IsBlockOutside() || BlockFits() == false)
	{
		curentBlock.Move(0, 1);
	}
}

void Game::MoveBlockRight()
{
	if (GameOver)
		return;
	curentBlock.Move(0, 1);
	if (IsBlockOutside() || BlockFits() == false)
	{
		curentBlock.Move(0, -1);
	}
}

void Game::MoveBlockDown()
{
	if (GameOver)
		return;
	curentBlock.Move(1, 0);
	if (IsBlockOutside() || BlockFits() == false)
	{
		curentBlock.Move(-1, 0);
		LockBlock();
	}
}

bool Game::IsBlockOutside()
{
	std::vector <Position> tiles = curentBlock.GetCellPosition();
	for (Position item : tiles)
	{
		if (grid.IsCellOutside(item.row, item.col))
		{
			return true;
		}
	}
	return false;
}

void Game::RotateBlock()
{
	curentBlock.Rotate();
	if (IsBlockOutside() || !BlockFits())
		curentBlock.UndoRotate();
}

void Game::LockBlock()
{
	std::vector<Position> tiles = curentBlock.GetCellPosition();
	for (Position item : tiles)
	{
		grid.grid[item.row][item.col] = curentBlock.id;
	}
	curentBlock = nextBlock;
	if (BlockFits() == false)
	{
		GameOver = true;
	}
	nextBlock = GetRandomBlock();
	int rowsCleared = grid.ClearFullRows();
	UpdateScore(rowsCleared, 0);
}

bool Game::BlockFits()
{
	std::vector<Position> tiles = curentBlock.GetCellPosition();
	for (Position item : tiles)
	{
		if (grid.IsCellEmpty(item.row, item.col) == false)
			return false;
	}
	return true;
}

void Game::Reset()
{
	if (score > hightScore)
		hightScore = score;
	save.SaveGame(hightScore);
	grid.Init();
	GameOver = false;
	score = 0;
	blocks = GetAllBlocks();
	curentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
	switch (linesCleared)
	{
	case 1:
	{
		score += 100;
	}break;
	case 2:
	{
		score += 300;
	}break;
	case 3:
	{
		score += 500;
	}break;
	case 4:
	{
		score += 800;
	}
	default:
		break;
	}
	score += moveDownPoints;
	
}
