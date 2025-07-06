#ifndef CIRCLECOLLISIONSYSTEM_HPP
#define CIRCLECOLLISIONSYSTEM_HPP

#include "../Components/CircleColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

#include <memory>
/**
 * @class CircleCollisionSystem
 * @brief System responsible for detecting and handling collisions between circular collider components.
 * 
 * This system iterates through entities with CircleColliderComponent and TransformComponent,
 * checking for circular collisions and emitting collision events when collisions occur.
 */
class CircleCollisionSystem : public System {
 public:
    /**
     * @brief Constructs the CircleCollisionSystem and sets required components.
     * 
     * Requires CircleColliderComponent and TransformComponent.
     */
  CircleCollisionSystem(){
    RequireComponent<CircleColliderComponent>();
    RequireComponent<TransformComponent>();
  }
    /**
     * @brief Updates the system by checking collisions between all entities with circular colliders.
     * 
     * @param eventManager Unique pointer to the EventManager used to emit collision events.
     */
  void Update(std::unique_ptr<EventManager>& eventManager) {
    auto entities = GetSystemEntities();

    for(auto i = entities.begin(); i != entities.end(); i++){
        Entity a = *i;
        auto aCollider = a.GetComponent<CircleColliderComponent>();
        auto aTransform = a.GetComponent<TransformComponent>();

        for(auto j = i; j != entities.end(); j++){
            Entity b = *j;

            if(a == b){
              continue;
            }
            auto bCollider = b.GetComponent<CircleColliderComponent>();
            auto bTransform = b.GetComponent<TransformComponent>();

            glm::vec2 aCenterPos = glm::vec2(
                aTransform.position.x - (aCollider.width / 2) * aTransform.scale.x,
                aTransform.position.y - (aCollider.height / 2) * aTransform.scale.y
            );

            glm::vec2 bCenterPos = glm::vec2(
                bTransform.position.x - (bCollider.width / 2) * bTransform.scale.x,
                bTransform.position.y - (bCollider.height / 2)* bTransform.scale.y
            );

            int aRadius = aCollider.radius * aTransform.scale.x;
            int bRadius = bCollider.radius * bTransform.scale.x;

            bool collision = CheckCircularCollision(aRadius, bRadius,
            aCenterPos, bCenterPos);
            if(collision){
             eventManager->EmitEvent<CollisionEvent>(a,b);
            }
        }
    }
  }
    /**
     * @brief Checks if two circles are colliding based on their radii and positions.
     * 
     * @param aRadius Radius of the first circle.
     * @param bRadius Radius of the second circle.
     * @param aPos Center position of the first circle.
     * @param bPos Center position of the second circle.
     * @return true if circles are colliding, false otherwise.
     */  
  bool CheckCircularCollision(int aRadius, int bRadius, glm::vec2 aPos
  , glm::vec2 bPos){
    glm::vec2 dif = aPos - bPos;
    double length = glm::sqrt((dif.x * dif.x) + (dif.y * dif.y));
    // Hay colision si la suma de los radios es mayor a la distancia
    // entre centros
    return (aRadius + bRadius) >= length;

 }
};
#endif