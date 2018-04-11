#include "MainMenuState.h"
#include "CommonStates.h"
#include "Input.h"
#include "StateManager.h"
#include "UserInterfaceManager.h"


MainMenuState::MainMenuState() 
	:
	State("MainMenu")
{
	//Initialise window and hide cursor
	GetMouseAndKeys()->Initialise(GetMainWnd(), 1, 1);
	GetGamepad()->Initialise();

	LoadTextures();
}

void MainMenuState::Update(float dTime){

	//Start Button
	if (
		GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
		&& ((GetMouseAndKeys()->GetMousePos(true).x >= 341) && (GetMouseAndKeys()->GetMousePos(true).x <= 672))
		&& ((GetMouseAndKeys()->GetMousePos(true).y >= 278) && (GetMouseAndKeys()->GetMousePos(true).y <= 367))
		)
	{
		GetStateManager()->changeState(1);
	}

	//Exit Button
	if (
		GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
		&& ((GetMouseAndKeys()->GetMousePos(true).x >= 341) && (GetMouseAndKeys()->GetMousePos(true).x <= 672))
		&& ((GetMouseAndKeys()->GetMousePos(true).y >= 400) && (GetMouseAndKeys()->GetMousePos(true).y <= 488))
		)
	{
		PostQuitMessage(0);
	}

	if (GetMouseAndKeys()->IsPressed(VK_1))
	{
		GetStateManager()->changeState(1);
	}
}

void MainMenuState::Render(float dTime) {
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


void MainMenuState::LoadTextures() {
	FX::MyFX& fx = *FX::GetMyFX();

	mpBackgroundTex = fx.mCache.LoadTexture("bg.dds", true, gd3dDevice);
	mBackgroundDimentions = fx.mCache.Get(mpBackgroundTex).dim;
}