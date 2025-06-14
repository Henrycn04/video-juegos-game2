#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <SDL2/SDL.h>
#include <tinyxml2/tinyxml2.h>

#include <memory>
#include <sol/sol.hpp>
#include <string>

#include "../AssetManager/AssetManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../ECS/ECS.hpp"

class SceneLoader {
  private:
  void LoadSprites(SDL_Renderer* render, const sol::table& sprites
  , std::unique_ptr<AssetManager>& assetManager);

   void LoadFonts(const sol::table& fonts
  , std::unique_ptr<AssetManager>& assetManager);

  void LoadKeys(const sol::table& keys, std::unique_ptr<ControllerManager>& 
  controllerManager);

  void LoadButtons(const sol::table& buttons, std::unique_ptr<ControllerManager>& 
  controllerManager);

  void LoadEntities(sol::state& lua, const sol::table& entites, 
  std::unique_ptr<Registry>& registry);
  void LoadMap(const sol::table map, std::unique_ptr<Registry>& registry);
  void LoadLayer(std::unique_ptr<Registry>& registry, tinyxml2::XMLElement* layer, int tWidth, 
  int tHeight, int mWidth, const std::string& tileSet, int columns);
  void LoadCollider(std::unique_ptr<Registry>& registry, tinyxml2::XMLElement* objectGroup);

  public:
  SceneLoader();
  ~SceneLoader();
  void LoadScene(const std::string& scenePath, sol::state& lua
  , std::unique_ptr<AssetManager>& assetManager
  , std::unique_ptr<ControllerManager>& controllerManager
  , std::unique_ptr<Registry>& registry, SDL_Renderer* renderer);
};

#endif