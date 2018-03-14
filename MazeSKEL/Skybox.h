#ifndef SKYBOX_H
#define SKYBOX_H

#include "Mesh.h"
#include "FX.h"
#include "Model.h"

#include <vector>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Skybox
{
public:
	~Skybox()
	{
		Release();
	}
	void Initialise();
	void Release();

	void setPosition(const Vector3&);
	Model getModel();

private:
	Model mSkybox;
};

#endif
