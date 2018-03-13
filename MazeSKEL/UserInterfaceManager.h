#pragma once
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

	void updateUI();
	void initialiseUI(bool showFPS);

	void printDebugText(std::string text);

	void setCrouch(bool crouching);

	void setFPS(float fpsNumber);

private:
	void Release();

	bool showFPS;
	bool isCrouching = false;

	struct debugText {
		std::string text;
		int timeAdded;
	};
	std::vector<debugText> debugTextVector;

	DirectX::SpriteBatch *mpSpriteBatch = nullptr;
	DirectX::SpriteFont *mpComicSans = nullptr, *mpAlgerian = nullptr;

	float FPS;

	time_t start;
};
SINGLETON_GET(UserInterfaceManager);

#endif