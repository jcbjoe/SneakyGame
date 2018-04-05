#include "Level.h"


Level::Level(string name)
{

	levelName = name;


}

void Level::setLevelMap(int level[10][10]) {
	for (int i = 10; i < 10; i++) {
		for (int j = 10; j < 10; j++) {
			levelMap[i][j] = level[i][j];
		}
	}
}