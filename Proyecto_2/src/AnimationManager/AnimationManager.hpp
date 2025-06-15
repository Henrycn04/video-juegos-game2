#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP
#include <map>
#include <string>


struct AnimationData {
    std::string textureId;
    int width;
    int height;
    int numFrames;
    int frameSpeedRate;
    bool isLoop;

    AnimationData(const std::string& textureId = "", int width = 0, int height = 0, int numFrames = 1, int frameSpeedRate = 1, bool isLoop = true)
        : textureId(textureId), width(width), height(height), numFrames(numFrames), frameSpeedRate(frameSpeedRate), isLoop(isLoop) {}
};

class AnimationManager {
    private:
    std::map<std::string, AnimationData> animations;
    public:
    AnimationManager();
    ~AnimationManager();
    void AddAnimation(const std::string& animationId, const std::string& textureId, int width, int height, int numFrames, int frameSpeedRate, bool isLoop);
    AnimationData GetAnimation(const std::string& textureId);


};

#endif // ANIMATION_MANAGER_HPP