#include "GameState.h"
#include "GameOverState.h"
#include "StateManager.h"
#include "CommonStates.h"

GameState::GameState()
	:
	State("MainGameState")
{
	gPlayer = new Player();
}

void GameState::Init() {

	GetLevelManager()->initialise();
	
	currGameStats.clear();

	Timer = GetLevelManager()->getCurrentLevel()->getLevelTimer();
	//Change array to use in level
	GetLevelManager()->loadLevel(0);

	//--- Init the UI - 1st Arg = ShowFPS
	GetUserInterfaceManager()->initialiseUI(true);

	FX::SetupDirectionalLight(0, true, Vector3(-1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.45f, 0.55f, 0.45f), Vector3(0.0f, 0.0f, 0.0f));

	paused = false;


	while (ShowCursor(false) >= 0) {};

}

void GameState::ReleaseFromLevel() {
	GetLevelManager()->Release();
	GetGameObjectManager()->Release();
	GetMeshManager()->Release();
	FX::MyFX& fx = *FX::GetMyFX();
	fx.mCache.Release();
}

void GameState::Destruct() {
	delete gPlayer;
}



void GameState::Update(float dTime) {
	GetIAudioMgr()->Update();
	if(GetIAudioMgr()->GetSongMgr()->IsPlaying(musicHdl) == false)
		GetIAudioMgr()->GetSongMgr()->Play("spookyMusic", true, false, &musicHdl, 0.5);

	if (GetMouseAndKeys()->IsPressed(VK_BACK)) {
		GetStateManager()->changeState("GameOverState");
	}

	//Timer Incrementer
	if (!paused) {
		Timer -= dTime;
		if (Timer < 0) {
			saveStats();
			gPlayer->resetStats();
			GetStateManager()->changeState("GameOverState");
			((GameOverState*)GetStateManager()->getCurrentState())->setStats(currGameStats);
		}
	}

	nearBoxFlag = false;
	if (GetMouseAndKeys()->IsPressed(VK_P) || (GetGamepad()->IsConnected(0) && GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_START))) {
		pDown = true;
	} else {
		if (pDown){
			paused = !paused;
			pDown = false;
			if (paused) {
				
				ShowCursor(true);
			} else {
				while (ShowCursor(false) >= 0) {};
			}
		}
	}

	//Update All GameObjects
	vector<GameObject*>& objects = GetGameObjectManager()->getGameObjects();
	for (int objIndex = 0; objIndex < objects.size(); objIndex++)
	{
		objects.at(objIndex)->Update(dTime);
	}

	float moveSpeed = dTime / 5.0f;
	float turnSpeed = 20.0f;

	gPlayer->Update(dTime);

	int index(0);
	for (GameObject* obj : objects) {
		string objName = obj->GetName();
		if (objName == "Loot" || objName == "RedKey" || objName == "RedDoor" || objName == "BlueKey" || objName == "BlueDoor" || objName == "YellowKey" || objName == "ReturnBox")
		{
			float distFromObj = distBetweenPlayerAndObj(obj);

			//float distFromLoot = 
			if (distFromObj < 1.2)
			{
				if (obj->GetName() == "RedDoor" && !obj->getMove())
				{
					if (gPlayer->getHasRedKey()) {
						if (!(gPlayer->getOpenedRed())) {
							GetIAudioMgr()->GetSfxMgr()->Play("soundDoorSlide", false, false, nullptr, 1.0);
						}
						gPlayer->setOpenedRed();
						obj->moveObject();
						return;
					}
				}
				else
					if (obj->GetName() == "BlueDoor" && !obj->getMove())
					{
						if (gPlayer->getHasBlueKey()) {

							if (!(gPlayer->getOpenedBlue())) {
								GetIAudioMgr()->GetSfxMgr()->Play("soundDoorCreak", false, false, nullptr, 1.0);
							}

							gPlayer->setOpenedBlue();
							obj->moveObject();
							return;
						}
					}
			}
			if (distFromObj < 0.5f)
			{
				if (obj->GetName() == "Loot" && !obj->getMove())
				{
					gPlayer->increaseScore();
					obj->setIndex(index);
					GetIAudioMgr()->GetSfxMgr()->Play("soundCoinCollect", false, false, nullptr, 0.5);
					obj->moveObject();
					return;
				}
				else
					if (obj->GetName() == "RedKey" && !obj->getMove())
					{
						gPlayer->setHasRedKey(true);
						obj->setIndex(index);
						GetIAudioMgr()->GetSfxMgr()->Play("soundCoinCollect", false, false, nullptr, 0.5);
						obj->moveObject();
						FX::DisableLight(2);
						return;
					}
					else
						if (obj->GetName() == "BlueKey" && !obj->getMove())
						{
							gPlayer->setHasBlueKey(true);
							obj->setIndex(index);
							GetIAudioMgr()->GetSfxMgr()->Play("soundCoinCollect", false, false, nullptr, 0.5);
							obj->moveObject();
							FX::DisableLight(3);
							return;
						}
						else
							if (obj->GetName() == "YellowKey" && !obj->getMove())
							{
								gPlayer->setHasYellowKey(true);
								obj->setIndex(index);
								GetIAudioMgr()->GetSfxMgr()->Play("soundCoinCollect", false, false, nullptr, 0.5);
								obj->moveObject();
								FX::DisableLight(4);
								return;
							}
			}
			if (objName == "ReturnBox")
			{
				if (distFromObj < 0.55f)
				{
					//If player has coins to deposit
					if (gPlayer->getScore() != 0)
					{
						//Deposit them
						GetIAudioMgr()->GetSfxMgr()->Play("soundCoinDeposit", false, false, nullptr, 1.0);
						gPlayer->dropOffCoins();
						if (gPlayer->getDeposited() == GetLevelManager()->getCurrentLevel()->getMaxCoins())
						{
							saveStats();
							gPlayer->resetStats();
							if (GetLevelManager()->getCurrentLevelNumber() == GetLevelManager()->getMaxLevels())
								GetStateManager()->changeState("GameOverState");
							else
							{
								GetLevelManager()->loadLevel((GetLevelManager()->getCurrentLevelNumber() + 1));
								Timer = GetLevelManager()->getCurrentLevel()->getLevelTimer();
							}
						}
					}

					return;
				}
				else if (distFromObj < 0.75f)
					nearBoxFlag = true;
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

	gPlayer->Render(dTime);

	FX::SetPerFrameConsts(gd3dImmediateContext, gPlayer->getCameraPosition());

	CreateProjectionMatrix(FX::GetProjectionMatrix(), 0.25f*PI, GetAspectRatio(), 0.25f, 20.0f);
	Matrix w = Matrix::CreateRotationY(sinf(gAngle));
	FX::SetPerObjConsts(gd3dImmediateContext, w);

	GetUserInterfaceManager()->updateUI(1 / dTime, Timer, gPlayer->getCrouchStatus(), gPlayer->getScore(), gPlayer->getDeposited(), GetLevelManager()->getCurrentLevel()->getMaxCoins(), gPlayer->getHasRedKey(), gPlayer->getHasBlueKey(), gPlayer->getHasYellowKey(), RedKey, BlueKey, YellowKey, gPlayer->getCameraPosition().x, gPlayer->getCameraPosition().z, gPlayer->get2DRotation(), nearBoxFlag);

	EndRender();
	GetMouseAndKeys()->PostProcess();
}



void GameState::setRedKey(const bool set) {
	RedKey = set;
}
void GameState::setBlueKey(const bool set) {
	BlueKey = set;
}
void GameState::setYellowKey(const bool set) {
	YellowKey = set;
}
bool GameState::getRedKey() {
	return RedKey;
}
bool GameState::getBlueKey() {
	return BlueKey;
}
bool GameState::getYellowKey() {
	return YellowKey;
}

float GameState::distBetweenPlayerAndObj(GameObject * obj)
{
	//check loot collision
	Vector3 vectorToLoot = gPlayer->getCameraPosition() - obj->GetPosition();
	float x = vectorToLoot.x *  vectorToLoot.x;
	float y = vectorToLoot.y *  vectorToLoot.y;
	float z = vectorToLoot.z * vectorToLoot.z;
	return sqrt(x + y + z);
}

void GameState::pauseKeyPressed()
{
	if (GetMouseAndKeys()->IsPressed(VK_P)) {
		pDown = true;
	}
	else {
		if (pDown) {
			paused = !paused;
			pDown = false;
			if (paused) {
				ShowCursor(true);
			}
			else {
				while (ShowCursor(false) >= 0) {};
			}
		}
	}
}

void GameState::saveStats()
{
	levelStats thisLevel;
	thisLevel.CoinsCollected = gPlayer->getDeposited();
	thisLevel.Level = GetLevelManager()->getCurrentLevelNumber() + 1;
	thisLevel.TimeTaken = GetLevelManager()->getCurrentLevel()->getLevelTimer() - Timer;

	currGameStats.push_back(thisLevel);
}
