#include "Physics.h"

namespace viper {
	float Physics::ms_pixelsPerUnit = 48.0f;

	bool Physics::Initialize() {
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = b2Vec2{ 0.0f, 10.0f };
		_worldId = b2CreateWorld(&worldDef);
	
		return true;
	}
	
	void Physics::Shutdown() {
		b2DestroyWorld(_worldId);
	}
	
	void Physics::Update(float dt) {
		b2World_Step(_worldId, 1.0f / 60.0f, 4);
		ProcessCollisionEvents();
	}

	void Physics::ProcessCollisionEvents() {
		b2ContactEvents contactEvents = b2World_GetContactEvents(_worldId);

		// Begin contact
		for (int i = 0; i < contactEvents.beginCount; i++) {
			b2ContactBeginTouchEvent* contactEvent = contactEvents.beginEvents + i;

			b2BodyId bodyA = b2Shape_GetBody(contactEvent->shapeIdA);
			b2BodyId bodyB = b2Shape_GetBody(contactEvent->shapeIdB);

			Actor* actorA = (Actor*)b2Body_GetUserData(bodyA);
			if (!actorA || actorA->destroyed || !actorA->active) continue;

			Actor* actorB = (Actor*)b2Body_GetUserData(bodyB);
			if (!actorB || actorB->destroyed || !actorB->active) continue;

			actorA->OnCollision(actorB);
			actorB->OnCollision(actorA);
		}

		// End contact
		for (int i = 0; i < contactEvents.endCount; i++) {
			b2ContactEndTouchEvent* contactEvent = contactEvents.endEvents + i;

			b2BodyId bodyA = b2Shape_GetBody(contactEvent->shapeIdA);
			b2BodyId bodyB = b2Shape_GetBody(contactEvent->shapeIdB);

			Actor* actorA = (Actor*)b2Body_GetUserData(bodyA);
			if (!actorA || actorA->destroyed || !actorA->active) continue;

			Actor* actorB = (Actor*)b2Body_GetUserData(bodyB);
			if (!actorB || actorB->destroyed || !actorB->active) continue;

			actorA->OnCollision(actorB);
			actorB->OnCollision(actorA);
		}

		// Sensor contact
		b2SensorEvents sensorEvents = b2World_GetSensorEvents(_worldId);
		for (int i = 0; i < sensorEvents.beginCount; i++) {
			b2SensorBeginTouchEvent* sensorEvent = sensorEvents.beginEvents + i;

			b2BodyId bodyA = b2Shape_GetBody(sensorEvent->sensorShapeId);
			b2BodyId bodyB = b2Shape_GetBody(sensorEvent->visitorShapeId);

			Actor* actorA = (Actor*)b2Body_GetUserData(bodyA);
			if (!actorA || actorA->destroyed || !actorA->active) continue;

			Actor* actorB = (Actor*)b2Body_GetUserData(bodyB);
			if (!actorB || actorB->destroyed || !actorB->active) continue;

			actorA->OnCollision(actorB);
			actorB->OnCollision(actorA);
		}
	}
}