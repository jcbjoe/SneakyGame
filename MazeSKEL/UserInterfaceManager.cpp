#include "UserInterfaceManager.h"
#include <sstream>
#include <time.h>
#include "StateManager.h"
#include "GameState.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void UserInterfaceManager::initialiseUI(bool showFPS) {

	mpSpriteBatch = new SpriteBatch(gd3dImmediateContext);
	assert(mpSpriteBatch);

	//Fonts
	mpComicSans = new SpriteFont(gd3dDevice, L"../bin/data/comicSansMS.spritefont");
	assert(mpComicSans);
	mpAlgerian = new SpriteFont(gd3dDevice, L"../bin/data/algerian.spritefont");
	assert(mpAlgerian);

	FX::MyFX& fx = *FX::GetMyFX();

	mpPausedTex = fx.mCache.LoadTexture("paused.dds", true, gd3dDevice);
	mPausedDimentions = fx.mCache.Get(mpPausedTex).dim;

	mpRedKeyTex = fx.mCache.LoadTexture("RedKey5.dds", true, gd3dDevice);
	mRedKeyDimentions = fx.mCache.Get(mpRedKeyTex).dim;

	mpBlueKeyTex = fx.mCache.LoadTexture("BlueKey5.dds", true, gd3dDevice);
	mBlueKeyDimentions = fx.mCache.Get(mpBlueKeyTex).dim;

	mpYellowKeyTex = fx.mCache.LoadTexture("YellowKey5.dds", true, gd3dDevice);
	mYellowKeyDimentions = fx.mCache.Get(mpYellowKeyTex).dim;

	mpRedEmptyTex = fx.mCache.LoadTexture("RedKeyEmpty.dds", true, gd3dDevice);
	mRedEmptyDimentions = fx.mCache.Get(mpRedEmptyTex).dim;

	mpBlueEmptyTex = fx.mCache.LoadTexture("BlueKeyEmpty.dds", true, gd3dDevice);
	mBlueEmptyDimentions = fx.mCache.Get(mpBlueEmptyTex).dim;

	mpYellowEmptyTex = fx.mCache.LoadTexture("YellowKeyEmpty.dds", true, gd3dDevice);
	mYellowEmptyDimentions = fx.mCache.Get(mpYellowEmptyTex).dim;

	start = time(0);
}

void UserInterfaceManager::printDebugText(string text) {
	int seconds_since_start = difftime(time(0), start);
	debugTextVector.push_back(debugText{ text, seconds_since_start});
}

void UserInterfaceManager::updateUI(const float fpsNumber, const float Timer, const bool& isCrouching, const int playerScore, const int& playerDeposited, const int& hasRedKey, const int& hasBlueKey, const int& hasYellowKey, const bool& RedKey, const bool& BlueKey, const bool& YellowKey) {

	mpSpriteBatch->Begin();

	//--- Begin Crouching Display 
	wstringstream crouching;
	wstringstream crosshair;
	if (isCrouching)
	{
		crosshair << "--=--";
		crouching << "Crouched";
	}
	else
	{
		crosshair << "-<O>-";
		crouching << "Not Crouched";
	}
	//Draw Crosshair
	mpComicSans->DrawString(mpSpriteBatch, crosshair.str().c_str(), Vector2(495, 384), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));
	//Show crouching ui
	mpAlgerian->DrawString(mpSpriteBatch, crouching.str().c_str(), Vector2(100, 200), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));
	//--- End Crouching Display 

	//--- Begin FPS Counter
	if (showFPS) {
		wstringstream FPSCounter;
		FPSCounter << "FPS: " << fpsNumber;
		mpAlgerian->DrawString(mpSpriteBatch, FPSCounter.str().c_str(), Vector2(0, 0), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));
	}
	//--- End FPS Counter

	//--- Begin Timer Display
	wstringstream clock;
	clock  << "Time: " << fixed << setprecision(1) << Timer;
	mpAlgerian->DrawString(mpSpriteBatch, clock.str().c_str(), Vector2(830, 0), Colors::GreenYellow, 0, Vector2(0, 0), Vector2(1.f, 1.f));
	//--- End Timer Display

	//--- Begin Coin Display
	wstringstream coinsPickedUp;
	coinsPickedUp << "Coins Collected: " << playerScore;
	mpAlgerian->DrawString(mpSpriteBatch, coinsPickedUp.str().c_str(), Vector2(0, 50), Colors::GreenYellow, 0, Vector2(0, 0), Vector2(1.f, 1.f));

	wstringstream coinsDeposited;
	coinsDeposited << "Coins Deposited: " << playerDeposited;
	mpAlgerian->DrawString(mpSpriteBatch, coinsDeposited.str().c_str(), Vector2(0, 100), Colors::AliceBlue, 0, Vector2(0, 0), Vector2(1.f, 1.f));
	//--- End Coin Display

	//--- Begin Key Display
	wstringstream redKeyFound;
	if (hasRedKey)
		//redKeyFound << "Red Key Collected";
		//mpAlgerian->DrawString(mpSpriteBatch, redKeyFound.str().c_str(), Vector2(0, 100), Colors::IndianRed, 0, Vector2(0, 0), Vector2(1.f, 1.f));
		mpSpriteBatch->Draw(mpRedKeyTex, Vector2(25, 740), nullptr, Colours::White, 0, mRedKeyDimentions*0.5f, Vector2(0.1, 0.1));
	else if(RedKey)
		mpSpriteBatch->Draw(mpRedEmptyTex, Vector2(25, 740), nullptr, Colours::White, 0, mRedEmptyDimentions*0.5f, Vector2(0.1, 0.1));

	wstringstream blueKeyFound;
	if (hasBlueKey)
		//blueKeyFound << "Blue Key Collected";
		//mpAlgerian->DrawString(mpSpriteBatch, blueKeyFound.str().c_str(), Vector2(0, 150), Colors::DeepSkyBlue, 0, Vector2(0, 0), Vector2(1.f, 1.f));
		mpSpriteBatch->Draw(mpBlueKeyTex, Vector2(75, 740), nullptr, Colours::White, 0, mBlueKeyDimentions*0.5f, Vector2(0.1, 0.1));
	else if(BlueKey)
		mpSpriteBatch->Draw(mpBlueEmptyTex, Vector2(75, 740), nullptr, Colours::White, 0, mBlueEmptyDimentions*0.5f, Vector2(0.1, 0.1));

	wstringstream YellowKeyFound;
	if (hasYellowKey)
		//blueKeyFound << "Blue Key Collected";
		//mpAlgerian->DrawString(mpSpriteBatch, blueKeyFound.str().c_str(), Vector2(0, 150), Colors::DeepSkyBlue, 0, Vector2(0, 0), Vector2(1.f, 1.f));
		mpSpriteBatch->Draw(mpYellowKeyTex, Vector2(125, 740), nullptr, Colours::White, 0, mYellowKeyDimentions*0.5f, Vector2(0.1, 0.1));
	else if (YellowKey)
		mpSpriteBatch->Draw(mpYellowEmptyTex, Vector2(125, 740), nullptr, Colours::White, 0, mYellowEmptyDimentions*0.5f, Vector2(0.1, 0.1));
	//--- End Key Display

	//--- Begin Debug Text
	int count = 0;
	for (int elementInVector = debugTextVector.size(); elementInVector > 0; elementInVector--) {
		wstringstream textToAdd;
		textToAdd << debugTextVector.at(elementInVector - 1).text.c_str();
		int height = 25 * ((debugTextVector.size() - elementInVector) + 1);
		mpComicSans->DrawString(mpSpriteBatch, textToAdd.str().c_str(), Vector2(0, height), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));

		count++;
		if (count == 30)
			break;
	}
	//--- End Debug Text

	if (GetStateManager()->getCurrentState()->getStateName() == "MainGameState") {
		if (((GameState*)GetStateManager()->getCurrentState())->paused) {

			//background
			int w, h;
			GetClientExtents(w, h);
			float sz(h / mPausedDimentions.y);
			if (sz > 1.25f)
				sz = 1.25f;
			mpSpriteBatch->Draw(mpPausedTex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mPausedDimentions*0.5f, Vector2(sz, sz));
		}
	}

	mpSpriteBatch->End();

	int seconds_since_start = difftime(time(0), start);
	for (int elementInVector = 0; elementInVector < debugTextVector.size(); elementInVector++) {
		const int secondsToStayOnScreen = 5;
		debugText currentText = debugTextVector.at(elementInVector);
		if ((seconds_since_start - currentText.timeAdded) > secondsToStayOnScreen) {
			debugTextVector.erase(debugTextVector.begin() + elementInVector);
		}
	}

}

void UserInterfaceManager::Release()
{

}