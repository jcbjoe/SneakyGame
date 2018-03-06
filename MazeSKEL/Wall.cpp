#include "Wall.h"
#include "GeometryBuilder.h"
#include "FX.h"
#include "Input.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Vector3 gWorldScale(10, 10, 10);

void Wall::Initialise() {
	mQuad.Initialise(BuildQuad(*GetMeshManager()));

	//textured lit box
	mBox.Initialise(BuildCube(*GetMeshManager()));
	mBox.GetPosition() = Vector3(0, -0.5f, 1);
	mBox.GetScale() = Vector3(0.5f, 0.5f, 0.5f);
	MaterialExt mat = mQuad.GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("test.dds", true, gd3dDevice);
	mat.texture = "test.dds";
	mBox.SetOverrideMat(&mat);


	// floor
	mQuad.GetScale() = Vector3(3, 1, 3);
	mQuad.GetPosition() = Vector3(0, -1, 0);
	mat = mQuad.GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 0), Vector4(0.9f, 0.8f, 0.8f, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("test.dds", true, gd3dDevice);
	mat.texture = "test.dds";
	mat.texTrsfm.scale = Vector2(10, 10);
	mQuad.SetOverrideMat(&mat);

	//scale the world
	mOpaques.push_back(&mQuad);
	mOpaques.push_back(&mBox);
	for (Model* obj : mOpaques)
	{
		obj->GetScale() *= gWorldScale;
		obj->GetPosition() *= gWorldScale;
	}
}

void Wall::Release()
{
}

void Wall::Update(float dTime) {

}

void Wall::Render(float dTime) {
	//render all the solid models first in no particular order
	for (Model*p : mOpaques)
		FX::GetMyFX()->Render(*p, gd3dImmediateContext);
}