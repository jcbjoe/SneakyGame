#include "Wall.h" 

void Wall::Initialise()
{
	mWall.Initialise(BuildWall(*GetMeshManager()));
	mWall.GetScale() = Vector3(0.5f, 0.5f, 0.5f);
	mWall.GetPosition() = Vector3(0, -0.5f, 1);
	MaterialExt mat = mWall.GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("WallGarage.dds", true, gd3dDevice);
	mat.texture = "WallGarage.dds";
	mWall.SetOverrideMat(&mat);
}

void Wall::Release()
{
}

void Wall::Update(float dTime) 
{

}

void Wall::Render(float dTime) 
{
	//render all the solid models first in no particular order 
	for (Model*p : mOpaques)
		FX::GetMyFX()->Render(*p, gd3dImmediateContext);
}