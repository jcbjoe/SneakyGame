#include "GameObjectManager.h"
#include "Skybox.h"

GameObjectManager::GameObjectManager() : loadedObjects(false){

}

void GameObjectManager::loadObjects()
{
	if (!loadedObjects) {
		
		/*Skybox* skybox = new Skybox("Skybox", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
		GetGameObjectManager()->addGameObject(skybox);*/

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

void GameObjectManager::Release()
{
	GetMeshManager()->Release();
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
	GameObject* sky = nullptr;
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
	if(sky)
		gameObjects.push_back(sky);
}