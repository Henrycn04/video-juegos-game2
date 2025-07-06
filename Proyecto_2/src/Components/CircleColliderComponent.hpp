#ifndef CIRCLECOLLIDERCOMPONENT_HPP
#define CIRCLECOLLIDERCOMPONENT_HPP

/**
 * @struct CircleColliderComponent
 * @brief Represents a circular collision shape with optional bounding box.
 *
 * This component defines a circular collider used for detecting radial collisions between entities.
 * It also optionally includes width and height values to define a bounding box if needed
 * for overlap checks or hybrid collision systems.
 */
struct CircleColliderComponent{
/// Radius of the circle collider.
 int radius;
/// Width of the associated bounding box (optional).
 int width;
/// Height of the associated bounding box (optional).
 int height;

     /**
     * @brief Constructs a CircleColliderComponent with optional radius and dimensions.
     *
     * @param radius The radius of the circular collider (default is 0).
     * @param width Optional width for a bounding box (default is 0).
     * @param height Optional height for a bounding box (default is 0).
     */
 CircleColliderComponent(int radius = 0,int width = 0,int height = 0){
    this->radius = radius;
    this->width = width;
    this->height = height;
 }

};
#endif