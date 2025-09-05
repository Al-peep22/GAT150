#include "Enemy.h"

#include "../GamePCH.h"
#include "Player.h"
#include "Rocket.h"
#include "GameData.h"

FACTORY_REGISTER(Enemy)

void Enemy::Start() {
    OBSERVER_ADD(player_dead);

    _rigidBody = owner->GetComponent<viper::RigidBody>();
    fireTimer = fireTime;
}

void Enemy::Update(float dt){
    // Particals to the engine
    viper::Particle particle;

    particle.position = owner->transform.position + viper::vec2{ -50, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation));
    particle.velocity = viper::vec2{ viper::random::getReal(-80.0f, -30.0f), 0 }.Rotate(viper::math::degToRad(owner->transform.rotation + viper::random::getReal(-90.0f, 90.0f)));
    particle.color = viper::vec3{ 1.0f, 1.0f, 1.0f };
    particle.lifespan = 0.5f;
    viper::GetEngine().GetParticleSystem().AddParticle(particle);

    bool playerSeen = false;

    viper::Actor* player = owner->scene->GetActorByName<viper::Actor>("player");
    if (player) {
        viper::vec2 direction{ 1, 0 };
        direction = player->transform.position - owner->transform.position;
        direction = direction.Normalized();

        viper::vec2 forward = viper::vec2{ 1,0 }.Rotate(viper::math::degToRad(owner->transform.rotation));
        float angle = viper::math::radToDeg(viper::vec2::AngleBetween(forward, direction));

        playerSeen = angle <= 30;

        if (playerSeen) {
            float angle = viper::vec2::SignedAngleBetween(forward, direction);
            angle = viper::math::sign(angle);
            _rigidBody->ApplyTorque(angle * 5);

            //owner->transform.rotation += viper::math::radToDeg(angle * 5 * dt);
        }
        
    }

    viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation)) * speed;
    _rigidBody->ApplyForce(force);

    owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    
    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireTime;
        viper::Transform transform{ owner->transform.position, owner->transform.rotation, 0.75 };

        auto rocket = viper::Instantiate("enemy-rocket", transform);
        owner->scene->AddActor(std::move(rocket));

        
    }
}

void Enemy::OnCollision(viper::Actor* other) {
    if (owner->tag != other->tag) {
        owner->destroyed = true;
        EVENT_NOTIFY_DATA(add_points, 100);

        for (int i = 0; i < 100; i++) {
            viper::Particle particle;
            particle.position = owner->transform.position;
			particle.velocity = viper::random::onUnitCircle() * viper::random::getReal(10.0f, 200.0f);
            particle.color = viper::vec3{ 1, 1, 1 };
            particle.lifespan = 2;
            viper::GetEngine().GetParticleSystem().AddParticle(particle);
        }

        auto sound = viper::Resources().Get<viper::AudioClip>("audio/explosion.wav", viper::GetEngine().GetAudio()).get();
        if (sound) {
            viper::GetEngine().GetAudio().PlaySound(*sound);
        }
    }
}

void Enemy::OnNotify(const viper::Event& event) {
    if (viper::equalsIqnoreCase(event.id, "player_dead")) {
        owner->destroyed = true;
    }
}

void Enemy::Read(const viper::json::value_t& value) {
    Object::Read(value);

    JSON_READ(value, speed);
    JSON_READ(value, fireTime);
    JSON_READ(value, fireTimer);
}