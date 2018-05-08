#ifndef MAINMENUSTATE_H 
#define MAINMENUSTATE_H 

#include "State.h"
#include "FPSCamera.h"
class MainMenuState : public State
{
public:
	MainMenuState();

	void Render(float dTime) override;
	void LoadTextures();
	void Update(float dTime) override;

	void Release() override;

private:
	FPSCamera mCamera;

	ID3D11ShaderResourceView *mpBackgroundTex = nullptr;
	ID3D11ShaderResourceView *mStartButtonTex = nullptr;
	ID3D11ShaderResourceView *mExitButtonTex = nullptr;
	ID3D11ShaderResourceView *mArrowTex = nullptr;
	ID3D11ShaderResourceView *mHighscoreButtonTex = nullptr;
	ID3D11ShaderResourceView *mHelpButtonTex = nullptr;
	DirectX::SimpleMath::Vector2 mBackgroundDimentions, mStartButtonDimentions, mExitButtonDimentions, mArrowDimentions, mHighscoreButtonDimentions, mHelpButtonDimentions;

	int selected;

	bool gamepadDown = false;

};

#endif
