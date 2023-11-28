#pragma once
#include <fstream>

class Save
{
public:
	Save();
	int GetHighScore();
	void SaveGame(int score);
private:
	char my_document[200] = "";
};