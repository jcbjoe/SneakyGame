#include "GameObject.h"



GameObject::GameObject(string name, Vector3 position, Vector3 rotation, Vector3 scale) :
	name_(name),
	position_(position),
	rotation_(rotation),
	scale_(scale)
{

}

GameObject::GameObject(string name, Vector3 position, Vector3 rotation, Vector3 scale, string mesh, string texture) :
	name_(name),
	position_(position),
	rotation_(rotation),
	scale_(scale)
{
	GetModel().Initialise(*GetMeshManager()->GetMesh(mesh));

	GetModel().GetScale() = GetScale();
	GetModel().GetPosition() = GetPosition();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture(texture, true, gd3dDevice);
	mat.texture = texture;

	GetModel().SetOverrideMat(&mat);
}

void GameObject::Update(float dTime)
{
}

void GameObject::Render()
{
	FX::MyFX& fx = *FX::GetMyFX();
	fx.Render(model_, gd3dImmediateContext);
}

void GameObject::moveObject() {
	move_ = true;
}

bool GameObject::getMove() {
	return move_;
}

int GameObject::getIndex() {
	return index_;
}

void GameObject::setIndex(int index) {
	index_ = index;
}

void GameObject::setInitialPos() {
	SetPosition(position_);
	SetRotation(rotation_);
	SetScale(scale_);
}