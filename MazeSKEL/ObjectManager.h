#ifndef ObjectManager_H
#define ObjectManager_H

#include "Mesh.h"
#include "Model.h"
#include "FX.h"
#include "D3D.h"
#include "GeometryBuilder.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class ObjectManager
{
public:

	void initialiseObjects();
	void render();

	void createFloor(Vector3 location);
	void createWall(Vector3 location);
	void createLoot(Vector3 location);
	Model* createEnemy(Vector3 location);
	void createWaypoint(Vector3 location);

	void ObjectManager::setSkyboxPos(Vector3);

private:

	Model mBox, mWall, mQuad, mSkybox, mLoot, mWaypoint;

	Model* mEnemy;

	vector<Model> mOpaques;

	const Vector3 gWorldScale = Vector3(10, 10, 10);
};


#endif
