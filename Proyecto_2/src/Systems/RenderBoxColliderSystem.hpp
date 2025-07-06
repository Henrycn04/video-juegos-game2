#ifndef RENDERBOXCOLLIDERSYSTEM_HPP
#define RENDERBOXCOLLIDERSYSTEM_HPP

#include <SDL2/SDL.h>
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class RenderBoxColliderSystem
 * @brief System responsible for rendering the bounding boxes of entities with BoxCollider and Transform components.
 * 
 * This system draws red rectangles representing the box colliders adjusted by the camera position and entity scale.
 */
class RenderBoxColliderSystem : public System {
    public:
    /**
     * @brief Constructs the RenderBoxColliderSystem and requires BoxColliderComponent and TransformComponent.
     */
    RenderBoxColliderSystem(){
        RequireComponent<BoxColliderComponent>();
        RequireComponent<TransformComponent>();
    }
    /**
     * @brief Renders the box collider rectangles for all entities in the system.
     * 
     * @param renderer SDL_Renderer pointer used to draw rectangles.
     * @param camera SDL_Rect representing the current camera view for offsetting positions.
     */
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