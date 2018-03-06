#include <algorithm>

#include "WindowUtils.h"
#include "D3D.h"
#include "Game.h"
#include "GeometryBuilder.h"
#include "FX.h"
#include "Input.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


void Game::OnResize(int screenWidth, int screenHeight)
{
	OnResize_Default(screenWidth, screenHeight);
}

void Game::Initialise()
{
	FX::SetupDirectionalLight(0, true, Vector3(-0.7f, -0.7f, 0.7f), Vector3(0.67f, 0.67f, 0.67f), Vector3(0.25f, 0.25f, 0.25f), Vector3(0.15f, 0.15f, 0.15f));

	gWall.Initialise();
	gPlayer.Initialise();
}

void Game::Release()
{
	gWall.Release();
	gPlayer.Release();
}

void Game::Update(float dTime)
{
	gWall.Update(dTime);
	gPlayer.Update(dTime);
}

void Game::Render(float dTime)
{
	BeginRender(Colours::Black);

	float alpha = 0.5f + sinf(gAngle * 2)*0.5f;


	FX::SetPerFrameConsts(gd3dImmediateContext, mCamera.GetPos());

	//CreateViewMatrix(FX::GetViewMatrix(), mCamPos, Vector3(0, 0, 0), Vector3(0, 1, 0));
	CreateProjectionMatrix(FX::GetProjectionMatrix(), 0.25f*PI, GetAspectRatio(), 1, 1000.f);
	Matrix w = Matrix::CreateRotationY(sinf(gAngle));
	FX::SetPerObjConsts(gd3dImmediateContext, w);


	gWall.Render(dTime);
	gPlayer.Render(dTime);
	EndRender();
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
		}
	}

	//default message handling (resize window, full screen, etc)
	return DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

