#ifndef CONTROLLERMANAGER_HPP
#define CONTROLLERMANAGER_HPP

#include <SDL2/SDL.h>

#include <map>
#include <string>
#include <tuple>

/**
 * @class ControllerManager
 * @brief Manages keyboard and mouse input actions and states.
 *
 * This class tracks key and mouse button presses, maps them to named actions,
 * and provides querying functions for input states and mouse position.
 */
class ControllerManager {
 private:
/// Maps action names to keyboard key codes.
  std::map<std::string, int> actionKeyName;
/// Tracks which keyboard keys are currently pressed.
  std::map<int, bool> keyDown;
/// Maps mouse button names to SDL mouse button codes.
  std::map<std::string, int> mouseButtonName;
/// Tracks which mouse buttons are currently pressed.
  std::map<int, bool>mouseButtonDown;
/// Current mouse X position.
  int mousePosX;
/// Current mouse Y position.
  int mousePosY;

 public:
  /**
   * @brief Constructs a new ControllerManager instance.
   */
  ControllerManager();
  /**
   * @brief Destroys the ControllerManager instance.
   */
  ~ControllerManager();

  /**
   * @brief Clears all registered actions and input states.
   */
  void Clear();

  //Keyboard

    /**
   * @brief Registers a keyboard key code to an action name.
   * 
   * @param action Name of the action.
   * @param keyCode SDL key code to associate with the action.
   */
  void AddActionKey(const std::string& action, int keyCode);
    /**
   * @brief Marks a keyboard key as pressed.
   * 
   * @param keyCode SDL key code of the key pressed.
   */
  void KeyDown(int keyCode);
  /**
   * @brief Marks a keyboard key as released.
   * 
   * @param keyCode SDL key code of the key released.
   */
  void KeyUp (int keyCode);
  /**
   * @brief Checks if an action is currently activated (key pressed).
   * 
   * @param action The action name to check.
   * @return true if the key mapped to the action is pressed, false otherwise.
   */
  bool IsActionActivated(const std::string& action);

  // Mouse

    /**
   * @brief Registers a mouse button code to a named button.
   * 
   * @param name Name of the mouse button action.
   * @param buttonCode SDL mouse button code.
   */
  void AddMouseButton(const std::string& name, int buttonCode);
  /**
   * @brief Marks a mouse button as pressed.
   * 
   * @param buttonCode SDL mouse button code pressed.
   */ 
  void MouseButtonDown(int buttonCode);
  /**
   * @brief Marks a mouse button as released.
   * 
   * @param buttonCode SDL mouse button code released.
   */
  void MouseButtonUp(int buttonCode);
  /**
   * @brief Checks if a named mouse button is currently pressed.
   * 
   * @param name Name of the mouse button action.
   * @return true if the mouse button is pressed, false otherwise.
   */
  bool IsMouseButtonDown(const std::string& name);

    /**
   * @brief Sets the current mouse position.
   * 
   * @param x Mouse X coordinate.
   * @param y Mouse Y coordinate.
   */
  void SetMousePosition(int x, int y);

  /**
   * @brief Gets the current mouse position.
   * 
   * @return A tuple containing mouse X and Y coordinates.
   */
  std::tuple<int, int> GetMousePosition();

};
#endif