
#ifndef USERINTERFACEMANAGER_H
#define USERINTERFACEMANAGER_H

#include "Singleton.h"
#include <vector>
#include <string>

#include "SpriteFont.h"
#include "D3D.h"


class UserInterfaceManager : public Singleton<UserInterfaceManager>
{
public:
	~UserInterfaceManager() {
		Release();
	}

	void updateUI(const float fpsNumber, const bool&, const int, const bool&);
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
};
SINGLETON_GET(UserInterfaceManager);

#endif