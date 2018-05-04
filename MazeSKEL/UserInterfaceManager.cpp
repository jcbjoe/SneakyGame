#include "UserInterfaceManager.h"
#include <sstream>
#include <time.h>
#include "StateManager.h"
#include "GameState.h"
#include "CommonStates.h"

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

	mpRedKeyTex = fx.mCache.LoadTexture("RedKey2.dds", true, gd3dDevice);
	mRedKeyDimentions = fx.mCache.Get(mpRedKeyTex).dim;

	mpBlueKeyTex = fx.mCache.LoadTexture("BlueKey2.dds", true, gd3dDevice);
	mBlueKeyDimentions = fx.mCache.Get(mpBlueKeyTex).dim;

	mpYellowKeyTex = fx.mCache.LoadTexture("YellowKey2.dds", true, gd3dDevice);
	mYellowKeyDimentions = fx.mCache.Get(mpYellowKeyTex).dim;

	mpRedEmptyTex = fx.mCache.LoadTexture("RedKeyEmpty2.dds", true, gd3dDevice);
	mRedEmptyDimentions = fx.mCache.Get(mpRedEmptyTex).dim;

	mpBlueEmptyTex = fx.mCache.LoadTexture("BlueKeyEmpty2.dds", true, gd3dDevice);
	mBlueEmptyDimentions = fx.mCache.Get(mpBlueEmptyTex).dim;

	mpYellowEmptyTex = fx.mCache.LoadTexture("YellowKeyEmpty2.dds", true, gd3dDevice);
	mYellowEmptyDimentions = fx.mCache.Get(mpYellowEmptyTex).dim;

	mpMinimapBGTex = fx.mCache.LoadTexture("mini.dds", true, gd3dDevice);
	mMinimapBGDimentions = fx.mCache.Get(mpMinimapBGTex).dim;

	mpMiniSquareTex = fx.mCache.LoadTexture("Grating3.dds", true, gd3dDevice);
	mMiniSquareDimensions = fx.mCache.Get(mpMiniSquareTex).dim;

	start = time(0);
	offx = 1.0f;
	offy = 9.0f;
}

void UserInterfaceManager::printDebugText(string text) {
	int seconds_since_start = difftime(time(0), start);
	debugTextVector.push_back(debugText{ text, seconds_since_start});
}

void UserInterfaceManager::updateUI(const float fpsNumber, const float Timer, const bool& isCrouching, const int playerScore, const int& playerDeposited, const int& hasRedKey, const int& hasBlueKey, const int& hasYellowKey, const bool& RedKey, const bool& BlueKey, const bool& YellowKey, const float& pPosx, const float& pPosz, const float& pRotY) {

	CommonStates state(gd3dDevice);
	mpSpriteBatch->Begin(SpriteSortMode_Deferred, state.NonPremultiplied());

	//background
	int w, h;
	GetClientExtents(w, h);

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
	mpComicSans->DrawString(mpSpriteBatch, crosshair.str().c_str(), Vector2(w / 2.0f - 25, h / 2.0f), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));
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
			mpSpriteBatch->Draw(mpRedKeyTex, Vector2(50, h - 50), nullptr, Colours::White, 0, mRedKeyDimentions*0.5f, Vector2(0.2, 0.2));
	else if (RedKey)
		mpSpriteBatch->Draw(mpRedEmptyTex, Vector2(50, h - 50), nullptr, Colours::White, 0, mRedEmptyDimentions*0.5f, Vector2(0.2f, 0.2f));

	wstringstream blueKeyFound;
	if (hasBlueKey)
		mpSpriteBatch->Draw(mpBlueKeyTex, Vector2(150, h - 50), nullptr, Colours::White, 0, mBlueKeyDimentions*0.5f, Vector2(0.2f, 0.2f));
	else if(BlueKey)
		mpSpriteBatch->Draw(mpBlueEmptyTex, Vector2(150, h - 50), nullptr, Colours::White, 0, mBlueEmptyDimentions*0.5f, Vector2(0.2f, 0.2f));

	wstringstream YellowKeyFound;
	if (hasYellowKey)
		mpSpriteBatch->Draw(mpYellowKeyTex, Vector2(250, h - 50), nullptr, Colours::White, 0, mYellowKeyDimentions*0.5f, Vector2(0.2f, 0.2f));
	else if (YellowKey)
		mpSpriteBatch->Draw(mpYellowEmptyTex, Vector2(250, h - 50), nullptr, Colours::White, 0, mYellowEmptyDimentions*0.5f, Vector2(0.2f, 0.2f));

	//--- End Key Display

	////////////////////////
	//--- Minimap
	////////////////////////
	//MINIMAP VARIABLES (CAN CHANGE)
	float centerXPos = w - 200.0f;
	float centerYPos = 200.0f;
	float scaleOfMinimap = 0.6f;
	//Scale variables for above values (DONT CHANGE)
	float scaleOfItems	 = 0.1143f * scaleOfMinimap;
	float distBetweenItems = 57.0f * scaleOfMinimap;
	float fadeOffLimit = 240.0f * scaleOfMinimap;
	////////////////////////

	//Draw minimap background
	mpSpriteBatch->Draw(mpMinimapBGTex, Vector2(centerXPos, centerYPos), nullptr, Colours::White, 0, mMinimapBGDimentions*0.5f, Vector2(scaleOfMinimap, scaleOfMinimap));

	Level* CurrLVL = GetLevelManager()->getCurrentLevel();

	float sinAngle = sin(pRotY + PI/2.0f);
	float cosAngle = cos(pRotY + PI/2.0f);

	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < 20; i++)
		{
			int Object = CurrLVL->getObjectAtCoordinate(i, j);
			//If a wall needs to be drawn
			if (Object == 1 || Object == 3 )
			{
				//I can simplify maths later - leaving it for now since it works.
				//Manipulate i/j so it rotates right way
				float atOriginx = i - pPosx;
				float atOriginy = j - pPosz;

				float xNew = (atOriginx * cosAngle) - (atOriginy * sinAngle);
				float yNew = (atOriginx * sinAngle) + (atOriginy * cosAngle);

				xNew += pPosx;
				yNew += pPosz;

				//Final coordinates to plot to screen
				float xCoord = centerXPos + (yNew * distBetweenItems) - (pPosz * distBetweenItems);
				float yCoord = centerYPos + xNew * distBetweenItems - (pPosx * distBetweenItems);

				//Check distance from player
				float xSqu = centerXPos - xCoord;
				float xs = xSqu * xSqu;

				float ySqu = centerYPos - yCoord;
				float ys = ySqu * ySqu;

				float sq = sqrt(xs + ys);

				//if should be shown on minimap
				if (sq < fadeOffLimit)
				{
					float transparencyPercentage = 1.0f;

					if (sq > fadeOffLimit * 0.9f)
					{
						float closenessToEdge = fadeOffLimit - sq;
						transparencyPercentage = closenessToEdge / (fadeOffLimit * 0.1f);
					}

					Vector4 transCol;
					switch (Object)
					{
					case 1:
						transCol = Vector4(1.0f, 1.0f, 1.0f, transparencyPercentage);
						mpSpriteBatch->Draw(mpMiniSquareTex, Vector2(xCoord, yCoord), nullptr, transCol, -pRotY, mMiniSquareDimensions*0.5f, Vector2(scaleOfItems, scaleOfItems));
						break;
					case 3:
						transCol = Vector4(1.0f, 1.0f, 0.0f, transparencyPercentage);
						mpSpriteBatch->Draw(mpMiniSquareTex, Vector2(xCoord, yCoord), nullptr, transCol, -pRotY + PI / 4.0f, mMiniSquareDimensions*0.5f, Vector2(scaleOfItems * 0.6f, scaleOfItems * 0.6f));
						break;
					}
				}
			}
		}
	}
	//Draw player position on map
	mpSpriteBatch->Draw(mpMiniSquareTex, Vector2(centerXPos, centerYPos), nullptr, Colours::Green, 0, mMiniSquareDimensions*0.5f, Vector2(scaleOfItems * 0.75f, scaleOfItems * 0.75f));

	

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