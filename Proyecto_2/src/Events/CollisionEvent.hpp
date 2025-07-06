#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

/**
 * @class CollisionEvent
 * @brief Event triggered when two entities collide in the ECS system.
 *
 * This event holds references to the two entities involved in the collision.
 * It is typically emitted by a collision detection system and used by other systems
 * (e.g., damage handling, sound, or score updates) to react to collisions.
 */
class CollisionEvent : public Event {
 public:
    /**
     * @brief The first entity involved in the collision.
     */
    Entity a;

    /**
     * @brief The second entity involved in the collision.
     */
     Entity b;
    /**
     * @brief Constructs a CollisionEvent with two colliding entities.
     * @param a The first entity.
     * @param b The second entity.
     */
    CollisionEvent(Entity a, Entity b) : a(a), b(b) {}
};
#endif