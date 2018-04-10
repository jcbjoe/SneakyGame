#include "UserInterfaceManager.h"
#include <sstream>
#include <time.h>
#include "FX.h"
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

	start = time(0);
}

void UserInterfaceManager::printDebugText(string text) {
	int seconds_since_start = difftime(time(0), start);
	debugTextVector.push_back(debugText{ text, seconds_since_start});
}

void UserInterfaceManager::updateUI(const float fpsNumber, const bool& isCrouching, const int playerScore, const int& playerDeposited, const int& hasRedKey, const int& hasBlueKey) {

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

	wstringstream coinsPickedUp;
	coinsPickedUp << "Coins Collected: " << playerScore;
	mpAlgerian->DrawString(mpSpriteBatch, coinsPickedUp.str().c_str(), Vector2(0, 50), Colors::GreenYellow, 0, Vector2(0, 0), Vector2(1.f, 1.f));

	wstringstream coinsDeposited;
	coinsDeposited << "Coins Collected: " << playerDeposited;
	mpAlgerian->DrawString(mpSpriteBatch, coinsDeposited.str().c_str(), Vector2(0, 100), Colors::AliceBlue, 0, Vector2(0, 0), Vector2(1.f, 1.f));

	wstringstream redKeyFound;
	if(hasRedKey)
		redKeyFound << "Red Key Collected";
	mpAlgerian->DrawString(mpSpriteBatch, redKeyFound.str().c_str(), Vector2(0, 100), Colors::IndianRed, 0, Vector2(0, 0), Vector2(1.f, 1.f));

	wstringstream blueKeyFound;
	if (hasBlueKey)
		blueKeyFound << "Blue Key Collected";
	mpAlgerian->DrawString(mpSpriteBatch, blueKeyFound.str().c_str(), Vector2(0, 150), Colors::DeepSkyBlue, 0, Vector2(0, 0), Vector2(1.f, 1.f));

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