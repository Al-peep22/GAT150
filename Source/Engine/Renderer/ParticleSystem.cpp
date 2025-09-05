#include "ParticleSystem.h"

#include "Renderer.h"

namespace viper {
    bool ParticleSystem::Initialize(int poolSize) {
		_particles.resize(poolSize); // Reserve space for 1000 particles

        return true;
    }

    void ParticleSystem::ShutDown() {
		_particles.clear(); // Clear the particle vector
    }

    void ParticleSystem::Update(float dt) {
        for (auto& particle : _particles) {
            if (particle.active) {
				particle.lifespan -= dt;
				particle.active = particle.lifespan > 0;
				particle.position += particle.velocity * dt;
            }
        }

    }

    void ParticleSystem::Draw(Renderer& renderer) {
        for (auto& particle : _particles) {
            if (particle.active) {
				renderer.SetColor(particle.color.r, particle.color.g, particle.color.b);
				renderer.DrawPoint(particle.position.x, particle.position.y);
            }
        }
    }

    void ParticleSystem::AddParticle(const Particle& particle) {
        Particle* freeParticle = GetFreeParticle();
        if (freeParticle) {
			*freeParticle = particle; // Copy the particle data
			freeParticle->active = true; // Set the particle as active
        }
    }

    Particle* ParticleSystem::GetFreeParticle() {
		for (auto& particle : _particles) {
            if (!particle.active) return &particle;
		}

        return nullptr;
    }
}