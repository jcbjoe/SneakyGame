#ifndef WALL_H 
#define WALL_H 

#include <vector> 
#include "GameObject.h"
#include "Mesh.h" 
#include "Model.h" 
#include "GeometryBuilder.h" 
#include "FX.h" 

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Wall : public GameObject
{
public:
	Wall(string name, Vector3 position, Quaternion rotation, Vector3 scale);

	void start();
	void update(float dTime); // Virtual

private:

};
#endif
