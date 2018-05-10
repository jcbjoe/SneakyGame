#include "D3D.h"
#include "FX.h"
#include "Mesh.h"
#include "Input.h"
#include "File.h"
#include "UserFolder.h"
#include "AudioMgr.h"
#include "AudioMgrFMOD.h"
#include "LevelManager.h"
#include "StateManager.h"
#include "UserInterfaceManager.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Update(float dTime)
{
	GetStateManager()->Update(dTime);
}

void Render(float dTime)
{
	GetStateManager()->Render(dTime);
}

void OnResize(int screenWidth, int screenHeight)
{

	OnResize_Default(screenWidth, screenHeight);
}


LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
			
			//GetUserInterfaceManager()->printDebugText(to_string(mCamera.GetPos().x) + " : " + to_string(mCamera.GetPos().z));
			break;
		}
	}

	//default message handling (resize window, full screen, etc)
	return DefaultMssgHandler(hwnd, msg, wParam, lParam);
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
	new Gamepad;
	new AudioMgrFMOD;
	GetIAudioMgr()->Initialise();
	new LevelManager;
	new StateManager;
	GetStateManager()->getCurrentState()->Init();

	Run(Update, Render);
	//shut down
	delete GetMouseAndKeys();
	delete GetGamepad();
	delete GetMeshManager();
	delete GetUserInterfaceManager();
	delete GetGameObjectManager();
	delete GetLevelManager();
	delete GetStateManager();
	delete FX::GetMyFX();
	delete GetIAudioMgr();

	ReleaseD3D();

	return 0;
}