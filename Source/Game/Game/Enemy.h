#pragma once

#include "Framework/Component.h"

class Enemy : public viper::Component, public viper::ICollidable, public viper::IObserver {
public:
	float speed = 200;
	float fireTimer = 0;
	float fireTime = 0;

	viper::RigidBody* _rigidBody{ nullptr };

public:
	Enemy() = default;
	CLASS_PROTOTYPE(Enemy)

	void Start() override;

	void Update(float dt) override;

	void OnCollision(class viper::Actor* other) override;

	void OnNotify(const viper::Event& event) override;

	void Read(const viper::json::value_t& value) override;
};