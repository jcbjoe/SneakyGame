#ifndef FLOOR_H 
#define FLOOR_H 

#include <vector> 

#include "Mesh.h" 
#include "Model.h" 
#include "GeometryBuilder.h" 
#include "FX.h" 

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Floor
{
public:
	~Floor()
	{
		Release();
	}
	void Initialise();
	void Update(float dTime);
	void Render(float dTime);
	void Release();

	Model getModel();
	void setPosition(const int&, const int&, const int&);

private:

	std::vector<Model*> mOpaques;
	Model mFloor;

};
#endif
