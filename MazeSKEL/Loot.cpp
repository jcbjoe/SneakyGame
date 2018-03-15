#include "Loot.h" 

Loot::Loot(string name, Vector3 position, Quaternion rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale) {

	GetModel().Initialise(*GetMeshManager()->GetMesh("loot"));
	GetModel().GetScale() = GetScale();
	GetModel().GetPosition() = GetPosition();
	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Metal.dds", true, gd3dDevice);
	mat.texture = "Metal.dds";
	GetModel().SetOverrideMat(&mat);
}

void Loot::Update(float dTime)
{

}