#include "Floor.h" 

void Floor::Initialise()
{
	mFloor.Initialise(BuildFloor(*GetMeshManager()));
	mFloor.GetScale() = Vector3(0.5, 0.5, 0.5);
	mFloor.GetPosition() = Vector3(0, 0, 0);
	MaterialExt mat = mFloor.GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("test.dds", true, gd3dDevice);
	mat.texture = "test.dds";
	mat.texTrsfm.scale = Vector2(1, 1);
	mFloor.SetOverrideMat(&mat);
}

void Floor::Release()
{
}

void Floor::Update(float dTime)
{

}

void Floor::Render(float dTime)
{
	//render all the solid models first in no particular order 
	for (Model*p : mOpaques)
		FX::GetMyFX()->Render(*p, gd3dImmediateContext);
}
Model Floor::getModel()
{
	return mFloor;
}

void Floor::setPosition(const int& x, const int& y, const int& z)
{
	mFloor.GetPosition() = Vector3(x, y, z);
}