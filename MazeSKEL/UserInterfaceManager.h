
#ifndef USERINTERFACEMANAGER_H
#define USERINTERFACEMANAGER_H

#include "Singleton.h"
#include <vector>
#include <string>

#include "SpriteFont.h"
#include "D3D.h"
#include "FX.h"


class UserInterfaceManager : public Singleton<UserInterfaceManager>
{
public:
	~UserInterfaceManager() {
		Release();
	}

	void updateUI(const float fpsNumber, const float Timer, const bool&, const int, const int&, const int&, const int&, const int&, const bool&, const bool&, const bool&, const float&, const float&, const float&);
	void initialiseUI(bool showFPS);

	void printDebugText(std::string text);

private:
	void Release();

	bool showFPS;
	//Minimap
	float offx;
	float offy;


	struct debugText {
		std::string text;
		int timeAdded;
	};
	std::vector<debugText> debugTextVector;

	DirectX::SpriteBatch *mpSpriteBatch = nullptr;
	DirectX::SpriteFont *mpComicSans = nullptr, *mpAlgerian = nullptr;

	time_t start;

	ID3D11ShaderResourceView *mpPausedTex = nullptr;
	DirectX::SimpleMath::Vector2 mPausedDimentions;

	ID3D11ShaderResourceView *mpRedKeyTex = nullptr;
	DirectX::SimpleMath::Vector2 mRedKeyDimentions;

	ID3D11ShaderResourceView *mpBlueKeyTex = nullptr;
	DirectX::SimpleMath::Vector2 mBlueKeyDimentions;

	ID3D11ShaderResourceView *mpYellowKeyTex = nullptr;
	DirectX::SimpleMath::Vector2 mYellowKeyDimentions;

	ID3D11ShaderResourceView *mpRedEmptyTex = nullptr;
	DirectX::SimpleMath::Vector2 mRedEmptyDimentions;

	ID3D11ShaderResourceView *mpBlueEmptyTex = nullptr;
	DirectX::SimpleMath::Vector2 mBlueEmptyDimentions;

	ID3D11ShaderResourceView *mpYellowEmptyTex = nullptr;
	DirectX::SimpleMath::Vector2 mYellowEmptyDimentions;

	ID3D11ShaderResourceView *mpMinimapBGTex = nullptr;
	DirectX::SimpleMath::Vector2 mMinimapBGDimentions;

	ID3D11ShaderResourceView *mpMiniSquareTex = nullptr;
	DirectX::SimpleMath::Vector2 mMiniSquareDimensions;

	ID3D11ShaderResourceView *mpTimerTex = nullptr;
	DirectX::SimpleMath::Vector2 mTimerDimensions;

};
SINGLETON_GET(UserInterfaceManager);

#endif