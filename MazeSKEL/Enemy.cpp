#include "Enemy.h"
#include "UserInterfaceManager.h"


Enemy::Enemy(Vector3 position, Model& model) : model_(model){

	Pos = position;
	
	
	//int randomSpawn = rand() % EnemySpawnLocations->Length + 1;



}

void Enemy::setWaypoints(vector<Vector3> wayPoints) {
	wayPointsList = wayPoints;
}

void Enemy::enemyTick(float dTime) {
	//model_->GetPosition(Vector3(model_))
	Vector3 pos = Vector3::Lerp(model_.GetPosition(), wayPointsList.at(waypointNumber), 1*dTime);
	//GetUserInterfaceManager()->printDebugText(to_string(pos.x) + " : " + to_string(pos.z));
	model_.GetPosition() = pos;
}
