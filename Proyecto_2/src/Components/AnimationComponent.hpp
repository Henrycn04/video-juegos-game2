#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <SDL2/SDL.h>

/**
 * @struct AnimationComponent
 * @brief Stores data related to sprite animation for an entity.
 *
 * This component is responsible for managing the frame-based animation of a sprite,
 * including how many frames the animation has, how fast it plays, and whether it loops.
 */
struct AnimationComponent {
/// Total number of frames in the animation.
 int numFrames;
/// The current frame index being displayed.
 int currentFrame;
/// Duration of each frame in milliseconds.
 int frameSpeedRate;
/// Indicates whether the animation should repeat after finishing.
 bool isLoop;
/// The timestamp (in milliseconds) when the animation started.
 int startTime;

     /**
     * @brief Constructs an AnimationComponent with optional parameters.
     * 
     * @param numFrames The total number of frames in the animation (default is 1).
     * @param frameSpeedRate Speed of the animation in milliseconds per frame (default is 1).
     * @param isLoop Whether the animation should loop (default is true).
     */
 AnimationComponent(int numFrames = 1, int frameSpeedRate = 1
 , bool isLoop = true){
    this->numFrames = numFrames;
    this->currentFrame = 1;
    this->frameSpeedRate = frameSpeedRate;
    this->isLoop = isLoop;
    this->startTime = SDL_GetTicks();
 }
};
#endif