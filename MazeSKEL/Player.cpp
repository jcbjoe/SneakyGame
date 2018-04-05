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

	//If player should be crouching
	if (GetMouseAndKeys()->IsPressed(VK_LSHIFT))
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

	mCamera.Move(dTime / moveSpeed, GetMouseAndKeys()->IsPressed(VK_W), GetMouseAndKeys()->IsPressed(VK_S), GetMouseAndKeys()->IsPressed(VK_A), GetMouseAndKeys()->IsPressed(VK_D));

	Vector2 m = (GetMouseAndKeys()->GetMouseMoveAndCentre() / turnSpeed);

	if (m.x != 0 || m.y != 0)
	{
		mCamera.Rotate(dTime, m.x, m.y, 0);
	}

	mCamera.Update(dTime);
	GetGameObjectManager()->getFirstObjectByName("Skybox")->SetPosition(mCamera.GetPos());
}
void Player::Render(float dTime) 
{
	GetMouseAndKeys()->PostProcess();
}

//Gets
Vector3 Player::getCameraPosition()
{
	return mCamera.GetPos();
}

bool Player::getCrouchStatus()
{
	return isCrouched;
}

int Player::getScore()
{
	return coins;
}

bool Player::getHasKey()
{
	return hasKey;
}

int Player::getKeyNo() {
	return keyNo;
}

//Sets
void Player::toggleCrouch()
{
	isCrouched = !isCrouched;
}

void Player::increaseScore()
{
	coins++;
}

void Player::setHasKey(bool x)
{
	hasKey = x;
}

void Player::changeKeyNo(int x)
{
	keyNo += x;
	if (keyNo > 0)
		setHasKey(true);
	else
		setHasKey(false);
}
