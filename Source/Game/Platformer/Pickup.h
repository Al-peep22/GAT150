#pragma once

#include "Framework/Component.h"

class Pickup : public viper::Component, public viper::ICollidable {
public:
	viper::RigidBody* _rigidBody{ nullptr };

public:
	Pickup() = default;
	CLASS_PROTOTYPE(Pickup)

	void Start() override;

	void Update(float dt) override;

	void OnCollision(class viper::Actor* other) override;

	void Read(const viper::json::value_t& value) override;
};