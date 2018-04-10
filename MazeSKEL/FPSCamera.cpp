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

void FPSCamera::Move(float dTime, bool forward, bool back, bool left, bool right, bool& isMoving)
{
	if (!forward && !back && !left && !right)
	{
		isMoving = false;
		return;
	}

	isMoving = true;		

	Matrix ori = Matrix::CreateFromYawPitchRoll(yaw, pitch, roll);
	Vector3 dir(0, 0, 1), up(0, 1, 0);
	dir = Vector3::TransformNormal(dir, ori);
	up = Vector3::TransformNormal(up, ori);
	Vector3 strafe = dir.Cross(up);

	float checkX(0);
	float checkZ(0);
	Vector3 keyDir(0.0f ,0.0f ,0.0f);
	Vector3 pos(mCamPos);

	if (forward)
	{
		keyDir = dir * dTime* speed;
		pos += dir * dTime* speed;
	}
	else if (back)
	{
		keyDir = -dir * dTime* speed;
		pos += -dir * dTime* speed;
	}
	if (left)
	{
		keyDir += strafe * dTime * speed;
		pos += strafe * dTime * speed;
	}
	else if (right)
	{
		keyDir -= strafe * dTime * speed;
		pos -= strafe * dTime * speed;

	}

	if (mLockAxis.x != UNLOCK)
		pos.x = mLockAxis.x;
	//if (mLockAxis.y != UNLOCK)
	//	pos.y = mLockAxis.y;
	if (mLockAxis.z != UNLOCK)
		pos.z = mLockAxis.z;


	//Collisions go here
	//Y doesnt change ever, so keep it the same.
	pos.y = mCamPos.y;

	////Neg or Pos based on 
	
	//What direction is the player trying to move in
	if (keyDir.x > 0)
	{
		checkX = 1;
	}
	else if (keyDir.x < 0)
	{
		checkX = -1;
	}
	
	if (keyDir.z > 0)
	{
		checkZ = 1;
	}
	else if (keyDir.z < 0)
	{
		checkZ = -1;
	}
	
	//Get world position of where we want to move, to check for an object
	//How far 
	float posToCheckX = pos.x + checkX * 0.1f;
	float posToCheckY = pos.z + checkZ * 0.1f;
	float distanceFromObjectX;
	float distanceFromObjectY;
	Vector2 vecFrom;
	//Return whatever numbered cell is in the array at that position
	switch (GetLevelManager()->getObjectAtWorldPos(posToCheckX, posToCheckY))
	{
	//If Player is near a wall
	case 1:

		vecFrom.x = mCamPos.x - round(posToCheckX);
		vecFrom.y = mCamPos.z - round(posToCheckY);
		
		distanceFromObjectX = 0.7f;
		distanceFromObjectY = 0.7f;
		//If you are close to the wall
		if (abs(vecFrom.x) < distanceFromObjectX && abs(vecFrom.y) < distanceFromObjectY)
		{
			//Dont allow the player to move
			pos.x = mCamPos.x;
			pos.z = mCamPos.z;
		}
		//posToCheckX = pos.x + checkX * 0.2f;
		//posToCheckY = pos.z + checkZ * 0.2f;
		//if (GetLevelManager()->getObjectAtWorldPos(posToCheckX, posToCheckY) == 1)
		//{
		//	pos.x = mCamPos.x;
		//	pos.z = mCamPos.z;
		//}
		break;
	case 7:
		vecFrom.x = mCamPos.x - round(posToCheckX);
		vecFrom.y = mCamPos.z - round(posToCheckY);

		distanceFromObjectX = 0.4f;
		distanceFromObjectY = 0.45f;
		//If you are close to the wall
		if (abs(vecFrom.x) <= distanceFromObjectX && abs(vecFrom.y) <= distanceFromObjectY)
		{
			//Dont allow the player to move
			pos.x = mCamPos.x;
			pos.z = mCamPos.z;
		}
		break;
		//ADD OTHER CASES FOR OTHER OBJECTS
	}


		
		

	////For every object in the level
	//for (int i(0); i < 10; i++)
	//{
	//	for (int k(0); k < 10; k++)
	//	{
	//		
	//		//If object in world is a wall
	//		if (GetLevelManager()->getObjectAtCoordinate(i, k) == 1)
	//		{
	//			//Setup variables
	//			float leftX = i - 0.5f;
	//			float rightX = i + 0.5f;
	//			float topZ = k + 0.5f;
	//			float bottomZ = k - 0.5f;
	//
	//			float finalZ = mCamPos.z;
	//			float finalX = mCamPos.x;
	//
	//			bool alreadyCollidedLR(false);
	//			bool alreadyCollidedTB(false);
	//			//If you have collided with the top side of a block
	//			if ((pos.z < topZ && pos.z > k + 0.5f) && (pos.x <= rightX && pos.x >= leftX))
	//			{
	//				//get players position relative to the array.
	//				int pIndexX = (int)round(pos.x);
	//				int pIndexZ = (int)round(pos.z);
	//				alreadyCollidedTB = true;
	//				finalZ = topZ;
	//			}
	//			else if ((pos.z > bottomZ && pos.z < k - 0.5f) && (pos.x <= rightX && pos.x >= leftX))
	//			{
	//				int pIndexX = (int)round(pos.x);
	//				int pIndexZ = (int)round(pos.z);
	//				alreadyCollidedTB = true;
	//				finalZ = bottomZ;
	//			}
	//
	//
	//			////If you have collided with the left side of a block
	//			else if ((pos.x > leftX && pos.x < i + 0.5f) && (pos.z <= topZ && pos.z >= bottomZ))
	//			{
	//				int pIndexX = (int)round(pos.x);
	//				int pIndexZ = (int)round(pos.z);
	//				finalX = leftX;
	//				alreadyCollidedLR = true;
	//			}
	//			//If you have collided with the right side of a block
	//			else if ((pos.x < rightX && pos.x > i - 0.5f) && (pos.z <= topZ && pos.z >= bottomZ))
	//			{
	//				int pIndexX = (int)pos.x;
	//				int pIndexZ = (int)pos.z;
	//				finalX = rightX;
	//				alreadyCollidedLR = true;
	//			}
	//
	//			if (alreadyCollidedTB)
	//			{
	//				pos.z = finalZ;
	//			}
	//			else if (alreadyCollidedLR)
	//			{
	//				pos.x = finalX;
	//			}
	//		}
	//	}
	//}

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

void FPSCamera::Bob(float dTime, bool isCrouched)
{
	bobY = sinf(((counter) * PI) / 180.0f) / 40.0f;

	if (isCrouched)
		counter += 4;
	else 
		counter += 8;

	mCamPos.y -= prevChangeY;
	mCamPos.y += bobY;
	prevChangeY = bobY;
}

void FPSCamera::ReturnToY(float dtime, float yVal)
{
	//If camera position needs to return to normal
	if (mCamPos.y != yVal)
	{
		float difference = yVal - mCamPos.y;
		if (difference > 0.05f)
		{
			mCamPos.y += 0.01f * dtime;
		}
		else if (difference < -0.05f)
		{
			mCamPos.y -= 0.01f * dtime;
		}
		else
		{
			mCamPos.y = yVal;
		}
	}
}
