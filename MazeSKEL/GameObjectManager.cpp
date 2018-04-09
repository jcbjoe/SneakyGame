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

void GameObjectManager::deleteAllObjects()
{
	GameObject* sky;
	//Delete everything other than the skybox (fixes mesh errors)
	for (GameObject* object : gameObjects)
	{
		if (object->GetName() != "Skybox") {
			delete object;
		}
		else {
			sky = object;
		}
	}
	gameObjects.clear();
	gameObjects.push_back(sky);
}