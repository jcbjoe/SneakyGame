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

private:
	FPSCamera mCamera;

	ID3D11ShaderResourceView *mpBackgroundTex = nullptr;
	DirectX::SimpleMath::Vector2 mBackgroundDimentions;
};

#endif
