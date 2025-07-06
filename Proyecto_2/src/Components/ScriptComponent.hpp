#ifndef SCRIPTCOMPONENT_HPP
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>

/**
 * @struct ScriptComponent
 * @brief Holds Lua script functions for entity behaviors.
 *
 * This component stores Lua functions for updating logic,
 * handling click events, and processing collision events.
 */
struct ScriptComponent {
    /// Lua function called every update cycle.
    sol::function update;
    /// Lua function called when the entity is clicked.
    sol::function onClick;
    /// Lua function called when the entity collides with another.
    sol::function onCollision;
    /**
     * @brief Constructs a ScriptComponent with optional Lua functions.
     * 
     * @param onCollision Lua function to call on collision (default: nil).
     * @param update Lua function to call on update (default: nil).
     * @param onClick Lua function to call on click (default: nil).
     */
    ScriptComponent(sol::function onCollision = sol::lua_nil,sol::function update = sol::lua_nil, 
    sol::function onClick = sol::lua_nil){
        this->update = update;
        this->onClick = onClick;
        this->onCollision = onCollision;
    }
};
#endif