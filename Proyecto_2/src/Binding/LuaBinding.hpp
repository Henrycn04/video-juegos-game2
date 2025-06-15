#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include <tuple>
#include <SDL2/SDL.h>
#include "../AnimationManager/AnimationManager.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"

//Controles
void ChangeAnimation(Entity entity, const std::string& animationId){
    auto& animation = entity.GetComponent<AnimationComponent>();
    auto& sprite = entity.GetComponent<SpriteComponent>();
    AnimationData animationData;
    animationData = Game::GetInstance().animationManager->GetAnimation(animationId);
    sprite.textureId = animationData.textureId;
    sprite.width = animationData.width;
    sprite.height = animationData.height;
    sprite.srcRect.x = 0;
    sprite.srcRect.y = 0;

    animation.currentFrame = 1;
    animation.numFrames = animationData.numFrames;
    animation.frameSpeedRate = animationData.frameSpeedRate;
    animation.isLoop = animationData.isLoop;
    animation.startTime = SDL_GetTicks();
}
bool IsActionActivated(const std::string& action){
    return Game::GetInstance().controllerManager->IsActionActivated(action);
}
// Collisions
bool LeftCollision(Entity e, Entity other){
    const auto& eCollider = e.GetComponent<BoxColliderComponent>();
    const auto& eTransform = e.GetComponent<TransformComponent>();

    const auto& oCollider = other.GetComponent<BoxColliderComponent>();
    const auto& oTransform = other.GetComponent<TransformComponent>();

    float eX = eTransform.previousPosition.x;
    float eY = eTransform.previousPosition.y;
    float eH = static_cast<float>(eCollider.height);

    float oX = oTransform.previousPosition.x;
    float oY = oTransform.previousPosition.y;
    float oH = static_cast<float>(oCollider.height);

    //El lado izquierdo e choca contra other
    return (
        oY < eY + eH &&
        oY + oH > eY &&
        oX < eX
    );

}

// Collisions
bool RightCollision(Entity e, Entity other){
    const auto& eCollider = e.GetComponent<BoxColliderComponent>();
    const auto& eTransform = e.GetComponent<TransformComponent>();

    const auto& oCollider = other.GetComponent<BoxColliderComponent>();
    const auto& oTransform = other.GetComponent<TransformComponent>();

    float eX = eTransform.previousPosition.x;
    float eY = eTransform.previousPosition.y;
    float eH = static_cast<float>(eCollider.height);

    float oX = oTransform.previousPosition.x;
    float oY = oTransform.previousPosition.y;
    float oH = static_cast<float>(oCollider.height);

    //El lado derecho e choca contra other
    return (
        oY < eY + eH &&
        oY + oH > eY &&
        oX > eX
    );

}
// RigidBodyComponent
std::tuple<int, int> GetVelocity(Entity entity){
    const auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    return {
        static_cast<int>(rigidbody.velocity.x),
        static_cast<int>(rigidbody.velocity.y),
    };
}

void SetVelocity(Entity entity, float x, float y){
    auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    rigidbody.velocity.x = x;
    rigidbody.velocity.y = y;
}
void AddForce(Entity entity, float x, float y){
    auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    rigidbody.sumForces += glm::vec2(x, y);
}

// TagComponent
std::string GetTag(Entity entity){
    return entity.GetComponent<TagComponent>().tag;
}
// Sprite

void FlipSprite(Entity entity, bool flip){
    auto& sprite = entity.GetComponent<SpriteComponent>();
    sprite.flip = flip;
}
//TransformComponent
std::tuple<int, int> GetPosition(Entity entity){
    const auto& transform = entity.GetComponent<TransformComponent>();
    return {
        static_cast<int>(transform.position.x),
        static_cast<int>(transform.position.y),
    };
}

void SetPosition(Entity entity, int x, int y){
    auto& transform = entity.GetComponent<TransformComponent>();
    transform.position.x = x;
    transform.position.y = y;

}

std::tuple<int, int> GetSize(Entity entity){
    const auto& sprite = entity.GetComponent<SpriteComponent>();
    const auto& transform = entity.GetComponent<TransformComponent>();

    int width = sprite.width * transform.scale.x;
    int height = sprite.height * transform.scale.y;

    return {width, height};

}

// Scenes
void GoToScene(const std::string& sceneName){
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}


#endif