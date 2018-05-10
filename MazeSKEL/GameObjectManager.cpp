#include "GameObjectManager.h"
#include "Skybox.h"

//Default Constructor
GameObjectManager::GameObjectManager() : 
	loadedObjects(false)
{}

//Load in objects used to populate levels
void GameObjectManager::loadObjects()
{
	if (!loadedObjects) {
		
		//Create Initial Objects to copy
		BuildFloor(*GetMeshManager());
		BuildWall(*GetMeshManager());
		BuildLoot(*GetMeshManager(), 10, 10);
		BuildCube(*GetMeshManager());
		BuildDoor(*GetMeshManager());

		Mesh* msKey = &GetMeshManager()->CreateMesh("Key");
		msKey->CreateFrom("../bin/data/key.fbx", gd3dDevice, FX::GetMyFX()->mCache);

		Mesh* msCoin = &GetMeshManager()->CreateMesh("Coin");
		msCoin->CreateFrom("../bin/data/CoinNew.fbx", gd3dDevice, FX::GetMyFX()->mCache);

		Mesh* msChest = &GetMeshManager()->CreateMesh("Chest");
		msChest->CreateFrom("../bin/data/chest.fbx", gd3dDevice, FX::GetMyFX()->mCache);

		Mesh* msHand = &GetMeshManager()->CreateMesh("Hands");
		msHand->CreateFrom("../bin/data/Hands.obj", gd3dDevice, FX::GetMyFX()->mCache);

		Mesh* msGhost = &GetMeshManager()->CreateMesh("Ghost");
		msGhost->CreateFrom("../bin/data/Boo.obj", gd3dDevice, FX::GetMyFX()->mCache);

		loadedObjects = true;
	}
}

//Delete all objects from the gameObjects vector
void GameObjectManager::Release()
{
	for (GameObject* obj : gameObjects) {
		delete obj;
	}
	gameObjects.clear();
}

//Add object to vector
void GameObjectManager::addGameObject(GameObject* gObj) {
	gameObjects.push_back(gObj);
}

//Returns the gameObjects vector
vector<GameObject*>& GameObjectManager::getGameObjects() {
	return gameObjects;
}

//Search for an object by its name (returns the first)
GameObject* GameObjectManager::getFirstObjectByName(const string name) {
	for (GameObject* obj : gameObjects) {
		if (obj->GetName() == name) {
			return obj;
		}
	}
}