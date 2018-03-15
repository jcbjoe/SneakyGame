#include "Player.h" 

void Player::Initialise(const float& i, const float& j) 
{
	mCamera.Initialise(Vector3(i, 0.5f,j), Vector3(0, 0, 1), FX::GetViewMatrix());
	mCamera.LockMovementAxis(FPSCamera::UNLOCK, FPSCamera::UNLOCK, FPSCamera::UNLOCK);
}
void Player::Release() 
{
}
void Player::Update(float dTime) 
{
	if (GetMouseAndKeys()->IsPressed(VK_LSHIFT)) {
		if (!isCrouched)
		{
			toggleCrouch();
			mCamera.Crouch(isCrouched);
		}
	}
	else
	{
		if (isCrouched)
		{
			toggleCrouch();
			mCamera.Crouch(isCrouched);
		}
	}

	mCamera.Move(dTime / moveSpeed, GetMouseAndKeys()->IsPressed(VK_W), GetMouseAndKeys()->IsPressed(VK_S), GetMouseAndKeys()->IsPressed(VK_A), GetMouseAndKeys()->IsPressed(VK_D), GetMouseAndKeys()->IsPressed(VK_LSHIFT), isCrouched);

	Vector2 m = (GetMouseAndKeys()->GetMouseMoveAndCentre() / turnSpeed);

	if (m.x != 0 || m.y != 0)
	{
		mCamera.Rotate(dTime, m.x, m.y, 0);
	}
}
void Player::Render(float dTime) 
{
	GetMouseAndKeys()->PostProcess();
}

void Player::toggleCrouch()
{
	isCrouched = !isCrouched;
}

Vector3 Player::getCameraPosition()
{
	return mCamera.GetPos();
}

bool Player::getCrouchStatus()
{
	return isCrouched;
}