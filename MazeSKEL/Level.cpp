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

void Level::reloadLevel(Player gPlayer) {
	//For every space in the level
	for (int i(0); i < 10; i++)
	{
		for (int j(0); j < 10; j++)
		{
			switch (levelMap[i][j])
			{
			case 0: {//Floor to be placed
				Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(floor);
				break;
			}

			case 1: { //Wall to be placed

				Wall* wall = new Wall("Wall", Vector3(i, 0.5f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(wall);

				break;
			}

			case 2: {
				//Place camera
				gPlayer.Initialise(i, j);
				//Place floor
				Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(floor);
				break;
			}

			case 3: { //Loot to be placed
				Loot* loot = new Loot("Loot", Vector3(i, 0.3f, j), Vector3(0, 0, 0), Vector3(0.02, 0.1, 0.1));
				GetGameObjectManager()->addGameObject(loot);

				//Place floor
				Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(floor);
				break;

			}

			case 4: { //Enemy to be placed
				Enemy* enemy = new Enemy("Enemy", Vector3(i, 0.5f, j), Vector3(0, 0, 0), Vector3(0.1f, 0.1f, 0.1f));
				GetGameObjectManager()->addGameObject(enemy);

				//Place floor
				Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(floor);
				break;
			}

			case 5: { //Key to be placed
				RedKey* redKey = new RedKey("RedKey", Vector3(i, 0.3f, j), Vector3(0, 0, 0), Vector3(0.02, 0.1, 0.1));
				GetGameObjectManager()->addGameObject(redKey);

				//Place floor
				Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(floor);
				break;
			}

			case 6: { //Door to be placed
				RedDoor* redDoor = new RedDoor("RedDoor", Vector3(i, 0.5f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(redDoor);

				//Place wall above door
				WallHalf* wallHalf = new WallHalf("WallHalf", Vector3(i, 1.5f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(wallHalf);

				//Place floor
				Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(floor);
				break;
			}

			case 7: { //Key to be placed
				BlueKey* blueKey = new BlueKey("BlueKey", Vector3(i, 0.3f, j), Vector3(0, 0, 0), Vector3(0.02, 0.1, 0.1));
				GetGameObjectManager()->addGameObject(blueKey);

				//Place floor
				Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(floor);
				break;
			}

			case 8: { //Door to be placed
				BlueKey* blueKey = new BlueKey("BlueKey", Vector3(i, 0.5f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(blueKey);

				//Place wall above door
				WallHalf* wallHalf = new WallHalf("WallHalf", Vector3(i, 1.5f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(wallHalf);

				//Place floor
				Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(floor);
				break;
			}
			}
		}
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