#include "BlueDoor.h" 

BlueDoor::BlueDoor(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale)
{
	GetModel().Initialise(*GetMeshManager()->GetMesh("door"));

	GameObject::setInitialPos();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.4, 0.4, 0.4, 1), Vector4(0.3, 0.3, 1, 0), Vector4(0.0f, 0.0f, 0.0f, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Door.dds", true, gd3dDevice);
	mat.texture = "Door.dds";

	GetModel().GetPreRotateOffset() = Vector3(0, 0, 1.0f);
	SetPosition(GetModel().GetPosition() - Vector3(0, 0, 0.5f));
	GetModel().SetOverrideMat(&mat);
}

void BlueDoor::Update(float dTime) {
	if (getMove()) {
		Vector3 currPos = GetPosition();

		//SetPosition(Vector3(0, 0, 0) + Vector3(0, 0, 0.5f));

		SetRotation({ 0, openMov, 0 });
		SetPosition(currPos);

		if (openMov <= PI / 2.0f)
		{
			openMov += 1 * dTime;
		}
		else
		{
			setMove(false);
		}
	}
}