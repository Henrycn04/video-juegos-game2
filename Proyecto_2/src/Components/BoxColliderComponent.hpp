#ifndef BOXCOLLIDERCOMPONENT_HPP
#define BOXCOLLIDERCOMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @struct BoxColliderComponent
 * @brief Represents a rectangular collision box for an entity.
 *
 * This component is used for detecting collisions between entities in a 2D space.
 * It defines the dimensions and offset of the collision box relative to the entity's position.
 */
struct BoxColliderComponent {
    /// Width of the collider box in pixels.
    int width;
    /// Height of the collider box in pixels.
    int height;
    /// Offset of the collider relative to the entity's position.
    glm::vec2 offset;

        /**
     * @brief Constructs a BoxColliderComponent with optional size and offset.
     *
     * @param width Width of the box collider (default is 0).
     * @param height Height of the box collider (default is 0).
     * @param offset Offset from the entity's position (default is (0, 0)).
     */
    BoxColliderComponent(int width= 0, int height = 0,
    glm::vec2 offset =glm::vec2(0)){
        this->width = width;
        this->height = height;
        this->offset = offset;
    }

};
#endif