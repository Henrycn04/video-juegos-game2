#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP
#include <glm/glm.hpp>
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
            auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
            auto& transform = entity.GetComponent<TransformComponent>();

            transform.previousPosition = transform.position;
            if (rigidbody.isDinamic) {
                rigidbody.acceleration = rigidbody.sumForces * rigidbody.invMass;
                rigidbody.velocity += rigidbody.acceleration * static_cast<float>(dt);
                transform.position += rigidbody.velocity * static_cast<float>(dt);
                rigidbody.sumForces = glm::vec2(0); 
            } else {
                transform.position.x += rigidbody.velocity.x * dt;
                transform.position.y += rigidbody.velocity.y * dt;            
            }
            
        }
    }
};

#endif