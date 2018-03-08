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
	bool isCrouching;

	std::vector<std::string> debugText;

	DirectX::SpriteBatch *mpSpriteBatch = nullptr;
	DirectX::SpriteFont *mpComicSans = nullptr, *mpAlgerian = nullptr;

	float FPS;
};
SINGLETON_GET(UserInterfaceManager);

#endif