#include "Level1.h"
#include "GameObjectManager.h"

Level1::Level1(string name): Level(name) {

	int level[10][10] =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 3, 0, 0, 0, 0, 0, 0, 4, 1 },
		{ 1, 6, 0, 1, 0, 1, 0, 8, 0, 1 },
		{ 1, 0, 0, 1, 1, 1, 0, 7, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 3, 0, 0, 0, 1 },
		{ 1, 3, 0, 3, 0, 6, 5, 2, 0, 1 },
		{ 1, 0, 0, 0, 1, 1, 0, 0, 9, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};


	setLevelMap(level);

	std::vector<Vector3> waypointLocations = 
	{
		Vector3(8, 0.4, 6),
		Vector3(7, 0.4, 6),
		Vector3(7, 0.4, 1),
		Vector3(4, 0.4, 1),
		Vector3(4, 0.4, 7),
		Vector3(5, 0.4, 7),
		Vector3(5, 0.4, 8),
		Vector3(8, 0.4, 8 )
	};

	addWaypointLocation(Vector3(8, 0.4, 6));

	int count(1);
	for (Vector3 vec : waypointLocations) {
		addWaypointLocation(vec);
	}
}

void Level1::Release() {

}