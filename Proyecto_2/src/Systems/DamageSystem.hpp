#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <iostream>
#include <memory>

#include "../Components/CircleColliderComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

class DamageSystem : public System {
 public:
  DamageSystem(){
    RequireComponent<CircleColliderComponent>();
  }

  void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager){
    eventManager->SubscribeToEvent<CollisionEvent, DamageSystem>(this,
    &DamageSystem::OnCollision);
  }

  void OnCollision(CollisionEvent& e){
    std::cout<< "[DamageSystem] Colison de la entidad " << e.a.GetId()
    << " y " << e.b.GetId() << std::endl;

    e.a.Kill();
    e.b.Kill();
  }
};
#endif