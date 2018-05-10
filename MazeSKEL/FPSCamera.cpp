#include "FPSCamera.h"
#include "D3D.h"
#include "D3DUtil.h"
#include "Game.h"
#include "GameState.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


void FPSCamera::Initialise(const Vector3& pos, const DirectX::SimpleMath::Vector3& tgt, Matrix& viewSpaceTfm)
{
	mpViewSpaceTfm = &viewSpaceTfm;
	CreateViewMatrix(*mpViewSpaceTfm, pos, tgt, Vector3(0, 1, 0));
	mCamPos = pos;
	startPos = pos;
}

void FPSCamera::Move(float dTime, bool forward, bool back, bool left, bool right, bool& isMoving, bool hasRedKey, bool hasBlueKey)
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
	switch (GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(posToCheckX, posToCheckY))
	{
	//If Player is near a wall
	case 01:

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
	//If Player is near a Red door
	case 02:

		vecFrom.x = mCamPos.x - round(posToCheckX);
		vecFrom.y = mCamPos.z - round(posToCheckY);

		distanceFromObjectX = 0.4f;
		distanceFromObjectY = 0.7f;
		//If you are close to the door
		if (abs(vecFrom.x) < distanceFromObjectX && abs(vecFrom.y) < distanceFromObjectY  && (!hasRedKey || GetGameObjectManager()->getFirstObjectByName("RedDoor")->getMove()))
		{
			//Dont allow the player to move
			pos.x = mCamPos.x;
			pos.z = mCamPos.z;
		}

		break;
	//If Player is near a Blue door
	case 03:

		vecFrom.x = mCamPos.x - round(posToCheckX);
		vecFrom.y = mCamPos.z - round(posToCheckY);

		distanceFromObjectX = 0.7f;
		distanceFromObjectY = 0.4f;
		//If you are close to the door
	
		if (abs(vecFrom.x) < distanceFromObjectX && abs(vecFrom.y) < distanceFromObjectY && (!hasBlueKey || GetGameObjectManager()->getFirstObjectByName("BlueDoor")->getMove()))
		{
			//Dont allow the player to move
			pos.x = mCamPos.x;
			pos.z = mCamPos.z;
		}

		break;
	//If Player is near a wallWindow
	case 05:

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

	//If player is near the deposit box
	case 10:
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



	CreateViewMatrix(*mpViewSpaceTfm, pos, pos + dir, up);

	mCamPos = Vector3(pos.x, mCamPos.y, pos.z);
		
		
}

void FPSCamera::Update(float dTime)
{
	if (!((GameState*)GetStateManager()->getCurrentState())->paused) {
		//Function to reupdate the camera (rotating by nothing)
		Rotate(dTime, 0, 0, 0);
	}

	vector<GameObject*> go = GetGameObjectManager()->getAllObjectsByName("Enemy");
	if (go.size() > 0)
	{
		float detect = 0;
		for (int i = 0; i < go.size(); i++)
		{
			Vector3 distFromPlayer = go[i]->GetPosition() - mCamPos;
			float len = distFromPlayer.Length();
			if (len < 0.3f)
			{
				//Move player back
				go[i]->setCaught(false);
				mCamPos = startPos;
			}
		}

	}
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
	rot += _yaw * dTime * rspeed;

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
		counter += 500 * dTime;
	else 
		counter += 1000 * dTime;

	mCamPos.y -= prevChangeY;
	currBobY -= prevChangeY;

	mCamPos.y += bobY;
	currBobY += bobY;

	prevChangeY = bobY;

	if(sinf(((counter)* PI) / 180.0f) < -0.99)
		if(isCrouched)
			GetIAudioMgr()->GetSfxMgr()->Play("soundFootstep3", false, false, nullptr, 0.3);
		else
			GetIAudioMgr()->GetSfxMgr()->Play("soundFootstep3", false, false, nullptr, 0.5);
}

void FPSCamera::ReturnToY(float dtime, float yVal)
{
	//If camera position needs to return to normal
	if (mCamPos.y != yVal)
	{
		float difference = yVal - mCamPos.y;
		if (difference > 0.05f)
		{
			currBobY += 0.01f * dtime;
			mCamPos.y += 0.01f * dtime;
		}
		else if (difference < -0.05f)
		{
			currBobY -= 0.01f * dtime;
			mCamPos.y -= 0.01f * dtime;
		}
		else
		{
			mCamPos.y = yVal;
		}
	}
}
