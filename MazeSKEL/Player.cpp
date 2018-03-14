#include "Player.h" 

void Player::Initialise() 
{
	mCamera.Initialise(Vector3(-15, -9.5, -25), Vector3(0, 0, 1), FX::GetViewMatrix());
	mCamera.LockMovementAxis(FPSCamera::UNLOCK, FPSCamera::UNLOCK, FPSCamera::UNLOCK);
}
void Player::Release() 
{
}
void Player::Update(float dTime) 
{

}
void Player::Render(float dTime) 
{
	GetMouseAndKeys()->PostProcess();
}