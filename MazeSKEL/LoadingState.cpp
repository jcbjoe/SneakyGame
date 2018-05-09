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

	counter = 0;
	loadingScreenDot = 0;
	loadingProgress = 0;

	LoadTextures();

	mLoadThread = std::async(launch::async, &LoadingState::Load, this);

}

void LoadingState::Load() {
	
	BuildFloor(*GetMeshManager());
	loadingProgress = 1;
	BuildWall(*GetMeshManager());
	loadingProgress = 2;
	BuildLoot(*GetMeshManager(), 10, 10);
	loadingProgress = 3;
	BuildCube(*GetMeshManager());
	loadingProgress = 4;
	BuildDoor(*GetMeshManager());
	loadingProgress = 5;
	Mesh* msKey = &GetMeshManager()->CreateMesh("Key");
	msKey->CreateFrom("../bin/data/key.fbx", gd3dDevice, FX::GetMyFX()->mCache);
	loadingProgress = 6;
	Mesh* msCoin = &GetMeshManager()->CreateMesh("Coin");
	msCoin->CreateFrom("../bin/data/CoinNew.fbx", gd3dDevice, FX::GetMyFX()->mCache);
	loadingProgress = 7;
	Mesh* msChest = &GetMeshManager()->CreateMesh("Chest");
	msChest->CreateFrom("../bin/data/chest.fbx", gd3dDevice, FX::GetMyFX()->mCache);
	loadingProgress = 8;
	Mesh* msHand = &GetMeshManager()->CreateMesh("Hands");
	msHand->CreateFrom("../bin/data/Hands.obj", gd3dDevice, FX::GetMyFX()->mCache);
	loadingProgress = 9;
	Mesh* msGhost = &GetMeshManager()->CreateMesh("Ghost");
	msGhost->CreateFrom("../bin/data/Boo.obj", gd3dDevice, FX::GetMyFX()->mCache);
	loadingProgress = 10;
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
	counter += dTime;
	if (counter >= 0.25) {
		if (loadingScreenDot == 3)
			loadingScreenDot = 0;
		else
			loadingScreenDot++;
		counter = 0;
	}
	switch (loadingScreenDot) {
		case 0:
			fx.mpSpriteB->Draw(mpBackgroundTex0, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBackgroundDimentions*0.5f, Vector2(sz, sz));
			break;
		case 1:
			fx.mpSpriteB->Draw(mpBackgroundTex1, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBackgroundDimentions*0.5f, Vector2(sz, sz));
			break;
		case 2:
			fx.mpSpriteB->Draw(mpBackgroundTex2, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBackgroundDimentions*0.5f, Vector2(sz, sz));
			break;
		case 3:
			fx.mpSpriteB->Draw(mpBackgroundTex3, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBackgroundDimentions*0.5f, Vector2(sz, sz));
			break;
	}

	float containersz(h / mContainerDimentions.y);
	if (containersz > 1.25f)
		containersz = 1.25f;

	fx.mpSpriteB->Draw(mpContainerTex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mContainerDimentions*0.5f, Vector2(containersz, containersz));

	float barsz(h / mBar0Dimentions.y);
	if (barsz > 1.25f)
		barsz = 1.25f;

	switch (loadingProgress) {
	case 0:
		fx.mpSpriteB->Draw(mpBar0Tex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBar0Dimentions*0.5f, Vector2(barsz, barsz));
		break;
	case 1:
		fx.mpSpriteB->Draw(mpBar1Tex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBar0Dimentions*0.5f, Vector2(barsz, barsz));
		break;
	case 2:
		fx.mpSpriteB->Draw(mpBar2Tex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBar0Dimentions*0.5f, Vector2(barsz, barsz));
		break;
	case 3:
		fx.mpSpriteB->Draw(mpBar3Tex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBar0Dimentions*0.5f, Vector2(barsz, barsz));
		break;
	case 4:
		fx.mpSpriteB->Draw(mpBar4Tex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBar0Dimentions*0.5f, Vector2(barsz, barsz));
		break;
	case 5:
		fx.mpSpriteB->Draw(mpBar5Tex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBar0Dimentions*0.5f, Vector2(barsz, barsz));
		break;
	case 6:
		fx.mpSpriteB->Draw(mpBar6Tex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBar0Dimentions*0.5f, Vector2(barsz, barsz));
		break;
	case 7:
		fx.mpSpriteB->Draw(mpBar7Tex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBar0Dimentions*0.5f, Vector2(barsz, barsz));
		break;
	case 8: 
		fx.mpSpriteB->Draw(mpBar8Tex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBar0Dimentions*0.5f, Vector2(barsz, barsz));
		break;
	case 9:
		fx.mpSpriteB->Draw(mpBar9Tex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBar0Dimentions*0.5f, Vector2(barsz, barsz));
		break;
	case 10:
		fx.mpSpriteB->Draw(mpBar10Tex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBar0Dimentions*0.5f, Vector2(barsz, barsz));
		break;

	}

	fx.mpSpriteB->End();

	EndRender();
}


void LoadingState::LoadTextures() {
	FX::MyFX& fx = *FX::GetMyFX();

	mpBackgroundTex0 = fx.mCache.LoadTexture("Screens/Loading/LoadingScreen0Dots.dds", true, gd3dDevice);
	mpBackgroundTex1 = fx.mCache.LoadTexture("Screens/Loading/LoadingScreen1Dots.dds", true, gd3dDevice);
	mpBackgroundTex2 = fx.mCache.LoadTexture("Screens/Loading/LoadingScreen2Dots.dds", true, gd3dDevice);
	mpBackgroundTex3 = fx.mCache.LoadTexture("Screens/Loading/LoadingScreen3Dots.dds", true, gd3dDevice);
	mBackgroundDimentions = fx.mCache.Get(mpBackgroundTex0).dim;

	mpContainerTex = fx.mCache.LoadTexture("Screens/Loading/bars/container.dds", true, gd3dDevice);
	mContainerDimentions = fx.mCache.Get(mpContainerTex).dim;

	mpBar0Tex = fx.mCache.LoadTexture("Screens/Loading/bars/0.dds", true, gd3dDevice);
	mpBar1Tex = fx.mCache.LoadTexture("Screens/Loading/bars/1.dds", true, gd3dDevice);
	mpBar2Tex = fx.mCache.LoadTexture("Screens/Loading/bars/2.dds", true, gd3dDevice);
	mpBar3Tex = fx.mCache.LoadTexture("Screens/Loading/bars/3.dds", true, gd3dDevice);
	mpBar4Tex = fx.mCache.LoadTexture("Screens/Loading/bars/4.dds", true, gd3dDevice);
	mpBar5Tex = fx.mCache.LoadTexture("Screens/Loading/bars/5.dds", true, gd3dDevice);
	mpBar6Tex = fx.mCache.LoadTexture("Screens/Loading/bars/6.dds", true, gd3dDevice);
	mpBar7Tex = fx.mCache.LoadTexture("Screens/Loading/bars/7.dds", true, gd3dDevice);
	mpBar8Tex = fx.mCache.LoadTexture("Screens/Loading/bars/8.dds", true, gd3dDevice);
	mpBar9Tex = fx.mCache.LoadTexture("Screens/Loading/bars/9.dds", true, gd3dDevice);
	mpBar10Tex = fx.mCache.LoadTexture("Screens/Loading/bars/10.dds", true, gd3dDevice);
	mBar0Dimentions = fx.mCache.Get(mpBar0Tex).dim;
}

void LoadingState::Release() {
	FX::MyFX& fx = *FX::GetMyFX();

	fx.mCache.Release();

}