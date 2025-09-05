#include "Player.h"

#include "../GamePCH.h"
#include "Rocket.h"
#include "SpaceGame.h"

FACTORY_REGISTER(Player)

void Player::Start() {
    _rigidBody = owner->GetComponent<viper::RigidBody>();
}

void Player::Update(float dt) { //dt = Delta Time
    //if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_W)) viper::GetEngine().GetAudio().PlaySound("unsc-engine");

    // Engine particle
	viper::Particle particle;

    particle.position = owner->transform.position + viper::vec2{ -50, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation));
    particle.velocity = viper::vec2{ viper::random::getReal(-80.0f, -30.0f), 0 }.Rotate(viper::math::degToRad(owner->transform.rotation + viper::random::getReal(-90.0f, 90.0f)));
	particle.color = viper::vec3{ 1.0f, 1.0f, 1.0f };
	particle.lifespan = 0.5f;
    viper::GetEngine().GetParticleSystem().AddParticle(particle);
    
    // Rotation
    float rotate = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;
    _rigidBody->ApplyTorque(rotate * rotationRate);

    // Thrust
    float thrust = 0;

    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    viper::vec2 direction{ 1, 0 };
    viper::vec2 force = direction.Rotate(viper::math::degToRad(owner->transform.rotation)) * thrust * speed;
    _rigidBody->ApplyForce(force);

    owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    
    // check fire key pressed
    // spawn rocket with staying to the players position
    fireTimer -= dt;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_E) && fireTimer <= 0) {
        fireTimer = fireTime;
        viper::Transform transform{ owner->transform.position, owner->transform.rotation, 0.75 };

        auto rocket = viper::Instantiate("player-rocket", transform);
        owner->scene->AddActor(std::move(rocket));
    }
}

void Player::OnCollision(viper::Actor* other) {
    if (owner->tag != other->tag) {
        owner->destroyed = true;
        EVENT_NOTIFY(player_dead);
		//dynamic_cast<SpaceGame*>(owner->scene->GetGame())->OnPlayerDeath();
        
        /*auto sound = viper::Resources().Get<viper::AudioClip>("audio/explosion.wav", viper::GetEngine().GetAudio()).get();
        if (sound) {
            viper::GetEngine().GetAudio().PlaySound(*sound);
        }*/
    }
}

void Player::Read(const viper::json::value_t& value) {
    Object::Read(value);

    JSON_READ(value, speed);
    JSON_READ(value, rotationRate);
    JSON_READ(value, fireTime);
}
