#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <SDL2/SDL.h>
#include <tinyxml2/tinyxml2.h>

#include <memory>
#include <sol/sol.hpp>
#include <string>
#include "../AnimationManager/AnimationManager.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../ECS/ECS.hpp"
/**
 * @struct TileSetInfo
 * @brief Stores information about a tileset used in a map.
 */
struct TileSetInfo {
    int firstgid;
    int columns;
    int tileWidth;
    int tileHeight;
    std::string textureId;
};
/**
 * @class SceneLoader
 * @brief Handles loading of scenes including assets, entities, maps, layers, and Lua scripts.
 */
class SceneLoader {
  private:
  std::vector<TileSetInfo> tilesets;
    /**
     * @brief Loads animations from a Lua table into the AnimationManager.
     */
  void LoadAnimations(const sol::table& animations
  , std::unique_ptr<AnimationManager>& animationManager);
    /**
     * @brief Loads sprite definitions from a Lua table into the AssetManager.
     */
  void LoadSprites(SDL_Renderer* render, const sol::table& sprites
  , std::unique_ptr<AssetManager>& assetManager);
    /**
     * @brief Loads fonts from a Lua table into the AssetManager.
     */
   void LoadFonts(const sol::table& fonts
  , std::unique_ptr<AssetManager>& assetManager);
    /**
     * @brief Loads keyboard action mappings from Lua into the ControllerManager.
     */
  void LoadKeys(const sol::table& keys, std::unique_ptr<ControllerManager>& 
  controllerManager);
    /**
     * @brief Loads clickable buttons from Lua into the ControllerManager.
     */
  void LoadButtons(const sol::table& buttons, std::unique_ptr<ControllerManager>& 
  controllerManager);
    /**
     * @brief Loads entities from Lua into the ECS Registry.
     */
  void LoadEntities(sol::state& lua, const sol::table& entites, 
  std::unique_ptr<Registry>& registry);
    /**
     * @brief Loads a tile-based map from Lua into the ECS Registry.
     */
  void LoadMap(sol::state& lua, const sol::table map, std::unique_ptr<Registry>& registry);
    /**
     * @brief Loads a single layer of tiles from the TMX map into the ECS Registry.
     */
  void LoadLayer(std::unique_ptr<Registry>& registry,
    tinyxml2::XMLElement* layer, int mWidth);
    /**
     * @brief Loads collision objects from the TMX object group into the ECS Registry.
     */  
  void LoadColliders(sol::state& lua, std::unique_ptr<Registry>& registry, tinyxml2::XMLElement* objectGroup);
     /**
     * @brief Loads music assets from Lua table into the AssetManager.
     * @param musicTable Lua table containing music definitions.
     * @param assetManager Unique pointer to the AssetManager instance.
     */
  void LoadMusic(const sol::table& musicTable, std::unique_ptr<AssetManager>& assetManager);
  public:
  float checkPosX = 32;
  float checkPosY = 32;
  int actualLife = 0;
      /**
     * @brief Constructs a SceneLoader instance.
     */
  SceneLoader();
      /**
     * @brief Destructor for SceneLoader.
     */
  ~SceneLoader();
      /**
     * @brief Loads a scene from a given file path using Lua definitions and TMX maps.
     * 
     * @param scenePath Path to the Lua scene file.
     * @param lua Lua state to execute scripts.
     * @param animationManager Pointer to the AnimationManager.
     * @param assetManager Pointer to the AssetManager.
     * @param controllerManager Pointer to the ControllerManager.
     * @param registry Pointer to the ECS Registry.
     * @param renderer SDL Renderer used for drawing.
     */
  void LoadScene(const std::string& scenePath, sol::state& lua
  , std::unique_ptr<AnimationManager>& animationManager
  , std::unique_ptr<AssetManager>& assetManager
  , std::unique_ptr<ControllerManager>& controllerManager
  , std::unique_ptr<Registry>& registry, SDL_Renderer* renderer);
};

#endif