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
  }


  void Update(sol::state& lua){
    for(auto entity : GetSystemEntities()){
        const auto& script = entity.GetComponent<ScriptComponent>();

        if(script.update != sol::lua_nil){
            lua["this"] = entity;
            script.update();
        }
    }
  }
};
#endif