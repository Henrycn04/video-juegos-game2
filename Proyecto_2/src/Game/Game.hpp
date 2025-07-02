#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <memory>
#include <sol/sol.hpp>
#include "../AnimationManager/AnimationManager.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "../ECS/ECS.hpp"
#include "../SceneManager/SceneManager.hpp"

const int FPS = 30;
const int MILISECS_PER_FRAME = 1000 / FPS;

class Game {
private:
    SDL_Window* window = nullptr;

    SDL_Rect camera = {0, 0, 0, 0};
    
    int milisecsPreviousFrame = 0;

    bool isRunning = false;
    bool isDebugMode = false;
    bool isPaused = false;///< Flag to check if the game is currently paused.
    bool wasPaused = false;///< Flag to check if the game was paused in the last frame.

public:
    SDL_Renderer* renderer = nullptr;

    std::unique_ptr<AnimationManager> animationManager;
    std::unique_ptr<AssetManager> assetManager;
    std::unique_ptr<EventManager> eventManager;
    std::unique_ptr<ControllerManager> controllerManager;
    std::unique_ptr<Registry> registry;
    std::unique_ptr<SceneManager> sceneManager;
    sol::state lua;

    int windowWidth = 0;
    int windowHeight = 0;

    int mapWidth = 0;
    int mapHeight = 0;


private:
    void Setup();
    void RunScene();
    void ProcessInput();
    void Update();
    void Render();

     Game();
    ~Game();

public: 
    static Game& GetInstance();

    void Init();
    void Run();
    void Destroy();
};
#endif