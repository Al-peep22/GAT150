#include "../GamePCH.h"
#include "Pickup.h"

FACTORY_REGISTER(Pickup)

void Pickup::Start() {
	_rigidBody = owner->GetComponent<viper::RigidBody>();
}

void Pickup::Update(float dt) {
	//
}

void Pickup::OnCollision(class viper::Actor* other) {
	if (viper::equalsIqnoreCase(other->tag, "player")) {
		owner->destroyed = true;
	}
}

void Pickup::Read(const viper::json::value_t& value) {
	Object::Read(value);
}