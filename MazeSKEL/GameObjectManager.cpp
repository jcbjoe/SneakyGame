#include "GameObjectManager.h"


void GameObjectManager::Release()
{

}

void GameObjectManager::addGameObject(GameObject gObj) {
	gameObjects.push_back(gObj);
}

vector<GameObject>& GameObjectManager::getGameObjects() {
	return gameObjects;
}