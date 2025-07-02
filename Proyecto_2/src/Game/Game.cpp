#include "Game.hpp"

#include <iostream>

#include "../Events/ClickEvent.hpp"

#include "../Systems/CircleCollisionSystem.hpp"
#include "../Systems/BoxCollisionSystem.hpp"
#include "../Systems/AnimationSystem.hpp"
//#include "../Systems/DamageSystem.hpp"
#include "../Systems/RenderSystem.hpp"
#include "../Systems/RenderBoxColliderSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/RenderTextSystem.hpp"
#include "../Systems/ScriptSystem.hpp"
#include "../Systems/UISystem.hpp"
#include "../Systems/CameraMovmentSystem.hpp"
#include "../Systems/PhysicsSystem.hpp"
#include "../Systems/OverlapSystem.hpp"
#include "../Systems/SceneTimeSystem.hpp"

Game::Game(){
    std::cout<< "[Game] Se ejecuta constructor" << std::endl;
    assetManager = std::make_unique<AssetManager>();
    controllerManager = std::make_unique<ControllerManager>();
    eventManager = std::make_unique<EventManager>();
    registry = std::make_unique<Registry>();
    sceneManager = std::make_unique<SceneManager>();
    animationManager = std::make_unique<AnimationManager>();
}

Game::~Game(){
    animationManager.reset();
    assetManager.reset();
    controllerManager.reset();
    eventManager.reset();
    registry.reset();
    sceneManager.reset();

    std::cout<< "[Game] Se ejecuta destructor" << std::endl;
}

Game& Game::GetInstance(){
    static Game game;
    return game;
}

void Game::Init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "[GAME] Error al inciializar SDL" << std::endl;
        return;
    }
    if(TTF_Init() != 0){
        std::cout << "[GAME] Error al inciializar SDL_ttf" << std::endl;
        return;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "[GAME] Error al inicializar SDL_mixer: " 
        << Mix_GetError() << std::endl;
        return;
    }
    int flags = MIX_INIT_MP3;  
    int initted = Mix_Init(flags);
    if ((initted & flags) != flags) {
        std::cout << "[GAME] No se pudo inicializar SDL_mixer con soporte MP3: " << Mix_GetError() << std::endl;
        return;
    }

    windowWidth = 800;
    windowHeight = 600;


  window = SDL_CreateWindow(
        "Motor de juegos 2D",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth, 
        windowHeight, 
        SDL_WINDOW_RESIZABLE
    );

    if(!window){
        std::cout << "[GAME] Error al crear ventana" << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(renderer, 800, 600);

    if(!renderer){
        std::cout << "[GAME] Error al crear renderer" << std::endl;
        return;
    }

    camera.x = 0;
    camera.y = 0;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    camera.w = windowWidth;
    camera.h = windowHeight;

    isRunning = true;
}

void Game:: Setup(){
    //registry->AddSystem<DamageSystem>();
    registry->AddSystem<AnimationSystem>();
    registry->AddSystem<CircleCollisionSystem>();
    registry->AddSystem<BoxCollisionSystem>();
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();
    registry->AddSystem<RenderBoxColliderSystem>();
    registry->AddSystem<ScriptSystem>();
    registry->AddSystem<RenderTextSystem>();
    registry->AddSystem<UISystem>();
    registry->AddSystem<CameraMovmentSystem>();
    registry->AddSystem<PhysicsSystem>();
    registry->AddSystem<OverlapSystem>();
        registry->AddSystem<SceneTimeSystem>();

    sceneManager->LoadSceneFromScript("./assets/scripts/scenes.lua", lua);

    lua.open_libraries(sol::lib::base, sol::lib::math);
    registry->GetSystem<ScriptSystem>().CreateLuaBinding(lua);

}

void Game::ProcessInput(){
    SDL_Event sdlEvent;
    while(SDL_PollEvent(&sdlEvent)){
        switch(sdlEvent.type){
            case SDL_QUIT:
              sceneManager->StopScene();
              isRunning = false;
              break;
            case SDL_KEYDOWN:
              if(sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                sceneManager->StopScene();
                isRunning = false;
                break;
              }else if (sdlEvent.key.keysym.sym == SDLK_p) {
                isPaused = !isPaused;
                std::cout << "[GAME] Pausa: " << (isPaused ? "Activada" : "Desactivada") << std::endl;
                 if (isPaused) {
                        wasPaused = true;
                    } 
                if(isPaused){
                    registry->GetSystem<SceneTimeSystem>().Pause();
                    assetManager->PauseMusic();
                    }
                else{
                    registry->GetSystem<SceneTimeSystem>().Resume();
                    assetManager->ResumeMusic();
                }
                break;
            }
              if(sdlEvent.key.keysym.sym == SDLK_i){
                isDebugMode = !isDebugMode;
                break;
              }
              controllerManager-> KeyDown(sdlEvent.key.keysym.sym);
              break;
            case SDL_KEYUP:
              controllerManager-> KeyUp(sdlEvent.key.keysym.sym);
              break;
            case SDL_MOUSEMOTION:
                int x, y;
                SDL_GetMouseState(&x, &y);
                controllerManager->SetMousePosition(x,y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                controllerManager->SetMousePosition(sdlEvent.button.x
                , sdlEvent.button.y);
                controllerManager->MouseButtonDown(static_cast<int>(sdlEvent.button.button));
                eventManager->EmitEvent<ClickEvent>(static_cast<int>(sdlEvent.button.button)
                , sdlEvent.button.x , sdlEvent.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
                controllerManager->SetMousePosition(sdlEvent.button.x
                , sdlEvent.button.y);
                controllerManager->MouseButtonUp(static_cast<int>(sdlEvent.button.button));
                break;
            default:
                break;

        }
    }

}

void Game::Update(){
    if (isPaused) {
        return;  
    }
    if (wasPaused) {
        milisecsPreviousFrame = SDL_GetTicks(); 
        wasPaused = false;  
    }
    int timeToWait = MILISECS_PER_FRAME - (SDL_GetTicks() - milisecsPreviousFrame);
    if(0 < timeToWait && timeToWait <= MILISECS_PER_FRAME){
        SDL_Delay(timeToWait);
    }

    double deltaTime = (SDL_GetTicks()- milisecsPreviousFrame) / 1000.0;
    // TODO: agregar esta variable al estado de LUA

    milisecsPreviousFrame = SDL_GetTicks();

    // Reiniciar las subscripciones
    eventManager->Reset();
    //registry->GetSystem<DamageSystem>().SubscribeToCollisionEvent(eventManager);
    registry->GetSystem<OverlapSystem>().SubscribeToCollisionEvents(eventManager);
    registry->GetSystem<UISystem>().SubscribeToClickEvent(eventManager);
    
    registry->Update();
    
    registry->GetSystem<SceneTimeSystem>().Update();
    registry->GetSystem<ScriptSystem>().Update(lua);

    registry->GetSystem<PhysicsSystem>().Update();
    registry->GetSystem<MovementSystem>().Update(deltaTime);
    registry->GetSystem<BoxCollisionSystem>().Update(eventManager, lua);
    registry->GetSystem<CircleCollisionSystem>().Update(eventManager);

    registry->GetSystem<AnimationSystem>().Update();
    registry->GetSystem<CameraMovmentSystem>().Update(camera);

}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 31, 31, 31, 255);
    SDL_RenderClear(renderer);

    registry->GetSystem<RenderSystem>().Update(renderer, camera, assetManager);
    registry->GetSystem<RenderTextSystem>().Update(renderer, assetManager, camera);
    if(isDebugMode){

     registry->GetSystem<RenderBoxColliderSystem>().Update(renderer, camera);}
      if(isPaused){
            registry->GetSystem<RenderTextSystem>().RenderFixedText(renderer,
                                     assetManager->GetFont("press_start_24"),
                                     "Press P to continue",
                                     SDL_Color{255,255,255,255},
                                     5, 550, 1.0f, 1.0f);
    }

    SDL_RenderPresent(renderer);
}

void Game::RunScene(){
    sceneManager->LoadScene();

    while(sceneManager->IsSceneRunning()){
        ProcessInput();
        Update();
        Render();
    }

    assetManager->ClearAssets();
    registry->ClearAllEntities();
}

void Game::Run(){
    Setup();
    while (isRunning){
        sceneManager->StartScene();
        RunScene();
    }
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
     assetManager->ClearMusic(); 
    TTF_Quit();
    SDL_Quit();
}




