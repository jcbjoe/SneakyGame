#include "HelpState.h"
#include "CommonStates.h"
#include "Input.h"
#include "StateManager.h"
#include "UserInterfaceManager.h"
#include "GameObjectManager.h"
#include "Mesh.h"
#include "AudioMgrFMOD.h"


HelpState::HelpState()
	:
	State("HelpState")
{

}

void HelpState::Init() {
	selected = 0;

	LoadTextures();

	ShowCursor(true);

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

void HelpState::Update(float dTime) {
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

void HelpState::Render(float dTime) {
	BeginRender(Colours::Black);

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

	float Textsz(h / mTextDimentions.y);
	if (Textsz > 0.5f)
		Textsz = 0.6f;
	fx.mpSpriteB->Draw(mpTextTex, Vector2(w / 2.f, h / 2.f), nullptr, Colours::White, 0, mTextDimentions*0.5f, Vector2(Textsz, Textsz));




	////////////////////////////////////////////// MAINMENU //////////////////////////////////////////////////////////////////////////////
	HelpState::bounds boundsOfMainMenu = drawButton(mpMainMenuTex, mMainMenuDimentions, 300, 0);
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

	int ArrowHOffset, ArrowWOffset;
	switch (selected) {

	case 0: ArrowHOffset = 300;
		ArrowWOffset = -240;
		break;
	}

	float arrowsz(h / mArrowDimentions.y);
	if (arrowsz > 1.25f)
		arrowsz = 1.25f;

	fx.mpSpriteB->Draw(mArrowTex, Vector2((w / 2.f) + ArrowWOffset, (h / 2.f) + ArrowHOffset), nullptr, Colours::White, 0, mArrowDimentions*0.5f, Vector2(arrowsz, arrowsz));

	fx.mpSpriteB->End();



	EndRender();
}


void HelpState::LoadTextures() {
	FX::MyFX& fx = *FX::GetMyFX();

	mpBackgroundTex = fx.mCache.LoadTexture("Screens/Help/Help.dds", true, gd3dDevice);
	mBackgroundDimentions = fx.mCache.Get(mpBackgroundTex).dim;

	mpTextTex = fx.mCache.LoadTexture("Screens/Help/helpText.dds", true, gd3dDevice);
	mTextDimentions = fx.mCache.Get(mpTextTex).dim;

	mpMainMenuTex = fx.mCache.LoadTexture("Screens/GameOver/mainMenuButton.dds", true, gd3dDevice);
	mMainMenuDimentions = fx.mCache.Get(mpMainMenuTex).dim;

	mArrowTex = fx.mCache.LoadTexture("Screens/MainMenu/Arrow.dds", true, gd3dDevice);
	mArrowDimentions = fx.mCache.Get(mArrowTex).dim;
}

HelpState::bounds HelpState::drawButton(ID3D11ShaderResourceView *tex, Vector2 dimentions, float hOffset, float wOffset) {
	HelpState::bounds boundsOfbutton;
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

void HelpState::ReleaseFromLevel() {
	FX::MyFX& fx = *FX::GetMyFX();
	fx.mCache.Release();
}

void HelpState::Destruct() {
	delete mpSpriteBatch;
}
