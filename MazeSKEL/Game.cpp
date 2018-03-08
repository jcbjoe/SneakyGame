#include <algorithm>

#include "WindowUtils.h"
#include "D3D.h"
#include "Game.h"
#include "GeometryBuilder.h"
#include "FX.h"
#include "Input.h"

#include <sstream>
#include <iomanip>
#include <thread>

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


	mQuad.Initialise(BuildQuad(*GetMeshManager()));
	//mWall.Initialise(BuildCube(*GetMeshManager()));

	mpSpriteBatch = new SpriteBatch(gd3dImmediateContext);
	assert(mpSpriteBatch);
	mpFont = new SpriteFont(gd3dDevice, L"../bin/data/comicSansMS.spritefont");
	assert(mpFont);

	mpFont2 = new SpriteFont(gd3dDevice, L"../bin/data/algerian.spritefont");
	assert(mpFont2);

	//textured lit box
	mBox.Initialise(BuildCube(*GetMeshManager()));
	mBox.GetPosition() = Vector3(0, 0, 0);
	mBox.GetScale() = Vector3(0.5f, 0.5f, 0.5f);
	MaterialExt mat = mQuad.GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("WallGarage.dds", true, gd3dDevice);
	mat.texture = "WallGarage.dds";
	mBox.SetOverrideMat(&mat);

	// floor
	//Set up geometry
	mQuad.GetScale() = Vector3(0.5, 0.5, 0.5);
	mQuad.GetPosition() = Vector3(0, 0, 0);
	//Set up material
	mat = mQuad.GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("test.dds", true, gd3dDevice);
	mat.texture = "test.dds";
	mat.texTrsfm.scale = Vector2(1, 1);
	mQuad.SetOverrideMat(&mat);

	

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


	//Loot Test
	Model mLoot = mBox;
	mLoot.GetScale() = Vector3(0.1f, 0.1f, 0.1f);
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Metal.dds", true, gd3dDevice);
	mat.texture = "Metal.dds";
	mLoot.SetOverrideMat(&mat);

	//mLoot.Initialise(BuildCube(*GetMeshManager()));
	//mBox.GetPosition() = Vector3(0, 0, 0);
	//mBox.GetScale() = Vector3(0.5f, 0.5f, 0.5f);
	//MaterialExt mat = mQuad.GetMesh().GetSubMesh(0).material;
	//mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 1));
	//mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("WallGarage.dds", true, gd3dDevice);
	//mat.texture = "WallGarage.dds";
	//mBox.SetOverrideMat(&mat);


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
				mQuad.GetPosition() = Vector3(i, 0, j);
				mOpaques.push_back(mQuad);
				break;
			case 1: //Wall to be placed
				mBox.GetPosition() = Vector3(i, 0.5f, j);
				mOpaques.push_back(mBox);
				break;
			case 2:
				//Place camera
				mCamera.Initialise(Vector3(i, 0.5f, j), Vector3(0, 0, 1), FX::GetViewMatrix());
				mCamera.LockMovementAxis(FPSCamera::UNLOCK, FPSCamera::UNLOCK, FPSCamera::UNLOCK);
				//Place floor
				mQuad.GetPosition() = Vector3(i, 0, j);
				mOpaques.push_back(mQuad);
				break;
			case 3:
				mLoot.GetPosition() = Vector3(i, 0.3f, j);
				mOpaques.push_back(mLoot);
				
				//Place floor
				mQuad.GetPosition() = Vector3(i, 0, j);
				mOpaques.push_back(mQuad);
				break;

			}		

		}
	}

	for (Model obj : mOpaques)
	{
		obj.GetScale() *= gWorldScale;
		obj.GetPosition() *= gWorldScale;
	}


	FX::SetupDirectionalLight(0, true, Vector3(-0.7f, -0.7f, 0.7f), Vector3(0.67f, 0.67f, 0.67f), Vector3(0.25f, 0.25f, 0.25f), Vector3(0.15f, 0.15f, 0.15f));

	
}

void Game::LoadDisplay(float dTime)
{
	//BeginRender(Colours::Black);

	mpSpriteBatch->Begin();

	wstringstream ss;
	ss << L"Crouching: ";
	ss << isCrouched;
	mpFont2->DrawString(mpSpriteBatch, ss.str().c_str(), Vector2(100, 200), Colours::White, 0, Vector2(0, 0), Vector2(1.f, 1.f));

	mpSpriteBatch->End();

	//EndRender();
}

void Game::Release()
{
}

void Game::Update(float dTime)
{
	float moveSpeed = dTime / 5.0f;
	float turnSpeed = 20.0f;

	if (GetMouseAndKeys()->IsPressed(VK_LSHIFT)) {
		if (!isCrouched) {
			isCrouched = true;
			//Crouch function
			mCamera.Crouch(isCrouched);
			//mCamera.Move(moveSpeed, GetMouseAndKeys()->IsPressed(VK_W), GetMouseAndKeys()->IsPressed(VK_S), GetMouseAndKeys()->IsPressed(VK_A), GetMouseAndKeys()->IsPressed(VK_D), GetMouseAndKeys()->IsPressed(VK_LSHIFT), isCrouched);
		}
	} else {
		if (isCrouched) {
			isCrouched = false;
			mCamera.Crouch(isCrouched);
		}
	}
	mCamera.Move(moveSpeed, GetMouseAndKeys()->IsPressed(VK_W), GetMouseAndKeys()->IsPressed(VK_S), GetMouseAndKeys()->IsPressed(VK_A), GetMouseAndKeys()->IsPressed(VK_D), GetMouseAndKeys()->IsPressed(VK_LSHIFT), isCrouched);
	
	Vector2 m = (GetMouseAndKeys()->GetMouseMoveAndCentre() / turnSpeed);

	if (m.x != 0 || m.y != 0)
	{
		
		mCamera.Rotate(dTime, m.x, m.y, 0);
	}

	//if (GetMouseAndKeys()->IsPressed(VK_LSHIFT))
	//{
	//	isCrouched = !isCrouched;
	//	//mCamera.Move(moveSpeed, GetMouseAndKeys()->IsPressed(VK_W), GetMouseAndKeys()->IsPressed(VK_S), GetMouseAndKeys()->IsPressed(VK_A), GetMouseAndKeys()->IsPressed(VK_D), GetMouseAndKeys()->IsPressed(VK_LSHIFT), isCrouched);
	//	
	//}

	gAngle += dTime * 0.5f;
	mBox.GetRotation().y = gAngle;
}

void Game::Render(float dTime)
{
	BeginRender(Colours::Black);

	//Load the text
	

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

	LoadDisplay(dTime);
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
		}
	}

	//default message handling (resize window, full screen, etc)
	return DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

