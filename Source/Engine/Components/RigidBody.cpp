#include "RigidBody.h"

#include "Engine.h"
#include "SpriteRenderer.h"

namespace viper {
	FACTORY_REGISTER(RigidBody)

	RigidBody::RigidBody(const RigidBody& other) {
		bodyDef = other.bodyDef;
		size = other.size;

		if (other._physicsBody) {
			_physicsBody = std::make_unique<PhysicsBody>(*other._physicsBody);
		}
	}

	void RigidBody::Start() {
		bodyDef.actor = owner;
		if (size.x == 0 && size.y == 0) {
			auto spriteRenderer = owner->GetComponent<SpriteRenderer>();
			if (spriteRenderer) {
				size = spriteRenderer->texture->GetSize();
			}
		}

		_physicsBody = std::make_unique<PhysicsBody>(owner->transform, size * scale, bodyDef, GetEngine().GetPhysics());
	}

	void RigidBody::Update(float dt) {
		owner->transform.position = _physicsBody->GetPosition();
		owner->transform.rotation = math::radToDeg(_physicsBody->GetAngle());
		velocity = _physicsBody->GetVelocity();
	}

	void RigidBody::ApplyForce(const vec2& force) {
		_physicsBody->ApplyForce(force);
	}

	void RigidBody::ApplyTorque(float radians) {
		_physicsBody->ApplyTorque(radians);
	}

	void RigidBody::SetVelocity(const vec2& velocity) {
		_physicsBody->SetVelocity(velocity);
	}

	void RigidBody::Read(const json::value_t& value) {
		Object::Read(value);

		JSON_READ(value, size);
		JSON_READ(value, scale);

		JSON_READ_NAME(value, "gravityScale", bodyDef.gravityScale);
		JSON_READ_NAME(value, "linearDamping", bodyDef.linearDamping);
		JSON_READ_NAME(value, "angularDamping", bodyDef.angularDamping);
		JSON_READ_NAME(value, "constrainAngle", bodyDef.constrainAngle);
		JSON_READ_NAME(value, "isDynamic", bodyDef.isDynamic);
		JSON_READ_NAME(value, "friction", bodyDef.friction);
		JSON_READ_NAME(value, "restitution", bodyDef.restitution);
		JSON_READ_NAME(value, "density", bodyDef.density);
		JSON_READ_NAME(value, "isSensor", bodyDef.isSensor);

		std::string shapeName;
		JSON_READ_NAME(value, "shape", shapeName);

		if (!shapeName.empty()) {
			if (equalsIqnoreCase(shapeName, "box")) bodyDef.shape = PhysicsBody::Shape::Box;
			else if (equalsIqnoreCase(shapeName, "capsule")) bodyDef.shape = PhysicsBody::Shape::Capsule;
			else if (equalsIqnoreCase(shapeName, "circle")) bodyDef.shape = PhysicsBody::Shape::Circle;
		}
	}
}