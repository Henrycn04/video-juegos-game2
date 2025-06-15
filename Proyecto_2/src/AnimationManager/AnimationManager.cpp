#include "AnimationManager.hpp"

AnimationManager::AnimationManager() {
    // Constructor implementation
}
AnimationManager::~AnimationManager() {
    // Destructor implementation
}
void AnimationManager::AddAnimation(const std::string& animationId, const std::string& textureId, int width, int height, int numFrames, int frameSpeedRate, bool isLoop) {
    animations[animationId] = AnimationData(textureId, width, height, numFrames, frameSpeedRate, isLoop);
}
AnimationData AnimationManager::GetAnimation(const std::string& textureId) {
    return animations[textureId]; // Return default AnimationData if not found
}
