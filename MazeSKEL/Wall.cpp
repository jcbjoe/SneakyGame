#include "Wall.h" 

Wall::Wall(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale)
{
	GetModel().Initialise(*GetMeshManager()->GetMesh("wall"));

	GameObject::setInitialPos();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.4, 0.4, 0.4, 1), Vector4(0.4, 0.4, 0.4, 0), Vector4(0.05f, 0.05f, 0.0f, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("WallStone.dds", true, gd3dDevice);
	mat.texture = "WallStone.dds";

	GetModel().SetOverrideMat(&mat);


	//SetRotation({ 45, 0, 0 });
}

void Wall::Update(float dTime) {

}