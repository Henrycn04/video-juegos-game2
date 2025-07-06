#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <iostream>
#include <memory>

#include "../Components/CircleColliderComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"


/**
 * @class DamageSystem
 * @brief System that listens for collision events and applies damage by killing involved entities.
 * 
 * This system requires entities to have a CircleColliderComponent to be considered.
 */
class DamageSystem : public System {
 public:
  /**
   * @brief Constructs the DamageSystem and requires CircleColliderComponent.
   */
  DamageSystem(){
    RequireComponent<CircleColliderComponent>();
  }

    /**
   * @brief Subscribes this system to CollisionEvent in the provided EventManager.
   * 
   * @param eventManager Unique pointer to the EventManager to subscribe to.
   */
  void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager){
    eventManager->SubscribeToEvent<CollisionEvent, DamageSystem>(this,
    &DamageSystem::OnCollision);
  }


  /**
   * @brief Callback invoked when a CollisionEvent occurs.
   * 
   * @param e Reference to the CollisionEvent containing the two entities involved.
   * 
   * This method logs the collision and kills both involved entities.
   */
  void OnCollision(CollisionEvent& e){
    std::cout<< "[DamageSystem] Colison de la entidad " << e.a.GetId()
    << " y " << e.b.GetId() << std::endl;

    e.a.Kill();
    e.b.Kill();
  }
};
#endif