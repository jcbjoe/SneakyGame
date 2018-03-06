#include "Player.h"
#include "Input.h"
#include "FX.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Player::Initialise() {
	mCamera.Initialise(Vector3(-15, -9.5, -25), Vector3(0, 0, 1), FX::GetViewMatrix());
	mCamera.LockMovementAxis(FPSCamera::UNLOCK, FPSCamera::UNLOCK, FPSCamera::UNLOCK);
}
void Player::Release() {

}
void Player::Update(float dTime) {
	mCamera.Move(dTime, GetMouseAndKeys()->IsPressed(VK_W), GetMouseAndKeys()->IsPressed(VK_S), GetMouseAndKeys()->IsPressed(VK_A), GetMouseAndKeys()->IsPressed(VK_D));
	Vector2 m = GetMouseAndKeys()->GetMouseMoveAndCentre();
	if (m.x != 0 || m.y != 0)
		mCamera.Rotate(dTime, m.x, m.y, 0);
}
void Player::Render(float dTime) {
	GetMouseAndKeys()->PostProcess();
}