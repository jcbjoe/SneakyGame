#include "Game.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Game::OnResize(int screenWidth, int screenHeight)
{
	OnResize_Default(screenWidth, screenHeight);
}

void Game::Initialise()
{

	const int levelx = 10;
	const int levely = 10;

	//Level testing
	//0 = Floor
	//1 = Wall
	//2 = Spawn/Entrance/Exit
	//3 = Coins
	//4 = Enemy
   
	//Create Initial Objects to copy
	BuildFloor(*GetMeshManager());
	BuildWall(*GetMeshManager());
	BuildLoot(*GetMeshManager(), 10, 10);
	BuildCube(*GetMeshManager());

	Skybox* skybox = new Skybox("Skybox", Vector3(0, 0, 0), Vector3(0,0,0), Vector3(1, 1, 1));
	GetGameObjectManager()->addGameObject(skybox);

	//For every space in the level
	for (int i(0); i < levelx; i++)
	{
		for (int j(0); j < levely; j++)
		{
			
			switch (GetLevelManager()->getObjectAtCoordinate(i, j))
			{
				case 0: {//Floor to be placed
					Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
					GetGameObjectManager()->addGameObject(floor);
					break;
				}

				case 1: { //Wall to be placed

					Wall* wall = new Wall("Wall", Vector3(i, 0.5f, j), Vector3(0,0,0), Vector3(0.5, 0.5, 0.5));
					GetGameObjectManager()->addGameObject(wall);

					break;
				}

				case 2: { //Player to be place
					//Place camera
					gPlayer.Initialise(i, j);

					//Place floor
					Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0,0,0), Vector3(0.5, 0.5, 0.5));
					GetGameObjectManager()->addGameObject(floor);
					break;
				}

				case 3: { //Loot to be placed
					Loot* loot = new Loot("Loot", Vector3(i, 0.3f, j), Vector3(0,0,0), Vector3(0.02, 0.1, 0.1));
					GetGameObjectManager()->addGameObject(loot);

					//Place floor
					Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0,0,0), Vector3(0.5, 0.5, 0.5));
					GetGameObjectManager()->addGameObject(floor);
					break;

				}

			    case 4: { //Enemy to be placed
					Enemy* enemy = new Enemy("Enemy", Vector3(i, 0.5f, j), Vector3(0,0,0), Vector3(0.1f, 0.1f, 0.1f));
					GetGameObjectManager()->addGameObject(enemy);

					//Place floor
					Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0,0,0), Vector3(0.5, 0.5, 0.5));
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


	GameObject* waypoint1 = new GameObject("Waypoint1", Vector3(8, 0.4, 6), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1), "cube", "waypoint.dds");
	GetGameObjectManager()->addGameObject(waypoint1);
	GameObject* waypoint2 = new GameObject("Waypoint2", Vector3(7, 0.4, 6), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1), "cube", "waypoint.dds");
	GetGameObjectManager()->addGameObject(waypoint2);
	GameObject* waypoint3 = new GameObject("Waypoint3", Vector3(7, 0.4, 1), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1), "cube", "waypoint.dds");
	GetGameObjectManager()->addGameObject(waypoint3);
	GameObject* waypoint4 = new GameObject("Waypoint4", Vector3(4, 0.4, 1), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1), "cube", "waypoint.dds");
	GetGameObjectManager()->addGameObject(waypoint4);
	GameObject* waypoint5 = new GameObject("Waypoint5", Vector3(4, 0.4, 7), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1), "cube", "waypoint.dds");
	GetGameObjectManager()->addGameObject(waypoint5);
	GameObject* waypoint6 = new GameObject("Waypoint6", Vector3(5, 0.4, 7), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1), "cube", "waypoint.dds");
	GetGameObjectManager()->addGameObject(waypoint6);
	GameObject* waypoint7 = new GameObject("Waypoint7", Vector3(5, 0.4, 8), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1), "cube", "waypoint.dds");
	GetGameObjectManager()->addGameObject(waypoint7);
	GameObject* waypoint8 = new GameObject("Waypoint8", Vector3(8, 0.4, 8), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1), "cube", "waypoint.dds");
	GetGameObjectManager()->addGameObject(waypoint8);

	//--- Init the UI - 1st Arg = ShowFPS
	GetUserInterfaceManager()->initialiseUI(true);

	FX::SetupDirectionalLight(0, true, Vector3(-0.7f, -0.7f, 0.7f), Vector3(0.67f, 0.67f, 0.67f), Vector3(0.25f, 0.25f, 0.25f), Vector3(0.15f, 0.15f, 0.15f));
}
void Game::reloadScene()
{

	//For every space in the level
	for (int i(0); i < 10; i++)
	{
		for (int j(0); j < 10; j++)
		{
			switch (GetLevelManager()->getObjectAtCoordinate(i, j))
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

void Game::Update(float dTime)
{
	//Load level 1 for now
	if (GetMouseAndKeys()->IsPressed(VK_1))
	{
		//Change array to use in level
		GetLevelManager()->loadLevel(1);
		//delete current gameobjects
		GetGameObjectManager()->deleteAllObjects();
		//Reset stats somewhere here
		//----
		//Reload scene
		reloadScene();
	}
	//Load level 2 for now
	else if (GetMouseAndKeys()->IsPressed(VK_2))
	{
		GetLevelManager()->loadLevel(2);
		GetGameObjectManager()->deleteAllObjects();
		reloadScene();
	}

	vector<GameObject*>& objects = GetGameObjectManager()->getGameObjects();


	for (GameObject* obj : objects) 
	{
		obj->Update(dTime);
	}

	float moveSpeed = dTime / 5.0f;
	float turnSpeed = 20.0f;

	gPlayer.Update(dTime);

	int index(0);
	for (GameObject* obj : objects) {
		if (obj->GetName() == "Loot" || obj->GetName() == "Key" || obj->GetName() == "Door")
		{
			//check loot collision
			Vector3 vectorToLoot = gPlayer.getCameraPosition() - obj->GetPosition();
			float x = vectorToLoot.x *  vectorToLoot.x;
			float y = vectorToLoot.y *  vectorToLoot.y;
			float z = vectorToLoot.z * vectorToLoot.z;
			float distanceFromLoot = sqrt(x + y + z);

			//float distFromLoot = 
			if (distanceFromLoot < 0.8)
			{
				if (obj->GetName() == "Door" && gPlayer.getHasKey()) 
				{
					gPlayer.changeKeyNo(-1);
					GetGameObjectManager()->deleteGameObjectByIndex(index);
					return;
				}
			}
			if (distanceFromLoot < 0.4f)
			{
				if (obj->GetName() == "Loot") 
				{
					gPlayer.increaseScore();
					GetGameObjectManager()->deleteGameObjectByIndex(index);
					return;
				}
				if (obj->GetName() == "Key") 
				{
					gPlayer.changeKeyNo(+1);
					GetGameObjectManager()->deleteGameObjectByIndex(index);
					return;
				}
			}
		}
		index++;
	}
}

void Game::Render(float dTime)
{
	BeginRender(Colours::Black);

	for (GameObject* obj : GetGameObjectManager()->getGameObjects()) {
		obj->Render();
	}

	float alpha = 0.5f + sinf(gAngle * 2)*0.5f;

	FX::SetPerFrameConsts(gd3dImmediateContext, gPlayer.getCameraPosition());

	CreateProjectionMatrix(FX::GetProjectionMatrix(), 0.25f*PI, GetAspectRatio(), 0.25f, 10.f);
	Matrix w = Matrix::CreateRotationY(sinf(gAngle));
	FX::SetPerObjConsts(gd3dImmediateContext, w);

	GetUserInterfaceManager()->updateUI(1 / dTime, gPlayer.getCrouchStatus(), gPlayer.getScore(), gPlayer.getKeyNo());


	EndRender();

	GetMouseAndKeys()->PostProcess();

}

void Game::Release() {

}

LRESULT Game::WindowsMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	const float camInc = 200.f * GetElapsedSec();

	switch (msg)
	{
	case WM_INPUT:
		GetMouseAndKeys()->MessageEvent((HRAWINPUT)lParam);
		break;
		// Respond to a keyboard event.
	case WM_CHAR:
		switch (wParam)
		{
		case 27:
		case 'q':
		case 'Q':
			PostQuitMessage(0);
			return 0;
		case 'j':
			//GetUserInterfaceManager()->printDebugText(to_string(mCamera.GetPos().x) + " : " + to_string(mCamera.GetPos().z));
			break;
		}
	}

	//default message handling (resize window, full screen, etc)
	return DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

