#include "Level1.h"

Level1::Level1(string name): Level(name) {

	int level[10][10] =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 3, 0, 0, 0, 0, 0, 0, 4, 1 },
		{ 1, 6, 5, 1, 0, 1, 0, 6, 0, 1 },
		{ 1, 0, 0, 1, 1, 1, 0, 5, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 3, 0, 0, 0, 1 },
		{ 1, 3, 0, 3, 0, 6, 5, 2, 0, 1 },
		{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	setLevelMap(level);
}

void Level1::Release() {

}