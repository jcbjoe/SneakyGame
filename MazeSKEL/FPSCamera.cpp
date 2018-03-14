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

void FPSCamera::Update()
{
	//CreateViewMatrix(*mpViewSpaceTfm, mCamPos, mCamPos, mCamPos.Up);
}

void FPSCamera::Move(float dTime, bool forward, bool back, bool left, bool right)
{
	if (!forward && !back && !left && !right)
		return;

	Matrix ori = Matrix::CreateFromYawPitchRoll(yaw, pitch, roll);
	Vector3 dir(0, 0, 1), up(0, 1, 0);
	dir = Vector3::TransformNormal(dir, ori);
	up = Vector3::TransformNormal(up, ori);
	Vector3 strafe = dir.Cross(up);


	Vector3 pos(mCamPos);

	//Set x and z
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

	//Set y
	pos.y = mCamPos.y;

	//Update screen
	CreateViewMatrix(*mpViewSpaceTfm, mCamPos, pos + dir, up);

	//Save Camera Position
	mCamPos = Vector3(pos.x, mCamPos.y, pos.z);
		
		
}

void FPSCamera::Crouch(bool isCrouched)
{
	if (isCrouched)
	{
		if (mCamPos.y > 0.25f)
			mCamPos.y -= 0.01f;
		else
			mCamPos.y = 0.25f;
	}
	else
	{
		if (mCamPos.y < 0.5f)
			mCamPos.y += 0.01f;
		else
			mCamPos.y = 0.5f;
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
	CreateViewMatrix(*mpViewSpaceTfm, mCamPos, mCamPos + dir, up);
}
