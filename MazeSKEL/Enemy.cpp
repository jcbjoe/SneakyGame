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

bool tDown = false;

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

		if (GetMouseAndKeys()->IsPressed(VK_T)) {
			tDown = true;
		}
		else {
			if (tDown) {
				GameObject* waypoint2 = GetGameObjectManager()->getFirstObjectByName("Waypoint" + to_string(waypointNumber));
				findPath({ round(waypoint2->GetPosition().x), (waypoint2->GetPosition().z) });
				tDown = false;
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

	vector<customNode*> openList;
	vector<customNode*> closedList;

	vector<customNode*> complete;

	customNode* start = new customNode();
	start->x = round(GetModel().GetPosition().x); // Initial Enemy Pos
	start->y = round(GetModel().GetPosition().z); // Initial Enemy Pos
	start->gScore = 0; // Distance from the start point - worked out by using parents value and adding 1
	start->hScore = manhattanFinder(Vector2(start->x, start->y), Vector2(dest.x, dest.y )); // Get very aprox distance from the destination using the manhattan method
	start->parent = nullptr; // Parent used for tracking route

	customNode* destNode = new customNode();
	destNode->x = round(dest.x);
	destNode->y = round(dest.y);
	destNode->gScore = 0;
	destNode->hScore = 0;

	
	openList.push_back(start); // Add the start point to the open list

	do {

		customNode* currentSquare = getSquareLowestFScore(openList); //Get the square with the lowest FScore

		closedList.push_back(currentSquare); // Add the lowest fscored square to closed list
		removeFromVector(currentSquare, openList); // Remove the current Square from the openList

		if (vectorContains(destNode, closedList)) {

			customNode* tmp = currentSquare;

			do {
				complete.push_back(tmp);
				tmp = tmp->parent; // Go backward
			} while (tmp != nullptr); // Until there is not more parent

			break;
		}
		
		vector<customNode*> adjacentSquares = getAdjacentSquares(currentSquare, destNode); // Get all the adjacent grid boxes - excluding walls

		
		for (int index = 0; index < adjacentSquares.size(); index++) { // Loop through adjacent

			if (vectorContains(adjacentSquares.at(index), closedList)) {
				continue;
			}

			if (!(vectorContains(adjacentSquares.at(index), openList))) {

				openList.push_back(adjacentSquares.at(index));
			} else {

				if ((currentSquare->gScore + 1) < adjacentSquares.at(index)->gScore) {

					customNode* newOne = adjacentSquares.at(index);
					newOne->gScore = currentSquare->gScore + 1;

					removeFromVector(adjacentSquares.at(index), openList);

					openList.push_back(newOne);

				}

			}

		}


	} while (!openList.empty());


	int testTxt = 0;
	for (customNode* test : complete) {
		GetUserInterfaceManager()->printDebugText("X: " + to_string(test->x) + " Y: " + to_string(test->y));

		stringstream ss;
		ss << "test1";
		ss << testTxt;

		GameObject* waypoint = new GameObject(ss.str() , Vector3(test->x, 0.4, test->y), Vector3(0, 0, 0), Vector3(0.1, 0.1, 0.1), "cube", "waypoint.dds");
		GetGameObjectManager()->addGameObject(waypoint);
		testTxt++;
	}



}

int Enemy::manhattanFinder(Vector2 a, Vector2 b)
{
	/* Considering the points have integer coordinates and is a 2D game */
	return abs(a.x - b.x) + abs(a.y - b.y);
}

Enemy::customNode* Enemy::getSquareLowestFScore(vector<customNode*> openlist) {

	customNode* toReturn;
	bool firstRun = true;
	int fScoreRecord;
	for (customNode* node : openlist) {
		if (firstRun) {
			fScoreRecord = node->gScore + node->hScore;
			toReturn = node;
			firstRun = false;
		} else {
			int overall = node->gScore + node->hScore;
			if (overall < fScoreRecord) {
				toReturn = node;
				fScoreRecord = overall;
			}
		}
	}

	return toReturn;
}

void Enemy::removeFromVector(customNode* nodeToRemove, vector<customNode*>& openList) {
	for (int i = 0; i < openList.size(); i++) {
		if (openList.at(i)->x == nodeToRemove->x && openList.at(i)->y == nodeToRemove->y) {
			openList.erase(openList.begin() + i);
		}
	}
}

bool Enemy::vectorContains(customNode* containNode, vector<customNode*>& nodeVector) {
	bool contains = false;
	for (customNode* node : nodeVector) {
		if (node->x == containNode->x && node->y == containNode->y) {
			contains = true;
		}
	}

	return contains;
}

vector<Enemy::customNode*> Enemy::getAdjacentSquares(customNode* node, customNode* destination) {
	vector<customNode*> adjSquares;

	//above
	if (GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(node->x, node->y + 1) != 1) {
		customNode* above = new customNode();
		above->x = node->x;
		above->y = node->y + 1;
		above->gScore = node->gScore + 1;
		above->hScore = manhattanFinder(Vector2(above->x, above->y ), Vector2(destination->x, destination->y ));
		above->parent = node;

		adjSquares.push_back(above);
	}
	//below
	if (GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(node->x, node->y - 1) != 1) {
		customNode* below = new customNode();
		below->x = node->x;
		below->y = node->y - 1;
		below->gScore = node->gScore + 1;
		below->hScore = manhattanFinder(Vector2(below->x, below->y ), Vector2(destination->x, destination->y ));
		below->parent = node;

		adjSquares.push_back(below);
	}

	//left
	if (GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(node->x - 1, node->y) != 1) {
		customNode* left = new customNode();
		left->x = node->x - 1;
		left->y = node->y;
		left->gScore = node->gScore + 1;
		left->hScore = manhattanFinder(Vector2(left->x, left->y ), Vector2( destination->x, destination->y ));
		left->parent = node;

		adjSquares.push_back(left);
	}

	//right
	if (GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(node->x + 1, node->y) != 1) {
		customNode* right = new customNode();
		right->x = node->x + 1;
		right->y = node->y;
		right->gScore = node->gScore + 1;
		right->hScore = manhattanFinder(Vector2(right->x, right->y ), Vector2(destination->x, destination->y));
		right->parent = node;

		adjSquares.push_back(right);
	}

	return adjSquares;
}