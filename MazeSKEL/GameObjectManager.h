
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
	GameObjectManager();

	void loadObjects();

	~GameObjectManager() {
		Release();
	}

	void addGameObject(GameObject* gObj);

	vector<GameObject*>& getGameObjects();

	GameObject* getFirstObjectByName(const string name);


	vector<GameObject*> GameObjectManager::getAllObjectsByName(const string name)
	{
		vector<GameObject*> tempVec;

		for (GameObject* obj : gameObjects) {
			if (obj->GetName() == name) {
				tempVec.push_back(obj);
			}
		}

		return tempVec;
	}

	void GameObjectManager::deleteGameObjectByIndex(const int index){
		gameObjects.erase(gameObjects.begin() + index);
	}

	void deleteAllObjects();

private:
	bool loadedObjects;

	void Release();

	vector<GameObject*> gameObjects;

};
SINGLETON_GET(GameObjectManager);

#endif