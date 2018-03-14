#ifndef FLOOR_H 
#define FLOOR_H 

#include <vector> 

#include "Mesh.h" 
#include "Model.h" 
#include "GeometryBuilder.h" 
#include "FX.h" 
#include "GameObject.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Floor : public GameObject
{
public:
	Floor(string name, Vector3 position, Quaternion rotation, Vector3 scale);
	void start();
	void Update(float dTime);

private:

};
#endif
