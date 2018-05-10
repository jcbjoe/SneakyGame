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
	gamepadDown = false;

	LoadTextures();

	ShowCursor(true);

	selector = 0;

	mLoadThread = std::async(launch::async, &GameOverState::handleGameOver, this);

	pressedOnInit = false;

	GetGamepad()->Update();
	if (GetGamepad()->IsConnected(0))
	{
		if (GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_A)) {
			pressedOnInit = true;
		}
	}
}

void GameOverState::handleGameOver() {
	GetMeshManager()->Release();
	handled = true;
}

void GameOverState::Update(float dTime) {
	GetIAudioMgr()->Update();
	if (GetIAudioMgr()->GetSongMgr()->IsPlaying(musicHdl) == false)
		GetIAudioMgr()->GetSongMgr()->Play("spookyMusic", true, false, &musicHdl, 0.5);

	//if (handled) {
	//	GetStateManager()->changeState("MainMenuState");
	//}

	GetGamepad()->Update();

	if (GetGamepad()->IsConnected(0))
		if (!(GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_A)) && pressedOnInit) {
			pressedOnInit = false;
		}

	if (GetGamepad()->IsConnected(0)) {

		if (GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_A) && !pressedOnInit) {
			saveToFile();
			levels = 0;
			totCoinsDeposited = 0;
			totTimeTaken = 0;
			keyPressed = false;
			GetStateManager()->changeState("MainMenuState");
		}
	}

	if (keyPressed == false)
	{
		//If ENTER KEY IS NOT PRESSED
		if (GetMouseAndKeys()->IsPressed(VK_W) || (GetGamepad()->IsConnected(0) && GetGamepad()->GetState(0).leftStickY > 0)) //up
		{
			keyPressed = true;

			if (name[selector] != 65)
				name[selector] = (char)name[selector] - 1;
		}
		else if (GetMouseAndKeys()->IsPressed(VK_S) || (GetGamepad()->IsConnected(0) && GetGamepad()->GetState(0).leftStickY < 0)) // down
		{
			keyPressed = true;

			if (name[selector] != 90)
				name[selector] = (char)name[selector] + 1;
		}
		else if (GetMouseAndKeys()->IsPressed(VK_A) || (GetGamepad()->IsConnected(0) && GetGamepad()->GetState(0).leftStickX < 0)) // left
		{
			keyPressed = true;
			if (selector == 0)
				selector = 2;
			else
				selector -= 1;
		}
		else if (GetMouseAndKeys()->IsPressed(VK_D) || (GetGamepad()->IsConnected(0) && GetGamepad()->GetState(0).leftStickX < 0)) //Right
		{
			keyPressed = true;
			if (selector == 2)
				selector = 0;
			else
				selector += 1;
		}
		else if (GetMouseAndKeys()->IsPressed(VK_RETURN) || GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON))
		{
			keyPressed = true;
			//SUBMIT HIGHSCORES AND GO TO MAIN MENU
			saveToFile();
			levels = 0;
			totCoinsDeposited = 0;
			totTimeTaken = 0;
			keyPressed = false;
			GetStateManager()->changeState("MainMenuState");
		}
	}
	
	if (GetGamepad()->IsConnected(0))
	{
		if (GetGamepad()->GetState(0).leftStickY == 0 && GetGamepad()->GetState(0).leftStickX == 0 && !GetMouseAndKeys()->IsPressed(VK_W) && !GetMouseAndKeys()->IsPressed(VK_A) && !GetMouseAndKeys()->IsPressed(VK_S) && !GetMouseAndKeys()->IsPressed(VK_D) && !GetMouseAndKeys()->IsPressed(VK_RETURN))
		{
			keyPressed = false;
		}
	}
	else
	{
		if (!GetMouseAndKeys()->IsPressed(VK_W) && !GetMouseAndKeys()->IsPressed(VK_A) && !GetMouseAndKeys()->IsPressed(VK_S) && !GetMouseAndKeys()->IsPressed(VK_D) && !GetMouseAndKeys()->IsPressed(VK_RETURN))
		{
			keyPressed = false;
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

	////////////////////////////////////////////// HIGHSCORES //////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////// MAINMENU //////////////////////////////////////////////////////////////////////////////
	GameOverState::bounds boundsOfMainMenu = drawButton(mpMainMenuTex, mMainMenuDimentions, 300, 0);

	int ArrowHOffset, ArrowWOffset;
	ArrowHOffset = 300;
	ArrowWOffset = -250;

	float arrowsz(h / mArrowDimentions.y);
	if (arrowsz > 1.25f)
		arrowsz = 1.25f;


	//Arrow on main menu button
	fx.mpSpriteB->Draw(mArrowTex, Vector2((w / 2.f) + ArrowWOffset, (h / 2.f) + ArrowHOffset), nullptr, Colours::White, 0, mArrowDimentions*0.5f, Vector2(arrowsz, arrowsz));

	//How long you survived
	float tot = totCoinsDeposited;
	float tot2 = totTimeTaken;
	float score = (tot / tot2) * 100.0f;
	int scr = (int)score;

	wstringstream wss;
	wss << "YOU SURVIVED TO LEVEL " << to_string(levels).c_str() << " AND GOT A LOOT EFFICIENCY SCORE OF " << to_string(scr).c_str();
	mpComicSans->DrawString(fx.mpSpriteB, wss.str().c_str(), Vector2(w * 0.35f, h * 0.35f), Colors::White, 0, Vector2(0, 0), Vector2(0.00052f * w, 0.00052f * w));

	wstringstream wss2;
	wss2 << "USE MOVEMENT KEYS TO ENTER A NAME, PRESS 'A' / CLICK TO SUBMIT SCORE";
	mpComicSans->DrawString(fx.mpSpriteB, wss2.str().c_str(), Vector2(0.30f * w, h * 0.4f), Colors::White, 0, Vector2(0, 0), Vector2(0.00052f * w, 0.00052f * w));


	wstringstream namewss;
	namewss << "[" << name[0] << "] [" << name[1] << "] [" << name[2] << "]";
	mpComicSans->DrawString(fx.mpSpriteB, namewss.str().c_str(), Vector2(0.4f * w, h * 0.5f), Colors::White, 0, Vector2(0, 0), Vector2(0.00156 * w, 0.00156 * w));
	
	//wstringstream test2;
	//test2 << " " << name[1] << " ";
	//mpComicSans->DrawString(fx.mpSpriteB, test2.str().c_str(), Vector2(0.25f * w + 100.0f, 50.0f), Colors::White, 0, Vector2(0, 0), Vector2(3.f, 3.f));
	//
	//wstringstream test3;
	//test3 << " " << name[2] << " ";
	//mpComicSans->DrawString(fx.mpSpriteB, test3.str().c_str(), Vector2(0.25f * w + 200.0f, 50.0f), Colors::White, 0, Vector2(0, 0), Vector2(3.f, 3.f));
	//
	wstringstream slector;
	slector << "[v] ";
	mpComicSans->DrawString(fx.mpSpriteB, slector.str().c_str(), Vector2(0.4f * w + (w * 0.06f * selector), h * 0.44), Colors::White, 0, Vector2(0, 0), Vector2(0.00156 * w, 0.00156 * w));

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

vector<PlayerStats> GameOverState::loadScores()
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

			// DECRYPT
			//char x = readIn.Name[0];
			//char y = readIn.Name[1];
			//char z = readIn.Name[2];
			//
			//x -= 5;
			//y -= 4;
			//z -= 3;
			//
			//readIn.Name[0] = x;
			//readIn.Name[1] = y;
			//readIn.Name[2] = z;
			//
			//readIn.ScoreGained -= 50;
			//readIn.LevelReached -= 50;

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

void GameOverState::updateScores(vector<PlayerStats>& allScores, const PlayerStats & playerScore)
{
	//For every score in all scores
	bool dataFound(false);

	for (int i = 0; (i < allScores.size() - 1); i++)
	{
		//If score is not being stored yet
		if (!dataFound)
		{
			//Need 2 if statements since score is ordered by level THEN score!

			//If should be inserted above (different level)
			if (playerScore.LevelReached > allScores[i].LevelReached)
			{
				//Insert data above
				allScores.insert(allScores.begin() + i, playerScore);
				dataFound = true;
			}
			//If should be inserted above (same level)
			else if (playerScore.LevelReached == allScores[i].LevelReached)
			{
				if (playerScore.ScoreGained >= allScores[i].ScoreGained)
				{
					//Insert data above
					allScores.insert(allScores.begin() + i, playerScore);
					dataFound = true;
				}
			}
		}
		else
		{
			//Can only have a maximum of 5 highscores
			if ((allScores.size() - 1) > 5)
				allScores.pop_back();
		}
	}
}

void GameOverState::saveScores(const vector<PlayerStats>& scoresToSave)
{
	ofstream output("highscores.txt");
	//For every score in the vector
	for (int i = 0; i < scoresToSave.size() - 1; i++)
	{
		output << scoresToSave[i].Name << " " << scoresToSave[i].LevelReached << " " << scoresToSave[i].ScoreGained << "\n";
	}
	output.close();
}

void GameOverState::saveToFile()
{
	//Load in from file
	vector<PlayerStats> currentScores = loadScores();
	
	stringstream pName;
	pName << name[0] << name[1] << name[2];

	float tot = totCoinsDeposited;
	float tot2 = totTimeTaken;

	float score = (tot / tot2) * 100.0f;
	int scr = (int)score;

	//int score = (int)((float)totCoinsDeposited / (float)totTimeTaken) * 100.0f;
	//alter loaded vector so it contains/doesnt contain score
	PlayerStats dataToSave{ pName.str() , levels, scr };

	// "ENCRYPT - obviously basic but any encryption would follow same steps, not worth complicating"
	//for (int i = 0; i < dataToSave.Name.size() - 1; i++)
	//{
	//	dataToSave.Name[i] += 60;
	////}
	//
	//char x = dataToSave.Name[0];
	//char y = dataToSave.Name[1];
	//char z = dataToSave.Name[2];
	//
	//x += 5;
	//y += 4;
	//z += 3;
	//
	//dataToSave.Name[0] = x;
	//dataToSave.Name[1] = y;
	//dataToSave.Name[2] = z;
	//
	//dataToSave.ScoreGained += 50;
	//dataToSave.LevelReached += 50;

	updateScores(currentScores, dataToSave);

	//save back to file
	saveScores(currentScores);
}

