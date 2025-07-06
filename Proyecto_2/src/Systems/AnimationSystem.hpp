#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include <SDL2/SDL.h>

#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class AnimationSystem
 * @brief System that updates animation frames for all entities that have both AnimationComponent and SpriteComponent.
 * 
 * This system calculates the current animation frame based on elapsed time and updates the sprite's source rectangle accordingly.
 */
class AnimationSystem : public System{
  public:
    /**
     * @brief Constructs the AnimationSystem and sets the required components.
     * 
     * Requires both AnimationComponent and SpriteComponent to function.
     */
   AnimationSystem() {
    RequireComponent<AnimationComponent>();
    RequireComponent<SpriteComponent>();
   }

void Update(){
    /**
     * @brief Updates the animation frames for all relevant entities.
     * 
     * Calculates the elapsed time since the animation started and updates the current frame based on the frame speed.
     * Then, it adjusts the sprite's source rectangle (`srcRect.x`) to show the correct frame.
     */
    Uint32 currentTime = SDL_GetTicks();
    
    for(auto entity : GetSystemEntities()){
        auto& animation = entity.GetComponent<AnimationComponent>();
        auto& sprite = entity.GetComponent<SpriteComponent>();
        
        // Verificar que startTime esté inicializado
        if(animation.startTime == 0) {
            animation.startTime = currentTime;
        }
        
        // Calcular elapsed time en segundos (más preciso)
        float elapsedSeconds = (currentTime - animation.startTime) / 1000.0f;
        
        // Calcular el frame actual de forma más segura
        int calculatedFrame = static_cast<int>(elapsedSeconds * animation.frameSpeedRate);
        animation.currentFrame = calculatedFrame % animation.numFrames;
        
        // Actualizar srcRect
        sprite.srcRect.x = animation.currentFrame * sprite.width;
        
    }
}
};
#endif