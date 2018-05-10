#include "HighscoreState.h"
#include "CommonStates.h"
#include "Input.h"
#include "StateManager.h"
#include "UserInterfaceManager.h"
#include "GameObjectManager.h"
#include "Mesh.h"
#include "AudioMgrFMOD.h"


HighscoreState::HighscoreState()
	:
	State("HighscoreState")
{
	mpComicSans = new SpriteFont(gd3dDevice, L"../bin/data/comicSansMS.spritefont");
	assert(mpComicSans);
}

void HighscoreState::Init() {
	selected = 0;

	LoadTextures();

	ShowCursor(true);
	
	statsToShow = loadScores();

	pressedOnInit = false;

	GetGamepad()->Update();

	if (GetGamepad()->IsConnected(0))
	{
		if (GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_A))
		{
			pressedOnInit = true;
		}
	}
}

void HighscoreState::Update(float dTime) {
	GetIAudioMgr()->Update();
	if (GetIAudioMgr()->GetSongMgr()->IsPlaying(musicHdl) == false)
		GetIAudioMgr()->GetSongMgr()->Play("spookyMusic", true, false, &musicHdl, 0.5);

	GetGamepad()->Update();

	if (GetGamepad()->IsConnected(0))
		if (!(GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_A)) && pressedOnInit) {
			pressedOnInit = false;
		}

	if (GetGamepad()->IsConnected(0)) {

		if (GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_A) && !pressedOnInit) {
			GetStateManager()->changeState("MainMenuState");
		}
	}
}

void HighscoreState::Render(float dTime) {
	BeginRender(Colours::Black);

	FX::MyFX& fx = *FX::GetMyFX();
	ResetStatesAfterSprites();
	FX::SetupDirectionalLight(0, true, Vector3(-0.7f, -0.7f, 0.7f), Vector3(0.7f, 0.65f, 0.65f), Vector3(0.15f, 0.1f, 0.1f), Vector3(0.01f, 0.01f, 0.01f));

	CommonStates state(gd3dDevice);
	fx.mpSpriteB->Begin(SpriteSortMode_Deferred, state.NonPremultiplied());

	//Show Background
	int w, h;
	GetClientExtents(w, h);
	float sz(h / mBackgroundDimentions.y);
	if (sz > 1.25f)
		sz = 1.25f;
	fx.mpSpriteB->Draw(mpBackgroundTex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mBackgroundDimentions*0.5f, Vector2(sz, sz));


	////////////////////////////////////////////// MAINMENU //////////////////////////////////////////////////////////////////////////////
	HighscoreState::bounds boundsOfMainMenu = drawButton(mpMainMenuTex, mMainMenuDimentions, 300, 0);
	if (
		((GetMouseAndKeys()->GetMousePos(true).x >= boundsOfMainMenu.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= boundsOfMainMenu.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= boundsOfMainMenu.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= boundsOfMainMenu.bottomRight.y))
		)
	{
		selected = 0;
	}

	if (
		GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
		&&
		((GetMouseAndKeys()->GetMousePos(true).x >= boundsOfMainMenu.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= boundsOfMainMenu.bottomRight.x))
		&&
		((GetMouseAndKeys()->GetMousePos(true).y >= boundsOfMainMenu.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= boundsOfMainMenu.bottomRight.y))
		)
	{
		GetStateManager()->changeState("MainMenuState");
	}


	//Show Arrow
	float arrowsz(h / mArrowDimentions.y);
	if (arrowsz > 1.25f)
		arrowsz = 1.25f;
	fx.mpSpriteB->Draw(mArrowTex, Vector2((w / 2.f) + -240, (h / 2.f) + 300), nullptr, Colours::White, 0, mArrowDimentions*0.5f, Vector2(arrowsz, arrowsz));


	//Show highscores
	
	wstringstream name;
	name << "NAME: ";
	mpComicSans->DrawString(fx.mpSpriteB, name.str().c_str() , Vector2(w / 2.0f -w * 0.2f, h / 2 - h * 0.25f), Colors::White, 0, Vector2(0, 0), Vector2(2.f, 2.f));

	wstringstream lvl;
	lvl << "LEVEL: ";
	mpComicSans->DrawString(fx.mpSpriteB, lvl.str().c_str(), Vector2(w / 2.0f, h / 2 - h * 0.25f), Colors::White, 0, Vector2(0, 0), Vector2(2.f, 2.f));

	wstringstream scr;
	scr << "SCORE: ";
	mpComicSans->DrawString(fx.mpSpriteB, scr.str().c_str(), Vector2(w / 2.0f + w * 0.2f, h / 2 - h * 0.25f), Colors::White, 0, Vector2(0, 0), Vector2(2.f, 2.f));


	//For every score in the board
	for (int i = 0; i < statsToShow.size() - 1; i++)
	{
		//Must use char for wstringstream

		wstringstream playerName;
		playerName << statsToShow[i].Name[0] << statsToShow[i].Name[1] << statsToShow[i].Name[2];
		mpComicSans->DrawString(fx.mpSpriteB, playerName.str().c_str() , Vector2(w / 2.0f + (-w * 0.2f), h / 2 + (h * 0.05f * i + 1) - h * 0.15f), Colors::White, 0, Vector2(0, 0), Vector2(2.f, 2.f));

		wstringstream playerLevel;
		playerLevel << statsToShow[i].LevelReached;
		mpComicSans->DrawString(fx.mpSpriteB, playerLevel.str().c_str(), Vector2(w / 2.0f , h / 2 + (h * 0.05f * i + 1) - h * 0.15f), Colors::White, 0, Vector2(0, 0), Vector2(2.f, 2.f));

		wstringstream playerScore;
		playerScore << statsToShow[i].ScoreGained;
		mpComicSans->DrawString(fx.mpSpriteB, playerScore.str().c_str(), Vector2(w / 2.0f + (w * 0.2f), h / 2 + (h * 0.05f * i +1 ) - h * 0.15f), Colors::White, 0, Vector2(0, 0), Vector2(2.f, 2.f));

	}
	//showHighscores();

	fx.mpSpriteB->End();



	EndRender();
}


void HighscoreState::LoadTextures() {
	FX::MyFX& fx = *FX::GetMyFX();

	mpBackgroundTex = fx.mCache.LoadTexture("Screens/Highscores/HighscoreScreen.dds", true, gd3dDevice);
	mBackgroundDimentions = fx.mCache.Get(mpBackgroundTex).dim;

	mpMainMenuTex = fx.mCache.LoadTexture("Screens/GameOver/mainMenuButton.dds", true, gd3dDevice);
	mMainMenuDimentions = fx.mCache.Get(mpMainMenuTex).dim;

	mArrowTex = fx.mCache.LoadTexture("Screens/MainMenu/Arrow.dds", true, gd3dDevice);
	mArrowDimentions = fx.mCache.Get(mArrowTex).dim;
}

HighscoreState::bounds HighscoreState::drawButton(ID3D11ShaderResourceView *tex, Vector2 dimentions, float hOffset, float wOffset) {
	HighscoreState::bounds boundsOfbutton;
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

void HighscoreState::ReleaseFromLevel() {
	FX::MyFX& fx = *FX::GetMyFX();
	fx.mCache.Release();
}

void HighscoreState::Destruct() {
	delete mpComicSans;
	delete mpSpriteBatch;
}

vector<PlayerStats> HighscoreState::loadScores()
{
	//Open file to input into
	ifstream input("highscores.txt");

	//Where we will store the data from file
	vector<PlayerStats> allDataFromFile;

	//If we successfully opened the file
	if (input.is_open())
	{
		//Until we get to the end of the file
		while (!input.eof())
		{
			//Read into an object and push it to the vector
			PlayerStats readIn;
			input >> readIn.Name >> readIn.LevelReached >> readIn.ScoreGained;
			allDataFromFile.push_back(readIn);
		}
	}
	else
	{
		//LOAD RESET FILE
		allDataFromFile.push_back(PlayerStats{ "NAN", 0, 0 });
		allDataFromFile.push_back(PlayerStats{ "NAN", 0, 0 });
		allDataFromFile.push_back(PlayerStats{ "NAN", 0, 0 });
		allDataFromFile.push_back(PlayerStats{ "NAN", 0, 0 });
		allDataFromFile.push_back(PlayerStats{ "NAN", 0, 0 });
	}
	//Finished with file, so close
	input.close();

	//return vector of all scores
	return allDataFromFile;
}

