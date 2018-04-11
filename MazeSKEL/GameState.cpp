#include "GameState.h"


GameState::GameState()
	:
	State("MainGameState")
{

}

void GameState::Init() {

	//Create Initial Objects to copy
	BuildFloor(*GetMeshManager());
	BuildWall(*GetMeshManager());
	BuildLoot(*GetMeshManager(), 10, 10);
	BuildCube(*GetMeshManager());
	BuildDoor(*GetMeshManager());
	Mesh* ms = &GetMeshManager()->CreateMesh("Coin");
	ms->CreateFrom("../bin/data/CoinNew.fbx", gd3dDevice, FX::GetMyFX()->mCache);

	GetLevelManager()->initialise();

	Timer = 100;

	gPlayer = new Player();

	//Change array to use in level
	GetLevelManager()->loadLevel(0);

	//--- Init the UI - 1st Arg = ShowFPS
	GetUserInterfaceManager()->initialiseUI(true);

	FX::SetupDirectionalLight(0, true, Vector3(-0.7f, -0.7f, 0.7f), Vector3(0.67f, 0.67f, 0.67f), Vector3(0.35f, 0.45f, 0.35f), Vector3(0.15f, 0.15f, 0.15f));
}

void GameState::Update(float dTime) {
	//Load level 1 for now
	if (GetMouseAndKeys()->IsPressed(VK_1))
	{
		GetLevelManager()->loadLevel(0);
		Timer = 100;
	}
	//Load level 2 for now
	else if (GetMouseAndKeys()->IsPressed(VK_2))
	{
		GetLevelManager()->loadLevel(1);
		Timer = 50;
	}

	//Timer Incrementer
	Timer -= dTime;

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

	gPlayer->Update(dTime);

	int index(0);
	for (GameObject* obj : objects) {
		string objName = obj->GetName();
		if (objName == "Loot" || objName == "RedKey" || objName == "RedDoor" || objName == "BlueKey" || objName == "BlueDoor" || objName == "ReturnBox")
		{
			//check loot collision
			Vector3 vectorToLoot = gPlayer->getCameraPosition() - obj->GetPosition();
			float x = vectorToLoot.x *  vectorToLoot.x;
			float y = vectorToLoot.y *  vectorToLoot.y;
			float z = vectorToLoot.z * vectorToLoot.z;
			float distanceFromLoot = sqrt(x + y + z);

			//float distFromLoot = 
			if (distanceFromLoot < 1.2)
			{
				if (obj->GetName() == "RedDoor")
				{
					if (gPlayer->getHasRedKey()) {
						gPlayer->setOpenedRed();
						obj->setIndex(index);
						obj->moveObject();
						return;
					}
				}
				else
					if (obj->GetName() == "BlueDoor")
					{
						if (gPlayer->getHasBlueKey()) {
							gPlayer->setOpenedBlue();
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
					gPlayer->increaseScore();
					GetGameObjectManager()->deleteGameObjectByIndex(index);
					return;
				}
				else
					if (obj->GetName() == "RedKey")
					{
						gPlayer->setHasRedKey(true);
						GetGameObjectManager()->deleteGameObjectByIndex(index);
						return;
					}
					else
						if (obj->GetName() == "BlueKey")
						{
							gPlayer->setHasBlueKey(true);
							GetGameObjectManager()->deleteGameObjectByIndex(index);
							return;
						}
			}
			if (distanceFromLoot < 0.55f && objName == "ReturnBox")
			{
				//If player has coins to deposit
				if (gPlayer->getScore() != 0)
				{
					//Deposit them
					gPlayer->dropOffCoins();
					if (gPlayer->getDeposited() == GetLevelManager()->getCurrentLevel()->getMaxCoins())
					{
						gPlayer->setDeposited(0);
						gPlayer->setHasRedKey(false);
						gPlayer->setHasBlueKey(false);
						GetLevelManager()->loadLevel((GetLevelManager()->getCurrentLevelNumber() + 1));
					}
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

	FX::SetPerFrameConsts(gd3dImmediateContext, gPlayer->getCameraPosition());

	CreateProjectionMatrix(FX::GetProjectionMatrix(), 0.25f*PI, GetAspectRatio(), 0.25f, 20.0f);
	Matrix w = Matrix::CreateRotationY(sinf(gAngle));
	FX::SetPerObjConsts(gd3dImmediateContext, w);

	GetUserInterfaceManager()->updateUI(1 / dTime, Timer, gPlayer->getCrouchStatus(), gPlayer->getScore(), gPlayer->getDeposited(), gPlayer->getHasRedKey(), gPlayer->getHasBlueKey());


	EndRender();
	GetMouseAndKeys()->PostProcess();
}

void GameState::Release() {
	GetLevelManager()->Release();
}