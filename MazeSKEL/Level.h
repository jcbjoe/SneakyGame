#ifndef LEVEL_H
#define LEVEL_H

#include <string>

using namespace std;

class Level
{
public:
	Level(string levelName);

	void setLevelMap(int[10][10]);

	int getObjectAtCoordinate(int x, int y) { return levelMap[x][y]; }

	string getLevelName();

private:

	string levelName;

	int levelMap[10][10];
};


#endif