#include "GameObject.h"



GameObject::GameObject(string name, Vector3 position, Quaternion rotation, Vector3 scale) :
	name_(name),
	position_(position),
	rotation_(rotation),
	scale_(scale)
{
	
}

void GameObject::Update(float dTime)
{
}

void GameObject::Render()
{
	FX::MyFX& fx = *FX::GetMyFX();
	fx.Render(model_, gd3dImmediateContext);
}
