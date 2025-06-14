#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

class MovementSystem : public System{
    public:
     MovementSystem(){
        RequireComponent<RigidBodyComponent>();
        RequireComponent<TransformComponent>();

     }

    void Update(double dt) {
        for(auto entity : GetSystemEntities()){
            const auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
            auto& transform = entity.GetComponent<TransformComponent>();

            transform.previousPosition = transform.position;

            transform.position.x += rigidbody.velocity.x * dt;
            transform.position.y += rigidbody.velocity.y * dt;
        }
    }
};

#endif