#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @struct RigidBodyComponent
 * @brief Represents the physics properties of an entity for movement and collision.
 *
 * This component stores information about dynamic state, solidity, invulnerability,
 * affiliation (enemy or player), and physics parameters such as velocity, forces,
 * acceleration, mass, and inverse mass.
 */
struct RigidBodyComponent{
    /// Indicates whether the entity is dynamic (affected by physics).
    bool isDinamic;
    /// Indicates whether the entity is solid (collidable).
    bool isSolid;
    /// Indicates if the entity is invulnerable to damage or physics effects.
    bool isInvulnerable;
    /// Flag to mark the entity as an enemy.
    bool isEnemy;
    /// Flag to mark the entity as a player.
    bool isPlayer;
    /// Current velocity vector of the entity.
    glm::vec2 velocity = glm::vec2(0);
    /// Sum of forces currently applied to the entity.
    glm::vec2 sumForces = glm::vec2(0);
    /// Current acceleration vector of the entity.
    glm::vec2 acceleration = glm::vec2(0);
    /// Mass of the entity.
    float mass;
    /// Inverse of the entity's mass (for optimized physics calculations).
    float invMass;
    /**
     * @brief Constructs a RigidBodyComponent with specified parameters.
     * 
     * @param isDynamic Whether the entity is dynamic (default: false).
     * @param isSolid Whether the entity is solid/collidable (default: false).
     * @param isEnemy Whether the entity is an enemy (default: false).
     * @param isPlayer Whether the entity is a player (default: false).
     * @param mass Mass of the entity (default: 1).
     */
    RigidBodyComponent(bool isDynamic = false, bool isSolid = false, bool isEnemy = false, bool isPlayer = false, float mass = 1){
        this->isDinamic = isDynamic;
        this->isSolid = isSolid;
        this->mass = mass;
        this->invMass = 1 / mass;
        this->isInvulnerable = false;
        this->isEnemy = isEnemy;
        this->isPlayer = isPlayer;
    }

};

#endif