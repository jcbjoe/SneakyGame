#include "LoadingState.h"
#include "CommonStates.h"
#include "Input.h"
#include "StateManager.h"
#include "UserInterfaceManager.h"
#include "GameObjectManager.h"


LoadingState::LoadingState()
	:
	State("LoadingState")
{

}

void LoadingState::Init() {
	Loaded = false;

	LoadTextures();

	mLoadThread = std::async(launch::async, &LoadingState::Load, this);

}

void LoadingState::Load() {
	
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

	Loaded = true;
}

void LoadingState::Update(float dTime) {
	if (Loaded) {
		GetStateManager()->changeState("MainGameState");
	}
}

void LoadingState::Render(float dTime) {
	BeginRender(Colours::Black);

	mCamera.Initialise(Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 1.f), FX::GetViewMatrix());

	FX::MyFX& fx = *FX::GetMyFX();

	ResetStatesAfterSprites();
	FX::SetupDirectionalLight(0, true, Vector3(-0.7f, -0.7f, 0.7f), Vector3(0.7f, 0.65f, 0.65f), Vector3(0.15f, 0.1f, 0.1f), Vector3(0.01f, 0.01f, 0.01f));


	CommonStates state(gd3dDevice);
	fx.mpSpriteB->Begin(SpriteSortMode_Deferred, state.NonPremultiplied());


	//background
	int w, h;
	GetClientExtents(w, h);
	float sz(h / mBackgroundDimentions.y);
	if (sz > 1.25f)
		sz = 1.25f;
	fx.mpSpriteB->Draw(mpBackgroundTex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBackgroundDimentions*0.5f, Vector2(sz, sz));



	fx.mpSpriteB->End();

	EndRender();
}


void LoadingState::LoadTextures() {
	FX::MyFX& fx = *FX::GetMyFX();

	mpBackgroundTex = fx.mCache.LoadTexture("LoadingScreen.dds", true, gd3dDevice);
	mBackgroundDimentions = fx.mCache.Get(mpBackgroundTex).dim;
}