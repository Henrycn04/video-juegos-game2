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
#include "../Components/HealthComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"


int GetTicks(){
    return SDL_GetTicks();
}

void CreateArrow(Entity shooter) {
    
    // Verificar que el shooter existe y tiene los componentes necesarios
    if (!shooter.HasComponent<TransformComponent>()) {
        std::cout << "[ERROR] Shooter doesn't have TransformComponent!" << std::endl;
        return;
    }
    
    // Obtener la posición del disparador
    const auto& shooterTransform = shooter.GetComponent<TransformComponent>();
    float start_x = shooterTransform.position.x;
    float start_y = shooterTransform.position.y;
    
    
    // Determinar dirección de disparo
    float vel_x = 400.0f;
    float vel_y = 0.0f;
    
    
    // Crear la entidad flecha
    Entity arrow = Game::GetInstance().registry->CreateEntity();    
    // Agregar componentes a la flecha
    arrow.AddComponent<TagComponent>("arrow01");
    
    // Transform con posición inicial ligeramente desplazada del shooter
    float arrow_x = start_x + (vel_x > 0 ? 25 : -25); // Desplazar según dirección
    arrow.AddComponent<TransformComponent>(glm::vec2(arrow_x, start_y), glm::vec2(1, 1), 0);
        
    // Collider
    arrow.AddComponent<BoxColliderComponent>(28, 12, glm::vec2(0, 0));
    
    // Animación
    arrow.AddComponent<AnimationComponent>(2, 10, true);
    
    arrow.AddComponent<SpriteComponent>("arrow01", 28, 12, 0, 0);
    
    // RigidBody con velocidad aplicada
    arrow.AddComponent<RigidBodyComponent>(true, true, true, false, 2.0f);
    auto& rigidbody = arrow.GetComponent<RigidBodyComponent>();
    rigidbody.sumForces += glm::vec2(1500 * 64.0, vel_y);


}
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
bool TopCollision(Entity e, Entity other) {
    // Obtener componentes

    const auto& eCollider = e.GetComponent<BoxColliderComponent>();
    const auto& eTransform = e.GetComponent<TransformComponent>();
    const auto& oCollider = other.GetComponent<BoxColliderComponent>();
    const auto& oTransform = other.GetComponent<TransformComponent>();

    // Extraer posiciones y dimensiones
    float eX = eTransform.position.x;
    float eY = eTransform.position.y;
    float eW = static_cast<float>(eCollider.width);
    float eH = static_cast<float>(eCollider.height);
    
    float oX = oTransform.position.x;
    float oY = oTransform.position.y;
    float oW = static_cast<float>(oCollider.width);
    float oH = static_cast<float>(oCollider.height);
    
    // Calcular bordes importantes
    float eTop = eY;
    float eLeft = eX;
    float eRight = eX + eW;
    
    float oBottom = oY + oH;
    float oLeft = oX;
    float oRight = oX + oW;
    
    // Verificar solapamiento horizontal primero
    bool horizontalOverlap = (eLeft < oRight) && (eRight > oLeft);
    if (!horizontalOverlap) return false;
    

    // Verificar si están en rango vertical (5 píxeles)
    // El borde inferior de 'other' debe estar cerca del borde superior de 'e'
    const float range = 10.0f;
    bool inVerticalRange = (oBottom >= eTop - range) && (oBottom <= eTop + range);

    return inVerticalRange;
}

bool BottomCollision(Entity e, Entity other){
    const auto& eCollider = e.GetComponent<BoxColliderComponent>();
    const auto& eTransform = e.GetComponent<TransformComponent>();
    const auto& oCollider = other.GetComponent<BoxColliderComponent>();
    const auto& oTransform = other.GetComponent<TransformComponent>();
    
    float eX = eTransform.previousPosition.x;
    float eY = eTransform.previousPosition.y;
    float eW = static_cast<float>(eCollider.width);
    float eH = static_cast<float>(eCollider.height);
    float oX = oTransform.previousPosition.x;
    float oY = oTransform.previousPosition.y;
    float oW = static_cast<float>(oCollider.width);
    float oH = static_cast<float>(oCollider.height);
    
    // La parte inferior de e choca contra other
    return (
        oX < eX + eW &&
        oX + oW > eX &&
        oY + oH > eY + eH
    );
}
void DeactivateCollisions(Entity entity){
    auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    rigidbody.isDinamic = true;
    rigidbody.isSolid = false;
    rigidbody.isInvulnerable = true;
}
// HealthComponent
void DoDamage(Entity self, Entity other){
    auto& sRigidbody = self.GetComponent<RigidBodyComponent>();
    auto& oRigidbody = other.GetComponent<RigidBodyComponent>();
    if (!sRigidbody.isInvulnerable && !oRigidbody.isInvulnerable){
        auto& health = self.GetComponent<HealthComponent>();
        health.Damage(1);
    }
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

std::tuple<int, int> GetSumForces(Entity entity) {
    const auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    std::cout << "Sum Forces: " << rigidbody.sumForces.x << ", " << rigidbody.sumForces.y << std::endl;
    return {
        static_cast<int>(rigidbody.sumForces.x),
        static_cast<int>(rigidbody.sumForces.y)
    };
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