#include "GameOverState.h"
#include "CommonStates.h"
#include "Input.h"
#include "StateManager.h"
#include "UserInterfaceManager.h"
#include "GameObjectManager.h"
#include "Mesh.h"
#include "AudioMgrFMOD.h"


GameOverState::GameOverState()
	:
	State("GameOverState")
{
	
}

void GameOverState::Init() {
	handled = false;
	selected = 0;
	gamepadDown = false;
	LoadTextures();

	ShowCursor(true);

	mLoadThread = std::async(launch::async, &GameOverState::handleGameOver, this);
}

void GameOverState::handleGameOver() {
	GetMeshManager()->Release();
	handled = true;
}

void GameOverState::Update(float dTime) {
	GetIAudioMgr()->Update();
	if (GetIAudioMgr()->GetSongMgr()->IsPlaying(musicHdl) == false)
		GetIAudioMgr()->GetSongMgr()->Play("spookyMusic", true, false, &musicHdl, 0.5);

	if (handled) {
		GetStateManager()->changeState("MainMenuState");
	}
	GetGamepad()->Update();
	if (GetGamepad()->IsConnected(0)) {

		if (GetGamepad()->GetState(0).leftStickY < 0) {
			if (!gamepadDown) {
				if (selected == 2)
					selected = 0;
				else
					selected++;
			}
			gamepadDown = true;
		}
		else if (GetGamepad()->GetState(0).leftStickY > 0) {
			if (!gamepadDown) {
				if (selected == 0)
					selected = 2;
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
		if (GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_A) && selected == 2) {
			GetStateManager()->changeState("MainMenu");
		}
	}
}

void GameOverState::Render(float dTime) {
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

	////////////////////////////////////////////// PLAY AGAIN //////////////////////////////////////////////////////////////////////////////
	GameOverState::bounds boundsOfPlayAgain = drawButton(mpPlayAgainTex, mPlayAgainDimentions, -50, 0);

	if (
		((GetMouseAndKeys()->GetMousePos(true).x >= boundsOfPlayAgain.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= boundsOfPlayAgain.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= boundsOfPlayAgain.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= boundsOfPlayAgain.bottomRight.y))
		)
	{
		selected = 0;
	}

	if (
		GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
		&&
		((GetMouseAndKeys()->GetMousePos(true).x >= boundsOfPlayAgain.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= boundsOfPlayAgain.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= boundsOfPlayAgain.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= boundsOfPlayAgain.bottomRight.y))
		)
	{
		GetStateManager()->changeState("LoadingState");
	}


	////////////////////////////////////////////// HIGHSCORES //////////////////////////////////////////////////////////////////////////////
	GameOverState::bounds boundsOfHighscore = drawButton(mpHighscoreTex, mHighscoreDimentions, 50, 0);
	if (
		((GetMouseAndKeys()->GetMousePos(true).x >= boundsOfHighscore.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= boundsOfHighscore.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= boundsOfHighscore.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= boundsOfHighscore.bottomRight.y))
		)
	{
		selected = 1;
	}

	if (
		GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
		&&
		((GetMouseAndKeys()->GetMousePos(true).x >= boundsOfHighscore.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= boundsOfHighscore.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= boundsOfHighscore.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= boundsOfHighscore.bottomRight.y))
		)
	{
		//GetStateManager()->changeState("LoadingState");
	}

	////////////////////////////////////////////// MAINMENU //////////////////////////////////////////////////////////////////////////////
	GameOverState::bounds boundsOfMainMenu = drawButton(mpMainMenuTex, mMainMenuDimentions, 150, 0);
	if (
		((GetMouseAndKeys()->GetMousePos(true).x >= boundsOfMainMenu.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= boundsOfMainMenu.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= boundsOfMainMenu.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= boundsOfMainMenu.bottomRight.y))
		)
	{
		selected = 2;
	}

	if (
		GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
		&&
		((GetMouseAndKeys()->GetMousePos(true).x >= boundsOfMainMenu.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= boundsOfMainMenu.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= boundsOfMainMenu.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= boundsOfMainMenu.bottomRight.y))
		)
	{
		GetStateManager()->changeState("MainMenu");
	}

	int ArrowHOffset, ArrowWOffset;
	switch (selected) {

	case 0: ArrowHOffset = -50;
		ArrowWOffset = -240;
		break;
	case 1: ArrowHOffset = 50;
		ArrowWOffset = -255;
		break;
	case 2: ArrowHOffset = 150;
		ArrowWOffset = -250;
		break;
	}

	float arrowsz(h / mArrowDimentions.y);
	if (arrowsz > 1.25f)
		arrowsz = 1.25f;

	fx.mpSpriteB->Draw(mArrowTex, Vector2((w / 2.f) + ArrowWOffset, (h / 2.f) + ArrowHOffset), nullptr, Colours::White, 0, mArrowDimentions*0.5f, Vector2(arrowsz, arrowsz));

	fx.mpSpriteB->End();



	EndRender();
}


void GameOverState::LoadTextures() {
	FX::MyFX& fx = *FX::GetMyFX();

	mpBackgroundTex = fx.mCache.LoadTexture("Screens/GameOver/GameOver.dds", true, gd3dDevice);
	mBackgroundDimentions = fx.mCache.Get(mpBackgroundTex).dim;

	mpPlayAgainTex = fx.mCache.LoadTexture("Screens/GameOver/playagain.dds", true, gd3dDevice);
	mpHighscoreTex = fx.mCache.LoadTexture("Screens/GameOver/HighscoreButton.dds", true, gd3dDevice);
	mpMainMenuTex = fx.mCache.LoadTexture("Screens/GameOver/mainMenuButton.dds", true, gd3dDevice);
	mPlayAgainDimentions = fx.mCache.Get(mpPlayAgainTex).dim;
	mHighscoreDimentions = fx.mCache.Get(mpHighscoreTex).dim;
	mMainMenuDimentions = fx.mCache.Get(mpMainMenuTex).dim;

	mArrowTex = fx.mCache.LoadTexture("Screens/MainMenu/Arrow.dds", true, gd3dDevice);
	mArrowDimentions = fx.mCache.Get(mArrowTex).dim;
}

GameOverState::bounds GameOverState::drawButton(ID3D11ShaderResourceView *tex, Vector2 dimentions, float hOffset, float wOffset) {
	GameOverState::bounds boundsOfbutton;
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

void GameOverState::ReleaseFromLevel() {
	FX::MyFX& fx = *FX::GetMyFX();
	fx.mCache.Release();
}

void GameOverState::Destruct() {

}

void GameOverState::setStats(vector<levelStats> ls)
{
	//Do something with stored stats :)_

}