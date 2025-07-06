#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP
#include <map>
#include <string>
/**
 * @struct AnimationData
 * @brief Represents the data required for a single animation.
 *
 * This struct contains all necessary parameters to describe an animation,
 * such as its associated texture, dimensions of each frame, number of frames,
 * frame playback speed, and whether the animation should loop.
 */

struct AnimationData {
     /// The ID of the texture used for the animation.
    std::string textureId;
    /// The width of each animation frame (in pixels).
    int width;
     /// The height of each animation frame (in pixels).
    int height;
    /// The total number of frames in the animation.
    int numFrames;
    /// The duration of each frame in milliseconds.
    int frameSpeedRate;
    /// Indicates whether the animation should loop.
    bool isLoop;

    /**
     * @brief Constructs an AnimationData object with optional parameters.
     * 
     * @param textureId ID of the texture used in the animation.
     * @param width Width of each animation frame.
     * @param height Height of each animation frame.
     * @param numFrames Total number of frames.
     * @param frameSpeedRate Duration of each frame (in ms).
     * @param isLoop Whether the animation loops.
     */
    AnimationData(const std::string& textureId = "", int width = 0, int height = 0, int numFrames = 1, int frameSpeedRate = 1, bool isLoop = true)
        : textureId(textureId), width(width), height(height), numFrames(numFrames), frameSpeedRate(frameSpeedRate), isLoop(isLoop) {}
};
/**
 * @class AnimationManager
 * @brief Manages and stores multiple animations.
 *
 * The AnimationManager class allows registering animations by ID and retrieving them later.
 * It stores a collection of animations identified by unique string keys.
 */
class AnimationManager {
    private:
    /// A map storing animation data indexed by animation ID.
    std::map<std::string, AnimationData> animations;
    public:
    /**
     * @brief Constructs an AnimationManager.
     */
    AnimationManager();
     /**
     * @brief Destroys the AnimationManager and clears resources.
     */
    ~AnimationManager();
    /**
     * @brief Adds an animation to the manager.
     *
     * @param animationId A unique identifier for the animation.
     * @param textureId The ID of the texture used by the animation.
     * @param width The width of each animation frame.
     * @param height The height of each animation frame.
     * @param numFrames The total number of frames in the animation.
     * @param frameSpeedRate The speed of each frame in milliseconds.
     * @param isLoop Whether the animation should loop.
     */
    void AddAnimation(const std::string& animationId, const std::string& textureId, int width, int height, int numFrames, int frameSpeedRate, bool isLoop);
    /**
     * @brief Retrieves the animation data associated with a given animation ID.
     *
     * @param textureId The ID of the animation to retrieve.
     * @return AnimationData object containing the animation properties.
     *
     * @note If the animation ID is not found, the behavior depends on the implementation.
     */
    AnimationData GetAnimation(const std::string& textureId);


};

#endif // ANIMATION_MANAGER_HPP