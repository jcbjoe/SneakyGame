#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector> 
#include "GameObject.h"
#include "Mesh.h" 
#include "Model.h" 
#include "GeometryBuilder.h" 
#include "FX.h" 

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Skybox : public GameObject
{
public:
	Skybox(string name, Vector3 position, Vector3 rotation, Vector3 scale);

	void Update(float dTime) override;

private:
};

#endif
