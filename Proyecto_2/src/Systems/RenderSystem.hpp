#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "../AssetManager/AssetManager.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class RenderSystem
 * @brief System responsible for rendering entities with SpriteComponent and TransformComponent.
 * 
 * This system draws textured sprites on the screen, applying transformations such as scaling, rotation, and flipping.
 */
class RenderSystem : public System {
  public:
    /**
     * @brief Constructs the RenderSystem and sets required components.
     * 
     * Requires entities to have both SpriteComponent and TransformComponent.
     */
   RenderSystem(){
    RequireComponent<SpriteComponent>();
    RequireComponent<TransformComponent>();
   }
    /**
     * @brief Renders all entities managed by this system.
     * 
     * @param renderer Pointer to the SDL_Renderer used for drawing.
     * @param camera SDL_Rect representing the current camera view to offset rendering.
     * @param AssetManager Unique pointer to the AssetManager to retrieve textures.
     */
   void Update(SDL_Renderer* renderer, SDL_Rect& camera
   , const std::unique_ptr<AssetManager>& AssetManager){
    for(auto entity : GetSystemEntities() ){
        const auto sprite = entity.GetComponent<SpriteComponent>();
        const auto transform = entity.GetComponent<TransformComponent>();

        SDL_Rect srcRect = sprite.srcRect;
        SDL_Rect dstRect = {
            static_cast<int>(transform.position.x - camera.x),
            static_cast<int>(transform.position.y - camera.y),
            static_cast<int>(sprite.width * transform.scale.x),
            static_cast<int>(sprite.height * transform.scale.y),
        };
        SDL_RenderCopyEx(
            renderer,
            AssetManager->GetTexture(sprite.textureId),
            &srcRect,
            &dstRect,
            transform.rotation,
            NULL,
            (sprite.flip) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
        );
      }
  }



};




#endif