#pragma once

#include "Framework/Component.h"

class PlayerController : public viper::Component, public viper::ICollidable {
public:
	float speed = 0;
	float maxSpeed = 0;
	float jump = 0;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;

	viper::RigidBody* _rigidBody{ nullptr };

public:
	PlayerController() = default;
	CLASS_PROTOTYPE(PlayerController)

	void Start() override;

	void Update(float dt) override;

	void OnCollision(class viper::Actor* other) override;

	void Read(const viper::json::value_t& value) override;
};