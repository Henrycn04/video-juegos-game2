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
        
    }

};
#endif