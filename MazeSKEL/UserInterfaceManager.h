
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
	UserInterfaceManager();
	~UserInterfaceManager() {
		Release();
	}

	void updateUI(const float fpsNumber, const float Timer, const bool&, const int, const int&, const int&, const int&, const int&, const int&, const bool&, const bool&, const bool&, const float&, const float&, const float&, const bool&);
	void initialiseUI(bool showFPS);

	void printDebugText(std::string text);

private:
	void Release();

	void handlePauseMenu();

	bool showFPS;
	//Minimap
	float offx;
	float offy;


	struct debugText {
		std::string text;
		int timeAdded;
	};
	std::vector<debugText> debugTextVector;

	DirectX::SpriteFont *mpComicSans = nullptr, *mpAlgerian = nullptr;

	time_t start;

	//--Collected Keys Begin
		ID3D11ShaderResourceView *mpRedKeyTex = nullptr;
		DirectX::SimpleMath::Vector2 mRedKeyDimentions;

		ID3D11ShaderResourceView *mpBlueKeyTex = nullptr;
		DirectX::SimpleMath::Vector2 mBlueKeyDimentions;

		ID3D11ShaderResourceView *mpYellowKeyTex = nullptr;
		DirectX::SimpleMath::Vector2 mYellowKeyDimentions;
	//--Collected Keys Ended

	//--Uncollected Keys Begin
		ID3D11ShaderResourceView *mpRedEmptyTex = nullptr;
		DirectX::SimpleMath::Vector2 mRedEmptyDimentions;

		ID3D11ShaderResourceView *mpBlueEmptyTex = nullptr;
		DirectX::SimpleMath::Vector2 mBlueEmptyDimentions;

		DirectX::SimpleMath::Vector2 mYellowEmptyDimentions;
		ID3D11ShaderResourceView *mpYellowEmptyTex = nullptr;
	//--Uncollected Keys End

	ID3D11ShaderResourceView *mpMinimapBGTex = nullptr;
	DirectX::SimpleMath::Vector2 mMinimapBGDimentions;

	ID3D11ShaderResourceView *mpMiniSquareTex = nullptr;
	DirectX::SimpleMath::Vector2 mMiniSquareDimensions;

	ID3D11ShaderResourceView *mpTimerTex = nullptr;
	DirectX::SimpleMath::Vector2 mTimerDimensions;


	//--Coins Begin
	ID3D11ShaderResourceView *mpUIChestTex = nullptr;
	DirectX::SimpleMath::Vector2 mUIChestDimentions;

		ID3D11ShaderResourceView *mpOneCoinTex = nullptr;
		DirectX::SimpleMath::Vector2 mOneCoinDimentions;

		ID3D11ShaderResourceView *mpTwoCoinTex = nullptr;
		DirectX::SimpleMath::Vector2 mTwoCoinDimentions;

		ID3D11ShaderResourceView *mpThreeCoinTex = nullptr;
		DirectX::SimpleMath::Vector2 mThreeCoinDimentions;

		ID3D11ShaderResourceView *mpFourCoinTex = nullptr;
		DirectX::SimpleMath::Vector2 mFourCoinDimentions;

		ID3D11ShaderResourceView *mpFiveCoinTex = nullptr;
		DirectX::SimpleMath::Vector2 mFiveCoinDimentions;
	//--Coins Ends

		ID3D11ShaderResourceView *mpPausedTex = nullptr;
		DirectX::SimpleMath::Vector2 mPausedDimentions;

		ID3D11ShaderResourceView *mpResumeTex = nullptr;
		DirectX::SimpleMath::Vector2 mResumeDimentions;

		ID3D11ShaderResourceView *mpMainMenuTex = nullptr;
		DirectX::SimpleMath::Vector2 mMainMenuDimentions;

		ID3D11ShaderResourceView *mArrowTex = nullptr;
		DirectX::SimpleMath::Vector2 mArrowDimentions;

		struct bounds {
			DirectX::SimpleMath::Vector2 topLeft;
			DirectX::SimpleMath::Vector2 bottomRight;
		};

		int selected;

		bounds drawButton(ID3D11ShaderResourceView *tex, DirectX::SimpleMath::Vector2 dimentions, float hOffset, float wOffset);

		bool gamepadDown;

		bool firstPause;
};
SINGLETON_GET(UserInterfaceManager);

#endif