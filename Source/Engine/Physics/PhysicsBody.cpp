#include "PhysicsBody.h"

namespace viper {
	PhysicsBody::PhysicsBody(const Transform& transform, const vec2& size, const PhysicsBodyDef& def, const Physics& physics) {
		b2BodyDef bodyDef = b2DefaultBodyDef();

		// Set body definition
		bodyDef.type = (def.isDynamic) ? b2_dynamicBody : b2_staticBody;
		bodyDef.position = to_b2(Physics::PixelToWorld(transform.position));
		bodyDef.rotation = b2MakeRot(math::degToRad(transform.rotation));
		bodyDef.motionLocks.angularZ = def.constrainAngle;
		bodyDef.gravityScale = def.gravityScale;
		bodyDef.linearDamping = def.linearDamping;
		bodyDef.angularDamping = def.angularDamping;
		bodyDef.userData = def.actor;

		// Create body
		_bodyId = b2CreateBody(physics._worldId, &bodyDef);

		// Set shape definition
		b2ShapeDef shapeDef = b2DefaultShapeDef();
		shapeDef.material.friction = def.friction;
		shapeDef.material.restitution = def.restitution;
		shapeDef.density = def.density;
		shapeDef.isSensor = def.isSensor;

		if (def.isSensor) shapeDef.enableSensorEvents = true;
		else shapeDef.enableContactEvents = true;

		// Create shape
		b2Vec2 hsize = to_b2(Physics::PixelToWorld(size * transform.scale * 0.5f));
		switch (def.shape) {
		case Shape::Box: {
			b2Polygon box = b2MakeBox(hsize.x, hsize.y);
			b2CreatePolygonShape(_bodyId, &shapeDef, &box);
		}
		break;

		case Shape::Capsule: {
			b2Capsule capsule{ b2Vec2{ 0, hsize.y - hsize.x }, b2Vec2{ 0, -(hsize.y - hsize.x) }, hsize.x };
			b2CreateCapsuleShape(_bodyId, &shapeDef, &capsule);
		}
		break;

		case Shape::Circle: {
			b2Circle circle{ b2Vec2{ 0, 0 }, hsize.x };
			b2CreateCircleShape(_bodyId, &shapeDef, &circle);
		}
		break;

		default:
			break;
		}
	}

	PhysicsBody::~PhysicsBody() {
		
		b2DestroyBody(_bodyId);
	}

	vec2 PhysicsBody::GetPosition() {
		return Physics::WorldToPixel(to_vec2(b2Body_GetPosition(_bodyId)));
	}

	float PhysicsBody::GetAngle() {
		return b2Rot_GetAngle(b2Body_GetRotation(_bodyId));
	}

	void PhysicsBody::ApplyForce(const vec2& force) {
		b2Body_ApplyForceToCenter(_bodyId, to_b2(Physics::PixelToWorld(force)), true);
	}

	void PhysicsBody::ApplyTorque(float radians) {
		b2Body_ApplyTorque(_bodyId, radians, true);
	}
	void PhysicsBody::SetVelocity(const vec2& velocity) {
		b2Body_SetLinearVelocity(_bodyId, to_b2(Physics::PixelToWorld(velocity)));
	}

	vec2 PhysicsBody::GetVelocity() {
		return Physics::WorldToPixel(to_vec2(b2Body_GetLinearVelocity(_bodyId)));
	}
}