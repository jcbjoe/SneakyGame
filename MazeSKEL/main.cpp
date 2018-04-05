#include "D3D.h"
#include "FX.h"
#include "Mesh.h"
#include "Input.h"
#include "File.h"
#include "UserFolder.h"
#include "AudioMgrFMOD.h"
#include "Game.h"
#include "LevelManager.h"


using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Game gGame;


void Update(float dTime)
{
	gGame.Update(dTime);
}

void Render(float dTime)
{
	gGame.Render(dTime);
}

void OnResize(int screenWidth, int screenHeight)
{
	gGame.OnResize(screenWidth, screenHeight);
}


LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_INPUT:
		GetMouseAndKeys()->MessageEvent((HRAWINPUT)lParam);
		break;
	}

	return gGame.WindowsMssgHandler(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	SeedRandom();
	File::initialiseSystem();
	USER::SetUserDataFolder("MyGame");

	if (!InitMainWindow(1024, 768, hInstance, "MyGame", MainWndProc))
		assert(false);

	if (!InitDirect3D(OnResize))
		assert(false);

	//startup
	new FX::MyFX(gd3dDevice);
	new MeshManager;
	new UserInterfaceManager;
	new GameObjectManager;
	new MouseAndKeys;
	new LevelManager;
	//Initialise window and hide cursor
	GetMouseAndKeys()->Initialise(GetMainWnd(), 0, 1);
	gGame.Initialise();

	Run(Update, Render);

	//shut down
	gGame.Release();
	delete GetMouseAndKeys();
	delete GetMeshManager();
	delete GetUserInterfaceManager();
	delete GetGameObjectManager();
	delete FX::GetMyFX();
	delete GetLevelManager();

	ReleaseD3D();

	return 0;
}
