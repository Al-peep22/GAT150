#include "../GamePCH.h"
#include "FlyingEnemyController.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start() {
	_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void FlyingEnemyController::Update(float dt) {
	//float dir = 0;

	viper::Actor* player = owner->scene->GetActorByName<viper::Actor>("player");
	if (player) {
		//if (player->transform.position.x < owner->transform.position.x) dir = -1;
		//else dir = 1;
		viper::vec2 direction = player->transform.position - owner->transform.position;
		_rigidBody->ApplyForce(direction.Normalized() * speed);
	}

	//if (dir != 0) {
	//	_rigidBody->ApplyForce(viper::vec2{ 1, 0 } *dir * 500);
	//}
}

void FlyingEnemyController::OnCollision(class viper::Actor* other) {

}

void FlyingEnemyController::Read(const viper::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}