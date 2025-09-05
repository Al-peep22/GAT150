#include "../GamePCH.h"
#include "EnemyController.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start() {
	_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void EnemyController::Update(float dt) {
	float dir = 0;

	viper::Actor* player = owner->scene->GetActorByName<viper::Actor>("player");
	if (player) {
		if (player->transform.position.x < owner->transform.position.x) dir = -1;
		else dir = 1;
	}

	if (dir != 0) {
		_rigidBody->ApplyForce(viper::vec2{ 1, 0 } * dir * 500);
	}

	// Save for possible multiplayer code
	/*if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) dir = -1;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) dir = +1;

	if (dir != 0) {

		_rigidBody->ApplyForce(viper::vec2{ 1, 0 } * dir * speed);
	}

	if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_UP)) {
		_rigidBody->ApplyForce(viper::vec2{ 0, -1 } * 100000);
	}*/
}

void EnemyController::OnCollision(class viper::Actor* other) {

}

void EnemyController::Read(const viper::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}