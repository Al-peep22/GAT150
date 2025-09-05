#include "../GamePCH.h"
#include "PlatformerGame.h"

bool PlatformerGame::Initialize() {
    OBSERVER_ADD(player_dead);
    OBSERVER_ADD(add_points);

    _scene = std::make_unique<viper::Scene>(this);
    _scene->Load("scenes/prototypes.json");
    _scene->Load("scenes/level.json");
    return false;
}

void PlatformerGame::Update(float dt) {
    switch (_gameState) {

    case GameState::Initialize:
        _gameState = GameState::StartLevel;
        break;

    case GameState::Title:
        break;

    case GameState::StartGame:
        break;

    case GameState::StartLevel:
        SpawnPlayer();
        SpawnEnemy();
        _gameState = GameState::Game;
        break;

    case GameState::Game:
        break;

    case GameState::PlayerDead:
        break;

    case GameState::GameOver:
        break;

    default:
        break;
    }

    _scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void PlatformerGame::Draw(class viper::Renderer& renderer) {
    _scene->Draw(renderer);

    viper::GetEngine().GetParticleSystem().Draw(renderer);
}

void PlatformerGame::OnPlayerDeath() {

}

void PlatformerGame::OnNotify(const viper::Event& event) {

}

void PlatformerGame::Shutdown() {

}

void PlatformerGame::SpawnEnemy() {
    auto enemy = viper::Instantiate("enemy");
    _scene->AddActor(std::move(enemy));

    auto bat = viper::Instantiate("bat");
    _scene->AddActor(std::move(bat));
}

void PlatformerGame::SpawnPlayer() {
    auto player = viper::Instantiate("player");
    //player->transform.position = viper::vec2{ viper::random::getReal(0.0f, 1080.0f), viper::random::getReal(0.0f, 100.0f) };
    _scene->AddActor(std::move(player));
}