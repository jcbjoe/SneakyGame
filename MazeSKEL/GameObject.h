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
	//Main Constructor for making classes and inheritance
	GameObject(string name, Vector3 position, Vector3 rotation, Vector3 scale);

	//Secondary Constructor for creating objects when a class isnt nessesary
	GameObject(string name, Vector3 position, Vector3 rotation, Vector3 scale, string mesh, string texture);

	virtual void Update(float dTime);
	virtual void Render();

	void SetModel(Model& model) {
		model_ = model;
	}

	//Getters and Setters
	Model &GetModel() { return model_;}

	Vector3 GetPosition() {
		return position_;
	}
	Vector3 GetScale() {
		return scale_;
	}
	Vector3 GetRotation() {
		return rotation_;
	}
	string GetName() {
		return name_;
	}

	void SetPosition(Vector3 pos) {
		position_ = pos;
		GetModel().GetPosition() = pos;
	}

	void SetRotation(Vector3 rot) {
		rotation_ = rot;
		GetModel().GetRotation() = rot;
	}

	void SetScale(Vector3 scale) {
		scale_ = scale;
		GetModel().GetScale() = scale;
	}

	void incrementYRotation(const float rotation) {
		model_.GetRotation() += Vector3(0, rotation, 0);
	}

	void moveObject();
	bool getMove();
	void setIndex(int index);
	int getIndex();
private:

	string name_;
	Vector3 position_;
	Vector3 rotation_;
	Vector3 scale_;
	bool move_ = false;
	int index_;

	Model model_;
};

#endif