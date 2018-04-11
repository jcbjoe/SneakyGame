#include "Floor.h" 

Floor::Floor(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale) {

	GetModel().Initialise(*GetMeshManager()->GetMesh("floor"));

	GameObject::setInitialPos();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.8f, 0.8f, 0.8f, 0), Vector4(0.8f, 0.8f, 0.8f, 0), Vector4(0.0f, 0.0f, 0.0f, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("FloorWood.dds", true, gd3dDevice);
	mat.texture = "FloorWood.dds";
	mat.texTrsfm.scale = Vector2(20, 20);

	GetModel().SetOverrideMat(&mat);

	//SetRotation({ 0, 0, PI });
}


void Floor::Update(float dTime)
{

}