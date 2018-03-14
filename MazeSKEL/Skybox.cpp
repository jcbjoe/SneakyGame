#include "Skybox.h"

void Skybox::Initialise()
{
	Mesh& sb = GetMeshManager()->CreateMesh("skybox");
	sb.CreateFrom("data/skybox.fbx", gd3dDevice, FX::GetMyFX()->mCache);
	mSkybox.Initialise(sb);
	mSkybox.GetScale() = Vector3(1, 1, 1);
	mSkybox.GetPosition() = Vector3(0, 0, 0);
	mSkybox.GetRotation() = Vector3(PI / 2, 0, 0);
	MaterialExt& defMat = mSkybox.GetMesh().GetSubMesh(0).material;
	defMat.flags &= ~MaterialExt::LIT;
	defMat.flags &= ~MaterialExt::ZTEST;
}

void Skybox::Release()
{

}

void Skybox::setPosition(const Vector3& camPos)
{
	mSkybox.GetPosition() = camPos;
}

Model Skybox::getModel()
{
	return mSkybox;
}