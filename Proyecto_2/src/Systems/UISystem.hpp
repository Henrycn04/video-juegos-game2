#ifndef UISYSTEM_HPP
#define UISYSTEM_HPP

#include <SDL2/SDL.h>

#include <memory>
#include <string>
#include <iostream>

#include "../Components/ClickableComponent.hpp"

#include "../Components/ScriptComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/ClickEvent.hpp"


/**
 * @class UISystem
 * @brief System that handles user interface interaction such as mouse clicks on UI elements.
 * 
 * This system listens for click events and checks if the mouse coordinates intersect
 * with any clickable UI entities. If so, it triggers the corresponding Lua script.
 */
class UISystem : public System {
    public:
    /**
     * @brief Constructs the UISystem and sets required components.
     * 
     * Requires ClickableComponent, TextComponent, and TransformComponent for operation.
     */
    UISystem(){
        RequireComponent<ClickableComponent>();
        RequireComponent<TextComponent>();
        RequireComponent<TransformComponent>();
    }
    /**
     * @brief Subscribes the system to listen for click events.
     * 
     * @param eventManager Reference to the EventManager to subscribe with.
     */
    void SubscribeToClickEvent(std::unique_ptr<EventManager>& eventManager){
        eventManager->SubscribeToEvent<ClickEvent, UISystem>(this, 
        &UISystem::OnClickEvent);
    }
    /**
     * @brief Callback function triggered when a ClickEvent occurs.
     * 
     * Checks if the click coordinates fall within the bounding box of any UI element (based on its text dimensions).
     * If the clicked entity has a ScriptComponent with a valid `onClick` Lua function, that function is called.
     * 
     * @param e The ClickEvent containing mouse position data.
     */
    void OnClickEvent(ClickEvent& e){
        for(auto entity : GetSystemEntities()){
            const auto& text = entity.GetComponent<TextComponent>();
            const auto& transform = entity.GetComponent<TransformComponent>();

            if(transform.position.x < e.posX
            && e.posX < transform.position.x + text.width
            && transform.position.y < e.posY
            && e.posY < transform.position.y + text.height){
             if(entity.HasComponent<ScriptComponent>()){
                const auto& script = entity.GetComponent<ScriptComponent>();
                if(script.onClick != sol::nil){
                    script.onClick();
                }
             }
            }
        }
    }
};

#endif