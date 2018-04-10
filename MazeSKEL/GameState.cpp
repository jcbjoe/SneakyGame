#include "GameState.h"


GameState::GameState()
	:
	State("MainGameState")
{

}

void GameState::Init() {


	//Initialise window and hide cursor Fix later
	//GetMouseAndKeys()->Initialise(GetMainWnd(), 0, 1);

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
	BuildDoor(*GetMeshManager());

	

	Skybox* skybox = new Skybox("Skybox", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	GetGameObjectManager()->addGameObject(skybox);

	Floor* floor = new Floor("Floor", Vector3(4.5f, 0.0f, 4.5f), Vector3(0, 0, 0), Vector3(5, 1, 5));
	GetGameObjectManager()->addGameObject(floor);

	GetLevelManager()->initialise();

	//For every space in the level
	for (int i(0); i < levelx; i++)
	{
		for (int j(0); j < levely; j++)
		{

			switch (GetLevelManager()->getCurrentLevel()->getObjectAtCoordinate(i, j))
			{
			case 0: {//Floor to be placed
				//Floor* floor = new Floor("Floor", Vector3(i, 0.0f, j), Vector3(0, 0, 0), Vector3(5, 1, 5));
				//GetGameObjectManager()->addGameObject(floor);
				break;
			}

			case 1: { //Wall to be placed

				Wall* wall = new Wall("Wall", Vector3(i, 0.5f, j), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5));
				GetGameObjectManager()->addGameObject(wall);

				break;
			}

			case 2: { //Player to be place
					  //Place camera
				gPlayer.Initialise(i, j);
				break;
			}

			case 3: { //Loot to be placed
				Loot* loot = new Loot("Loot", Vector3(i, 0.3f, j), Vector3(0, 0, 0), Vector3(0.02, 0.1, 0.1));
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

	//--- Init the UI - 1st Arg = ShowFPS
	GetUserInterfaceManager()->initialiseUI(true);

	FX::SetupDirectionalLight(0, true, Vector3(-0.7f, -0.7f, 0.7f), Vector3(0.67f, 0.67f, 0.67f), Vector3(0.25f, 0.25f, 0.25f), Vector3(0.15f, 0.15f, 0.15f));
}

void GameState::Update(float dTime) {

	//Load level 1 for now
	if (GetMouseAndKeys()->IsPressed(VK_1))
	{
		//Change array to use in level
		GetLevelManager()->loadLevel(0);
		//delete current gameobjects
		GetGameObjectManager()->deleteAllObjects();
		//Reset stats somewhere here
		//----
		//Reload scene
		GetLevelManager()->getCurrentLevel()->reloadLevel(gPlayer);
	}
	//Load level 2 for now
	else if (GetMouseAndKeys()->IsPressed(VK_2))
	{
		GetLevelManager()->loadLevel(1);
		GetGameObjectManager()->deleteAllObjects();
		GetLevelManager()->getCurrentLevel()->reloadLevel(gPlayer);
	}

	if (GetMouseAndKeys()->IsPressed(VK_P)) {
		paused = !paused;
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
		string objName = obj->GetName();
		if (objName == "Loot" || objName == "RedKey" || objName == "RedDoor" || objName == "BlueKey" || objName == "BlueDoor" || objName == "ReturnBox")
		{
			//check loot collision
			Vector3 vectorToLoot = gPlayer.getCameraPosition() - obj->GetPosition();
			float x = vectorToLoot.x *  vectorToLoot.x;
			float y = vectorToLoot.y *  vectorToLoot.y;
			float z = vectorToLoot.z * vectorToLoot.z;
			float distanceFromLoot = sqrt(x + y + z);

			//float distFromLoot = 
			if (distanceFromLoot < 1.2)
			{
				if (obj->GetName() == "RedDoor")
				{
					if (gPlayer.getHasRedKey()) {
						gPlayer.setOpenedRed();
						obj->setIndex(index);
						obj->moveObject();
						return;
					}
				}
				else
					if (obj->GetName() == "BlueDoor")
					{
						if (gPlayer.getHasBlueKey()) {
							gPlayer.setOpenedBlue();
							obj->setIndex(index);
							obj->moveObject();
							return;
						}
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
				else
					if (obj->GetName() == "RedKey")
					{
						gPlayer.setHasRedKey();
						GetGameObjectManager()->deleteGameObjectByIndex(index);
						return;
					}
					else
						if (obj->GetName() == "BlueKey")
						{
							gPlayer.setHasBlueKey();
							GetGameObjectManager()->deleteGameObjectByIndex(index);
							return;
						}
			}
			if (distanceFromLoot < 0.55f && objName == "ReturnBox")
			{
				//If player has coins to deposit
				if (gPlayer.getScore() != 0)
				{
					//Deposit them
					gPlayer.dropOffCoins();
				}
				return;
			}
		}
		index++;
	}
}

void GameState::Render(float dTime) {
	BeginRender(Colours::Black);

	for (GameObject* obj : GetGameObjectManager()->getGameObjects()) {
		obj->Render();
	}

	float alpha = 0.5f + sinf(gAngle * 2)*0.5f;

	FX::SetPerFrameConsts(gd3dImmediateContext, gPlayer.getCameraPosition());

	CreateProjectionMatrix(FX::GetProjectionMatrix(), 0.25f*PI, GetAspectRatio(), 0.25f, 10.f);
	Matrix w = Matrix::CreateRotationY(sinf(gAngle));
	FX::SetPerObjConsts(gd3dImmediateContext, w);

	GetUserInterfaceManager()->updateUI(1 / dTime, gPlayer.getCrouchStatus(), gPlayer.getScore(), gPlayer.getDeposited(), gPlayer.getHasRedKey(), gPlayer.getHasBlueKey());


	EndRender();
	GetMouseAndKeys()->PostProcess();
}

void GameState::Release() {
	GetLevelManager()->Release();
}