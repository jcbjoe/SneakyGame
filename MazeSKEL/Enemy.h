#ifndef ENEMY_H
#define ENEMY_H

#include "D3D.h"
#include "Model.h"
#include "UserInterfaceManager.h"
#include <vector>

#include "Mesh.h" 
#include "Model.h" 
#include "GeometryBuilder.h" 
#include "FX.h" 
#include "GameObject.h"
#include "GameObjectManager.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Enemy : public GameObject
{
public:

	Enemy(string name, Vector3 position, Vector3 rotation, Vector3 scale);

	void Update(float dTime) override;

	void pathFindToNextWaypoint();


private:

	void detectPlayer(bool& bl);
	float detectionMeter;
	float visionCone;

	int waypointNumber;
	vector<Vector2> canSee(int x0, int y0, int x1, int y1);
	bool followingPath;
	int currentPathPos;
	vector<Vector3> currentPath;
	float movespeed = 1.5f;

	struct customNode {
		int x;
		int y;
		int gScore;
		int hScore;
		customNode* parent;
	};
	vector<Vector3> findPath(Vector2 dest);
	int manhattanFinder(Vector2 a, Vector2 b);
	customNode* getSquareLowestFScore(vector<customNode*> openlist);
	void removeFromVector(customNode* nodeToRemove, vector<customNode*>& openList);
	bool vectorContains(customNode* containNode, vector<customNode*>& nodeVector);
	vector<customNode*> getAdjacentSquares(customNode* node, customNode* destination);
	float EnemyPlayerAngle();

	vector<customNode*> allNodes;
};

#endif

