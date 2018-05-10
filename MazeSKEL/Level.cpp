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

//Base class for levels

//Constructor
Level::Level(string n, float t)
	: levelName(n), timer(t)
{}

//Initialise level to level map
void Level::setLevelMap(int level[levelSize][levelSize]) {

	// x and z are level axes
	for (int x = 0; x < 20; x++) {
		for (int z = 0; z < 20; z++) {
			levelMap[x][z] = level[x][z];
		}
	}
}

//Return level name
string Level::getLevelName() {
	return levelName;
}

//Load a level
void Level::reloadLevel() {

	maxCoins = 0;		//Reset max coins to default amount of zero

	((GameState*)GetStateManager()->getCurrentState())->setRedKey(false);
	((GameState*)GetStateManager()->getCurrentState())->setBlueKey(false);
	((GameState*)GetStateManager()->getCurrentState())->setYellowKey(false);		//Reset all keys to be not collected

	Floor* floor = new Floor("Floor", Vector3(9.5f, 0.0f, 9.5f), Vector3(0, 0, 0), Vector3(10, 1, 10));
	GetGameObjectManager()->addGameObject(floor);									//Create the floor, one large piece

	Ceiling* ceiling = new Ceiling("Ceiling", Vector3(9.5f, 2.0f, 9.5f), Vector3(PI, 0, 0), Vector3(10, 1, 10));
	GetGameObjectManager()->addGameObject(ceiling);									//Create the ceiling, also one large piece

	//////////////////////////////////////////////
	//											//
	//		For every space in the level		//
	//											//
	//////////////////////////////////////////////
	// For terrain pieces:						//
	//											//
	// 00 = EMPTY SPACE							//
	// 01 = WALL								//
	// 02 = RED DOOR							//
	// 03 = BLUE DOOR						    //
	// 04 = YELLOW DOOR						    //
	//										    //
	// For collectables:					    //
	//										    //
	// 10 = RETURN BOX (WITH GOLD LIGHT)	    //
	// 11 = COIN							    //
	// 12 = RED KEY (WITH RED LIGHT)		    //
	// 13 = BLUE KEY (WITH BLUE LIGHT)		    //
	// 14 = YELLOW KEY (WITH YELLOW LIGHT~)	    //
	//										    //
	// For lighting:						    //
	//										    //
	//										    //
	// For the player:						    //
	//										    //
	// 30 = PLAYER							    //
	// 31 = ENEMY							    //
	//////////////////////////////////////////////


	// x and z are level axes (position)
	// Cycle through the level array and create objects depending on the table above, all objects added to a vector of gameobjects
	for (int x(0); x < 20; x++)
	{
		for (int z(0); z < 20; z++)
		{
			switch (levelMap[x][z])
			{
			case 00: //Empty
			{
				break;
			}
			case 01: //Wall
			{ 
				Wall* wall = new Wall("Wall", Vector3(x, 1.0f, z), Vector3(0, 0, 0), Vector3(0.5, 1.0, 0.5));
				GetGameObjectManager()->addGameObject(wall);
				break;
			}
			case 02: //Red Door
			{ 
				RedDoor* redDoor = new RedDoor("RedDoor", Vector3(x, 0.5f, z), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.1));
				GetGameObjectManager()->addGameObject(redDoor);

				//Half wall
				WallHalf* wallHalf = new WallHalf("WallHalf", Vector3(x, 1.5f, z), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(wallHalf);
				break;
			}
			case 03: //Blue Door
			{ 
				BlueDoor* blueDoor = new BlueDoor("BlueDoor", Vector3(x - 0.45f, 0.5f, z), Vector3(0, 0, 0), Vector3(0.05, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(blueDoor);

				//Half wall
				WallHalf* wallHalf = new WallHalf("WallHalf", Vector3(x, 1.5f, z), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(wallHalf);
				break;
			}
			case 04: //Yellow Door
			{
				//Half wall
				WallHalf* wallHalf = new WallHalf("WallHalf", Vector3(x, 1.5f, z), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(wallHalf);
				break;
			}
			case 10: //Return Box
			{ 
				Vector3 offset;

				if (levelMap[x + 1][z] != 01)
					offset = Vector3(0, PI, 0);
				else if (levelMap[x - 1][z] != 01)
					offset = Vector3(0, 0, 0);
				else if (levelMap[x][z + 1] != 01)
					offset = Vector3(0, (PI / 2), 0);
				else if (levelMap[x][z - 1] != 01)
					offset = Vector3(0, -(PI / 2), 0 );
					

				ReturnBox* returnBox = new ReturnBox("ReturnBox", Vector3(x, 0.13f, z), offset, Vector3(0.05, 0.05, 0.05));

				GetGameObjectManager()->addGameObject(returnBox);

				//Light 1 for collection box
				FX::SetupSpotLight(1, true, { (float)x, 2, (float)z }, { 0, -1, 0 }, Vector3(1.0f, 0.84f, 0.0f), Vector3(0.35f, 0.35f, 0.35f), Vector3(1.0f, 0.84f, 0.0f), 5.0f, 0.5f, D2R(15), D2R(45));
				break;
			}
			case 11: //Coin
			{ 
				Loot* loot = new Loot("Loot", Vector3(x, 0.3f, z), Vector3(-PI / 2, 0, 0), Vector3(0.02, 0.02, 0.02));
				GetGameObjectManager()->addGameObject(loot);

				maxCoins++;
				break;
			}
			case 12: //Red Key
			{ 
				RedKey* redKey = new RedKey("RedKey", Vector3(x, 0.3f, z), Vector3(0, 0, PI / 2), Vector3(0.0005, 0.0005, 0.0005));
				GetGameObjectManager()->addGameObject(redKey);

				//Light 2
				FX::SetupSpotLight(2, true, { (float)x, 1, (float)z }, { 0, -1, 0 }, Vector3(1.0f, 0.0f, 0.0f), Vector3(0.35f, 0.35f, 0.35f), Vector3(1.0f, 0.0f, 0.0f), 5.0f, 0.7f, D2R(15), D2R(30));

				((GameState*)GetStateManager()->getCurrentState())->setRedKey(true);
				break;
			}
			case 13: //Blue Key
			{ 
				BlueKey* blueKey = new BlueKey("BlueKey", Vector3(x, 0.3f, z), Vector3(0, 0, PI / 2), Vector3(0.0005, 0.0005, 0.0005));
				GetGameObjectManager()->addGameObject(blueKey);

				//Light 3
				FX::SetupSpotLight(3, true, { (float)x, 1, (float)z }, { 0, -1, 0 }, Vector3(0.0f, 0.0f, 1.0f), Vector3(0.35f, 0.35f, 0.35f), Vector3(0.0f, 0.0f, 1.0f), 5.0f, 0.7f, D2R(15), D2R(30));

				((GameState*)GetStateManager()->getCurrentState())->setBlueKey(true);
				break;
			}
			case 14: //Yellow Key
			{ 
				YellowKey* yellowKey = new YellowKey("YellowKey", Vector3(x, 0.3f, z), Vector3(0, 0, PI / 2), Vector3(0.0005, 0.0005, 0.0005));
				GetGameObjectManager()->addGameObject(yellowKey);

				//Light 4
				FX::SetupSpotLight(4, true, { (float)x, 1, (float)z }, { 0, -1, 0 }, Vector3(1.0f, 1.0f, 0.0f), Vector3(0.35f, 0.35f, 0.35f), Vector3(1.0f, 1.0f, 0.0f), 5.0f, 0.7f, D2R(15), D2R(30));

				((GameState*)GetStateManager()->getCurrentState())->setYellowKey(true);
				break;
			}
			case 30: //Player
			{ 
				((GameState*)GetStateManager()->getCurrentState())->getPlayer()->Initialise(x, z);
				break;
			}
			
			case 31: //Enemy
			{ 
				Enemy* enemy = new Enemy("Enemy", Vector3(x, 0.5f, z), Vector3(0, 0, 0), Vector3(0.007f, 0.007f, 0.007f));
				GetGameObjectManager()->addGameObject(enemy);
				break;
			}
			default:
				break;
			}
		}
	}
	//Create waypoints for enemy pathing system

	int count(1);
	for (Vector3 loc : waypointLocations) {
		std::ostringstream oss;
		oss << "Waypoint" << count;
		GameObject* waypoint = new GameObject(oss.str(), loc, Vector3(0, 0, 0), Vector3(0, 0, 0), "cube", "waypoint.dds"); //Scale of zero so the objects are not rendered
		GetGameObjectManager()->addGameObject(waypoint);
		count++;
	}

}

void Level::Release() {

}
//Return an object at a specified position (rounds float to be used as int)
int Level::getObjectAtWorldPos(float x, float y)
{
	x = round(x);
	y = round(y);

	return getObjectAtCoordinate(x, y);;
}

//Return an object at a specified position
int Level::getObjectAtCoordinate(int x, int y) {

	if (x < 0 || x > (levelSize - 1) || y < 0 || y > (levelSize - 1)) {

		return 1;

	} else {

		return levelMap[x][y];

	}
}

//Add a waypoint to the waypoint location vector
void Level::addWaypointLocation(Vector3 loc) {
	waypointLocations.push_back(loc);
}

//Get total waypoints
int Level::getHowManyWaypoints() {
	return waypointLocations.size() - 1;
}