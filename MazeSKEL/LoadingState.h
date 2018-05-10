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

	void Init() override;

	void ReleaseFromLevel() override;

private:
	FPSCamera mCamera;

	ID3D11ShaderResourceView *mpBackgroundTex0 = nullptr;
	ID3D11ShaderResourceView *mpBackgroundTex1 = nullptr;
	ID3D11ShaderResourceView *mpBackgroundTex2 = nullptr;
	ID3D11ShaderResourceView *mpBackgroundTex3 = nullptr;
	DirectX::SimpleMath::Vector2 mBackgroundDimentions, mContainerDimentions;

	ID3D11ShaderResourceView *mpContainerTex = nullptr;

	ID3D11ShaderResourceView *mpBar0Tex = nullptr;
	ID3D11ShaderResourceView *mpBar1Tex = nullptr;
	ID3D11ShaderResourceView *mpBar2Tex = nullptr;
	ID3D11ShaderResourceView *mpBar3Tex = nullptr;
	ID3D11ShaderResourceView *mpBar4Tex = nullptr;
	ID3D11ShaderResourceView *mpBar5Tex = nullptr;
	ID3D11ShaderResourceView *mpBar6Tex = nullptr;
	ID3D11ShaderResourceView *mpBar7Tex = nullptr;
	ID3D11ShaderResourceView *mpBar8Tex = nullptr;
	ID3D11ShaderResourceView *mpBar9Tex = nullptr;
	ID3D11ShaderResourceView *mpBar10Tex = nullptr;
	DirectX::SimpleMath::Vector2 mBar0Dimentions;

	std::future<void> mLoadThread;

	bool Loaded = false;

	void Load();

	float counter;

	int loadingScreenDot;

	int loadingProgress;
};

#endif
