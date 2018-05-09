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
	void Release() override;

	void setStats(vector<levelStats> ls);

private:
	FPSCamera mCamera;

	ID3D11ShaderResourceView *mpBackgroundTex = nullptr;
	ID3D11ShaderResourceView *mpPlayAgainTex = nullptr;
	ID3D11ShaderResourceView *mpHighscoreTex = nullptr;
	ID3D11ShaderResourceView *mpMainMenuTex = nullptr;
	ID3D11ShaderResourceView *mArrowTex = nullptr;

	DirectX::SimpleMath::Vector2 mBackgroundDimentions;
	DirectX::SimpleMath::Vector2 mPlayAgainDimentions;
	DirectX::SimpleMath::Vector2 mHighscoreDimentions; 
	DirectX::SimpleMath::Vector2 mMainMenuDimentions; 
	DirectX::SimpleMath::Vector2 mArrowDimentions;

	void handleGameOver();

	std::future<void> mLoadThread;

	bool handled = false;

	struct bounds {
		Vector2 topLeft;
		Vector2 bottomRight;
	};

	bounds drawButton(ID3D11ShaderResourceView *tex, Vector2 dimentions, float hOffset, float wOffset);
	int selected;
	bool gamepadDown;
};

#endif
