#include "FPSCamera.h"
#include "D3D.h"
#include "D3DUtil.h"
#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


void FPSCamera::Initialise(const Vector3& pos, const DirectX::SimpleMath::Vector3& tgt, Matrix& viewSpaceTfm)
{
	mpViewSpaceTfm = &viewSpaceTfm;
	CreateViewMatrix(*mpViewSpaceTfm, pos, tgt, Vector3(0, 1, 0));
	mCamPos = pos;
}

void FPSCamera::Move(float dTime, bool forward, bool back, bool left, bool right, bool hasRedKey, bool hasBlueKey)
{
	if (!forward && !back && !left && !right)
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


	//Collisions go here
	//Set y
	pos.y = mCamPos.y;
	
	
	//For every object in the level
	for (int i(0); i < 10; i++)
	{
		for (int k(0); k < 10; k++)
		{
			
			//If object in world is a wall
			if (GetLevelManager()->getCurrentLevel()->getObjectAtCoordinate(i, k) == 1 || (GetLevelManager()->getCurrentLevel()->getObjectAtCoordinate(i, k) == 6 && !hasRedKey) || (GetLevelManager()->getCurrentLevel()->getObjectAtCoordinate(i, k) == 8 && !hasBlueKey))
			{
				//Setup variables
				float leftX = i - 0.65f;
				float rightX = i + 0.65f;
				float topZ = k + 0.65f;
				float bottomZ = k - 0.65f;
	
				float finalZ = mCamPos.z;
				float finalX = mCamPos.x;
	
				bool alreadyCollidedLR(false);
				bool alreadyCollidedTB(false);
				//If you have collided with the top side of a block
				if ((pos.z < topZ && pos.z > k + 0.5f) && (pos.x <= rightX && pos.x >= leftX))
				{
					alreadyCollidedTB = true;
					finalZ = topZ;
				}
				else if ((pos.z > bottomZ && pos.z < k - 0.5f) && (pos.x <= rightX && pos.x >= leftX))
				{
					alreadyCollidedTB = true;
					finalZ = bottomZ;
				}
	
	
				////If you have collided with the left side of a block
				if ((pos.x > leftX && pos.x < i + 0.5f) && (pos.z <= topZ && pos.z >= bottomZ) && alreadyCollidedTB == false)
				{
					finalX = leftX;
					alreadyCollidedLR = true;
				}
				//If you have collided with the right side of a block
				else if ((pos.x < rightX && pos.x > i - 0.5f) && (pos.z <= topZ && pos.z >= bottomZ) && alreadyCollidedTB == false)
				{
					finalX = rightX;
					alreadyCollidedLR = true;
				}
				if (alreadyCollidedTB)
				{
					pos.z = finalZ;
				}
				else if (alreadyCollidedLR)
				{
					pos.x = finalX;
				}
			}
		}
	}

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
	float crouchHeight = 0.3f;
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

