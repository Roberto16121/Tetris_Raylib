#include <iostream>
#include "grid.h"
#include "colors.h"

Grid::Grid()
{
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	colors = GetCellColors();
	Init();
}

void Grid::Init()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
			grid[i][j] = 0;
	}
}

void Grid::Print()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
			std::cout << grid[i][j] << " ";
		std::cout << std::endl;
	}
}


void Grid::Draw()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			int cellValue = grid[i][j];
			DrawRectangle(j * cellSize + 11, i * cellSize + 11, cellSize-1, cellSize-1, colors[cellValue]);
		}
	}
}

bool Grid::IsCellOutside(int row, int column)
{
	if (row >= 0 && row < numRows && column >= 0 && column < numCols)
	{
		return false;
	}
	return true;
}

bool Grid::IsCellEmpty(int row, int col)
{
	if (grid[row][col] == 0)
		return true;

	return false;
}

int Grid::ClearFullRows()
{
	int completed = 0;
	for (int row = numRows - 1; row >= 0; row--)
	{
		if (IsRowFull(row))
		{
			ClearRow(row);
			completed++;
		}
		else if (completed > 0)
		{
			MoveRowDown(row, completed);
		}
	}
	
	return completed;
}

bool Grid::IsRowFull(int row)
{
	for (int col = 0; col < numCols; col++)
	{
		if (grid[row][col] == 0)
			return false;
	}

	return true;
}

void Grid::ClearRow(int row)
{
	for (int col = 0; col < numCols; col++)
	{
		grid[row][col] = 0;
	}
}

void Grid::MoveRowDown(int row, int numRows)
{
	for (int col = 0; col < numCols; col++)
	{
		grid[row + numRows][col] = grid[row][col];
		grid[row][col] = 0;
	}
}
