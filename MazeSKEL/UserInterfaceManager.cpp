#include "UserInterfaceManager.h"
#include <sstream>
#include <time.h>
#include "StateManager.h"
#include "GameState.h"
#include "CommonStates.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

UserInterfaceManager::UserInterfaceManager() {
	//Fonts
	mpComicSans = new SpriteFont(gd3dDevice, L"../bin/data/comicSansMS.spritefont");
	assert(mpComicSans);
	mpAlgerian = new SpriteFont(gd3dDevice, L"../bin/data/algerian.spritefont");
	assert(mpAlgerian);
}

void UserInterfaceManager::initialiseUI(bool showFPS) {

	FX::MyFX& fx = *FX::GetMyFX();

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

		mpPausedTex = fx.mCache.LoadTexture("Screens/Paused/PausedBG.dds", true, gd3dDevice);
		mPausedDimentions = fx.mCache.Get(mpPausedTex).dim;

		mpMainMenuTex = fx.mCache.LoadTexture("Screens/Paused/MainMenuButton.dds", true, gd3dDevice);
		mMainMenuDimentions = fx.mCache.Get(mpMainMenuTex).dim;

		mpResumeTex = fx.mCache.LoadTexture("Screens/Paused/Resume.dds", true, gd3dDevice);
		mResumeDimentions = fx.mCache.Get(mpResumeTex).dim;

		mArrowTex = fx.mCache.LoadTexture("Screens/MainMenu/Arrow.dds", true, gd3dDevice);
		mArrowDimentions = fx.mCache.Get(mArrowTex).dim;

		selected = 0;

	start = time(0);
	offx = 1.0f;
	offy = 9.0f;

	gamepadDown = false;
	firstPause = false;

}

void UserInterfaceManager::printDebugText(string text) {
	int seconds_since_start = difftime(time(0), start);
	debugTextVector.push_back(debugText{ text, seconds_since_start});
}

void UserInterfaceManager::updateUI(const float fpsNumber, const float Timer, const bool& isCrouching, const int playerScore, const int& playerDeposited, const int& maxCoins, const int& hasRedKey, const int& hasBlueKey, const int& hasYellowKey, const bool& RedKey, const bool& BlueKey, const bool& YellowKey, const float& pPosx, const float& pPosz, const float& pRotY, const bool& nearBoxFlag) {

	FX::MyFX& fx = *FX::GetMyFX();
	CommonStates state(gd3dDevice);
	fx.mpSpriteB->Begin(SpriteSortMode_Deferred, state.NonPremultiplied());

	if (GetStateManager()->getCurrentStateName() == "MainGameState") {
		if (((GameState*)(GetStateManager()->getCurrentState()))->paused) {
			handlePauseMenu();
		}
		else {
			firstPause = false;



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
			mpComicSans->DrawString(fx.mpSpriteB, crosshair.str().c_str(), Vector2(w / 2.0f - 25, h / 2.0f), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));
			//--- End Crouching Display 

			//--- Begin FPS Counter
			if (showFPS) {
				wstringstream FPSCounter;
				FPSCounter << "FPS: " << fpsNumber;
				mpAlgerian->DrawString(fx.mpSpriteB, FPSCounter.str().c_str(), Vector2(0, 0), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));
			}
			//--- End FPS Counter



			//--- Begin Coin Display
			//wstringstream coinsPickedUp;
			//coinsPickedUp << "Coins Collected: " << playerScore;
			//mpAlgerian->DrawString(fx.mpSpriteB, coinsPickedUp.str().c_str(), Vector2(0, 50), Colors::GreenYellow, 0, Vector2(0, 0), Vector2(1.f, 1.f));
			//
			//wstringstream coinsDeposited;
			//coinsDeposited << "Coins Deposited: " << playerDeposited;
			//mpAlgerian->DrawString(fx.mpSpriteB, coinsDeposited.str().c_str(), Vector2(0, 100), Colors::AliceBlue, 0, Vector2(0, 0), Vector2(1.f, 1.f));
			//--- End Coin Display

			////////////////////////
			//--- Minimap
			////////////////////////
			//MINIMAP VARIABLES (CAN CHANGE)
			float centerXPos = w * 0.85f;
			float centerYPos = h * 0.2f;
			float scaleOfMinimap = 0.000315f * w;
			float keyScale = 0.000156f * w;
			float coinScale = 0.00026f * w;
			float chestScale = 0.0000885f * w;
			//Scale variables for above values (DONT CHANGE)
			float scaleOfItems = 0.1143f * scaleOfMinimap;
			float distBetweenItems = 57.0f * scaleOfMinimap;
			float fadeOffLimit = 240.0f * scaleOfMinimap;
			////////////////////////

			//Draw minimap background
			fx.mpSpriteB->Draw(mpMinimapBGTex, Vector2(centerXPos, centerYPos), nullptr, Colours::White, 0, mMinimapBGDimentions*0.5f, Vector2(scaleOfMinimap, scaleOfMinimap));

			Level* CurrLVL = GetLevelManager()->getCurrentLevel();

			float sinAngle = sin(pRotY + PI / 2.0f);
			float cosAngle = cos(pRotY + PI / 2.0f);

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
								fx.mpSpriteB->Draw(mpMiniSquareTex, Vector2(xCoord, yCoord), nullptr, transCol, -pRotY, mMiniSquareDimensions*0.5f, Vector2(scaleOfItems, scaleOfItems));
								break;
							case 11:
								transCol = Vector4(1.0f, 1.0f, 0.0f, transparencyPercentage);
								fx.mpSpriteB->Draw(mpMiniSquareTex, Vector2(xCoord, yCoord), nullptr, transCol, -pRotY + PI / 4.0f, mMiniSquareDimensions*0.5f, Vector2(scaleOfItems * 0.6f, scaleOfItems * 0.6f));
								break;
							case 02:
								transCol = Vector4(0.5f, 0.3f, 0.0f, transparencyPercentage);
								fx.mpSpriteB->Draw(mpMiniSquareTex, Vector2(xCoord, yCoord), nullptr, transCol, -pRotY, mMiniSquareDimensions*0.5f, Vector2(scaleOfItems, scaleOfItems * 0.2f));
								break;
							case 03:
								transCol = Vector4(0.5f, 0.3f, 0.0f, transparencyPercentage);
								fx.mpSpriteB->Draw(mpMiniSquareTex, Vector2(xCoord, yCoord), nullptr, transCol, -pRotY, mMiniSquareDimensions*0.5f, Vector2(scaleOfItems * 0.2f, scaleOfItems));
								break;
							}
						}
					}
				}
			}
			//Draw player position on map
			fx.mpSpriteB->Draw(mpMiniSquareTex, Vector2(centerXPos, centerYPos), nullptr, Colours::Green, 0, mMiniSquareDimensions*0.5f, Vector2(scaleOfItems * 0.75f, scaleOfItems * 0.75f));

			//Draw Timer
			fx.mpSpriteB->Draw(mpTimerTex, Vector2(w / 2.0f, mTimerDimensions.y * scaleOfMinimap * 0.5f), nullptr, Colours::White, 0, mTimerDimensions*0.5f, Vector2(scaleOfMinimap, scaleOfMinimap));
			//--- Begin Timer Display
			wstringstream level;
			level << "Level: " << (GetLevelManager()->getCurrentLevelNumber() + 1);

			mpAlgerian->DrawString(fx.mpSpriteB, level.str().c_str(), Vector2(w * 0.45f, 0), Colours::White, 0, Vector2(0, 0), Vector2(scaleOfMinimap * 2.5f, scaleOfMinimap * 2.5f));

			wstringstream clock;
			clock << fixed << setprecision(1) << Timer;
			Vector4 col = Colors::GreenYellow;
			if (Timer < 10.0f)
				col = Colors::MediumVioletRed;
			mpAlgerian->DrawString(fx.mpSpriteB, clock.str().c_str(), Vector2(w * 0.47f, mTimerDimensions.y * scaleOfMinimap * 0.4f), col, 0, Vector2(0, 0), Vector2(scaleOfMinimap * 2.5f, scaleOfMinimap * 2.5f));

			//--- End Timer Display

			//--- KEY SIDE OVERLAY
			//Draw Key UI BG
			fx.mpSpriteB->Draw(mpTimerTex, Vector2((w * 0.1f), h - (mTimerDimensions.y * scaleOfMinimap * 0.5f)), nullptr, Colours::White, PI, mTimerDimensions*0.5f, Vector2(scaleOfMinimap * 3.0f, scaleOfMinimap * 2.0f));
			//--- Begin Key Display
			if (hasRedKey)
				fx.mpSpriteB->Draw(mpRedKeyTex, Vector2(0.040 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.58f)), nullptr, Colours::White, 0, mRedKeyDimentions*0.5f, Vector2(keyScale, keyScale));
			else if (RedKey)
				fx.mpSpriteB->Draw(mpRedEmptyTex, Vector2(0.040 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.58f)), nullptr, Colours::White, 0, mRedEmptyDimentions*0.5f, Vector2(keyScale, keyScale));

			if (hasBlueKey)
				fx.mpSpriteB->Draw(mpBlueKeyTex, Vector2(0.136 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.58f)), nullptr, Colours::White, 0, mBlueKeyDimentions*0.5f, Vector2(keyScale, keyScale));
			else if (BlueKey)
				fx.mpSpriteB->Draw(mpBlueEmptyTex, Vector2(0.136 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.58f)), nullptr, Colours::White, 0, mBlueEmptyDimentions*0.5f, Vector2(keyScale, keyScale));

			if (hasYellowKey)
				fx.mpSpriteB->Draw(mpYellowKeyTex, Vector2(0.226 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.58f)), nullptr, Colours::White, 0, mYellowKeyDimentions*0.5f, Vector2(keyScale, keyScale));
			else if (YellowKey)
				fx.mpSpriteB->Draw(mpYellowEmptyTex, Vector2(0.226 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.58f)), nullptr, Colours::White, 0, mYellowEmptyDimentions*0.5f, Vector2(keyScale, keyScale));

			//Draw 
			fx.mpSpriteB->Draw(mpTimerTex, Vector2((w * 0.9f), h - (mTimerDimensions.y * scaleOfMinimap * 0.5f)), nullptr, Colours::White, PI, mTimerDimensions*0.5f, Vector2(scaleOfMinimap * 3.0f, scaleOfMinimap * 4.0f));

			//--- Begin Coin Display
			//wstringstream coinsPickedUp;
			//coinsPickedUp << "Coins Collected: " << playerScore;
			//mpAlgerian->DrawString(fx.mpSpriteB, coinsPickedUp.str().c_str(), Vector2(0, 100), Colors::GreenYellow, 0, Vector2(0, 0), Vector2(1.f, 1.f));

			//Drawing coins on screen
			switch (playerScore) {
			case 1:
				fx.mpSpriteB->Draw(mpOneCoinTex, Vector2(0.83 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.61f)), nullptr, Colours::White, 0, mOneCoinDimentions*0.5f, Vector2(coinScale, coinScale));
				break;
			case 2:
				fx.mpSpriteB->Draw(mpTwoCoinTex, Vector2(0.83 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.61f)), nullptr, Colours::White, 0, mTwoCoinDimentions*0.5f, Vector2(coinScale, coinScale));
				break;
			case 3:
				fx.mpSpriteB->Draw(mpThreeCoinTex, Vector2(0.83 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.61f)), nullptr, Colours::White, 0, mThreeCoinDimentions*0.5f, Vector2(coinScale, coinScale));
				break;
			case 4:
				fx.mpSpriteB->Draw(mpFourCoinTex, Vector2(0.83 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.61f)), nullptr, Colours::White, 0, mFourCoinDimentions*0.5f, Vector2(coinScale, coinScale));
				break;
			case 5:
				fx.mpSpriteB->Draw(mpFiveCoinTex, Vector2(0.83 * w, h - (mTimerDimensions.y * scaleOfMinimap * 0.61f)), nullptr, Colours::White, 0, mFiveCoinDimentions*0.5f, Vector2(coinScale, coinScale));
				break;
			}

			//Collected coins
			fx.mpSpriteB->Draw(mpUIChestTex, Vector2(0.85 * w, h - (mTimerDimensions.y * scaleOfMinimap * 1.60f)), nullptr, Colours::White, 0, mUIChestDimentions*0.5f, Vector2(chestScale, chestScale));

			wstringstream maxCoinsStr;
			maxCoinsStr << playerDeposited << "/" << maxCoins;
			mpAlgerian->DrawString(fx.mpSpriteB, maxCoinsStr.str().c_str(), Vector2(0.90f * w, h - (mTimerDimensions.y * scaleOfMinimap * 1.8f)), Colors::White, 0, Vector2(0, 0), Vector2(scaleOfMinimap * 3.0f, scaleOfMinimap * 3.0f));

			//NEAR DEPOSIT BOX
			if ((nearBoxFlag == true) && playerScore > 0)
			{
				wstringstream nearBoxStr;
				nearBoxStr << "Press 'CROUCH' To Deposit";
				mpAlgerian->DrawString(fx.mpSpriteB, nearBoxStr.str().c_str(), Vector2(0.3f * w, h * 0.70f), Colors::Orange, 0, Vector2(0, 0), Vector2(scaleOfMinimap * 3.0f, scaleOfMinimap * 3.0f));
				//wstringstream coinsDeposited;
				//coinsDeposited << "Coins Deposited: " << playerDeposited;
				//mpAlgerian->DrawString(fx.mpSpriteB, coinsDeposited.str().c_str(), Vector2(0, 100), Colors::AliceBlue, 0, Vector2(0, 0), Vector2(1.f, 1.f));
				//--- End Coin Display

			}

			//--- Begin Debug Text
			int count = 0;
			for (int elementInVector = debugTextVector.size(); elementInVector > 0; elementInVector--) {
				wstringstream textToAdd;
				textToAdd << debugTextVector.at(elementInVector - 1).text.c_str();
				int height = 25 * ((debugTextVector.size() - elementInVector) + 1);
				mpComicSans->DrawString(fx.mpSpriteB, textToAdd.str().c_str(), Vector2(0, height), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));



				//--- Begin Debug Text
				int count = 0;
				for (int elementInVector = debugTextVector.size(); elementInVector > 0; elementInVector--) {
					wstringstream textToAdd;
					textToAdd << debugTextVector.at(elementInVector - 1).text.c_str();
					int height = 25 * ((debugTextVector.size() - elementInVector) + 1);
					mpComicSans->DrawString(fx.mpSpriteB, textToAdd.str().c_str(), Vector2(0, height), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));

					count++;
					if (count == 30)
						break;
				}
				//--- End Debug Text



				int seconds_since_start = difftime(time(0), start);
				for (int elementInVector = 0; elementInVector < debugTextVector.size(); elementInVector++) {
					const int secondsToStayOnScreen = 5;
					debugText currentText = debugTextVector.at(elementInVector);
					if ((seconds_since_start - currentText.timeAdded) > secondsToStayOnScreen) {
						debugTextVector.erase(debugTextVector.begin() + elementInVector);
					}
				}
			}
		}
	}
	fx.mpSpriteB->End();
}

void UserInterfaceManager::Release()
{

	//Fonts
	delete mpComicSans;
	delete mpAlgerian;
}

void UserInterfaceManager::handlePauseMenu() {

	if (!firstPause) {
		firstPause = true;
		selected = 0;
		gamepadDown = false;
	}

	if (GetGamepad()->IsConnected(0)) {

		if (GetGamepad()->GetState(0).leftStickY < 0) {
			if (!gamepadDown) {
				if (selected == 1)
					selected = 0;
				else
					selected++;
			}
			gamepadDown = true;
		}
		else if (GetGamepad()->GetState(0).leftStickY > 0) {
			if (!gamepadDown) {
				if (selected == 0)
					selected = 1;
				else
					selected--;
			}
			gamepadDown = true;
		} else {
			if (gamepadDown) {
				gamepadDown = false;
			}
		}

		if (GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_A)) {
			if (selected == 0) {
				while (ShowCursor(false) >= 0) {};
				((GameState*)(GetStateManager()->getCurrentState()))->paused = false;
			}
			if (selected == 1) {
				GetStateManager()->changeState("MainMenu");
			}
		}
	}
	FX::MyFX& fx = *FX::GetMyFX();
		//background
		int w, h;
		GetClientExtents(w, h);
		float sz(h / mPausedDimentions.y);
		if (sz > 1.25f)
			sz = 1.25f;
		fx.mpSpriteB->Draw(mpPausedTex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mPausedDimentions*0.5f, DirectX::SimpleMath::Vector2(sz, sz));

		UserInterfaceManager::bounds resumeBounds = drawButton(mpResumeTex, mResumeDimentions, -50, 0);

		UserInterfaceManager::bounds mainmenuBounds = drawButton(mpMainMenuTex, mMainMenuDimentions, 100, 0);

		if (
			((GetMouseAndKeys()->GetMousePos(true).x >= resumeBounds.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= resumeBounds.bottomRight.x))
			&&
			((GetMouseAndKeys()->GetMousePos(true).y >= resumeBounds.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= resumeBounds.bottomRight.y))
			)
		{
			selected = 0;
		}
		if (
			GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
			&&
			((GetMouseAndKeys()->GetMousePos(true).x >= resumeBounds.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= resumeBounds.bottomRight.x))
			&&
			((GetMouseAndKeys()->GetMousePos(true).y >= resumeBounds.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= resumeBounds.bottomRight.y))
			)
		{
			while (ShowCursor(false) >= 0) {};
			((GameState*)(GetStateManager()->getCurrentState()))->paused = false;
		}
		if (
			((GetMouseAndKeys()->GetMousePos(true).x >= mainmenuBounds.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= mainmenuBounds.bottomRight.x))
			&&
			((GetMouseAndKeys()->GetMousePos(true).y >= mainmenuBounds.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= mainmenuBounds.bottomRight.y))
			)
		{
			selected = 1;
		}
		if (
			GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
			&&
			((GetMouseAndKeys()->GetMousePos(true).x >= mainmenuBounds.topLeft.x) && (GetMouseAndKeys()->GetMousePos(true).x <= mainmenuBounds.bottomRight.x))
			&&
			((GetMouseAndKeys()->GetMousePos(true).y >= mainmenuBounds.topLeft.y) && (GetMouseAndKeys()->GetMousePos(true).y <= mainmenuBounds.bottomRight.y))
			)
		{
			GetStateManager()->changeState("MainMenu");
		}

		int ArrowHOffset, ArrowWOffset;
		switch (selected) {

		case 0: ArrowHOffset = -50;
			ArrowWOffset = -220;
			break;
		case 1: ArrowHOffset = 100;
			ArrowWOffset = -255;
			break;
		}

		float arrowsz(h / mArrowDimentions.y);
		if (arrowsz > 1.25f)
			arrowsz = 1.25f;

		fx.mpSpriteB->Draw(mArrowTex, Vector2((w / 2.f) + ArrowWOffset, (h / 2.f) + ArrowHOffset), nullptr, Colours::White, 0, mArrowDimentions*0.5f, DirectX::SimpleMath::Vector2(arrowsz, arrowsz));
}

UserInterfaceManager::bounds UserInterfaceManager::drawButton(ID3D11ShaderResourceView *tex, DirectX::SimpleMath::Vector2 dimentions, float hOffset, float wOffset) {
	FX::MyFX& fx = *FX::GetMyFX();
	UserInterfaceManager::bounds boundsOfbutton;
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