#ifndef PHYSICSYSTEM_HPP
#define PHYSICSYSTEM_HPP
#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"
class PhysicsSystem : public System {
public:
    PhysicsSystem() {
        RequireComponent<RigidBodyComponent>();
    }

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