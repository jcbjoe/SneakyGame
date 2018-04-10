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

	

	//Collisions
	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		if (GetLevelManager()->getObjectAtCoordinate(i, j) == 1)
	//		{
	//			if (((mCamera.GetPos().x + 0.5f) >= (i - 0.5f)) &&	
	//				((mCamera.GetPos().x - 0.5f) <= (i + 0.5f)) &&	
	//				((mCamera.GetPos().z + 0.5f) >= (j - 0.5f)) &&	
	//				((mCamera.GetPos().z - 0.5f) <= (j + 0.5f)))
	//			{
	//				if (GetMouseAndKeys()->IsPressed(VK_W))
	//					mCamera.Move(dTime / moveSpeed, true, false, false, false);
	//
	//				if (GetMouseAndKeys()->IsPressed(VK_S))
	//					mCamera.Move(dTime / moveSpeed, false, true, false, false);
	//
	//				if (GetMouseAndKeys()->IsPressed(VK_A))
	//					mCamera.Move(dTime / moveSpeed, false, false, true, false);
	//
	//				if (GetMouseAndKeys()->IsPressed(VK_D))
	//					mCamera.Move(dTime / moveSpeed, false, false, true, true);
	//
	//			}
	//		}
	//	}
	//}
	mCamera.Move(dTime / moveSpeed, GetMouseAndKeys()->IsPressed(VK_W), GetMouseAndKeys()->IsPressed(VK_S), GetMouseAndKeys()->IsPressed(VK_A), GetMouseAndKeys()->IsPressed(VK_D), isMoving);

	//Rotate camera
	Vector2 m = (GetMouseAndKeys()->GetMouseMoveAndCentre() / turnSpeed);
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

//int Player::getKeyNo() {
//	return keyNo;
//}

//Sets
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

void Player::setHasRedKey()
{
	hasRedKey = true;
}

void Player::setHasBlueKey()
{
	hasBlueKey = true;
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