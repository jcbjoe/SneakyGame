#ifndef RETURNBOX_H 
#define RETURNBOX_H 

#include <vector> 
#include "GameObject.h"
#include "Mesh.h" 
#include "Model.h" 
#include "GeometryBuilder.h" 
#include "FX.h" 

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class ReturnBox : public GameObject
{
public:
	ReturnBox(string name, Vector3 position, Vector3 rotation, Vector3 scale);


	void Update(float dTime) override;

private:

	int coinsStored;
	int coinsRequired;
};
#endif
