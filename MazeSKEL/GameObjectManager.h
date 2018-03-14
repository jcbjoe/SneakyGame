
#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include "Singleton.h"
#include <vector>
#include <string>
#include "GameObject.h"

#include "D3D.h"

using namespace std;


class GameObjectManager : public Singleton<GameObjectManager>
{
public:
	~GameObjectManager() {
		Release();
	}

	void addGameObject(GameObject gObj);

	vector<GameObject> getGameObjects();

private:
	void Release();

	vector<GameObject> gameObjects;

};
SINGLETON_GET(GameObjectManager);

#endif