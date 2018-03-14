#ifndef LOOT_H 
#define LOOT_H 

#include <vector> 

#include "Mesh.h" 
#include "Model.h" 
#include "GeometryBuilder.h" 
#include "FX.h" 

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Loot
{
public:
	~Loot()
	{
		Release();
	}
	void Initialise();
	void Update(float dTime);
	void Render(float dTime);
	void Release();

	Model getModel();
	void setPosition(const float&, const float&, const float&);
	void setRotation(const float&, const float&, const float&);

private:
	std::vector<Model*> mOpaques;
	Model mLoot;
};
#endif

