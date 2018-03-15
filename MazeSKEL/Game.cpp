#include "Game.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Game::OnResize(int screenWidth, int screenHeight)
{
	OnResize_Default(screenWidth, screenHeight);
}

void Game::Initialise()
{
	const int levelx = 10;
	const int levely = 10;

	//Level testing
	//0 = Floor
	//1 = Wall
	//2 = Spawn/Entrance/Exit
	//3 = Coins
	//4 = Enemy
	int level1[][levelx] = 
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 3, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 3, 0, 0, 0, 1 },
		{ 1, 3, 0, 3, 0, 0, 0, 2, 0, 1 },
		{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	//Create Initial Objects to copy
	BuildFloor(*GetMeshManager());
	BuildWall(*GetMeshManager());
	BuildLoot(*GetMeshManager(), 10, 10);

	//For every space in the leve
	for (int i(0); i < levelx; i++)
	{
		for (int j(0); j < levely; j++)
		{
			switch (level1[i][j])
			{
				case 0: {//Floor to be placed
					Floor floor("Floor", Vector3(i, 0.0f, j), Quaternion::Identity, Vector3(0.5, 0.5, 0.5));
					GetGameObjectManager()->addGameObject(floor);
					break;
				}

				case 1: { //Wall to be placed

					Wall wall("Wall", Vector3(i, 0.5f, j), Quaternion::Identity, Vector3(0.5, 0.5, 0.5));
					GetGameObjectManager()->addGameObject(wall);

					break;
				}

				case 2: {
					//Place camera
					gPlayer.Initialise(i, j);

					//Place floor
					Floor floor("Floor", Vector3(i, 0.0f, j), Quaternion::Identity, Vector3(0.5, 0.5, 0.5));
					GetGameObjectManager()->addGameObject(floor);
					break;
				}

				case 3: {
					Loot loot("Loot", Vector3(i, 0.3f, j), Quaternion::Identity, Vector3(0.02, 0.1, 0.1));
					GetGameObjectManager()->addGameObject(loot);

					//Place floor
					Floor floor("Floor", Vector3(i, 0.0f, j), Quaternion::Identity, Vector3(0.5, 0.5, 0.5));
					GetGameObjectManager()->addGameObject(floor);
					break;

				}

			    case 4: {
					Enemy enemy = Enemy("Enemy", Vector3(i, 0.5f, j), Quaternion::Identity, Vector3(0.1f, 0.1f, 0.1f));
					enemy.setWaypoints(waypointsVector);
					GetGameObjectManager()->addGameObject(enemy);

					//Place floor
					Floor floor("Floor", Vector3(i, 0.0f, j), Quaternion::Identity, Vector3(0.5, 0.5, 0.5));
					GetGameObjectManager()->addGameObject(floor);
					break;
				}
			}
		}
	}

	//--- Init the UI - 1st Arg = ShowFPS
	GetUserInterfaceManager()->initialiseUI(true);

	FX::SetupDirectionalLight(0, true, Vector3(-0.7f, -0.7f, 0.7f), Vector3(0.67f, 0.67f, 0.67f), Vector3(0.25f, 0.25f, 0.25f), Vector3(0.15f, 0.15f, 0.15f));
}

void Game::Update(float dTime)
{

	for (GameObject obj : GetGameObjectManager()->getGameObjects()) {
		obj.Update(dTime);
	}


	float moveSpeed = dTime / 5.0f;
	float turnSpeed = 20.0f;

	gPlayer.Update(dTime);
	
	Vector2 m = (GetMouseAndKeys()->GetMouseMoveAndCentre() / turnSpeed);

	if (m.x != 0 || m.y != 0)
	{
		
		mCamera.Rotate(dTime, m.x, m.y, 0);
	}

	//gPlayer.Update(dTime);

}

void Game::Render(float dTime)
{
	BeginRender(Colours::Black);

	for (GameObject obj : GetGameObjectManager()->getGameObjects()) {
		obj.Render();
	}

	float alpha = 0.5f + sinf(gAngle * 2)*0.5f;

	FX::SetPerFrameConsts(gd3dImmediateContext, gPlayer.getCameraPosition());

	CreateProjectionMatrix(FX::GetProjectionMatrix(), 0.25f*PI, GetAspectRatio(), 1, 1000.f);
	Matrix w = Matrix::CreateRotationY(sinf(gAngle));
	FX::SetPerObjConsts(gd3dImmediateContext, w);

	//objectManager.setSkyboxPos(mCamera.GetPos());

	GetUserInterfaceManager()->updateUI(1 / dTime, isCrouched);


	GetUserInterfaceManager()->updateUI(gPlayer.getCrouchStatus());

	EndRender();

	GetMouseAndKeys()->PostProcess();

}

void Game::Release() {

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
			GetUserInterfaceManager()->printDebugText(to_string(mCamera.GetPos().x) + " : " + to_string(mCamera.GetPos().z));
			break;
		}
	}

	//default message handling (resize window, full screen, etc)
	return DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

