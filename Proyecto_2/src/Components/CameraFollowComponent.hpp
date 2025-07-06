#ifndef CAMERAFOLLOWCOMPONENT_HPP
#define CAMERAFOLLOWCOMPONENT_HPP

/**
 * @struct CameraFollowComponent
 * @brief Tag component used to make the camera follow an entity.
 *
 * When an entity has this component, the game camera will track the entity's position,
 * centering the view around it. This component does not store any data and acts as a marker.
 */
struct CameraFollowComponent{
    /**
     * @brief Default constructor for CameraFollowComponent.
     */
    CameraFollowComponent(){}

};
#endif