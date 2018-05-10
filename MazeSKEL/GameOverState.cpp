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
	levels = 0;
	totCoinsDeposited = 0;
	totTimeTaken = 0;
	keyPressed = false;

	mpComicSans = new SpriteFont(gd3dDevice, L"../bin/data/comicSansMS.spritefont");
	assert(mpComicSans);
}

void GameOverState::Init() {
	handled = false;
	selected = 0;
	gamepadDown = false;

	

	LoadTextures();

	ShowCursor(true);

	selector = 0;

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

	if (keyPressed == false)
	{
		//If ENTER KEY IS NOT PRESSED
		if (GetMouseAndKeys()->IsPressed(VK_W)) //up
		{
			keyPressed = true;

			if (name[selector] != 65)
				name[selector] = (char)name[selector] - 1;
		}
		else if (GetMouseAndKeys()->IsPressed(VK_S)) // down
		{
			keyPressed = true;

			if (name[selector] != 90)
				name[selector] = (char)name[selector] + 1;
		}
		else if (GetMouseAndKeys()->IsPressed(VK_A)) // left
		{
			keyPressed = true;
			if (selector == 0)
				selector = 2;
			else
				selector -= 1;
		}
		else if (GetMouseAndKeys()->IsPressed(VK_D)) //Right
		{
			keyPressed = true;
			if (selector == 2)
				selector = 0;
			else
				selector += 1;
		}
		else if (GetMouseAndKeys()->IsPressed(VK_RETURN))
		{
			//SUBMIT HIGHSCORES AND GO TO MAIN MENU
		}
	}
	
	if (!GetMouseAndKeys()->IsPressed(VK_W) && !GetMouseAndKeys()->IsPressed(VK_A) && !GetMouseAndKeys()->IsPressed(VK_S) && !GetMouseAndKeys()->IsPressed(VK_D) && !GetMouseAndKeys()->IsPressed(VK_RETURN))
	{
		keyPressed = false;
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


	wstringstream wss;
	wss << "YOU SURVIVED TO LEVEL " << to_string(levels).c_str() << " AND COLLECTED " << to_string(totCoinsDeposited).c_str() << " IN " << to_string(totTimeTaken).c_str() << " SECONDS";
	mpComicSans->DrawString(fx.mpSpriteB, wss.str().c_str(), Vector2(0.0f, 0.0f), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));

	wstringstream wss2;
	wss2 << "USE MOVEMENT KEYS TO ENTER A NAME, ENTER TO SUBMIT SCORE";
	mpComicSans->DrawString(fx.mpSpriteB, wss2.str().c_str(), Vector2(0.25f * w, 20.0f), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));


	float sz(h / mBackgroundDimentions.y);
	if (sz > 1.25f)
		sz = 1.25f;
	fx.mpSpriteB->Draw(mpBackgroundTex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBackgroundDimentions*0.5f, Vector2(sz, sz));

	////////////////////////////////////////////// PLAY AGAIN //////////////////////////////////////////////////////////////////////////////
	GameOverState::bounds boundsOfPlayAgain = drawButton(mpPlayAgainTex, mPlayAgainDimentions, 100, 0);

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
	GameOverState::bounds boundsOfHighscore = drawButton(mpHighscoreTex, mHighscoreDimentions, 200, 0);
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
		GetStateManager()->changeState("HighscoreState");
	}

	////////////////////////////////////////////// MAINMENU //////////////////////////////////////////////////////////////////////////////
	GameOverState::bounds boundsOfMainMenu = drawButton(mpMainMenuTex, mMainMenuDimentions, 300, 0);
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

	case 0: ArrowHOffset = 100;
		ArrowWOffset = -240;
		break;
	case 1: ArrowHOffset = 200;
		ArrowWOffset = -255;
		break;
	case 2: ArrowHOffset = 300;
		ArrowWOffset = -250;
		break;
	}

	float arrowsz(h / mArrowDimentions.y);
	if (arrowsz > 1.25f)
		arrowsz = 1.25f;

	fx.mpSpriteB->Draw(mArrowTex, Vector2((w / 2.f) + ArrowWOffset, (h / 2.f) + ArrowHOffset), nullptr, Colours::White, 0, mArrowDimentions*0.5f, Vector2(arrowsz, arrowsz));

	wstringstream test1;
	test1 << " " << name[0] << " ";
	mpComicSans->DrawString(fx.mpSpriteB, test1.str().c_str(), Vector2(0.25f * w, 50.0f), Colors::White, 0, Vector2(0, 0), Vector2(3.f, 3.f));

	wstringstream test2;
	test2 << " " << name[1] << " ";
	mpComicSans->DrawString(fx.mpSpriteB, test2.str().c_str(), Vector2(0.25f * w + 100.0f, 50.0f), Colors::White, 0, Vector2(0, 0), Vector2(3.f, 3.f));

	wstringstream test3;
	test3 << " " << name[2] << " ";
	mpComicSans->DrawString(fx.mpSpriteB, test3.str().c_str(), Vector2(0.25f * w + 200.0f, 50.0f), Colors::White, 0, Vector2(0, 0), Vector2(3.f, 3.f));

	wstringstream test4;
	test4 << " v ";
	mpComicSans->DrawString(fx.mpSpriteB, test4.str().c_str(), Vector2(0.25f * w + 100.0f * selector, 25.0f), Colors::White, 0, Vector2(0, 0), Vector2(3.f, 3.f));

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
	delete mpComicSans;
	delete mpSpriteBatch;
}

void GameOverState::setStats(vector<levelStats> ls)
{
	for (int i = 0; i < ls.size(); i++)
	{
		levels += 1;
		totCoinsDeposited += ls[i].CoinsCollected;
		totTimeTaken += (int)ls[i].TimeTaken;
	}
}