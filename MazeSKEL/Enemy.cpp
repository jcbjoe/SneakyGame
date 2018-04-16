#include "Enemy.h"
#include "StateManager.h"
#include "GameState.h"

Enemy::Enemy(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale) {

	waypointNumber = 1;

	GetModel().Initialise(*GetMeshManager()->GetMesh("cube"));

	GameObject::setInitialPos();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Enemy.dds", true, gd3dDevice);
	mat.texture = "Enemy.dds";
	mat.texTrsfm.scale = Vector2(1, 1);

	GetModel().SetOverrideMat(&mat);
}

void Enemy::Update(float dTime) {

	if (GetStateManager()->getCurrentStateName() == "MainGameState") {

		Vector3 playerPos = ((GameState*)GetStateManager()->getCurrentState())->getPlayer()->getCameraPosition();

		bool canSeeBool = true;

		vector<Vector2> inbetween = canSee(round(playerPos.x), round(playerPos.z), round(GetModel().GetPosition().x), round(GetModel().GetPosition().z));

		for (Vector2 coords : inbetween) {
			int objType = GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(coords.x, coords.y);
			if (objType == 1) {
				canSeeBool = false;
				break;
			}
		}

		float distance = Vector3().Distance(GetModel().GetPosition(), playerPos);

		if (canSeeBool) {
			if (((GameState*)GetStateManager()->getCurrentState())->getPlayer()->getCrouchStatus()) {
				if (distance > 1.5) {
					canSeeBool = false;
				}
			}
			else {
				if (distance > 3) {
					canSeeBool = false;
				}
			}
		}


		if (canSeeBool) {

			Vector3 pos = Vector3::Lerp(GetModel().GetPosition(), playerPos, (1 * dTime) / distance);

			Vector3 rotato = playerPos;
			rotato.x = 0;
			rotato.z = 0;

			Vector3 rot = Vector3::Lerp(GetModel().GetRotation(), rotato, (1 * dTime) / 99.0f);
			SetPosition(pos);
			SetRotation(rotato);

		}
		else {


			GameObject* waypoint = GetGameObjectManager()->getFirstObjectByName("Waypoint" + to_string(waypointNumber));

			float distance = Vector3().Distance(GetModel().GetPosition(), waypoint->GetPosition());

			Vector3 pos = Vector3::Lerp(GetModel().GetPosition(), waypoint->GetPosition(), (1 * dTime) / distance);

			SetPosition(pos);


			if (distance < 0.1) {
				if (waypointNumber == 8)
					waypointNumber = 1;
				else
					waypointNumber++;

			}
		}
	}
}

vector<Vector2> Enemy::canSee(int x0, int y0, int x1, int y1)
{
	vector<Vector2> blocks;

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int x = x0;
	int y = y0;
	int n = 1 + dx + dy;
	int x_inc = (x1 > x0) ? 1 : -1;
	int y_inc = (y1 > y0) ? 1 : -1;
	int error = dx - dy;
	dx *= 2;
	dy *= 2;

	for (; n > 0; --n)
	{

		blocks.push_back({ (float)x,(float)y });

		if (error > 0)
		{
			x += x_inc;
			error -= dy;
		}
		else
		{
			y += y_inc;
			error += dx;
		}
	}

	return blocks;
}


void Enemy::findPath(Vector2 dest) {

	vector<customNode> openList;
	vector<customNode> closedList;

	customNode start;
	start.x = round(GetModel().GetPosition().x);
	start.y = round(GetModel().GetPosition().y);
	start.gScore = 0; // Distance from the start point - worked out by using parents value and adding 1
	start.hScore = manhattanFinder({ start.x, start.y }, { dest.x, dest.y }); // Get very aprox distance from the destination using the manhattan method

	customNode destNode;
	start.x = round(dest.x);
	start.y = round(dest.y);

	
	openList.push_back(start); // Add the start point to the open list

	do {

		customNode currentSquare = getSquareLowestFScore(openList); //Get the square with the lowest FScore

		closedList.push_back(currentSquare); // Add the lowest fscored square to closed list
		removeFromVector(currentSquare, openList); // Remove the current Square from the openList

		if (vectorContains(destNode, closedList)) {
			break;
		}
		
		vector<customNode> adjacentSquares = getAdjacentSquares(currentSquare, destNode);

		for (customNode adjSquare : adjacentSquares) {

			if (vectorContains(adjSquare, closedList)) {
				continue;
			}

			if (!(vectorContains(adjSquare, openList))) {
				openList.push_back(adjSquare);
			}

		}


	} while (!closedList.empty());



}

int Enemy::manhattanFinder(Vector2 a, Vector2 b)
{
	/* Considering the points have integer coordinates and is a 2D game */
	return abs(a.x - b.x) + abs(a.y - b.y);
}

Enemy::customNode Enemy::getSquareLowestFScore(vector<customNode> openlist) {

	customNode toReturn;
	bool firstRun = true;
	int fScoreRecord;
	for (customNode node : openlist) {
		if (firstRun) {
			fScoreRecord = node.gScore + node.hScore;
			toReturn = node;
			firstRun = false;
		} else {
			int overall = node.gScore + node.hScore;
			if (overall < fScoreRecord) {
				toReturn = node;
				fScoreRecord = overall;
			}
		}
	}

	return toReturn;
}

void Enemy::removeFromVector(customNode nodeToRemove, vector<customNode>& openList) {
	int count = 0; // Remove the current square from the openList
	for (customNode node : openList) {
		if (node.x == nodeToRemove.x && node.y == nodeToRemove.y) {
			openList.erase(openList.begin() + (count - 1));
		}
		count++;
	}
}

bool Enemy::vectorContains(customNode containNode, vector<customNode>& nodeVector) {
	bool contains = false;
	for (customNode node : nodeVector) {
		if (node.x == containNode.x && node.y == containNode.y) {
			contains = true;
		}
	}

	return contains;
}

vector<Enemy::customNode> Enemy::getAdjacentSquares(customNode node, customNode destination) {
	vector<customNode> adjSquares;

	//above
	if (GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(node.x, node.y + 1) != 1) {
		customNode above;
		above.x = node.x;
		above.y = node.y + 1;
		above.gScore = node.gScore + 1;
		above.hScore = manhattanFinder({ above.x, above.y }, { destination.x, destination.y });

		adjSquares.push_back(above);
	}
	//below
	if (GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(node.x, node.y - 1) != 1) {
		customNode below;
		below.x = node.x;
		below.y = node.y - 1;
		below.gScore = node.gScore + 1;
		below.hScore = manhattanFinder({ below.x, below.y }, { destination.x, destination.y });

		adjSquares.push_back(below);
	}

	//left
	if (GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(node.x - 1, node.y) != 1) {
		customNode left;
		left.x = node.x - 1;
		left.y = node.y;
		left.gScore = node.gScore + 1;
		left.hScore = manhattanFinder({ left.x, left.y }, { destination.x, destination.y });

		adjSquares.push_back(left);
	}

	//right
	if (GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(node.x + 1, node.y) != 1) {
		customNode right;
		right.x = node.x + 1;
		right.y = node.y;
		right.gScore = node.gScore + 1;
		right.hScore = manhattanFinder({ right.x, right.y }, { destination.x, destination.y });

		adjSquares.push_back(right);
	}

	return adjSquares;
}