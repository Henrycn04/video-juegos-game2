#ifndef OVERLAPSYSTEM_HPP
#define OVERLAPSYSTEM_HPP
#include "../Components/TransformComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Events/CollisionEvent.hpp"
#include "../EventManager/EventManager.hpp"
#include <memory>

enum Direction {top, left, bottom, right};

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

        if (CheckCollision(a, b, Direction::top)) { // revisar esta cosa
            bTransform.position = glm::vec2(bTransform.position.x, aTransform.previousPosition.y - bBoxCollider.height * bTransform.scale.y);
            bRigidBody.velocity = glm::vec2(bRigidBody.velocity.x, 0);
        } 
        if (CheckCollision(a, b, Direction::bottom)) {
            bTransform.position = glm::vec2(bTransform.position.x, aTransform.previousPosition.y + aBoxCollider.height * aTransform.scale.y);
            bRigidBody.velocity = glm::vec2(bRigidBody.velocity.x, 0);
        }
        if (CheckCollision(a, b, Direction::left)) {
            bTransform.position = glm::vec2(aTransform.previousPosition.x - bBoxCollider.width * bTransform.scale.x, bTransform.position.y);
            bRigidBody.velocity = glm::vec2(0, bRigidBody.velocity.y);
        }
        if (CheckCollision(a, b, Direction::right)) {
            bTransform.position = glm::vec2(aTransform.previousPosition.x + aBoxCollider.width * aTransform.scale.x, bTransform.position.y);
            bRigidBody.velocity = glm::vec2(0, bRigidBody.velocity.y);
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
            bool isPlayerEnemyCollision = 
                (aRigidBody.isPlayer && bRigidBody.isEnemy) || 
                (aRigidBody.isEnemy && bRigidBody.isPlayer);

            if (aRigidBody.isSolid && bRigidBody.isSolid && !isPlayerEnemyCollision && !aRigidBody.isInvulnerable&& !bRigidBody.isInvulnerable) {
                if (aRigidBody.mass >= bRigidBody.mass) {
                    AvoidOverlap(e.a, e.b);
                } else {
                    AvoidOverlap(e.b, e.a);
                }
            }
        }


};
#endif