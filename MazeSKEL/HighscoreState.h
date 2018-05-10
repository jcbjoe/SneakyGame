#ifndef HIGHSCORESTATE_H 
#define HIGHSCORESTATE_H 

#include "State.h"
#include "FPSCamera.h"
#include "LevelStats.h"
class HighscoreState : public State
{
public:
	HighscoreState();
	~HighscoreState() {
		Destruct();
	}

	void Render(float dTime) override;
	void LoadTextures();
	void Update(float dTime) override;
	void Init() override;
	void ReleaseFromLevel() override;
	void Destruct() override;

	void setStats(vector<levelStats> ls);

private:

	ID3D11ShaderResourceView *mpBackgroundTex = nullptr;
	ID3D11ShaderResourceView *mpMainMenuTex = nullptr;
	ID3D11ShaderResourceView *mArrowTex = nullptr;

	DirectX::SimpleMath::Vector2 mBackgroundDimentions;
	DirectX::SimpleMath::Vector2 mMainMenuDimentions;
	DirectX::SimpleMath::Vector2 mArrowDimentions;

	DirectX::SpriteBatch *mpSpriteBatch = nullptr;
	DirectX::SpriteFont *mpComicSans = nullptr, *mpAlgerian = nullptr;

	struct bounds {
		Vector2 topLeft;
		Vector2 bottomRight;
	};

	bounds drawButton(ID3D11ShaderResourceView *tex, Vector2 dimentions, float hOffset, float wOffset);
	int selected;
	
	bool pressedOnInit;

	unsigned int musicHdl;
};

#endif
