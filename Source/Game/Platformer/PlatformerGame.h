#pragma once

#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

class PlatformerGame : public viper::Game, public viper::IObserver {
public:
	enum class GameState {
		Initialize,
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver
	};

public:
	PlatformerGame() = default;

	bool Initialize() override;

	void Update(float dt) override;

	void Draw(class viper::Renderer& renderer) override;

	void OnPlayerDeath();

	void OnNotify(const viper::Event& event) override;

	void Shutdown() override;

private:
	void SpawnEnemy();

	void SpawnPlayer();

	void SpawnRing();

private:
	GameState _gameState = GameState::Initialize;
	float _enemySpawnTimer{ 0 };
	float _stateTimer{ 0 };

	std::unique_ptr<viper::Text> _titleText;
	std::unique_ptr<viper::Text> _scoreText;
	std::unique_ptr<viper::Text> _livesText;
};