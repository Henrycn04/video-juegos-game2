#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include <glm/glm.hpp>

struct RigidBodyComponent{
    bool isDinamic;
    glm::vec2 velocity = glm::vec2(0);
    glm::vec2 sumForces = glm::vec2(0);
    glm::vec2 acceleration = glm::vec2(0);
    float mass;
    float invMass;

    RigidBodyComponent(bool isDynamic = false, float mass = 1){
        this->isDinamic = isDynamic;
        this->mass = mass;
        this->invMass = 1 / mass;
    }

};

#endif