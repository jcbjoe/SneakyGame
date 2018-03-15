#ifndef GAMEOBJECT_H 
#define GAMEOBJECT_H 

#include <vector> 
#include <string>

#include "Mesh.h" 
#include "Model.h" 
#include "GeometryBuilder.h" 
#include "FX.h" 

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class GameObject
{
public:
	GameObject(string name, Vector3 position, Quaternion rotation, Vector3 scale);

	virtual void Update(float dTime);
	virtual void Render();
	void SetModel(Model& model) {
		model_ = model;
	}
	Model &GetModel() { return model_;}
	Vector3 &GetPosition() {
		return position_;
	}
	Vector3 &GetScale() {
		return scale_;
	}
	Vector3 &GetRotation() {
		return model_.GetRotation();
	}
	string &GetName() {
		return name_;
	}

	void setYRotation(const float& rotation)
	{
		GetRotation().Y =+ Quaternion::CreateFromAxisAngle(Vector3(0, 1, 0), rotation);
	}


private:

	string name_;
	Vector3 position_;
	Quaternion rotation_;
	Vector3 scale_;

	Model model_;

};

#endif