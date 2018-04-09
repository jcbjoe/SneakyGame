#include "Level.h"

#include "Player.h"
#include "Wall.h"
#include "Loot.h"
#include "Floor.h"
#include "Skybox.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"

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
				Key* key = new Key("Key", Vector3(i, 0.3f, j), Vector3(0, 0, 0), Vector3(0.02, 0.1, 0.1));
				GetGameObjectManager()->addGameObject(key);

				//Place floor
				Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(floor);
				break;
			}

			case 6: { //Door to be placed
				Door* door = new Door("Door", Vector3(i, 0.5f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(door);

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