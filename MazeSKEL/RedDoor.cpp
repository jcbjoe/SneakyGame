#include "RedDoor.h" 

RedDoor::RedDoor(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale)
{
	GetModel().Initialise(*GetMeshManager()->GetMesh("door"));

	GameObject::setInitialPos();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 0.3, 0.3, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Door.dds", true, gd3dDevice);
	mat.texture = "Door.dds";

	GetModel().SetOverrideMat(&mat);
}

void RedDoor::Update(float dTime) {
	if (getMove()) {
		GetModel().GetPosition() = GetPosition() + Vector3(x, 0, 0);
		if (x <= 0.97) {
			x += 0.5 * dTime;
		}
	}
}