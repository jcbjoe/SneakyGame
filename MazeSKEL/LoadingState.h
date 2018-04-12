#ifndef LOADINGSTATE_H 
#define LOADINGSTATE_H 

#include "State.h"
#include "FPSCamera.h"
class LoadingState : public State
{
public:
	LoadingState();

	void Render(float dTime) override;
	void LoadTextures();
	void Update(float dTime) override;

private:
	FPSCamera mCamera;

	ID3D11ShaderResourceView *mpBackgroundTex = nullptr;
	DirectX::SimpleMath::Vector2 mBackgroundDimentions;
};

#endif
