#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP
#include <glm/glm.hpp>
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class MovementSystem
 * @brief Updates entities' positions by integrating forces, velocity, and acceleration.
 * 
 * Requires entities to have both RigidBodyComponent and TransformComponent.
 * Supports dynamic entities with physics integration and non-dynamic entities with direct velocity-based movement.
 */
class MovementSystem : public System{
    public:
    /**
     * @brief Constructs MovementSystem and sets required components.
     */
     MovementSystem(){
        RequireComponent<RigidBodyComponent>();
        RequireComponent<TransformComponent>();

     }
    /**
     * @brief Updates all entities in the system, integrating movement over time.
     * 
     * @param dt Delta time in seconds since the last update.
     */
    void Update(double dt) {
        for(auto entity : GetSystemEntities()){
            auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
            auto& transform = entity.GetComponent<TransformComponent>();

            // Store previous position before integration
            transform.previousPosition = transform.position;

            if (rigidbody.isDinamic) {
                // Integrate forces -> acceleration -> velocity -> position
                rigidbody.acceleration = rigidbody.sumForces * rigidbody.invMass;
                rigidbody.velocity += rigidbody.acceleration * static_cast<float>(dt);
                transform.position += rigidbody.velocity * static_cast<float>(dt);

                // Reset applied forces
                rigidbody.sumForces = glm::vec2(0); 
            } else {
                // Movement without force integration, only velocity (e.g., for moving platforms)
                transform.position.x += rigidbody.velocity.x * static_cast<float>(dt);
                transform.position.y += rigidbody.velocity.y * static_cast<float>(dt);            
            }
        }
    }
};

#endif