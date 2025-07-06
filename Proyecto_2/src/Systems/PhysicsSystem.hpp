#ifndef PHYSICSYSTEM_HPP
#define PHYSICSYSTEM_HPP
#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"
/**
 * @class PhysicsSystem
 * @brief Applies physics-related forces to entities with a RigidBodyComponent.
 * 
 * Currently, it applies gravity to dynamic rigid bodies.
 */
class PhysicsSystem : public System {
public:
    /**
     * @brief Constructs PhysicsSystem and requires RigidBodyComponent.
     */
    PhysicsSystem() {
        RequireComponent<RigidBodyComponent>();
    }
    /**
     * @brief Updates all dynamic rigid bodies by applying physics forces.
     * 
     * Adds gravity force to the sum of forces acting on the rigid body.
     */
    void Update() {
        for (auto entity : GetSystemEntities()) {
            auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

            if (rigidbody.isDinamic) {
                rigidbody.sumForces += glm::vec2(0.0f, 9.8 * rigidbody.mass * 64); // TODO: revisar multiplicador de gravedad
            }
        }
    }
};



#endif