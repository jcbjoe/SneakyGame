#include "UserInterfaceManager.h"
#include <sstream>

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
}

void UserInterfaceManager::printDebugText(string text) {
	debugText.push_back(text);
}

void UserInterfaceManager::setCrouch(bool crouching) {
	isCrouching = crouching;
}

void UserInterfaceManager::setFPS(float fpsNumber) {
	FPS = fpsNumber;
}

void UserInterfaceManager::updateUI() {

	mpSpriteBatch->Begin();

	//--- Begin Crouching Display
	wstringstream crouching;
	if (isCrouching)
		crouching << "Crouched";
	else
		crouching << "Not Crouched";
	mpAlgerian->DrawString(mpSpriteBatch, crouching.str().c_str(), Vector2(100, 200), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));
	//--- End Crouching Display

	//--- Begin FPS Counter
	if (showFPS) {
		wstringstream FPSCounter;
		FPSCounter << "FPS: " << FPS;
		mpAlgerian->DrawString(mpSpriteBatch, FPSCounter.str().c_str(), Vector2(0, 0), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));
	}
	//--- End FPS Counter

	//--- Begin Debug Text
	for (int elementInVector = debugText.size(); elementInVector > 0; elementInVector--) {
		wstringstream textToAdd;
		textToAdd << debugText.at(elementInVector).c_str();
		mpComicSans->DrawString(mpSpriteBatch, textToAdd.str().c_str(), Vector2(100, 50*(elementInVector - debugText.size())), Colors::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));
	}
	//--- End Debug Text

	mpSpriteBatch->End();

}

void UserInterfaceManager::Release()
{

}