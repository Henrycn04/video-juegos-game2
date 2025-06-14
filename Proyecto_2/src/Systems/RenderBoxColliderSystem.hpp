#ifndef RENDERBOXCOLLIDERSYSTEM_HPP
#define RENDERBOXCOLLIDERSYSTEM_HPP

#include <SDL2/SDL.h>
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

class RenderBoxColliderSystem : public System {
    public:
    RenderBoxColliderSystem(){
        RequireComponent<BoxColliderComponent>();
        RequireComponent<TransformComponent>();
    }

    void Update(SDL_Renderer* renderer, SDL_Rect& camera){
      for(auto entity: GetSystemEntities()){
        const auto& collider = entity.GetComponent<BoxColliderComponent>();
        const auto& transform = entity.GetComponent<TransformComponent>();

        SDL_Rect box = {
            static_cast<int>(transform.position.x - camera.x),
            static_cast<int>(transform.position.y - camera.y),
            static_cast<int>(collider.width * transform.scale.x),
            static_cast<int>(collider.height * transform.scale.y)

        };

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &box);
      }  
    }

};
#endif