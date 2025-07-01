#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include <SDL2/SDL.h>

#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../ECS/ECS.hpp"

class AnimationSystem : public System{
  public:
   AnimationSystem() {
    RequireComponent<AnimationComponent>();
    RequireComponent<SpriteComponent>();
   }

void Update(){
    // Obtener el tiempo actual una vez para toda la iteración
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