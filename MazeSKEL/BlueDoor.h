#ifndef BLUEDOOR_H 
#define BLUEDOOR_H 

#include <vector> 
#include "GameObject.h"
#include "Mesh.h" 
#include "Model.h" 
#include "GeometryBuilder.h" 
#include "FX.h"
#include "GameObjectManager.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class BlueDoor : public GameObject
{
public:
	BlueDoor(string name, Vector3 position, Vector3 rotation, Vector3 scale);
	void Update(float dTime) override;
private:
	float openMov = 0;
};
#endif