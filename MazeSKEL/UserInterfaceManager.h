
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

	void updateUI(const float fpsNumber, const float Timer, const bool&, const int, const int&, const int&, const int&, const int&);
	void initialiseUI(bool showFPS);

	void printDebugText(std::string text);

private:
	void Release();

	bool showFPS;
	
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

	ID3D11ShaderResourceView *mpEmptyTex = nullptr;
	DirectX::SimpleMath::Vector2 mEmptyDimentions;
};
SINGLETON_GET(UserInterfaceManager);

#endif