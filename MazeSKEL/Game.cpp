#include "Game.h"

Vector3 gWorldScale(10, 10, 10);

void Game::OnResize(int screenWidth, int screenHeight)
{
	OnResize_Default(screenWidth, screenHeight);
}

void Game::Initialise()
{
	//Test
	const int levelx = 10;
	const int levely = 10;

	gWall.Initialise();
	gFloor.Initialise();
	gPlayer.Initialise();
	gLoot.Initialise();	
	gSkybox.Initialise();

	//Level testing
	//0 = Floor
	//1 = Wall
	//2 = Spawn/Entrance/Exit
	//3 = Coins
	int level1[][levelx] = 
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 3, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 1, 1, 0, 0, 3, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 3, 0, 0, 0, 1 },
		{ 1, 3, 0, 3, 0, 0, 0, 2, 0, 1 },
		{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	//For every space in the leve
	for (int i(0); i < levelx; i++)
	{
		for (int j(0); j < levely; j++)
		{
			switch (level1[i][j])
			{
			case 0://Floor to be placed
				gFloor.setPosition(i, 0, j);
				mOpaques.push_back(gFloor.getModel());
				break;
			case 1: //Wall to be placed
				gWall.setPosition(i, 0.5f, j);
				mOpaques.push_back(gWall.getModel());
				break;
			case 2:
				//Place camera
				gPlayer.initCamera(i, j);
				//Place floor
				gFloor.setPosition(i, 0, j);
				mOpaques.push_back(gFloor.getModel());
				break;
			case 3:
				gLoot.setPosition(i, 0.3f, j);
				mOpaques.push_back(gLoot.getModel());
				//Place floor
				gFloor.setPosition(i, 0, j);
				mOpaques.push_back(gFloor.getModel());
				break;
			}		
		}
	}

	for (Model obj : mOpaques)
	{
		obj.GetScale() *= gWorldScale;
		obj.GetPosition() *= gWorldScale;
	}

	//--- Init the UI - 1st Arg = ShowFPS
	GetUserInterfaceManager()->initialiseUI(true);

	FX::SetupDirectionalLight(0, true, Vector3(-0.7f, -0.7f, 0.7f), Vector3(0.67f, 0.67f, 0.67f), Vector3(0.25f, 0.25f, 0.25f), Vector3(0.15f, 0.15f, 0.15f));
}

void Game::Release()
{
	gWall.Release();
	gPlayer.Release();
	gFloor.Release();
	gLoot.Release();
}

void Game::Update(float dTime)
{
	GetUserInterfaceManager()->setFPS(1 / dTime);

	gPlayer.Update(dTime);
	gAngle += dTime * 0.5f;
	gLoot.setRotation(00.f, gAngle, 0.0f);

	GetUserInterfaceManager()->updateUI(gPlayer.getCrouchStatus());
}

void Game::Render(float dTime)
{
	BeginRender(Colours::Black);

	float alpha = 0.5f + sinf(gAngle * 2)*0.5f;

	FX::SetPerFrameConsts(gd3dImmediateContext, gPlayer.getCameraPosition());

	//CreateViewMatrix(FX::GetViewMatrix(), mCamPos, Vector3(0, 0, 0), Vector3(0, 1, 0));
	CreateProjectionMatrix(FX::GetProjectionMatrix(), 0.25f*PI, GetAspectRatio(), 1, 1000.f);
	Matrix w = Matrix::CreateRotationY(sinf(gAngle));
	FX::SetPerObjConsts(gd3dImmediateContext, w);

	gSkybox.setPosition(gPlayer.getCameraPosition());
	FX::GetMyFX()->Render(gSkybox.getModel() , gd3dImmediateContext);
	//render all the solid models first in no particular order
	for (Model p: mOpaques)
	{
		FX::GetMyFX()->Render(p, gd3dImmediateContext);
	}
	EndRender();

	GetMouseAndKeys()->PostProcess();
}

LRESULT Game::WindowsMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	const float camInc = 200.f * GetElapsedSec();

	switch (msg)
	{
	case WM_INPUT:
		GetMouseAndKeys()->MessageEvent((HRAWINPUT)lParam);
		break;
		// Respond to a keyboard event.
	case WM_CHAR:
		switch (wParam)
		{
		case 27:
		case 'q':
		case 'Q':
			PostQuitMessage(0);
			return 0;
		case 'j':
			GetUserInterfaceManager()->printDebugText("TEST123");
			break;
		}
	}

	//default message handling (resize window, full screen, etc)
	return DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

