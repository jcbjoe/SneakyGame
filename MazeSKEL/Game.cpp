#include "Game.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

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

	//Skybox
	Mesh& sb = GetMeshManager()->CreateMesh("skybox");
	sb.CreateFrom("data/skybox.fbx", gd3dDevice, FX::GetMyFX()->mCache);
	mSkybox.Initialise(sb);
	mSkybox.GetScale() = Vector3(1,1,1);
	mSkybox.GetPosition() = Vector3(0,0,0);
	mSkybox.GetRotation() = Vector3(PI/2,0,0);
	MaterialExt& defMat = mSkybox.GetMesh().GetSubMesh(0).material;
	defMat.flags &= ~MaterialExt::LIT;
	defMat.flags &= ~MaterialExt::ZTEST;

	gWall.Initialise();
	gFloor.Initialise();
	gPlayer.Initialise();
	gLoot.Initialise();	

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
				gWall.getPosition() = Vector3(i, 0.5f, j);
				mOpaques.push_back(gWall.getModel());
				break;
			case 2:
				//Place camera
				mCamera.Initialise(Vector3(i, 0.5f, j), Vector3(0, 0, 1), FX::GetViewMatrix());
				mCamera.LockMovementAxis(FPSCamera::UNLOCK, FPSCamera::UNLOCK, FPSCamera::UNLOCK);
				//Place floor
				gFloor.setPosition(i, 0, j);
				mOpaques.push_back(gFloor.getModel());
				break;
			case 3:
				gLoot.getPosition() = Vector3(i, 0.3f, j);
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
	float moveSpeed = dTime / 5.0f;
	float turnSpeed = 20.0f;

	if (GetMouseAndKeys()->IsPressed(VK_LSHIFT)) {
		if (!isCrouched) 
		{
			isCrouched = true;
			//Crouch function
			mCamera.Crouch(isCrouched);
			GetUserInterfaceManager()->setCrouch(isCrouched);
		}
	} 
	else 
	{
		if (isCrouched) 
		{
			isCrouched = false;
			mCamera.Crouch(isCrouched);
			GetUserInterfaceManager()->setCrouch(isCrouched);
		}
	}
	mCamera.Move(moveSpeed, GetMouseAndKeys()->IsPressed(VK_W), GetMouseAndKeys()->IsPressed(VK_S), GetMouseAndKeys()->IsPressed(VK_A), GetMouseAndKeys()->IsPressed(VK_D), GetMouseAndKeys()->IsPressed(VK_LSHIFT), isCrouched);
	
	Vector2 m = (GetMouseAndKeys()->GetMouseMoveAndCentre() / turnSpeed);

	if (m.x != 0 || m.y != 0)
	{
		
		mCamera.Rotate(dTime, m.x, m.y, 0);
	}

	GetUserInterfaceManager()->setFPS(1 / dTime);

	gAngle += dTime * 0.5f;
	//gLoot.setRotation(00.f, gAngle, 0.0f);

	GetUserInterfaceManager()->updateUI();
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

	mSkybox.GetPosition() = mCamera.GetPos();
	FX::GetMyFX()->Render(mSkybox, gd3dImmediateContext);
	//render all the solid models first in no particular order
	for (Model p: mOpaques)
	{
		FX::GetMyFX()->Render(p, gd3dImmediateContext);
	}

	GetUserInterfaceManager()->updateUI();
	//*GetUserInterfaceManager();
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

