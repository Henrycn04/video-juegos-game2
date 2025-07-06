#ifndef BOXCOLLISIONSYSTEM_HPP
#define BOXCOLLISIONSYSTEM_HPP

#include <iostream>
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Events/CollisionEvent.hpp"
#include "../EventManager/EventManager.hpp"

/**
 * @class BoxCollisionSystem
 * @brief System to detect and handle collisions between entities using BoxColliderComponent and TransformComponent.
 * 
 * This system checks for AABB collisions among entities and emits CollisionEvents when collisions occur.
 * It also invokes the onCollision script callback for involved entities if available.
 */
class BoxCollisionSystem : public System {
 private:
     /**
     * @brief Checks if two AABBs collide.
     * 
     * @param aX X position of first box.
     * @param aY Y position of first box.
     * @param aW Width of first box.
     * @param aH Height of first box.
     * @param bX X position of second box.
     * @param bY Y position of second box.
     * @param bW Width of second box.
     * @param bH Height of second box.
     * @return true if boxes collide, false otherwise.
     */
 bool CheckAABBCollision(float aX, float aY, float aW, float aH,
 float bX, float bY, float bW, float bH){
    return(
        aX < bX + bW &&
        aX + aW > bX &&
        aY < bY + bH &&
        aY + aH > bY
    );
 }
 public:
    /**
     * @brief Constructs the BoxCollisionSystem and sets required components.
     * 
     * Requires BoxColliderComponent and TransformComponent on entities.
     */
  BoxCollisionSystem(){
    RequireComponent<BoxColliderComponent>();
    RequireComponent<TransformComponent>();
  }
    /**
     * @brief Updates the system, checking for collisions between entities and handling collision events.
     * 
     * @param eventManager Shared pointer to the EventManager to emit collision events.
     * @param lua Reference to the Lua state used for calling onCollision script functions.
     */
void Update(const std::unique_ptr<EventManager>& eventManager, sol::state& lua) {
    auto entities = GetSystemEntities();

for(auto i = entities.begin(); i != entities.end(); i++){
    Entity a = *i;
    const auto& aCollider = a.GetComponent<BoxColliderComponent>();
    const auto& aTransform = a.GetComponent<TransformComponent>();

    for(auto j = i; j != entities.end(); j++){
        Entity b = *j;

        if(a == b){
            continue;
        }
        const auto& bCollider = b.GetComponent<BoxColliderComponent>();
        const auto& bTransform = b.GetComponent<TransformComponent>();

        float aWidth = static_cast<float>(aCollider.width) * aTransform.scale.x;
        float aHeight = static_cast<float>(aCollider.height) * aTransform.scale.y;
        float bWidth = static_cast<float>(bCollider.width) * bTransform.scale.x;
        float bHeight = static_cast<float>(bCollider.height) * bTransform.scale.y;

        bool collision = CheckAABBCollision(
            aTransform.position.x,
            aTransform.position.y,
            aWidth,
            aHeight,
            bTransform.position.x,
            bTransform.position.y,
            bWidth,
            bHeight
        );
            if(collision){
                eventManager->EmitEvent<CollisionEvent>(a, b);
                if(a.HasComponent<ScriptComponent>()){
                    const auto& script = a.GetComponent<ScriptComponent>();
                    if(script.onCollision != sol::nil){
                        lua["this"] = a;
                        script.onCollision(b);
                    }
                }
                 if(b.HasComponent<ScriptComponent>()){
                    const auto& script = b.GetComponent<ScriptComponent>();
                    if(script.onCollision != sol::nil){
                        lua["this"] = b;
                        script.onCollision(a);
                    }
                }
            }
        }
    }
  }
};

#endif