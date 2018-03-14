#include "ObjectManager.h"
#include "UserInterfaceManager.h"

void ObjectManager::initialiseObjects() {
	mQuad.Initialise(BuildQuad(*GetMeshManager()));
	//mWall.Initialise(BuildCube(*GetMeshManager()));

	//textured lit box
	mBox.Initialise(BuildCube(*GetMeshManager()));
	mBox.GetPosition() = Vector3(0, 0, 0);
	mBox.GetScale() = Vector3(0.5f, 0.5f, 0.5f);
	MaterialExt mat = mQuad.GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("WallGarage.dds", true, gd3dDevice);
	mat.texture = "WallGarage.dds";
	mBox.SetOverrideMat(&mat);

	// floor
	//Set up geometry
	mQuad.GetScale() = Vector3(0.5, 0.5, 0.5);
	mQuad.GetPosition() = Vector3(0, 0, 0);
	//Set up material
	mat = mQuad.GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("test.dds", true, gd3dDevice);
	mat.texture = "test.dds";
	mat.texTrsfm.scale = Vector2(1, 1);
	mQuad.SetOverrideMat(&mat);


	//Skybox
	Mesh& sb = GetMeshManager()->CreateMesh("skybox");
	sb.CreateFrom("data/skybox.fbx", gd3dDevice, FX::GetMyFX()->mCache);
	mSkybox.Initialise(sb);
	mSkybox.GetScale() = Vector3(1, 1, 1);
	mSkybox.GetPosition() = Vector3(0, 0, 0);
	mSkybox.GetRotation() = Vector3(PI / 2, 0, 0);
	MaterialExt& defMat = mSkybox.GetMesh().GetSubMesh(0).material;
	defMat.flags &= ~MaterialExt::LIT;
	defMat.flags &= ~MaterialExt::ZTEST;


	//Loot Test
	mLoot = mBox;
	mLoot.GetScale() = Vector3(0.1f, 0.1f, 0.1f);
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Metal.dds", true, gd3dDevice);
	mat.texture = "Metal.dds";
	mLoot.SetOverrideMat(&mat);

	mEnemy = &mBox;
	mEnemy->GetScale() = Vector3(0.1f, 0.1f, 0.1f);
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Enemy.dds", true, gd3dDevice);
	mat.texture = "Enemy.dds";
	mEnemy->SetOverrideMat(&mat);

	mWaypoint = mBox;
	mWaypoint.GetScale() = Vector3(0.1f, 0.1f, 0.1f);
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Waypoint.dds", true, gd3dDevice);
	mat.texture = "Waypoint.dds";
	mWaypoint.SetOverrideMat(&mat);

	for (Model obj : mOpaques)
	{
		obj.GetScale() *= gWorldScale;
		obj.GetPosition() *= gWorldScale;
	}
}


void ObjectManager::render() {

	FX::GetMyFX()->Render(mSkybox, gd3dImmediateContext);

	for (Model p : mOpaques)
	{
		FX::GetMyFX()->Render(p, gd3dImmediateContext);
	}


	FX::GetMyFX()->Render(*mEnemy, gd3dImmediateContext);

	//GetUserInterfaceManager()->printDebugText(to_string(mOpaques.at(100).GetPosition().x) + " : " + to_string(mOpaques.at(100).GetPosition().z));
	//mOpaques.at(100).GetPosition() = Vector3(7, 0.5, 7);
}

void ObjectManager::createFloor(Vector3 location) {
	mQuad.GetPosition() = location;
	mOpaques.push_back(mQuad);
}

void ObjectManager::createWall(Vector3 location) {
	mBox.GetPosition() = location;
	mOpaques.push_back(mBox);
}

void ObjectManager::createLoot(Vector3 location) {
	mLoot.GetPosition() = location;
	mOpaques.push_back(mLoot);
}

Model* ObjectManager::createEnemy(Vector3 location) {
	mEnemy->GetPosition() = location;
	//mOpaques.push_back(*mEnemy);
	return mEnemy;
}

void ObjectManager::createWaypoint(Vector3 location) {
	mWaypoint.GetPosition() = location;
	mOpaques.push_back(mWaypoint);
}

void ObjectManager::setSkyboxPos(Vector3 pos) {
	mSkybox.GetPosition() = pos;
}