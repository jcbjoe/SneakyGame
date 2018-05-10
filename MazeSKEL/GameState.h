#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "SpriteFont.h"
#include "Player.h"
#include "Wall.h"
#include "Loot.h"
#include "Floor.h"
#include "Skybox.h"
#include "UserInterfaceManager.h"
#include "Enemy.h"
#include "WindowUtils.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "RedKey.h"
#include "RedDoor.h"
#include "BlueKey.h"
#include "BlueDoor.h"
#include "WallHalf.h"
#include "ReturnBox.h"
#include "AudioMgrFMOD.h"
#include <vector>

#include "levelStats.h"


class GameState : public State
{
public:

	GameState();
	void Update(float dTime) override;
	void Init() override;
	void Render(float dTime) override;
	void ReleaseFromLevel() override;
	void Destruct() override;

	bool paused = false;
	
	void setRedKey(const bool);
	void setBlueKey(const bool);
	void setYellowKey(const bool);
	bool getRedKey();
	bool getBlueKey();
	bool getYellowKey();

	Player* getPlayer() { return gPlayer; }

private:
	float gAngle = 0;
	Player* gPlayer;
	float Timer = 0;
	bool RedKey = false;
	bool BlueKey = false;
	bool YellowKey = false;
	bool pDown = false;
	bool nearBoxFlag = false;

	float distBetweenPlayerAndObj(GameObject* obj);
	void pauseKeyPressed();

	vector<levelStats> currGameStats;
	void saveStats();

	unsigned int musicHdl;

};


#endif