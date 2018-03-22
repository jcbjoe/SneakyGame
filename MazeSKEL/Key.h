#ifndef KEY_H
#define KEY_H

#include <vector> 
#include "Mesh.h" 
#include "Model.h" 
#include "GeometryBuilder.h" 
#include "FX.h" 
#include "GameObject.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Key : public GameObject
{
public:
	Key(string name, Vector3 position, Vector3 rotation, Vector3 scale);

	void Update(float dTime) override;
private:

};
#endif