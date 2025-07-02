#ifndef BOXCOLLISIONSYSTEM_HPP
#define BOXCOLLISIONSYSTEM_HPP

#include <iostream>
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Events/CollisionEvent.hpp"
#include "../EventManager/EventManager.hpp"

class BoxCollisionSystem : public System {
 private:
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
  BoxCollisionSystem(){
    RequireComponent<BoxColliderComponent>();
    RequireComponent<TransformComponent>();
  }

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

        // Calcular ancho y alto con escala
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