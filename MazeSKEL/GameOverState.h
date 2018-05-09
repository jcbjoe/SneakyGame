#ifndef GAMEOVERSTATE_H 
#define GAMEOVERSTATE_H 

#include "State.h"
#include "FPSCamera.h"
#include "LevelStats.h"
class GameOverState : public State
{
public:
	GameOverState();

	void Render(float dTime) override;
	void LoadTextures();
	void Update(float dTime) override;
	void Init() override;

	void setStats(vector<levelStats> ls);

private:
	FPSCamera mCamera;

	ID3D11ShaderResourceView *mpBackgroundTex = nullptr;
	DirectX::SimpleMath::Vector2 mBackgroundDimentions;

	void handleGameOver();

	std::future<void> mLoadThread;

	bool handled = false;

	unsigned int musicHdl;
};

#endif
