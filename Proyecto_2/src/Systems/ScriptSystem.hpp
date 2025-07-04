#ifndef SCRIPTSYSTEM_HPP
#define SCRIPTSYSTEM_HPP

#include <memory>
#include <sol/sol.hpp>

#include "../Binding/LuaBinding.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../ECS/ECS.hpp"
class ScriptSystem : public System {
 public:
  ScriptSystem(){
    RequireComponent<ScriptComponent>();
  }

  void CreateLuaBinding(sol::state& lua){
    // Classes
    lua.new_usertype<Entity>("entity");

    // Functions
    lua.set_function("change_animation", ChangeAnimation);
    lua.set_function("get_ticks", GetTicks);


    lua.set_function("create_arrow", CreateArrow);
    lua.set_function("is_action_activated", IsActionActivated);
    lua.set_function("get_velocity", GetVelocity);
    lua.set_function("set_velocity", SetVelocity);
    lua.set_function("do_damage", DoDamage);
    lua.set_function("add_force", AddForce);
    lua.set_function("get_sum_forces", GetSumForces);
    lua.set_function("go_to_scene", GoToScene);
    lua.set_function("flip_sprite", FlipSprite);
    lua.set_function("get_tag", GetTag);
     lua.set_function("get_id", GetId);
    lua.set_function("get_position", GetPosition);
    lua.set_function("set_position", SetPosition);
    lua.set_function("get_size", GetSize);
    lua.set_function("left_collision", LeftCollision);
    lua.set_function("right_collision", RightCollision);
    lua.set_function("top_collision", TopCollision);
    lua.set_function("bottom_collision", BottomCollision);
    lua.set_function("deactivate_collisions", DeactivateCollisions);
     lua.set_function("get_delta_time", GetDeltaTime);
    lua.set_function("get_time", GetTime);
    lua.set_function("set_timer", SetTimer);
    lua.set_function("kill_entity", KillEntity);
    lua.set_function("add_points", AddPoints);
    lua.set_function("get_health", GetHealth);
    lua.set_function("set_check", SetCheckPosition);
    lua.set_function("set_current_life", SetCurrentLife);
    lua.set_function("set_life_text", SetLifeText);
    lua.set_function("do_damage_to_self", DoDamageToSelf);
  }


void Update(sol::state& lua) {
    for (auto entity : GetSystemEntities()) {
        const auto& script = entity.GetComponent<ScriptComponent>();

        if (script.update.valid() && script.update != sol::lua_nil) {
            lua["this"] = entity;

            sol::protected_function update_fn = script.update;
            sol::protected_function_result result = update_fn();

            if (!result.valid()) {
                sol::error err = result;
                std::cerr << "[Lua Error] " << err.what() << std::endl;
                continue; 
            }
        } 
    }
}
};
#endif