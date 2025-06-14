#ifndef SCRIPTCOMPONENT_HPP
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>

struct ScriptComponent {
    sol::function update;
    sol::function onClick;
    sol::function onCollision;

    ScriptComponent(sol::function onCollision = sol::lua_nil,sol::function update = sol::lua_nil, 
    sol::function onClick = sol::lua_nil){
        this->update = update;
        this->onClick = onClick;
        this->onCollision = onCollision;
    }
};
#endif