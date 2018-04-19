#include "Level.h"
#include "Player.h"
#include "Wall.h"
#include "Loot.h"
#include "Floor.h"
#include "Ceiling.h"
#include "Skybox.h"
#include "Enemy.h"
#include "RedKey.h"
#include "RedDoor.h"
#include "BlueKey.h"
#include "BlueDoor.h"
#include "YellowKey.h"
#include "WallHalf.h"
#include "GameState.h"
#include "StateManager.h"

Level::Level(string name)
{
	levelName = name;
	maxCoins = 0;
}

void Level::setLevelMap(int level[20][20]) {

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			levelMap[i][j] = level[i][j];
		}
	}
}

string Level::getLevelName() {
	return levelName;
}

void Level::reloadLevel() {

	maxCoins = 0;
	((GameState*)GetStateManager()->getCurrentState())->setRedKey(false);
	((GameState*)GetStateManager()->getCurrentState())->setBlueKey(false);
	((GameState*)GetStateManager()->getCurrentState())->setYellowKey(false);

	Floor* floor = new Floor("Floor", Vector3(9.5f, 0.0f, 9.5f), Vector3(0, 0, 0), Vector3(10, 1, 10));
	GetGameObjectManager()->addGameObject(floor);

	Ceiling* ceiling = new Ceiling("Ceiling", Vector3(9.5f, 2.0f, 9.5f), Vector3(PI, 0, 0), Vector3(10, 1, 10));
	GetGameObjectManager()->addGameObject(ceiling);

	//For every space in the level
	for (int i(0); i < 20; i++)
	{
		for (int j(0); j < 20; j++)
		{
			switch (levelMap[i][j])
			{
			case 0: {
				break;
			}
			case 1: { //Wall to be placed

				Wall* wall = new Wall("Wall", Vector3(i, 1.0f, j), Vector3(0, 0, 0), Vector3(0.5, 1.0, 0.5));
				GetGameObjectManager()->addGameObject(wall);

				break;
			}
			case 2: { 
					 	//Place player
				((GameState*)GetStateManager()->getCurrentState())->getPlayer()->Initialise(i, j);
				break;
			}
			case 3: { //Loot to be placed
				Loot* loot = new Loot("Loot", Vector3(i, 0.3f, j), Vector3(-PI/2, 0, 0), Vector3(0.02, 0.02, 0.02));
				GetGameObjectManager()->addGameObject(loot);

				maxCoins++;
				break;

			}
			case 4: { //Enemy to be placed
				Enemy* enemy = new Enemy("Enemy", Vector3(i, 0.5f, j), Vector3(0, 0, 0), Vector3(0.1f, 0.1f, 0.1f));
				GetGameObjectManager()->addGameObject(enemy);
				break;
			}
			case 5: { //RedKey to be placed
				RedKey* redKey = new RedKey("RedKey", Vector3(i, 0.3f, j), Vector3(0, 0, PI/2), Vector3(0.0005, 0.0005, 0.0005));
				GetGameObjectManager()->addGameObject(redKey);
				((GameState*)GetStateManager()->getCurrentState())->setRedKey(true);
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
			case 7: { //BlueKey to be placed
				BlueKey* blueKey = new BlueKey("BlueKey", Vector3(i, 0.3f, j), Vector3(0, 0, PI/2), Vector3(0.0005, 0.0005, 0.0005));
				GetGameObjectManager()->addGameObject(blueKey);
				((GameState*)GetStateManager()->getCurrentState())->setBlueKey(true);
				break;
			}
			case 8: { //Door to be placed
				BlueDoor* blueDoor = new BlueDoor("BlueDoor", Vector3(i - 0.45f, 0.5f, j), Vector3(0, 0, 0), Vector3(0.05, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(blueDoor);

				//Place wall above door
				WallHalf* wallHalf = new WallHalf("WallHalf", Vector3(i, 1.5f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(wallHalf);
				break;
			}
			case 9: { //Door to be placed
				ReturnBox* returnBox = new ReturnBox("ReturnBox", Vector3(i, 0.13f, j), Vector3(0, -(PI / 2), 0), Vector3(0.05, 0.05, 0.05));
				GetGameObjectManager()->addGameObject(returnBox);
				break;
			}
			case 10: { //YellowKey to be placed
				YellowKey* yellowKey = new YellowKey("YellowKey", Vector3(i, 0.3f, j), Vector3(0, 0, PI / 2), Vector3(0.0005, 0.0005, 0.0005));
				GetGameObjectManager()->addGameObject(yellowKey);
				((GameState*)GetStateManager()->getCurrentState())->setYellowKey(true);
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