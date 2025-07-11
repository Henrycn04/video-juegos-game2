#ifndef OVERLAPSYSTEM_HPP
#define OVERLAPSYSTEM_HPP

#include "../Components/TransformComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Events/CollisionEvent.hpp"
#include "../EventManager/EventManager.hpp"
#include <memory>

/**
 * @enum Direction
 * @brief Directions used for collision checking.
 */
enum Direction { top, left, bottom, right };
/**
 * @class OverlapSystem
 * @brief Manages collision overlap resolution between entities with box colliders and rigid bodies.
 * 
 * Handles positional adjustments and velocity resets to avoid overlapping after collisions.
 * Supports special handling for moving platforms and passengers standing on them.
 */
class OverlapSystem : public System {
private:
    /**
     * @brief Checks collision between two entities in a given direction based on previous positions.
     * 
     * @param a First entity.
     * @param b Second entity.
     * @param dir Direction of collision to check.
     * @return true if collision occurs in the specified direction, false otherwise.
     */
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
    /**
     * @brief Adjusts positions and velocities to avoid overlapping between two entities.
     * 
     * @param a Entity considered as reference.
     * @param b Entity to be adjusted.
     */
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
    /**
     * @brief Special handling to avoid overlap between a moving platform and a passenger entity standing on it.
     * 
     * Adjusts passenger position and transfers vertical movement from platform to passenger.
     * 
     * @param platform Moving platform entity.
     * @param passenger Entity standing on the platform.
     */
void AvoidOverlapPlatform(Entity platform, Entity passenger) {
    auto& platformTransform = platform.GetComponent<TransformComponent>();
    auto& passengerTransform = passenger.GetComponent<TransformComponent>();
    auto& platformBox = platform.GetComponent<BoxColliderComponent>();
    auto& passengerBox = passenger.GetComponent<BoxColliderComponent>();
    auto& platformRigidBody = platform.GetComponent<RigidBodyComponent>();
    auto& passengerRigidBody = passenger.GetComponent<RigidBodyComponent>();

    float platformLeft = platformTransform.position.x;
    float platformRight = platformTransform.position.x + platformBox.width * platformTransform.scale.x;
    float platformTop = platformTransform.position.y;


    float passengerLeft = passengerTransform.position.x;
    float passengerRight = passengerTransform.position.x + passengerBox.width * passengerTransform.scale.x;
    float passengerTop = passengerTransform.position.y;
    float passengerBottom = passengerTransform.position.y + passengerBox.height * passengerTransform.scale.y;

    // Verificar si el passenger está realmente solapando la parte superior de la plataforma
    bool xOverlap = (passengerRight > platformLeft) && (passengerLeft < platformRight);
    bool yOverlap = (passengerBottom > platformTop) && (passengerTop < platformTop);

    // Solo si viene cayendo hacia la plataforma
    bool fallingOntoPlatform = passengerRigidBody.velocity.y >= 0;

    if (xOverlap && yOverlap && fallingOntoPlatform) {
        // Ajustar posición justo encima de la plataforma
        passengerTransform.position.y = platformTop - passengerBox.height * passengerTransform.scale.y;

        // Transferir el movimiento vertical de la plataforma al pasajero
        passengerTransform.position.y += platformRigidBody.velocity.y;


        // Resetear velocidad vertical del pasajero si está cayendo
        if (passengerRigidBody.velocity.y > 0) {
            passengerRigidBody.velocity.y = 0;
        }
    }
}
public:
    /**
     * @brief Constructs OverlapSystem and sets required components.
     */
    OverlapSystem() {
        RequireComponent<TransformComponent>();
        RequireComponent<BoxColliderComponent>();
        RequireComponent<RigidBodyComponent>();
    }

    /**
     * @brief Subscribes the system to collision events from the EventManager.
     * 
     * @param eventManager Pointer to the EventManager instance.
     */
    void SubscribeToCollisionEvents(const std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<CollisionEvent, OverlapSystem>(this, &OverlapSystem::OnCollisionEvent);
    }
    /**
     * @brief Collision event handler that resolves overlap based on entity properties.
     * 
     * @param e Reference to the collision event data.
     */
    void OnCollisionEvent(CollisionEvent& e) {
        auto& aRigidBody = e.a.GetComponent<RigidBodyComponent>();
        auto& bRigidBody = e.b.GetComponent<RigidBodyComponent>();

        bool isPlayerEnemyCollision = (aRigidBody.isPlayer && bRigidBody.isEnemy) || (aRigidBody.isEnemy && bRigidBody.isPlayer);
        bool isEnemyEnemyCollision = (aRigidBody.isEnemy && bRigidBody.isEnemy);
        bool isPlatformPlatformCollision = (e.a.GetComponent<TagComponent>().tag == "moveV" && e.b.GetComponent<TagComponent>().tag == "moveV") ||
                                           (e.a.GetComponent<TagComponent>().tag == "moveH" && e.b.GetComponent<TagComponent>().tag == "moveH") ||
                                           (e.a.GetComponent<TagComponent>().tag == "moveV" && e.b.GetComponent<TagComponent>().tag == "moveH") ||
                                           (e.a.GetComponent<TagComponent>().tag == "moveH" && e.b.GetComponent<TagComponent>().tag == "moveV");
        if (aRigidBody.isSolid && bRigidBody.isSolid && !isPlayerEnemyCollision && !isEnemyEnemyCollision && !isPlatformPlatformCollision && !aRigidBody.isInvulnerable && !bRigidBody.isInvulnerable) {
            if (e.a.GetComponent<TagComponent>().tag == "moveV" || e.b.GetComponent<TagComponent>().tag == "moveV" ||
                e.a.GetComponent<TagComponent>().tag == "moveH" || e.b.GetComponent<TagComponent>().tag == "moveH") {
                if (aRigidBody.mass >= bRigidBody.mass) {
                    AvoidOverlapPlatform(e.a, e.b);
                } else {
                    AvoidOverlapPlatform(e.b, e.a);
                }
            }else {
                if (aRigidBody.mass >= bRigidBody.mass) {
                    AvoidOverlap(e.a, e.b);
                } else {
                    AvoidOverlap(e.b, e.a);
                }
            }

        }
    }
};

#endif

