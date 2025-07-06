#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @struct TransformComponent
 * @brief Stores spatial information of an entity including position, scale, and rotation.
 *
 * This component tracks the current position, scale factors,
 * previous position (for movement calculations), and rotation angle.
 */
struct TransformComponent {
    /// Current position of the entity in 2D space.
    glm::vec2 position;
    /// Scale factors along the X and Y axes.
    glm::vec2 scale;
    /// Previous position of the entity, useful for physics or interpolation.
    glm::vec2 previousPosition;
    /// Rotation angle in degrees (or radians, depending on usage).
    double rotation;
    
    /**
     * @brief Constructs a TransformComponent with optional position, scale, and rotation.
     * 
     * @param position Initial position (default is (0.0, 0.0)).
     * @param scale Initial scale (default is (1.0, 1.0)).
     * @param rotation Initial rotation (default is 0.0).
     */
    TransformComponent(glm::vec2 position = glm::vec2(0.0, 0.0)
    , glm::vec2 scale = glm::vec2(1.0, 1.0), double rotation = 0.0){
      this->position = position;
      this->previousPosition = position;
      this->scale = scale;
      this->rotation = rotation;
    }
};

#endif