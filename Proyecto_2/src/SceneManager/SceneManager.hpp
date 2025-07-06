#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <map>
#include <memory>
#include <sol/sol.hpp>
#include <string>

#include "SceneLoader.hpp"
/**
 * @class SceneManager
 * @brief Manages the loading, transition, and state of game scenes.
 */
class SceneManager{
 private:
  std::map<std::string, std::string> scenes;
  std::string nextScene;
  bool isSceneRunning = false;

public:
std::unique_ptr<SceneLoader> sceneLoader;
    /**
     * @brief Constructs a SceneManager instance.
     */
 SceneManager();
    /**
     * @brief Destroys the SceneManager instance.
     */
 ~SceneManager();

    /**
     * @brief Loads scene data from a Lua script.
     * @param path Path to the Lua script defining the scene.
     * @param lua The Lua state used to execute the script.
     */
 void LoadSceneFromScript(const std::string& path, sol::state& lua);
 
    /**
     * @brief Loads the scene defined in the nextScene field using the SceneLoader.
     */
 void LoadScene();
    /**
     * @brief Retrieves the name of the next scene to load.
     * @return A string containing the next scene name.
     */
 std::string GetNextScene() const;
     /**
     * @brief Sets the name of the next scene to load.
     * @param nextScene Name of the next scene.
     */
 void SetNextScene(const std::string& nextScene);
    /**
     * @brief Checks if a scene is currently running.
     * @return True if a scene is running, false otherwise.
     */
 bool IsSceneRunning() const;
     /**
     * @brief Marks that a scene has started running.
     */
 void StartScene();
     /**
     * @brief Marks that the current scene has stopped.
     */
 void StopScene();
};
#endif