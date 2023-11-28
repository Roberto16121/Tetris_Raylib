#include "save.h"


Save::Save()
{
	strcpy_s(my_document,"C:/Users/Public/Documents/save.data");
}

int Save::GetHighScore()
{
	int highScore=0;
	std::fstream file;
	file.open(my_document, std::ios::in | std::ios::out);
	file >> highScore;
	file.close();
	if (highScore != NULL)
		return highScore;
	else return 0;
}

void Save::SaveGame(int score)
{
	std::remove(my_document);
	std::fstream file;
	file.open(my_document, std::ios::in | std::ios::out | std::ios::trunc);
	file << score;
	file.close();
}

