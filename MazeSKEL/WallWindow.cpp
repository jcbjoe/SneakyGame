#include "WallWindow.h" 

WallWindow::WallWindow(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale)
{
	GetModel().Initialise(*GetMeshManager()->GetMesh("door"));

	GameObject::setInitialPos();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.4, 0.4, 0.4, 1), Vector4(0.4, 0.4, 0.4, 1), Vector4(0.05f, 0.05f, 0.0f, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("WallStoneWindow.dds", true, gd3dDevice);
	mat.texture = "WallStone.dds";
	mat.flags |= MaterialExt::TFlags::ALPHA_TRANSPARENCY;
	GetModel().SetOverrideMat(&mat);
}

void WallWindow::Update(float dTime) {

}