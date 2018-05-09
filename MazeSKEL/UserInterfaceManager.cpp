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

	//--Collected Keys Begin
		mpRedKeyTex = fx.mCache.LoadTexture("RedKey2.dds", true, gd3dDevice);
		mRedKeyDimentions = fx.mCache.Get(mpRedKeyTex).dim;

		mpBlueKeyTex = fx.mCache.LoadTexture("BlueKey2.dds", true, gd3dDevice);
		mBlueKeyDimentions = fx.mCache.Get(mpBlueKeyTex).dim;

		mpYellowKeyTex = fx.mCache.LoadTexture("YellowKey2.dds", true, gd3dDevice);
		mYellowKeyDimentions = fx.mCache.Get(mpYellowKeyTex).dim;
	//--Collected Keys End

	//--Uncollected Keys Begin
		mpRedEmptyTex = fx.mCache.LoadTexture("RedKeyEmpty2.dds", true, gd3dDevice);
		mRedEmptyDimentions = fx.mCache.Get(mpRedEmptyTex).dim;

		mpBlueEmptyTex = fx.mCache.LoadTexture("BlueKeyEmpty2.dds", true, gd3dDevice);
		mBlueEmptyDimentions = fx.mCache.Get(mpBlueEmptyTex).dim;

		mpYellowEmptyTex = fx.mCache.LoadTexture("YellowKeyEmpty2.dds", true, gd3dDevice);
		mYellowEmptyDimentions = fx.mCache.Get(mpYellowEmptyTex).dim;
	//--Uncollected Keys End

	mpMinimapBGTex = fx.mCache.LoadTexture("mini.dds", true, gd3dDevice);
	mMinimapBGDimentions = fx.mCache.Get(mpMinimapBGTex).dim;

	mpMiniSquareTex = fx.mCache.LoadTexture("Grating3.dds", true, gd3dDevice);
	mMiniSquareDimensions = fx.mCache.Get(mpMiniSquareTex).dim;

	mpTimerTex = fx.mCache.LoadTexture("Timer.dds", true, gd3dDevice);
	mTimerDimensions = fx.mCache.Get(mpTimerTex).dim;

	//--Coins Begin
		mpUIChestTex = fx.mCache.LoadTexture("UIChest.dds", true, gd3dDevice);
		mUIChestDimentions = fx.mCache.Get(mpUIChestTex).dim;

		mpOneCoinTex = fx.mCache.LoadTexture("UIOneCoin.dds", true, gd3dDevice);
		mOneCoinDimentions = fx.mCache.Get(mpOneCoinTex).dim;

		mpTwoCoinTex = fx.mCache.LoadTexture("UITwoCoin.dds", true, gd3dDevice);
		mTwoCoinDimentions = fx.mCache.Get(mpTwoCoinTex).dim;

		mpThreeCoinTex = fx.mCache.LoadTexture("UIThreeCoin.dds", true, gd3dDevice);
		mThreeCoinDimentions = fx.mCache.Get(mpThreeCoinTex).dim;

		mpFourCoinTex = fx.mCache.LoadTexture("UIFourCoin.dds", true, gd3dDevice);
		mFourCoinDimentions = fx.mCache.Get(mpFourCoinTex).dim;

		mpFiveCoinTex = fx.mCache.LoadTexture("UIFiveCoin.dds", true, gd3dDevice);
		mFiveCoinDimentions = fx.mCache.Get(mpFiveCoinTex).dim;
	//--Coins End

	start = time(0);
	offx = 1.0f;
	offy = 9.0f;
}

void UserInterfaceManager::printDebugText(string text) {
	int seconds_since_start = difftime(time(0), start);
	debugTextVector.push_back(debugText{ text, seconds_since_start});
}

void UserInterfaceManager::updateUI(const float fpsNumber, const float Timer, const bool& isCrouching, const int playerScore, const int& playerDeposited, const int& maxCoins, const int& hasRedKey, const int& hasBlueKey, const int& hasYellowKey, const bool& RedKey, const bool& BlueKey, const bool& YellowKey, const float& pPosx, const float& pPosz, const float& pRotY, const bool& nearBoxFlag) {

	CommonStates state(gd3dDevice);
	mpSpriteBatch->Begin(SpriteSortMode_Deferred, state.NonPremultiplied());

	//background
	int w, h;
	GetClientExtents(w, h);

	//--- Begin Crouching Display 
	wstringstream crosshair;
	if (isCrouching)
	{
		crosshair << "--=--";
	}
	else
	{
		crosshair << "-<O>-";
	}
	//Draw Crosshair
	mpComicSans->DrawString(mpSpriteBatch, crosshair.str().c_str(), Vector2(w / 2.0f - 25, h / 2.0f), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));
	//--- End Crouching Display 

	//--- Begin FPS Counter
		if (showFPS) {
			wstringstream FPSCounter;
			FPSCounter << "FPS: " << fpsNumber;
			mpAlgerian->DrawString(mpSpriteBatch, FPSCounter.str().c_str(), Vector2(0, 0), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));
		}
	//--- End FPS Counter

	

	//--- Begin Coin Display
	//wstringstream coinsPickedUp;
	//coinsPickedUp << "Coins Collected: " << playerScore;
	//mpAlgerian->DrawString(mpSpriteBatch, coinsPickedUp.str().c_str(), Vector2(0, 50), Colors::GreenYellow, 0, Vector2(0, 0), Vector2(1.f, 1.f));
	//
	//wstringstream coinsDeposited;
	//coinsDeposited << "Coins Deposited: " << playerDeposited;
	//mpAlgerian->DrawString(mpSpriteBatch, coinsDeposited.str().c_str(), Vector2(0, 100), Colors::AliceBlue, 0, Vector2(0, 0), Vector2(1.f, 1.f));
	//--- End Coin Display

	////////////////////////
	//--- Minimap
	////////////////////////
	//MINIMAP VARIABLES (CAN CHANGE)
	float centerXPos =	w * 0.85f;
	float centerYPos =	h * 0.2f;
	float scaleOfMinimap = 0.000315f * w;
	float keyScale =	0.000156f * w;
	float coinScale =	0.00026f * w;
	float chestScale =	0.0000885f * w;
	//Scale variables for above values (DONT CHANGE)
	float scaleOfItems= 0.1143f * scaleOfMinimap;
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
			if (Object == 01 || Object == 11 || Object == 02 || Object == 03)
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
					case 01:
						transCol = Vector4(1.0f, 1.0f, 1.0f, transparencyPercentage);
						mpSpriteBatch->Draw(mpMiniSquareTex, Vector2(xCoord, yCoord), nullptr, transCol, -pRotY, mMiniSquareDimensions*0.5f, Vector2(scaleOfItems, scaleOfItems));
						break;
					case 11:
						transCol = Vector4(1.0f, 1.0f, 0.0f, transparencyPercentage);
						mpSpriteBatch->Draw(mpMiniSquareTex, Vector2(xCoord, yCoord), nullptr, transCol, -pRotY + PI / 4.0f, mMiniSquareDimensions*0.5f, Vector2(scaleOfItems * 0.6f, scaleOfItems * 0.6f));
						break;
					case 02:
						transCol = Vector4(0.5f, 0.3f, 0.0f, transparencyPercentage);
						mpSpriteBatch->Draw(mpMiniSquareTex, Vector2(xCoord, yCoord), nullptr, transCol, -pRotY, mMiniSquareDimensions*0.5f, Vector2(scaleOfItems, scaleOfItems * 0.2f));
						break;
					case 03:
						transCol = Vector4(0.5f, 0.3f, 0.0f, transparencyPercentage);
						mpSpriteBatch->Draw(mpMiniSquareTex, Vector2(xCoord, yCoord), nullptr, transCol, -pRotY, mMiniSquareDimensions*0.5f, Vector2(scaleOfItems * 0.2f, scaleOfItems));
						break;
					}
				}
			}
		}
	}
	//Draw player position on map
	mpSpriteBatch->Draw(mpMiniSquareTex, Vector2(centerXPos, centerYPos), nullptr, Colours::Green, 0, mMiniSquareDimensions*0.5f, Vector2(scaleOfItems * 0.75f, scaleOfItems * 0.75f));

	//Draw Timer
	mpSpriteBatch->Draw(mpTimerTex, Vector2(w / 2.0f, mTimerDimensions.y * scaleOfMinimap * 0.5f), nullptr, Colours::White, 0, mTimerDimensions*0.5f, Vector2(scaleOfMinimap, scaleOfMinimap));
	//--- Begin Timer Display
	wstringstream level;
	level << "Level: " << (GetLevelManager()->getCurrentLevelNumber() + 1);

	mpAlgerian->DrawString(mpSpriteBatch, level.str().c_str(), Vector2(w * 0.45f, 0), Colours::White, 0, Vector2(0, 0), Vector2(scaleOfMinimap * 2.5f, scaleOfMinimap * 2.5f));

	wstringstream clock;
	clock << fixed << setprecision(1) << Timer;
	Vector4 col = Colors::GreenYellow;
	if (Timer < 10.0f)
		col = Colors::MediumVioletRed;
	mpAlgerian->DrawString(mpSpriteBatch, clock.str().c_str(), Vector2(w * 0.47f, mTimerDimensions.y * scaleOfMinimap * 0.4f), col, 0, Vector2(0, 0), Vector2(scaleOfMinimap * 2.5f, scaleOfMinimap * 2.5f));
	
	//--- End Timer Display

	//--- KEY SIDE OVERLAY
	//Draw Key UI BG
	mpSpriteBatch->Draw(mpTimerTex, Vector2((w * 0.1f), h - (mTimerDimensions.y * scaleOfMinimap * 0.5f)), nullptr, Colours::White, PI, mTimerDimensions*0.5f, Vector2(scaleOfMinimap * 3.0f, scaleOfMinimap * 2.0f));
	//--- Begin Key Display
	if (hasRedKey)
		mpSpriteBatch->Draw(mpRedKeyTex, Vector2(0.040 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.58f)), nullptr, Colours::White, 0, mRedKeyDimentions*0.5f, Vector2(keyScale, keyScale));
	else if (RedKey)
		mpSpriteBatch->Draw(mpRedEmptyTex, Vector2(0.040 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.58f)), nullptr, Colours::White, 0, mRedEmptyDimentions*0.5f, Vector2(keyScale, keyScale));

	if (hasBlueKey)
		mpSpriteBatch->Draw(mpBlueKeyTex, Vector2(0.136 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.58f)), nullptr, Colours::White, 0, mBlueKeyDimentions*0.5f, Vector2(keyScale, keyScale));
	else if (BlueKey)
		mpSpriteBatch->Draw(mpBlueEmptyTex, Vector2(0.136 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.58f)), nullptr, Colours::White, 0, mBlueEmptyDimentions*0.5f, Vector2(keyScale, keyScale));

	if (hasYellowKey)
		mpSpriteBatch->Draw(mpYellowKeyTex, Vector2(0.226 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.58f)), nullptr, Colours::White, 0, mYellowKeyDimentions*0.5f, Vector2(keyScale, keyScale));
	else if (YellowKey)
		mpSpriteBatch->Draw(mpYellowEmptyTex, Vector2(0.226 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.58f)), nullptr, Colours::White, 0, mYellowEmptyDimentions*0.5f, Vector2(keyScale, keyScale));

	//Draw 
	mpSpriteBatch->Draw(mpTimerTex, Vector2((w * 0.9f), h - (mTimerDimensions.y * scaleOfMinimap * 0.5f)), nullptr, Colours::White, PI, mTimerDimensions*0.5f, Vector2(scaleOfMinimap * 3.0f, scaleOfMinimap * 4.0f));
	
	//--- Begin Coin Display
	//wstringstream coinsPickedUp;
	//coinsPickedUp << "Coins Collected: " << playerScore;
	//mpAlgerian->DrawString(mpSpriteBatch, coinsPickedUp.str().c_str(), Vector2(0, 100), Colors::GreenYellow, 0, Vector2(0, 0), Vector2(1.f, 1.f));

	//Drawing coins on screen
	switch (playerScore) {
	case 1:
		mpSpriteBatch->Draw(mpOneCoinTex, Vector2(0.83 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.61f)), nullptr, Colours::White, 0, mOneCoinDimentions*0.5f, Vector2(coinScale, coinScale));
		break;
	case 2:
		mpSpriteBatch->Draw(mpTwoCoinTex, Vector2(0.83 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.61f)), nullptr, Colours::White, 0, mTwoCoinDimentions*0.5f, Vector2(coinScale, coinScale));
		break;
	case 3:
		mpSpriteBatch->Draw(mpThreeCoinTex, Vector2(0.83 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.61f)), nullptr, Colours::White, 0, mThreeCoinDimentions*0.5f, Vector2(coinScale, coinScale));
		break;
	case 4:
		mpSpriteBatch->Draw(mpFourCoinTex, Vector2(0.83 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.61f)), nullptr, Colours::White, 0, mFourCoinDimentions*0.5f, Vector2(coinScale, coinScale));
		break;
	case 5:
		mpSpriteBatch->Draw(mpFiveCoinTex, Vector2(0.83 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.61f)), nullptr, Colours::White, 0, mFiveCoinDimentions*0.5f, Vector2(coinScale, coinScale));
		break;
	}

	//Collected coins
	mpSpriteBatch->Draw(mpUIChestTex, Vector2(0.85 * w, h - (mTimerDimensions.y * scaleOfMinimap * 1.60f)), nullptr, Colours::White, 0, mUIChestDimentions*0.5f, Vector2(chestScale, chestScale));
	
	wstringstream maxCoinsStr;
	maxCoinsStr << playerDeposited << "/" << maxCoins;
	mpAlgerian->DrawString(mpSpriteBatch, maxCoinsStr.str().c_str(), Vector2(0.90f * w, h - (mTimerDimensions.y * scaleOfMinimap * 1.8f)), Colors::White, 0, Vector2(0, 0), Vector2( scaleOfMinimap * 3.0f, scaleOfMinimap * 3.0f));




	//NEAR DEPOSIT BOX
	if ((nearBoxFlag == true) && playerScore > 0)
	{
		wstringstream nearBoxStr;
		nearBoxStr << "Press 'CROUCH' To Deposit";
		mpAlgerian->DrawString(mpSpriteBatch, nearBoxStr.str().c_str(), Vector2(0.3f * w, h * 0.70f), Colors::Orange, 0, Vector2(0, 0), Vector2(scaleOfMinimap * 3.0f, scaleOfMinimap * 3.0f));

	}

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