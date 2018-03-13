#include "Enemy.h"

Enemy::Enemy(Vector3 position) {
	
	Pos = position;
	
	
	//int randomSpawn = rand() % EnemySpawnLocations->Length + 1;



}

void Enemy::setWaypoints(vector<Vector3> wayPoints) {
	wayPointsList = wayPoints;
}

