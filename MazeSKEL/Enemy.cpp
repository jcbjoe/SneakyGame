#include "Enemy.h"
#include "StateManager.h"
#include "GameState.h"

Enemy::Enemy(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale) {

	detectionMeter = 0.0f;
	waypointNumber = 1;

	visionCone = D2R(50);
	GetModel().Initialise(*GetMeshManager()->GetMesh("Ghost"));

	GameObject::setInitialPos();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.4f, 0.4f, 0.4f, 0), Vector4(1.0f, 1.0f, 1.0f, 0), Vector4(0.3f, 0.3f, 0.3f, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("booMap.dds", true, gd3dDevice);
	mat.texture = "booMap.dds";
	mat.texTrsfm.scale = Vector2(1, 1);

	GetModel().SetOverrideMat(&mat);

	pathFindToNextWaypoint();
}

bool tDown = false;

void Enemy::Update(float dTime) {

	if (GetStateManager()->getCurrentStateName() == "MainGameState") {
		if (!((GameState*)GetStateManager()->getCurrentState())->paused) {

			Vector3 playerPos = ((GameState*)GetStateManager()->getCurrentState())->getPlayer()->getCameraPosition();

			Vector3 eye = { 0, 0, -1 };
			Matrix ma = Matrix::CreateRotationY(GetRotation().y);

			FX::SetupSpotLight(6, true, { GetPosition().x, 0.0f, GetPosition().z }, Vector3::TransformNormal(eye, ma), Vector3(1.0f, 0.84f, 0.8f), Vector3(0.8f, 0.8f, 0.8f), Vector3(0.8f, 0.84f, 0.8f), 3.0f, 0.5f, D2R(15), D2R(50));

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

			if (distance < 0.2 && !caught) {
				setCaught();
				GetIAudioMgr()->GetSfxMgr()->Play("soundCaught", false, false, nullptr, 1.0);
			}

			if (canSeeBool) {
				if (((GameState*)GetStateManager()->getCurrentState())->getPlayer()->getCrouchStatus()) {
					if (distance > 2) {
						canSeeBool = false;
					}
					else
					{
						if (EnemyPlayerAngle() >= (visionCone / 2.0f))
						{
							canSeeBool = false;
						}
					}
				}
				else
				{
					if (distance > 5)
					{
						canSeeBool = false;
					}
				}
			}

			//Change bool based on enemies detection status
			detectPlayer(canSeeBool);

			if (canSeeBool) {

				Vector3 pos = Vector3::Lerp(GetModel().GetPosition(), playerPos, (movespeed * dTime) / distance);

				Vector3 rotato = playerPos;
				rotato.x = 0;
				rotato.z = 0;

				Vector2 dirToEnemy;
				dirToEnemy.x = ((GameState*)GetStateManager()->getCurrentState())->getPlayer()->getCameraPosition().x - GetModel().GetPosition().x;
				dirToEnemy.y = ((GameState*)GetStateManager()->getCurrentState())->getPlayer()->getCameraPosition().z - GetModel().GetPosition().z;

				// get the player angle on the y axis
				SetRotation(Vector3(GetModel().GetRotation().x, atan2(-dirToEnemy.y, dirToEnemy.x) - (PI / 2), GetModel().GetRotation().z));

				SetPosition(pos);

				followingPath = false;

			}
			else {

				if (followingPath) {

					float distanceFromPath = Vector3().Distance(GetModel().GetPosition(), currentPath.at(currentPathPos));

					Vector3 pos = Vector3::Lerp(GetModel().GetPosition(), currentPath.at(currentPathPos), (movespeed * dTime) / distanceFromPath);

					SetPosition(pos);

					Vector2 dirToEnemy;
					dirToEnemy.x = currentPath.at(currentPathPos).x - GetModel().GetPosition().x;
					dirToEnemy.y = currentPath.at(currentPathPos).z - GetModel().GetPosition().z;

					// get the player angle on the y axis
					Vector3 lerpToTarget = Vector3::Lerp(GetModel().GetRotation(), Vector3(GetModel().GetRotation().x, atan2(-dirToEnemy.y, dirToEnemy.x) - (PI / 2), GetModel().GetRotation().z), (5 * dTime));
					SetRotation(lerpToTarget);

					if (distanceFromPath < 0.25) {
						if (currentPathPos == (currentPath.size() - 1)) {

							pathFindToNextWaypoint();
							currentPathPos = 0;

							if (waypointNumber > GetLevelManager()->getCurrentLevel()->getHowManyWaypoints())
								waypointNumber = 1;
							else
								waypointNumber++;

							pathFindToNextWaypoint();

						}
						else {

							currentPathPos++;

						}
					}
				}
				else {
					pathFindToNextWaypoint();
				}

			}

			if (GetMouseAndKeys()->IsPressed(VK_T)) {
				tDown = true;
			}
			else {
				if (tDown) {
					GameObject* waypoint2 = GetGameObjectManager()->getFirstObjectByName("Waypoint" + to_string(waypointNumber));
					tDown = false;
				}
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

void Enemy::pathFindToNextWaypoint() {

	GameObject* waypoint2 = GetGameObjectManager()->getFirstObjectByName("Waypoint" + to_string(waypointNumber));

	vector<Vector3> path = findPath(Vector2(round(waypoint2->GetPosition().x), round(waypoint2->GetPosition().z)));
	if (path.empty())
		followingPath = false;
	else
		followingPath = true;
	currentPathPos = 0;
	currentPath = path;
}

vector<Vector3> Enemy::findPath(Vector2 dest) {

	vector<customNode*> openList; // all considered squares/nodes to find the shortest path
	vector<customNode*> closedList; // Squares/nodes not to consider again

	vector<customNode*> complete; // List of the completed path

	customNode* start = new customNode();
	start->x = round(GetModel().GetPosition().x); // Initial Enemy Pos
	start->y = round(GetModel().GetPosition().z); // Initial Enemy Pos
	start->gScore = 0; // Distance from the start point - worked out by using parents value and adding 1 - Diagonals increment by 2 so there favoured
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

		if (vectorContains(destNode, closedList)) { // We are at the destination

			customNode* tmp = currentSquare; // begin the tmp list from the current square

			do {
				complete.push_back(tmp); // Add node to completed list
				tmp = tmp->parent; // Go backward finding path
			} while (tmp != nullptr); // Loop untill the parent is nullptr

			break;
		}
		
		vector<customNode*> adjacentSquares = getAdjacentSquares(currentSquare, destNode); // Get all the adjacent grid boxes - excluding walls

		
		for (int index = 0; index < adjacentSquares.size(); index++) { // Loop through adjacent nodes/squares

			if (vectorContains(adjacentSquares.at(index), closedList)) { // If the selected node/square is in the closedlist just ignore
				continue;
			}

			if (!(vectorContains(adjacentSquares.at(index), openList))) { // if the square/node isnt in the open list then add it

				openList.push_back(adjacentSquares.at(index));

			} else { // This is kinda optional but used to 'better' routes

				if ((currentSquare->gScore + 1) < adjacentSquares.at(index)->gScore) { //Check if the adjacent square/node has a better gscore than the currentSquares

					customNode* newOne = adjacentSquares.at(index); // Using that node we assign it to a new pointer
					newOne->gScore = currentSquare->gScore + 1; // Add 1 to the score

					removeFromVector(adjacentSquares.at(index), openList); // remove the old version with the old score from the open list 

					openList.push_back(newOne); // re-add to list with new score

				}

			}

		}


	} while (!openList.empty()); // loop while the openList is not empty

	vector<Vector3> pathToReturn;


	for (int i = complete.size(); i != 0; i--) {
		pathToReturn.push_back(Vector3(complete.at(i - 1)->x, 0.4, complete.at(i - 1)->y));
	}

	//Releasing
	for (customNode* node : openList) {
		delete node;
	}
	openList.empty();
	for (customNode* node : closedList) {
		delete node;
	}
	delete destNode;
	delete start;
	closedList.empty();
	complete.empty();
	
	return pathToReturn;

}

int Enemy::manhattanFinder(Vector2 a, Vector2 b)
{
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

	bool aboveBool = false;
	bool belowBool = false;
	bool leftBool = false;
	bool rightBool = false;

	//above
	if (GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(node->x, node->y + 1) != 1) {
		customNode* above = new customNode();
		above->x = node->x;
		above->y = node->y + 1;
		above->gScore = node->gScore + 1;
		above->hScore = manhattanFinder(Vector2(above->x, above->y ), Vector2(destination->x, destination->y ));
		above->parent = node;
		aboveBool = true;
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
		belowBool = true;
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
		leftBool = true;
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
		rightBool = true;
		adjSquares.push_back(right);
	}

	//Diagonals

	//Up - Left
	if (GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(node->x - 1, node->y + 1) != 1 && aboveBool && leftBool) {
		customNode* UpLeft = new customNode();
		UpLeft->x = node->x - 1;
		UpLeft->y = node->y + 1;
		UpLeft->gScore = node->gScore + 2;
		UpLeft->hScore = manhattanFinder(Vector2(UpLeft->x, UpLeft->y), Vector2(destination->x, destination->y));
		UpLeft->parent = node;

		adjSquares.push_back(UpLeft);
	}

	//Up - Right
	if (GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(node->x + 1, node->y + 1) != 1 && aboveBool && rightBool) {
		customNode* UpRight = new customNode();
		UpRight->x = node->x + 1;
		UpRight->y = node->y + 1;
		UpRight->gScore = node->gScore + 2;
		UpRight->hScore = manhattanFinder(Vector2(UpRight->x, UpRight->y), Vector2(destination->x, destination->y));
		UpRight->parent = node;

		adjSquares.push_back(UpRight);
	}

	//Bottom - Left
	if (GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(node->x - 1, node->y - 1) != 1 && belowBool && leftBool) {
		customNode* BottomLeft = new customNode();
		BottomLeft->x = node->x - 1;
		BottomLeft->y = node->y - 1;
		BottomLeft->gScore = node->gScore + 2;
		BottomLeft->hScore = manhattanFinder(Vector2(BottomLeft->x, BottomLeft->y), Vector2(destination->x, destination->y));
		BottomLeft->parent = node;

		adjSquares.push_back(BottomLeft);
	}

	//Bottom - Right
	if (GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(node->x + 1, node->y - 1) != 1 && belowBool && rightBool) {
		customNode* BottomRight = new customNode();
		BottomRight->x = node->x + 1;
		BottomRight->y = node->y - 1;
		BottomRight->gScore = node->gScore + 2;
		BottomRight->hScore = manhattanFinder(Vector2(BottomRight->x, BottomRight->y), Vector2(destination->x, destination->y));
		BottomRight->parent = node;

		adjSquares.push_back(BottomRight);
	}


	return adjSquares;
}

float Enemy::EnemyPlayerAngle()
{

	Vector3 enemyDir = Vector3::TransformNormal({ 0, 0, -1 }, Matrix::CreateRotationY(GetRotation().y));
	Vector3 playerDir = ((GameState*)GetStateManager()->getCurrentState())->getPlayer()->getCameraPosition() - GetPosition();

	float dot = (float)playerDir.x * (float)enemyDir.x + (float)playerDir.x * (float)enemyDir.z;
	float modEnemy = sqrtf(abs((float)enemyDir.x * (float)enemyDir.x + (float)enemyDir.z + (float)enemyDir.z));
	float modPlayer = sqrtf(abs((float)playerDir.x * (float)playerDir.x + (float)playerDir.z + (float)playerDir.z));

	float angleBetween = (float)acosf(dot / (modEnemy * modPlayer));

	if (angleBetween > 360.0f || angleBetween < 0.0f)
		angleBetween = 0.0f;
	//GetUserInterfaceManager()->printDebugText("ANGLE: " + to_string((float)R2D(angleBetween))); 
	//Vector3 v = (((GameState*)GetStateManager()->getCurrentState())->getPlayer()->getCameraPosition().Forward()); 
	return angleBetween;
}

void Enemy::detectPlayer(bool& canSeeBool)
{
	if (canSeeBool)
	{
		detectionMeter += 0.5f;
		if (detectionMeter >= 100.0f)
		{
			detectionMeter = 100.0f;
		}
		else
			canSeeBool = false;
	}
	else
	{
		detectionMeter -= 0.5f;
		if (detectionMeter <= 0.0f)
		{
			detectionMeter = 0.0f;
		}
		canSeeBool = false;
	}
}

bool Enemy::getCaught() {
	return caught;
}
void Enemy::setCaught() {
	caught = true;
}