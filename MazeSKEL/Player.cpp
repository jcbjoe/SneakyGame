#include "Player.h" 
#include "UserInterfaceManager.h"
#include "GameState.h"
#include "StateManager.h"

#include <Math.h>
void Player::Initialise(const float& i, const float& j) 
{
	mCamera.Initialise(Vector3(i, 0.5f,j), Vector3(i + 1, 0.5, j), FX::GetViewMatrix());
	
	mCamera.LockMovementAxis(FPSCamera::UNLOCK, FPSCamera::UNLOCK, FPSCamera::UNLOCK);

	hands_.Initialise(*GetMeshManager()->GetMesh("Hands"));
	
	MaterialExt& mat = hands_.GetMesh().GetSubMesh(0).material;
	mat.flags &= ~MaterialExt::LIT;
	mat.gfxData.Set(Vector4(0.8f, 0.8f, 0.8f, 0), Vector4(0.8f, 0.8f, 0.8f, 0), Vector4(0.0f, 0.0f, 0.0f, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Grating3.dds", true, gd3dDevice);
	hands_.GetRotation() = Vector3(D2R(20), PI, 0);
	hands_.GetScale() = Vector3(0.00185, 0.00185, 0.00185);
}
void Player::Release() 
{
}

float Player::get2DRotation()
{
	const float i = mCamera.getRotY();
	return  i;
}

void Player::Update(float dTime) 
{
	GetGamepad()->Update();
	if (!((GameState*)GetStateManager()->getCurrentState())->paused) {

		//If player should be crouching
		if (GetMouseAndKeys()->IsPressed(VK_LSHIFT) || (GetGamepad()->IsConnected(0) && GetGamepad()->IsPressed(0, XINPUT_GAMEPAD_RIGHT_SHOULDER)))
		{
			isCrouched = true;
			moveSpeed = 20.0f;
			mCamera.Crouch(isCrouched);

		}
		else
		{
			isCrouched = false;			
			moveSpeed = 5.0f;
			mCamera.Crouch(isCrouched);
		}

		bool fwd = GetMouseAndKeys()->IsPressed(VK_W) || GetGamepad()->GetState(0).leftStickY > 0;
		bool bck = GetMouseAndKeys()->IsPressed(VK_S) || GetGamepad()->GetState(0).leftStickY < 0;
		bool lft = GetMouseAndKeys()->IsPressed(VK_A) || GetGamepad()->GetState(0).leftStickX < 0;
		bool rgt = GetMouseAndKeys()->IsPressed(VK_D) || GetGamepad()->GetState(0).leftStickX > 0;

		mCamera.Move(dTime / moveSpeed, fwd, bck, lft, rgt, isMoving, hasRedKey, hasBlueKey);
		//Rotate camera
		Vector2 m;

		if (GetGamepad()->IsConnected(0))
			m = (Vector2(GetGamepad()->GetState(0).rightStickX, -GetGamepad()->GetState(0).rightStickY) / turnSpeed * 1.5f);
		else
			m = (GetMouseAndKeys()->GetMouseMoveAndCentre() / turnSpeed);

		if (m.x != 0 || m.y != 0)
		{
			mCamera.Rotate(dTime, m.x, m.y, 0);
		}

		if (isMoving)
		{
			mCamera.Bob(dTime, isCrouched);
		}
		else
		{
			if (isCrouched)
				mCamera.ReturnToY(dTime, 0.3f);
			else
				mCamera.ReturnToY(dTime, 0.5f);
		}
		
		mCamera.Update(dTime);

		Vector3 look = { 0, 0, 1 };
		Matrix ma = Matrix::CreateFromYawPitchRoll(mCamera.getRotation().y, mCamera.getRotation().x, mCamera.getRotation().z);
		FX::SetupSpotLight(7, true, Vector3(mCamera.GetPos().x, mCamera.GetPos().y, mCamera.GetPos().z), Vector3::TransformNormal(look, ma), Vector3(0.4f, 0.4f, 0.4f), Vector3(0.35f, 0.35f, 0.35f), Vector3(0.2f, 0.2f, 0.2f), 100.0f, 0.1f, D2R(0), D2R(25));


	}
	else {

		//Return
		if (
			GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
			&& ((GetMouseAndKeys()->GetMousePos(true).x >= 250) && (GetMouseAndKeys()->GetMousePos(true).x <= 766))
			&& ((GetMouseAndKeys()->GetMousePos(true).y >= 250) && (GetMouseAndKeys()->GetMousePos(true).y <= 371))
			)
		{
			((GameState*)GetStateManager()->getCurrentState())->paused = false;
		}

		//MainMenu
		if (
			GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
			&& ((GetMouseAndKeys()->GetMousePos(true).x >= 250) && (GetMouseAndKeys()->GetMousePos(true).x <= 766))
			&& ((GetMouseAndKeys()->GetMousePos(true).y >= 440) && (GetMouseAndKeys()->GetMousePos(true).y <= 550))
			)
		{
			GetStateManager()->changeState("GameOverState");
		}

		//Exit
		if (
			GetMouseAndKeys()->GetMouseButton(GetMouseAndKeys()->LBUTTON)
			&& ((GetMouseAndKeys()->GetMousePos(true).x >= 250) && (GetMouseAndKeys()->GetMousePos(true).x <= 766))
			&& ((GetMouseAndKeys()->GetMousePos(true).y >= 620) && (GetMouseAndKeys()->GetMousePos(true).y <= 730))
			)
		{
			PostQuitMessage(0);
		}
	}
}
void Player::Render(float dTime) 
{
	GetMouseAndKeys()->PostProcess();

	FX::MyFX& fx = *FX::GetMyFX();

	Matrix camLocalToWorld = *mCamera.GetMatrix();
	camLocalToWorld = camLocalToWorld.Invert();
	
	Matrix mat;
	hands_.GetPosition() = Vector3(0.f, -0.03f + (mCamera.getCurrentBob() * 0.1f), 0.05f);

	hands_.GetWorldMatrix(mat);
	Matrix camLock = mat * camLocalToWorld;

	//GetUserInterfaceManager()->printDebugText("x: " + to_string(getCameraPosition().x) + " Z: " + to_string(getCameraPosition().z));


	fx.Render(hands_, gd3dImmediateContext, nullptr, &camLock);
}

//Gets
Vector3 Player::getCameraPosition()
{
	return mCamera.GetPos();
}

int Player::getDeposited()
{
	return depositedCoins;
}

bool Player::getCrouchStatus()
{
	return isCrouched;
}

int Player::getScore()
{
	return coins;
}

bool Player::getHasRedKey()
{
	return hasRedKey;
}

bool Player::getHasBlueKey()
{
	return hasBlueKey;
}

bool Player::getHasYellowKey()
{
	return hasYellowKey;
}

void Player::toggleCrouch()
{
	isCrouched = !isCrouched;
}

void Player::increaseScore()
{
	coins++;
}

void Player::dropOffCoins()
{
	depositedCoins += coins;
	coins = 0;
}

void Player::resetStats()
{
	setDeposited(0);
	setHasRedKey(false);
	setHasBlueKey(false);
	setHasYellowKey(false);
}

void Player::setHasRedKey(const bool& key)
{
	hasRedKey = key;
}

void Player::setHasBlueKey(const bool& key)
{
	hasBlueKey = key;
}

void Player::setHasYellowKey(const bool& key)
{
	hasYellowKey = key;
}

//void Player::changeKeyNo(int x)
//{
//	keyNo += x;
//	if (keyNo > 0)
//		setHasKey(true);
//	else
//		setHasKey(false);
//}

void Player::setOpenedRed() {
	openedRed = true;
}

bool Player::getOpenedRed() {
	return openedRed;
}

void Player::setOpenedBlue() {
	openedRed = true;
}

bool Player::getOpenedBlue() {
	return openedRed;
}