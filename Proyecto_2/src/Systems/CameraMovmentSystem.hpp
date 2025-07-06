#ifndef CAMERAMOVEMENTSYSTEM_HPP
#define CAMERAMOVEMENTSYSTEM_HPP

#include <SDL2/SDL.h>
#include "../Components/CameraFollowComponent.hpp"
#include"../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"

/**
 * @class CameraMovementSystem
 * @brief System that moves the camera to follow entities with CameraFollowComponent and TransformComponent.
 * 
 * The camera position is updated based on the entity's position, with constraints to keep the camera within the map boundaries.
 */
class CameraMovmentSystem : public System {
    public:
    /**
     * @brief Constructs the CameraMovementSystem and sets required components.
     * 
     * Requires CameraFollowComponent and TransformComponent.
     */
    CameraMovmentSystem(){
        RequireComponent<CameraFollowComponent>();
        RequireComponent<TransformComponent>();
    }
    /**
     * @brief Updates the camera position to follow the entity.
     * 
     * @param camera Reference to the SDL_Rect representing the camera viewport.
     * 
     * The camera will center on the entity's position but will not move beyond the map boundaries.
     * A vertical offset is applied to slightly adjust the camera height.
     */
    void Update(SDL_Rect& camera) {
    const int offsetY = 100; 

    for (auto entity : GetSystemEntities()) {
        const auto& transform = entity.GetComponent<TransformComponent>();


        if (transform.position.x + (camera.w / 2) < static_cast<float>(Game::GetInstance().mapWidth)) {
            camera.x = static_cast<int>(transform.position.x) - (camera.w / 2);
        }


        if (transform.position.y + (camera.h / 2) < static_cast<float>(Game::GetInstance().mapHeight)) {
            camera.y = static_cast<int>(transform.position.y) - (camera.h / 2) - offsetY;
        }

        camera.x = camera.x < 0 ? 0 : camera.x;
        camera.y = camera.y < 0 ? 0 : camera.y;
    }
}
};
#endif