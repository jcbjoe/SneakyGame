#include "MainMenuState.h"
#include "CommonStates.h"
#include "Input.h"
#include "StateManager.h"
#include "UserInterfaceManager.h"
#include "AudioMgrFMOD.h"


MainMenuState::MainMenuState() 
	:
	State("MainMenu"), selected(0)
{
	//Initialise window and hide cursor
	GetMouseAndKeys()->Initialise(GetMainWnd(), 1, 1);
	GetGamepad()->Initialise();

	LoadTextures();

	ShowCursor(true);

	//GetIAudioMgr()->GetSfxMgr()->Load("music");
	//GetIAudioMgr()->GetSfxMgr()->Play("NewYork", true, false, nullptr, 1.0);
}

void MainMenuState::Update(float dTime){

	if (GetMouseAndKeys()->IsPressed(VK_1))
	{
		GetStateManager()->changeState("LoadingState");
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
	int StartHOffset, StartWOffset;
	StartHOffset = -50;
	StartWOffset = 0;

	float startsz(h / mHighscoreButtonDimentions.y);
	if (startsz > 1.25f)
		startsz = 1.25f;
	fx.mpSpriteB->Draw(mStartButtonTex, Vector2((w / 2.f) + StartWOffset, (h / 2.f) + StartHOffset), nullptr, Colours::White, 0, mStartButtonDimentions*0.5f, Vector2(startsz, startsz));

	Vector2 startTopLeft = Vector2(((w / 2.f) + StartWOffset) - (mStartButtonDimentions.x * startsz), ((h / 2.f) + StartHOffset) - (mStartButtonDimentions.y * startsz));
	Vector2 startBottomRight = Vector2(((w / 2.f) + StartWOffset) + (mStartButtonDimentions.x * startsz), ((h / 2.f) + StartHOffset) + (mStartButtonDimentions.y * startsz));

	if (
		((GetMouseAndKeys()->GetMousePos(true).x >= startTopLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= startBottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= startTopLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= startBottomRight.y))
		)
	{
		selected = 0;
	}

	if (
		GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
		&&
		((GetMouseAndKeys()->GetMousePos(true).x >= startTopLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= startBottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= startTopLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= startBottomRight.y))
		)
	{
		GetStateManager()->changeState("LoadingState");
	}

	//////////////////////////////////////////////////////// HIGHSCORE BUTTON //////////////////////////////////////////////////////////////////////

	int HighscoreHOffset, HighscoreWOffset;
	HighscoreHOffset = 50;
	HighscoreWOffset = 0;

	float highscoresz(h / mHighscoreButtonDimentions.y);
	if (highscoresz > 1.25f)
		highscoresz = 1.25f;
	fx.mpSpriteB->Draw(mHighscoreButtonTex, Vector2((w / 2.f) + HighscoreWOffset, (h / 2.f) + HighscoreHOffset), nullptr, Colours::White, 0, mHighscoreButtonDimentions*0.5f, Vector2(highscoresz, highscoresz));

	Vector2 highscoreTopLeft = Vector2(((w / 2.f) + HighscoreWOffset) - (mHighscoreButtonDimentions.x * highscoresz), ((h / 2.f) + HighscoreHOffset) - (mHighscoreButtonDimentions.y * highscoresz));
	Vector2 highscoreBottomRight = Vector2(((w / 2.f) + HighscoreWOffset) + (mHighscoreButtonDimentions.x * highscoresz), ((h / 2.f) + HighscoreHOffset) + (mHighscoreButtonDimentions.y * highscoresz));

	if (
		((GetMouseAndKeys()->GetMousePos(true).x >= highscoreTopLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= highscoreBottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= highscoreTopLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= highscoreBottomRight.y))
		)
	{
		selected = 1;
	}

	//////////////////////////////////////////////////////// HELP BUTTON //////////////////////////////////////////////////////////////////////

	int HelpHOffset, HelpWOffset;
	HelpHOffset = 150;
	HelpWOffset = 0;

	float helpsz(h / mHelpButtonDimentions.y);
	if (helpsz > 1.25f)
		helpsz = 1.25f;
	fx.mpSpriteB->Draw(mHelpButtonTex, Vector2((w / 2.f) + HelpWOffset, (h / 2.f) + HelpHOffset), nullptr, Colours::White, 0, mHelpButtonDimentions*0.5f, Vector2(helpsz, helpsz));

	Vector2 helpTopLeft = Vector2(((w / 2.f) + HelpWOffset) - (mHelpButtonDimentions.x * helpsz), ((h / 2.f) + HelpHOffset) - (mHelpButtonDimentions.y * helpsz));
	Vector2 helpBottomRight = Vector2(((w / 2.f) + HelpWOffset) + (mHelpButtonDimentions.x * helpsz), ((h / 2.f) + HelpHOffset) + (mHelpButtonDimentions.y * helpsz));

	if (
		((GetMouseAndKeys()->GetMousePos(true).x >= helpTopLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= helpBottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= helpTopLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= helpBottomRight.y))
		)
	{
		selected = 2;
	}

	//////////////////////////////////////////////////////// EXIT BUTTON //////////////////////////////////////////////////////////////////////

	int ExitHOffset, ExitWOffset;
	ExitHOffset = 250;
	ExitWOffset = 0;

	float exitsz(h / mExitButtonDimentions.y);
	if (exitsz > 1.25f)
		exitsz = 1.25f;
	fx.mpSpriteB->Draw(mExitButtonTex, Vector2((w / 2.f) + ExitWOffset, (h / 2.f) + ExitHOffset), nullptr, Colours::White, 0, mExitButtonDimentions*0.5f, Vector2(exitsz, exitsz));

	Vector2 exitTopLeft = Vector2(((w / 2.f) + ExitWOffset) - (mExitButtonDimentions.x * exitsz), ((h / 2.f) + ExitHOffset) - (mExitButtonDimentions.y * exitsz));
	Vector2 exitBottomRight = Vector2(((w / 2.f) + ExitWOffset) + (mExitButtonDimentions.x * exitsz), ((h / 2.f) + ExitHOffset) + (mExitButtonDimentions.y * exitsz));


	if (
		((GetMouseAndKeys()->GetMousePos(true).x >= exitTopLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= exitBottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= exitTopLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= exitBottomRight.y))
		)
	{
		selected = 3;
	}

	//Exit Button
	if (
		GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
		&&
		((GetMouseAndKeys()->GetMousePos(true).x >= exitTopLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= exitBottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= exitTopLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= exitBottomRight.y))
		)
	{
		PostQuitMessage(0);
	}

	//////////////////////////////////////////////////////// ARROW //////////////////////////////////////////////////////////////////////

	int ArrowHOffset, ArrowWOffset;
	switch (selected) {

		case 0: ArrowHOffset = -50;
				ArrowWOffset = -150;
				break;
		case 1: ArrowHOffset = 50;
				ArrowWOffset = -285;
			break;
		case 2: ArrowHOffset = 150;
				ArrowWOffset = -160;
			break;
		case 3: ArrowHOffset = 250;
				ArrowWOffset = -125;
				break;
	}

	float arrowsz(h / mArrowDimentions.y);
	if (arrowsz > 1.25f)
		arrowsz = 1.25f;

	fx.mpSpriteB->Draw(mArrowTex, Vector2((w / 2.f) + ArrowWOffset, (h / 2.f) + ArrowHOffset), nullptr, Colours::White, 0, mArrowDimentions*0.5f, Vector2(arrowsz, arrowsz));


	GetGamepad()->Update();
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
		else if (GetGamepad()->GetState(0).leftStickY > 0){
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

		if (GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_A) && selected == 0) {
			GetStateManager()->changeState("LoadingState");
		}
		if (GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_A) && selected == 3) {
			PostQuitMessage(0);
		}
	}



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

void MainMenuState::Release() {
	FX::MyFX& fx = *FX::GetMyFX();

	fx.mCache.Release();

}