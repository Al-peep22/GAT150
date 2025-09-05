#include "Rocket.h"

#include "../GamePCH.h"
#include "Engine.h"
#include "Player.h"

FACTORY_REGISTER(Rocket)

void Rocket::Update(float dt) {
    viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation)) * speed;

    auto* rb = owner->GetComponent<viper::RigidBody>();
    if (rb) {
        rb->SetVelocity(force);
    }

    owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    float angle = owner->transform.rotation + viper::random::getReal(-30.0f, 30.0f);
    viper::vec2 velocity = viper::vec2{ 1,0 }.Rotate(viper::math::degToRad(angle));
    velocity *= viper::random::getReal(80.0f, 150.0f);

    viper::Particle particle;

    particle.position = owner->transform.position + viper::vec2{ -50, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation));
    particle.velocity = viper::vec2{ viper::random::getReal(-80.0f, -30.0f), 0 }.Rotate(viper::math::degToRad(owner->transform.rotation + viper::random::getReal(-90.0f, 90.0f)));
    particle.color = (owner->tag == "enemy") ? viper::vec3{ 1, 0, 0 } : viper::vec3{ 0, 1, 0 };
    particle.lifespan = 0.5f;
    viper::GetEngine().GetParticleSystem().AddParticle(particle);
}

void Rocket::OnCollision(viper::Actor* other) {
    if (owner->tag != other->tag) {
        owner->destroyed = true;

        /*auto sound = viper::Resources().Get<viper::AudioClip>("audio/explosion.wav", viper::GetEngine().GetAudio()).get();
        if (sound) {
            viper::GetEngine().GetAudio().PlaySound(*sound);
        }*/
    }
}

void Rocket::Read(const viper::json::value_t& value) {
    Object::Read(value);

    JSON_READ(value, speed);
}
