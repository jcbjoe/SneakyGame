#include "GameObjectManager.h"


void GameObjectManager::Release()
{

}

void GameObjectManager::addGameObject(GameObject* gObj) {
	gameObjects.push_back(gObj);
}

vector<GameObject*>& GameObjectManager::getGameObjects() {
	return gameObjects;
}

GameObject* GameObjectManager::getFirstObjectByName(const string name) {
	for (GameObject* obj : gameObjects) {
		if (obj->GetName() == name) {
			return obj;
		}
	}
}