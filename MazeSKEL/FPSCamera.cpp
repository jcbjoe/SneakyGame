#include "FPSCamera.h"
#include "D3D.h"
#include "D3DUtil.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


void FPSCamera::Initialise(const Vector3& pos, const DirectX::SimpleMath::Vector3& tgt, Matrix& viewSpaceTfm)
{
	mpViewSpaceTfm = &viewSpaceTfm;
	CreateViewMatrix(*mpViewSpaceTfm, pos, tgt, Vector3(0, 1, 0));
	mCamPos = pos;
}

void FPSCamera::Move(float dTime, bool forward, bool back, bool left, bool right, bool crouch, bool isCrouched)
{
	if (!forward && !back && !left && !right && !crouch)
		return;

	Matrix ori = Matrix::CreateFromYawPitchRoll(yaw, pitch, roll);
	Vector3 dir(0, 0, 1), up(0, 1, 0);
	dir = Vector3::TransformNormal(dir, ori);
	up = Vector3::TransformNormal(up, ori);
	Vector3 strafe = dir.Cross(up);


	Vector3 pos(mCamPos);
	if (forward)
		pos += dir * dTime* speed;
	else if (back)
		pos += -dir * dTime * speed;

	if (left)
		pos += strafe * dTime * speed;
	else if (right)
		pos -= strafe * dTime * speed;

	if (mLockAxis.x != UNLOCK)
		pos.x = mLockAxis.x;
	//if (mLockAxis.y != UNLOCK)
	//	pos.y = mLockAxis.y;
	if (mLockAxis.z != UNLOCK)
		pos.z = mLockAxis.z;

	CreateViewMatrix(*mpViewSpaceTfm, pos, pos + dir, up);

	mCamPos = Vector3(pos.x, mCamPos.y, pos.z);
		
		
}

void FPSCamera::Update(float dTime)
{
	//Function to reupdate the camera (rotating by nothing)
	Rotate(dTime, 0, 0, 0);
}

void FPSCamera::Crouch(bool isCrouched)
{
	float crouchHeight = 0.25f;
	float standingHeight = 0.5f;

	//If player should be crouching
	if (isCrouched)
	{
		//if player hasnt reached crouching position
		if (mCamPos.y > crouchHeight)
		{
			//Lower them down
			mCamPos.y -= 0.01f;
		}
	}
	//If player should be standing
	else
	{
		//If player isnt standing yet
		if (mCamPos.y < standingHeight)
		{
			//Make them stand up slowly
			mCamPos.y += 0.01f;
		}
	}

}



void FPSCamera::Rotate(float dTime, float _yaw, float _pitch, float _roll)
{
	yaw += _yaw * dTime * rspeed;
	pitch += _pitch * dTime * rspeed;
	roll += _roll * dTime * rspeed;
	Matrix ori;

	//Fix gimble lock
	if (pitch < -0.3f)
		pitch = -0.3f;

	if (pitch > 0.75f)
		pitch = 0.75f;


	ori = Matrix::CreateFromYawPitchRoll(yaw, pitch, roll);
	Vector3 dir(0, 0, 1), up(0, 1, 0);
	dir = Vector3::TransformNormal(dir, ori);
	up = Vector3::TransformNormal(up, ori);
	assert(mpViewSpaceTfm);
	CreateViewMatrix(*mpViewSpaceTfm, mCamPos, mCamPos + dir, up);
}
