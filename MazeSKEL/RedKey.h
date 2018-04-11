#ifndef REDKEY_H
#define REDKEY_H

#include <vector> 
#include "Mesh.h" 
#include "Model.h" 
#include "GeometryBuilder.h" 
#include "FX.h" 
#include "GameObject.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class RedKey : public GameObject
{
public:
	RedKey(string name, Vector3 position, Vector3 rotation, Vector3 scale);

	void Update(float dTime) override;
private:

};
#endif