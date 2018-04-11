#include "Level.h"

#include "Player.h"
#include "Wall.h"
#include "Loot.h"
#include "Floor.h"
#include "Skybox.h"
#include "Enemy.h"
#include "RedKey.h"
#include "RedDoor.h"
#include "BlueKey.h"
#include "BlueDoor.h"
#include "WallHalf.h"
#include "GameState.h"
#include "StateManager.h"

Level::Level(string name)
{

	levelName = name;


}

void Level::setLevelMap(int level[10][10]) {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			levelMap[i][j] = level[i][j];
		}
	}
}

string Level::getLevelName() {
	return levelName;
}

void Level::reloadLevel() {
	//For every space in the level
	for (int i(0); i < 10; i++)
	{
		for (int j(0); j < 10; j++)
		{
			switch (levelMap[i][j])
			{
			case 0: {//Floor to be placed
				Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0, 0, 0), Vector3(5, 1, 5));
				GetGameObjectManager()->addGameObject(floor);
				break;
			}

			case 1: { //Wall to be placed

				Wall* wall = new Wall("Wall", Vector3(i, 0.5f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(wall);

				break;
			}

			case 2: { //Player to be place
					 	//Place camera
				((GameState*)GetStateManager()->getCurrentState())->getPlayer()->Initialise(i, j);
				break;
			}

			case 3: { //Loot to be placed
				Loot* loot = new Loot("Loot", Vector3(i, 0.3f, j), Vector3(-45, 0, 0), Vector3(0.02, 0.02, 0.02));
				GetGameObjectManager()->addGameObject(loot);
				break;

			}

			case 4: { //Enemy to be placed
				Enemy* enemy = new Enemy("Enemy", Vector3(i, 0.5f, j), Vector3(0, 0, 0), Vector3(0.1f, 0.1f, 0.1f));
				GetGameObjectManager()->addGameObject(enemy);
				break;
			}

			case 5: { //Key to be placed
				RedKey* redKey = new RedKey("RedKey", Vector3(i, 0.3f, j), Vector3(0, 0, 0), Vector3(0.02, 0.1, 0.1));
				GetGameObjectManager()->addGameObject(redKey);
				break;
			}

			case 6: { //Door to be placed
				RedDoor* redDoor = new RedDoor("RedDoor", Vector3(i, 0.5f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.1));
				GetGameObjectManager()->addGameObject(redDoor);

				//Place wall above door
				WallHalf* wallHalf = new WallHalf("WallHalf", Vector3(i, 1.5f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(wallHalf);
				break;
			}
			case 7: { //Key to be placed
				BlueKey* blueKey = new BlueKey("BlueKey", Vector3(i, 0.3f, j), Vector3(0, 0, 0), Vector3(0.02, 0.1, 0.1));
				GetGameObjectManager()->addGameObject(blueKey);
				break;
			}

			case 8: { //Door to be placed
				BlueDoor* blueDoor = new BlueDoor("BlueDoor", Vector3(i, 0.5f, j), Vector3(0, 0, 0), Vector3(0.1, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(blueDoor);

				//Place wall above door
				WallHalf* wallHalf = new WallHalf("WallHalf", Vector3(i, 1.5f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(wallHalf);
				break;
			}
			case 9: { //Door to be placed
				ReturnBox* returnBox = new ReturnBox("ReturnBox", Vector3(i, 0.2f, j), Vector3(0, 0, 0), Vector3(0.2, 0.2, 0.4));
				GetGameObjectManager()->addGameObject(returnBox);
				break;
			}

			default:
				break;
			}
		}
	}

	int count(1);
	for (Vector3 loc : waypointLocations) {
		std::ostringstream oss;
		oss << "Waypoint" << count;
		GameObject* waypoint = new GameObject(oss.str(), loc, Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1), "cube", "waypoint.dds");
		GetGameObjectManager()->addGameObject(waypoint);
		count++;
	}
}

void Level::Release() {

}

int Level::getObjectAtWorldPos(float x, float y)
{
	x = round(x);
	y = round(y);

	return getObjectAtCoordinate(x, y);;
}

void Level::addWaypointLocation(Vector3 loc) {
	waypointLocations.push_back(loc);
}