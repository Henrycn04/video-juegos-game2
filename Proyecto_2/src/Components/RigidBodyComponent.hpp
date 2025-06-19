#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include <glm/glm.hpp>

struct RigidBodyComponent{
    bool isDinamic;
    bool isSolid;
    bool isInvulnerable;
    bool isEnemy;
    bool isPlayer;;
    glm::vec2 velocity = glm::vec2(0);
    glm::vec2 sumForces = glm::vec2(0);
    glm::vec2 acceleration = glm::vec2(0);
    float mass;
    float invMass;

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