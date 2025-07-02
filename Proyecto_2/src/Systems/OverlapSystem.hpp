#ifndef OVERLAPSYSTEM_HPP
#define OVERLAPSYSTEM_HPP

#include "../Components/TransformComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Events/CollisionEvent.hpp"
#include "../EventManager/EventManager.hpp"
#include <memory>

enum Direction { top, left, bottom, right };

class OverlapSystem : public System {
private:
    bool CheckCollision(Entity a, Entity b, Direction dir) {
        auto& aTransform = a.GetComponent<TransformComponent>();
        auto& bTransform = b.GetComponent<TransformComponent>();
        auto& aBox = a.GetComponent<BoxColliderComponent>();
        auto& bBox = b.GetComponent<BoxColliderComponent>();

        float aX = aTransform.previousPosition.x;
        float aY = aTransform.previousPosition.y;
        float bX = bTransform.previousPosition.x;
        float bY = bTransform.previousPosition.y;

        float aW = aBox.width * aTransform.scale.x;
        float aH = aBox.height * aTransform.scale.y;
        float bW = bBox.width * bTransform.scale.x;
        float bH = bBox.height * bTransform.scale.y;

        bool xOverlap = (aX < bX + bW) && (aX + aW > bX);
        bool yOverlap = (aY < bY + bH) && (aY + aH > bY);

        if (dir == Direction::top) {
            return xOverlap && (aY >= bY + bH);
        }
        if (dir == Direction::bottom) {
            return xOverlap && (aY + aH <= bY);
        }
        if (dir == Direction::left) {
            return yOverlap && (aX >= bX + bW);
        }
        if (dir == Direction::right) {
            return yOverlap && (aX + aW <= bX);
        }

        return false;
    }

    void AvoidOverlap(Entity a, Entity b) {
        auto& aTransform = a.GetComponent<TransformComponent>();
        auto& bTransform = b.GetComponent<TransformComponent>();
        auto& aBoxCollider = a.GetComponent<BoxColliderComponent>();
        auto& bBoxCollider = b.GetComponent<BoxColliderComponent>();
        auto& bRigidBody = b.GetComponent<RigidBodyComponent>();

        // Colisión desde arriba (B debajo de A)
        if (CheckCollision(a, b, Direction::top)) {
            bTransform.position.y = aTransform.position.y - bBoxCollider.height * bTransform.scale.y;
            // Si B está cayendo (velocity.y > 0), cancelar la velocidad
            if (bRigidBody.velocity.y > 0) {
                bRigidBody.velocity.y = 0;
            }
        }

        // Colisión desde abajo (B encima de A)
        if (CheckCollision(a, b, Direction::bottom)) {
            bTransform.position.y = aTransform.position.y + aBoxCollider.height * aTransform.scale.y + 1.0f;
        }


        // Colisión desde la izquierda (B a la derecha de A)
        if (CheckCollision(a, b, Direction::left)) {
            bTransform.position.x = aTransform.position.x - bBoxCollider.width * bTransform.scale.x;
            if (bRigidBody.velocity.x > 0) {
                bRigidBody.velocity.x = 0;
            }
        }

        // Colisión desde la derecha (B a la izquierda de A)
        if (CheckCollision(a, b, Direction::right)) {
            bTransform.position.x = aTransform.position.x + aBoxCollider.width * aTransform.scale.x;
            if (bRigidBody.velocity.x < 0) {
                bRigidBody.velocity.x = 0;
            }
        }
    }

public:
    OverlapSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<BoxColliderComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    void SubscribeToCollisionEvents(const std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<CollisionEvent, OverlapSystem>(this, &OverlapSystem::OnCollisionEvent);
    }

    void OnCollisionEvent(CollisionEvent& e) {
        auto& aRigidBody = e.a.GetComponent<RigidBodyComponent>();
        auto& bRigidBody = e.b.GetComponent<RigidBodyComponent>();

        bool isPlayerEnemyCollision = (aRigidBody.isPlayer && bRigidBody.isEnemy) || (aRigidBody.isEnemy && bRigidBody.isPlayer);

        if (aRigidBody.isSolid && bRigidBody.isSolid && !isPlayerEnemyCollision && !aRigidBody.isInvulnerable && !bRigidBody.isInvulnerable) {
            if (aRigidBody.mass >= bRigidBody.mass) {
                AvoidOverlap(e.a, e.b);
            } else {
                AvoidOverlap(e.b, e.a);
            }
        }
    }
};

#endif

/*
🔧 Ajuste clave:
- Ya NO cancela velocity.y cuando un objeto sube y choca desde abajo, solo lo reposiciona.
- Esto permite saltos naturales y evita que enemigos o jugadores queden pegados al techo.
- Lógica estrictamente dentro de los atributos que compartiste.
*/
