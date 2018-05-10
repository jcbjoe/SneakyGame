#include "MainMenuState.h"
#include "CommonStates.h"
#include "Input.h"
#include "StateManager.h"
#include "UserInterfaceManager.h"
#include "AudioMgrFMOD.h"


MainMenuState::MainMenuState() 
	:
	State("MainMenuState"), selected(0)
{
	//Initialise window and hide cursor


	//GetIAudioMgr()->GetSfxMgr()->Load("music");
	//GetIAudioMgr()->GetSfxMgr()->Play("NewYork", true, false, nullptr, 1.0);
}

void MainMenuState::Init() {
	GetMouseAndKeys()->Initialise(GetMainWnd(), 1, 1);
	GetGamepad()->Initialise();

	LoadTextures();

	ShowCursor(true);

	GetIAudioMgr()->GetSfxMgr()->Load("music");
	pressedOnInit = false;

	GetGamepad()->Update();
	if (GetGamepad()->IsConnected(0))
	{
		if (GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_A)) {
			pressedOnInit = true;
		}
	}
}

void MainMenuState::Update(float dTime){
	GetIAudioMgr()->Update();
	if (GetIAudioMgr()->GetSongMgr()->IsPlaying(musicHdl) == false)
		GetIAudioMgr()->GetSongMgr()->Play("spookyMusic", true, false, &musicHdl, 0.5);
		
	GetGamepad()->Update();
	if (GetGamepad()->IsConnected(0))
		if (!(GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_A)) && pressedOnInit) {
		pressedOnInit = false;
	}
	
	if (GetGamepad()->IsConnected(0)) {

		if (GetGamepad()->GetState(0).leftStickY < 0) {
			if (!gamepadDown) {
				if (selected == 3)
					selected = 0;
				else
					selected++;
			}
			gamepadDown = true;
		}
		else if (GetGamepad()->GetState(0).leftStickY > 0) {
			if (!gamepadDown) {
				if (selected == 0)
					selected = 3;
				else
					selected--;
			}
			gamepadDown = true;
		}
		else {
			if (gamepadDown) {
				gamepadDown = false;
			}
		}

		if (GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_A) && !pressedOnInit) {
			if(selected == 0)
				GetStateManager()->changeState("LoadingState");
			if (selected == 1)
				GetStateManager()->changeState("HighscoreState");
			if (selected == 2)
				;
			if(selected == 3)
				PostQuitMessage(0);
		}
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

	//////////////////////////////////////////////////////// START BUTTON //////////////////////////////////////////////////////////////////////
	bounds startBounds = drawButton(mStartButtonTex, mStartButtonDimentions, -50, 0);

	if (
		((GetMouseAndKeys()->GetMousePos(true).x >= startBounds.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= startBounds.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= startBounds.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= startBounds.bottomRight.y))
		)
	{
		selected = 0;
	}

	if (
		GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
		&&
		((GetMouseAndKeys()->GetMousePos(true).x >= startBounds.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= startBounds.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= startBounds.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= startBounds.bottomRight.y))
		)
	{
		GetStateManager()->changeState("LoadingState");
	}

	//////////////////////////////////////////////////////// HIGHSCORE BUTTON //////////////////////////////////////////////////////////////////////
	bounds highscoreBounds = drawButton(mHighscoreButtonTex, mHighscoreButtonDimentions, 50, 0);

	if (
		((GetMouseAndKeys()->GetMousePos(true).x >= highscoreBounds.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= highscoreBounds.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= highscoreBounds.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= highscoreBounds.bottomRight.y))
		)
	{
		selected = 1;
	}
	if (
		GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
		&&
		((GetMouseAndKeys()->GetMousePos(true).x >= highscoreBounds.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= highscoreBounds.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= highscoreBounds.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= highscoreBounds.bottomRight.y))
		)
	{
		GetStateManager()->changeState("HighscoreState");
	}

	//////////////////////////////////////////////////////// HELP BUTTON //////////////////////////////////////////////////////////////////////


	bounds helpBounds = drawButton(mHelpButtonTex, mHelpButtonDimentions, 150, 0);

	if (
		((GetMouseAndKeys()->GetMousePos(true).x >= helpBounds.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= helpBounds.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= helpBounds.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= helpBounds.bottomRight.y))
		)
	{
		selected = 2;
	}

	//////////////////////////////////////////////////////// EXIT BUTTON //////////////////////////////////////////////////////////////////////
	bounds exitBounds = drawButton(mExitButtonTex, mExitButtonDimentions, 250, 0);

	if (
		((GetMouseAndKeys()->GetMousePos(true).x >= exitBounds.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= exitBounds.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= exitBounds.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= exitBounds.bottomRight.y))
		)
	{
		selected = 3;
	}

	//Exit Button
	if (
		GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
		&&
		((GetMouseAndKeys()->GetMousePos(true).x >= exitBounds.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= exitBounds.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= exitBounds.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= exitBounds.bottomRight.y))
		)
	{
		PostQuitMessage(0);
	}

	//////////////////////////////////////////////////////// ARROW //////////////////////////////////////////////////////////////////////

	int ArrowHOffset, ArrowWOffset;
	switch (selected) {

		case 0: ArrowHOffset = -50;
				ArrowWOffset = -120;
				break;
		case 1: ArrowHOffset = 50;
				ArrowWOffset = -255;
			break;
		case 2: ArrowHOffset = 150;
				ArrowWOffset = -130;
			break;
		case 3: ArrowHOffset = 250;
				ArrowWOffset = -95;
				break;
	}

	float arrowsz(h / mArrowDimentions.y);
	if (arrowsz > 1.25f)
		arrowsz = 1.25f;

	fx.mpSpriteB->Draw(mArrowTex, Vector2((w / 2.f) + ArrowWOffset, (h / 2.f) + ArrowHOffset), nullptr, Colours::White, 0, mArrowDimentions*0.5f, Vector2(arrowsz, arrowsz));



	fx.mpSpriteB->End();

	EndRender();
}


void MainMenuState::LoadTextures() {
	FX::MyFX& fx = *FX::GetMyFX();

	mpBackgroundTex = fx.mCache.LoadTexture("Screens/MainMenu/MainMenu.dds", true, gd3dDevice);
	mBackgroundDimentions = fx.mCache.Get(mpBackgroundTex).dim;

	mStartButtonTex = fx.mCache.LoadTexture("Screens/MainMenu/StartButton.dds", true, gd3dDevice);
	mStartButtonDimentions = fx.mCache.Get(mStartButtonTex).dim;

	mExitButtonTex = fx.mCache.LoadTexture("Screens/MainMenu/ExitButton.dds", true, gd3dDevice);
	mExitButtonDimentions = fx.mCache.Get(mExitButtonTex).dim;

	mArrowTex = fx.mCache.LoadTexture("Screens/MainMenu/Arrow.dds", true, gd3dDevice);
	mArrowDimentions = fx.mCache.Get(mArrowTex).dim;

	mHighscoreButtonTex = fx.mCache.LoadTexture("Screens/MainMenu/highscoreButton.dds", true, gd3dDevice);
	mHighscoreButtonDimentions = fx.mCache.Get(mHighscoreButtonTex).dim;
	
	mHelpButtonTex = fx.mCache.LoadTexture("Screens/MainMenu/helpButton.dds", true, gd3dDevice);
	mHelpButtonDimentions = fx.mCache.Get(mHelpButtonTex).dim;
}

void MainMenuState::ReleaseFromLevel() {
	FX::MyFX& fx = *FX::GetMyFX();

	fx.mCache.Release();
}

MainMenuState::bounds MainMenuState::drawButton(ID3D11ShaderResourceView *tex, Vector2 dimentions, float hOffset, float wOffset) {
	MainMenuState::bounds boundsOfbutton;
	FX::MyFX& fx = *FX::GetMyFX();
	int w, h;
	GetClientExtents(w, h);
	float sz(h / dimentions.y);
	if (sz > 1.25f)
		sz = 1.25f;
	fx.mpSpriteB->Draw(tex, Vector2((w / 2.f) + wOffset, (h / 2.f) + hOffset), nullptr, Colours::White, 0, dimentions*0.5f, Vector2(sz, sz));

	Vector2 TopLeft = Vector2(((w / 2.f) + wOffset) - (dimentions.x / 2 * sz), ((h / 2.f) + hOffset) - (dimentions.y / 2 * sz));
	Vector2 BottomRight = Vector2(((w / 2.f) + wOffset) + (dimentions.x / 2 * sz), ((h / 2.f) + hOffset) + (dimentions.y / 2 * sz));
	boundsOfbutton.topLeft = TopLeft;
	boundsOfbutton.bottomRight = BottomRight;

	return boundsOfbutton;
}