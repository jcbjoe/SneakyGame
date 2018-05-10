#include "GameObject.h"

//Baseclass for the majority of objects placed into each level

//Constructor
GameObject::GameObject(string name, Vector3 position, Vector3 rotation, Vector3 scale) :
	name_(name),
	position_(position),
	rotation_(rotation),
	scale_(scale)
{

}

//Constructor
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

//Update
void GameObject::Update(float dTime)
{
}

//Render
void GameObject::Render()
{
	FX::MyFX& fx = *FX::GetMyFX();
	if (GetName() == "WallWindow") {
		model_.HasOverrideMat()->flags &= ~MaterialExt::TFlags::CCW_WINDING; //render the back
		fx.Render(model_, gd3dImmediateContext);
		model_.HasOverrideMat()->flags |= MaterialExt::TFlags::CCW_WINDING;	//render the front
	}
	fx.Render(model_, gd3dImmediateContext);
}

//Set the object to moving
void GameObject::moveObject() {
	move_ = true;
}

//Is the object moving
bool GameObject::getMove() {
	return move_;
}

//What is the objects index
int GameObject::getIndex() {
	return index_;
}

//Set the objects index
void GameObject::setIndex(int index) {
	index_ = index;
}

//Set initial attributes of an object
void GameObject::setInitialPos() {
	SetPosition(position_);
	SetRotation(rotation_);
	SetScale(scale_);
}

//Set the object to be moving/ not moving
void GameObject::setMove(bool bl)
{
	move_ = bl;
}

bool GameObject::getCaught() {
	return caught;
}
void GameObject::setCaught(bool bl) {
	caught = bl;
}