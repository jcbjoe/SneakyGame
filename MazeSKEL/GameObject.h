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
	Quaternion &GetRotation() {
		return rotation_;
	}
	float &GetRotationAngle()
	{
		return dAngle_;
	}
	void setYRotation(const float& rotation)
	{
		rotation_ =+ Quaternion::CreateFromAxisAngle(Vector3(0, 1, 0), rotation);
	}


private:

	float dAngle_ = 0.0f;

	string name_;
	Vector3 position_;
	Quaternion rotation_;
	Vector3 scale_;

	Model model_;

};

#endif