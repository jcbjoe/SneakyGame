#include "Skybox.h"

Skybox::Skybox(string name, Vector3 position, Quaternion rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale)
{
	Mesh& sb = GetMeshManager()->CreateMesh("skybox");
	sb.CreateFrom("data/skybox.fbx", gd3dDevice, FX::GetMyFX()->mCache);

	GetModel().Initialise(sb);
	GetModel().GetScale() = GetScale();
	GetModel().GetPosition() = GetPosition();
	// GetModel().GetRotation() = GetRotation();
	GetModel().GetRotation() = Vector3(PI / 2, 0, 0);

	MaterialExt& defMat = GetModel().GetMesh().GetSubMesh(0).material;
	defMat.flags &= ~MaterialExt::LIT;
	defMat.flags &= ~MaterialExt::ZTEST;
}

void Skybox::Update(float dTime) {

}