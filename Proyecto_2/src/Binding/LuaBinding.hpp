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
#include "../Components/ScriptComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"
#include "../Systems/SceneTimeSystem.hpp"
#include <iomanip>
#include <sstream>


/**
 * @file LuaBinding.hpp
 * @brief Contains functions exposed to Lua for controlling game entities, physics, animation, UI, collisions, and more.
 *
 * This file defines global utility functions that are registered in the Lua scripting environment
 * and allow scripts to interact with entities, perform collision checks, modify animations,
 * control movement, health, and manage scene transitions.
 *
 * @note This header is designed to be included in a Lua binding setup and used with Sol2.
 */


/**
 * @brief Returns the number of milliseconds since the SDL library was initialized.
 * @return Milliseconds since initialization.
 */ 
int GetTicks(){
    return SDL_GetTicks();
}

/**
 * @brief Marks an entity for deletion and logs information about it, unless it is an "arrow01".
 * @param entity The entity to kill.
 */
void KillEntity(Entity entity) {
    auto& tag = entity.GetComponent<TagComponent>();
    auto& transform = entity.GetComponent<TransformComponent>();
    if (tag.tag != "arrow01") {
    std::cout << "[INFO] Killing entity with ID: " << entity.GetId()
              << " Tag: " << tag.tag
              << " at position (" << transform.position.x << ", " << transform.position.y << ")"
              << std::endl;
    }


    entity.Kill();
}

/**
 * @brief Creates a new arrow entity shot from the given shooter entity.
 * Initializes its transform, collider, sprite, animation, physics, and Lua script.
 * @param shooter The entity that shoots the arrow.
 */
void CreateArrow(Entity shooter) {
    
    if (!shooter.HasComponent<TransformComponent>()) {
        std::cout << "[ERROR] Shooter doesn't have TransformComponent!" << std::endl;
        return;
    }
    
    const auto& shooterTransform = shooter.GetComponent<TransformComponent>();
    float start_x = shooterTransform.position.x;
    float start_y = shooterTransform.position.y;
    
    
    float vel_y = 0.0f;
    
    
    // Crear la entidad flecha
    Entity arrow = Game::GetInstance().registry->CreateEntity();    
    // Agregar componentes a la flecha
    arrow.AddComponent<TagComponent>("arrow01");
    
    // Transform con posición inicial ligeramente desplazada del shooter
    float arrow_x = start_x; // Desplazar según dirección
    arrow.AddComponent<TransformComponent>(glm::vec2(arrow_x, start_y), glm::vec2(1, 1), 0);
        
    // Collider
    arrow.AddComponent<BoxColliderComponent>(28, 12, glm::vec2(0, 0));
    
    // Animación
    arrow.AddComponent<AnimationComponent>(2, 10, true);
    
    arrow.AddComponent<SpriteComponent>("arrow01", 28, 12, 0, 0);
    auto& lua = Game::GetInstance().lua;
                lua["on_awake"] = sol::nil;
                lua["update"] = sol::nil;
                lua["on_click"] = sol::nil;
                lua["on_collision"] = sol::nil;
                lua.script_file("./assets/scripts/arrow01.lua");

                sol::optional<sol::function> hasOnAwake = lua["on_awake"];
                sol::function onAwake = sol::nil;
                if(hasOnAwake != sol::nullopt){
                    onAwake = lua["on_awake"];
                    onAwake(); 
                }

                sol::optional<sol::function> hasOnCollision = lua["on_collision"];
                sol::function onCollision = sol::nil;
                if(hasOnCollision != sol::nullopt){
                    onCollision = lua["on_collision"];
                }

                sol::optional<sol::function> hasOnClick = lua["on_click"];
                sol::function onClick = sol::nil;
                if(hasOnClick != sol::nullopt){
                    onClick = lua["on_click"];
                }

                sol::optional<sol::function> hasUpdate = lua["update"];
                sol::function update = sol::nil;
                if(hasUpdate != sol::nullopt){
                    update = lua["update"];
                }

                arrow.AddComponent<ScriptComponent>(onCollision, update, onClick);
    
    arrow.AddComponent<RigidBodyComponent>(true, true, true, false, 2.0f);


    auto& spriteShooter = shooter.GetComponent<SpriteComponent>();
    int direccion = 1; 
    if (spriteShooter.flip) { 
        direccion = -1; 
        arrow.GetComponent<SpriteComponent>().flip = true; // Voltear sprite de la flecha
    }
    auto& rigidbody = arrow.GetComponent<RigidBodyComponent>();
    rigidbody.sumForces += glm::vec2(direccion * 1300 * 64.0, vel_y);

}

/**
 * @brief Changes the current animation of an entity to the one identified by animationId.
 * @param entity The target entity.
 * @param animationId The animation ID to set.
 */
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

/**
 * @brief Checks if a specific game action is currently activated.
 * @param action The action name (e.g., "jump", "shoot").
 * @return true if the action is active; false otherwise.
 */
bool IsActionActivated(const std::string& action){
    return Game::GetInstance().controllerManager->IsActionActivated(action);
}


/**
 * @brief Checks if another entity is colliding with the left side of the given entity.
 * @param e The base entity.
 * @param other The other entity to check collision with.
 * @return true if collision from the left is detected.
 */
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


    return (
        oY < eY + eH &&
        oY + oH > eY &&
        oX < eX
    );

}

/**
 * @brief Checks if another entity is colliding with the right side of the given entity.
 * @param e The base entity.
 * @param other The other entity to check collision with.
 * @return true if collision from the right is detected.
 */
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

    return (
        oY < eY + eH &&
        oY + oH > eY &&
        oX > eX
    );

}

/**
 * @brief Checks if another entity is colliding with the top side of the given entity.
 * @param e The base entity.
 * @param other The other entity to check collision with.
 * @return true if collision from the top is detected.
 */
bool TopCollision(Entity e, Entity other) {

    const auto& eCollider = e.GetComponent<BoxColliderComponent>();
    const auto& eTransform = e.GetComponent<TransformComponent>();
    const auto& oCollider = other.GetComponent<BoxColliderComponent>();
    const auto& oTransform = other.GetComponent<TransformComponent>();

  
    float eX = eTransform.position.x;
    float eY = eTransform.position.y;
    float eW = static_cast<float>(eCollider.width);

    float oX = oTransform.position.x;
    float oY = oTransform.position.y;
    float oW = static_cast<float>(oCollider.width);
    float oH = static_cast<float>(oCollider.height);

   
    float eTop = eY;
    float eLeft = eX;
    float eRight = eX + eW;

    float oBottom = oY + oH;
    float oLeft = oX;
    float oRight = oX + oW;

   
    bool horizontalOverlap = (eLeft < oRight) && (eRight > oLeft);
    if (!horizontalOverlap) return false;

  
    float oPreviousY = oTransform.previousPosition.y;
    float oBottomPrevious = oPreviousY + oH;

   
    bool wasAbove = oBottomPrevious <= eTop + 5.0f;
    bool isNowOverlapping = oBottom >= eTop;

    return wasAbove && isNowOverlapping;
}


/**
 * @brief Checks if another entity is colliding with the bottom side of the given entity.
 * @param e The base entity.
 * @param other The other entity to check collision with.
 * @return true if collision from the bottom is detected.
 */
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
    
    return (
        oX < eX + eW &&
        oX + oW > eX &&
        oY + oH > eY + eH
    );
}

/**
 * @brief Makes an entity non-solid and invulnerable (disables collisions).
 * @param entity The entity to modify.
 */
void DeactivateCollisions(Entity entity){
    auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    rigidbody.isDinamic = true;
    rigidbody.isSolid = false;
    rigidbody.isInvulnerable = true;
}

/**
 * @brief Applies 1 point of damage to `self` if both entities are not invulnerable.
 * @param self The entity taking damage.
 * @param other The entity dealing damage.
 */
void DoDamage(Entity self, Entity other){
    auto& sRigidbody = self.GetComponent<RigidBodyComponent>();
    auto& oRigidbody = other.GetComponent<RigidBodyComponent>();
    if (!sRigidbody.isInvulnerable && !oRigidbody.isInvulnerable){ // TODO: revisar cual es el que tiene invencibilidad (para jugador mas que todo)
        auto& health = self.GetComponent<HealthComponent>();
        health.Damage(1);
    }
}

/**
 * @brief Applies 1 point of damage to `self`, if not invulnerable.
 * @param self The entity to damage.
 */
void DoDamageToSelf(Entity self){
    auto& sRigidbody = self.GetComponent<RigidBodyComponent>();
    if (!sRigidbody.isInvulnerable){ // TODO: revisar cual es el que tiene invencibilidad (para jugador mas que todo)
        auto& health = self.GetComponent<HealthComponent>();
        health.Damage(1);
    }
}

/**
 * @brief Sets the current checkpoint position for the scene loader.
 * @param posX X coordinate.
 * @param posY Y coordinate.
 */
void SetCheckPosition(float posX, float posY){
    Game::GetInstance().sceneManager->sceneLoader->checkPosX = posX;
    Game::GetInstance().sceneManager->sceneLoader->checkPosY = posY;

}

/**
 * @brief Sets the current player life value in the scene loader.
 * @param currentLife The life value to set.
 */
void SetCurrentLife(int currentLife){
    Game::GetInstance().sceneManager->sceneLoader->actualLife = currentLife;

}


/**
 * @brief Updates a TextComponent with the player's current life count.
 * @param entity The entity with the TextComponent.
 */
void SetLifeText(Entity entity){
    std::string life = std::to_string(Game::GetInstance().sceneManager->sceneLoader->actualLife);
    if (life == "0"){
        life = "5";
    }
    entity.GetComponent<TextComponent>().text = life;
}

/**
 * @brief Gets the current health value of an entity.
 * @param self The entity to check.
 * @return Integer value representing health.
 */
int GetHealth(Entity self){
   auto& health = self.GetComponent<HealthComponent>();
   return health.health;
    
}

/**
 * @brief Gets the velocity of an entity as a tuple.
 * @param entity The entity to check.
 * @return A tuple of (x, y) velocity.
 */
std::tuple<int, int> GetVelocity(Entity entity){
    const auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    return {
        static_cast<int>(rigidbody.velocity.x),
        static_cast<int>(rigidbody.velocity.y),
    };
}

/**
 * @brief Sets the velocity of an entity.
 * @param entity The entity to modify.
 * @param x Velocity in the x-axis.
 * @param y Velocity in the y-axis.
 */
void SetVelocity(Entity entity, float x, float y){
    auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    rigidbody.velocity.x = x;
    rigidbody.velocity.y = y;
}

/**
 * @brief Adds a force to an entity.
 * @param entity The entity to modify.
 * @param x Force in the x-axis.
 * @param y Force in the y-axis.
 */
void AddForce(Entity entity, float x, float y){
    auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    rigidbody.sumForces += glm::vec2(x, y);
}

/**
 * @brief Gets the accumulated forces of an entity.
 * @param entity The entity to check.
 * @return A tuple of (x, y) forces.
 */
std::tuple<int, int> GetSumForces(Entity entity) {
    const auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
    std::cout << "Sum Forces: " << rigidbody.sumForces.x << ", " << rigidbody.sumForces.y << std::endl;
    return {
        static_cast<int>(rigidbody.sumForces.x),
        static_cast<int>(rigidbody.sumForces.y)
    };
}

/**
 * @brief Gets the tag of an entity.
 * @param entity The entity to inspect.
 * @return The tag as a string.
 */
std::string GetTag(Entity entity){
    return entity.GetComponent<TagComponent>().tag;
}

/**
 * @brief Sets the horizontal flip status of an entity's sprite.
 * @param entity The entity to modify.
 * @param flip Whether to flip the sprite.
 */
void FlipSprite(Entity entity, bool flip){
    auto& sprite = entity.GetComponent<SpriteComponent>();
    sprite.flip = flip;
}

/**
 * @brief Gets the position of an entity.
 * @param entity The entity to inspect.
 * @return Tuple (x, y) with position.
 */
std::tuple<int, int> GetPosition(Entity entity){
    const auto& transform = entity.GetComponent<TransformComponent>();
    return {
        static_cast<int>(transform.position.x),
        static_cast<int>(transform.position.y),
    };
}

/**
 * @brief Sets the position of an entity.
 * @param entity The entity to move.
 * @param x New x coordinate.
 * @param y New y coordinate.
 */
void SetPosition(Entity entity, int x, int y){
    auto& transform = entity.GetComponent<TransformComponent>();
    transform.position.x = x;
    transform.position.y = y;

}

/**
 * @brief Gets the size of an entity considering sprite size and scale.
 * @param entity The entity to check.
 * @return Tuple (width, height).
 */
std::tuple<int, int> GetSize(Entity entity){
    const auto& sprite = entity.GetComponent<SpriteComponent>();
    const auto& transform = entity.GetComponent<TransformComponent>();

    int width = sprite.width * transform.scale.x;
    int height = sprite.height * transform.scale.y;

    return {width, height};

}

/**
 * @brief Transitions to the specified scene.
 * @param sceneName The name of the next scene.
 */
void GoToScene(const std::string& sceneName){
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}

/**
 * @brief Gets the unique ID of an entity.
 * @param entity The entity.
 * @return Integer ID.
 */
int GetId(Entity entity){
    return entity.GetId();
}

//Time


/**
 * @brief Gets the delta time of the current scene from SceneTimeSystem.
 * @return Delta time in milliseconds.
 */
int GetDeltaTime(){
    int time = Game::GetInstance().registry->GetSystem<SceneTimeSystem>().GetDeltaTime();
    return time;
}

/**
 * @brief Gets the total scene time from SceneTimeSystem.
 * @return Scene time in milliseconds.
 */
int GetTime(){
    int time = Game::GetInstance().registry->GetSystem<SceneTimeSystem>().GetSceneTime();
    return time;
}

/**
 * @brief Sets a timer text value in a TextComponent from the given time.
 * @param entity The target entity.
 * @param newTime New time value in milliseconds.
 */
void SetTimer(Entity entity, int newTime){
    std::string timer = std::to_string(newTime / 1000);
    entity.GetComponent<TextComponent>().text = timer;
}

/**
 * @brief Adds the points from an enemy to the player and updates the score UI.
 * @param enemy The defeated entity.
 * @param player The player entity gaining points.
 */
void AddPoints(Entity enemy, Entity player){
    auto& health = enemy.GetComponent<HealthComponent>();
    auto& healthPlayer = player.GetComponent<HealthComponent>();


    int puntaje = healthPlayer.points += health.points;
    std::ostringstream oss;
    oss << std::setw(8) << std::setfill('0') << puntaje;


    auto& text = player.GetComponent<TextComponent>();
    text.text = oss.str();
}




#endif