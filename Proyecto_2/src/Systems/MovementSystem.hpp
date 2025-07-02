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

            // Guardar la posición anterior antes de integrar
            transform.previousPosition = transform.position;

            if (rigidbody.isDinamic) {
                // Integración de fuerzas -> aceleración -> velocidad -> posición
                rigidbody.acceleration = rigidbody.sumForces * rigidbody.invMass;
                rigidbody.velocity += rigidbody.acceleration * static_cast<float>(dt);
                transform.position += rigidbody.velocity * static_cast<float>(dt);

                // Resetear fuerzas aplicadas
                rigidbody.sumForces = glm::vec2(0); 
            } else {
                // Movimiento sin integración de fuerzas, solo con velocidad (ej. para plataformas móviles)
                transform.position.x += rigidbody.velocity.x * static_cast<float>(dt);
                transform.position.y += rigidbody.velocity.y * static_cast<float>(dt);            
            }
        }
    }
};

#endif