#include "Game/SpaceGame.h"
#include "Platformer/PlatformerGame.h"

int main(int argc, char* argv[]) {
    viper::file::SetCurrentDirectory("Assets/Platformer");
    viper::Logger::Info("Current directory {}", viper::file::GetCurrentDirectory());
    
    // Initialize Engine Systems
    viper::GetEngine().Initialize();
    viper::Logger::Info("Initializing Engine");

    // Initialize Game
    //std::unique_ptr<viper::Game> game = std::make_unique<SpaceGame>();
    std::unique_ptr<viper::Game> game = std::make_unique<PlatformerGame>();
    game->Initialize();
    viper::Logger::Info("Initializing Game");

    SDL_Event e;
    bool quit = false;

    float rotate = 0;

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // Update Engine Systems
        viper::GetEngine().Update();
        game->Update(viper::GetEngine().GetTime().GetDeltaTime());
        
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        // Draw
        viper::vec3 color{ 0, 0, 0 };

        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear(); // Clear the screen with black

        game->Draw(viper::GetEngine().GetRenderer());

        viper::GetEngine().GetRenderer().Present();
    }

    game->Shutdown();
    game.release();
    viper::GetEngine().Shutdown();
    viper::Logger::Info("Shuting down Game and Engine");

    return 0;
}