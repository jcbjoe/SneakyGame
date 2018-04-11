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

class GameState : public State
{
public:

	GameState();
	void Update(float dTime) override;
	void Init() override;
	void Render(float dTime) override;
	void Release() override;

	bool paused = false;

	Player* getPlayer() { return gPlayer; }
private:
	float gAngle = 0;
	Player* gPlayer;
	float Timer = 0;
};


#endif