#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

/**
 * @class AssetManager
 * @brief Manages game assets such as textures, fonts, and music.
 *
 * This class provides functionality to load, store, and retrieve various
 * media assets used in the game, including textures (SDL_Texture), fonts (TTF_Font),
 * and music (Mix_Music). It also keeps track of the currently playing music.
 */

class AssetManager{
 private:
  /// Map of texture IDs to SDL_Texture pointers.
  std::map<std::string, SDL_Texture*> textures;
  /// Map of font IDs to TTF_Font pointers.
  std::map<std::string, TTF_Font*> fonts;
    /// Map of music IDs to Mix_Music pointers.
  std::map<std::string, Mix_Music*> musics;

  /// Currently playing music.
  Mix_Music* currentMusic = nullptr;

 public:
     /**
     * @brief Constructs an AssetManager.
     */
  AssetManager();

      /**
     * @brief Destroys the AssetManager and releases all assets.
     */
  ~AssetManager();

      /**
     * @brief Clears all loaded assets (textures, fonts, music).
     */
  void ClearAssets();

      /**
     * @brief Loads and stores a texture.
     *
     * @param renderer The SDL renderer used to create the texture.
     * @param textureId A unique identifier for the texture.
     * @param filePath Path to the texture image file.
     */
  void AddTexture(SDL_Renderer* renderer, const std::string& textureId
    , const std::string& filePath);

  
    /**
     * @brief Retrieves a previously loaded texture.
     *
     * @param textureId The ID of the texture to retrieve.
     * @return Pointer to the SDL_Texture, or nullptr if not found.
     */
  SDL_Texture* GetTexture(const std::string& textureId);

      /**
     * @brief Loads and stores a font.
     *
     * @param fontId A unique identifier for the font.
     * @param filePath Path to the font file (e.g., .ttf).
     * @param fontSize The size of the font to load.
     */
  void AddFont(const std::string& fontId, const std::string& filePath
  , int fontSize);

      /**
     * @brief Retrieves a previously loaded font.
     *
     * @param fontId The ID of the font to retrieve.
     * @return Pointer to the TTF_Font, or nullptr if not found.
     */
  TTF_Font* GetFont(const std::string& fontId);

    /**
   * @brief Loads a music track from file.
   * 
   * @param musicId The unique ID to associate with the music.
   * @param filePath The path to the music file.
   */
  void LoadMusic(const std::string& musicId, const std::string& filePath);

  /**
   * @brief Plays a loaded music track.
   * 
   * @param musicId The ID of the music to play.
   * @param loops Number of times the music should loop. Default is -1 (infinite).
   */
  void PlayMusic(const std::string& musicId, int loops = -1);

  /**
   * @brief Stops the currently playing music.
   */
  void StopMusic();

  /**
   * @brief Resumes paused music playback.
   */
  void ResumeMusic();

  /**
   * @brief Pauses the currently playing music.
   */
  void PauseMusic();

  /**
   * @brief Frees all loaded music assets.
   */
  void ClearMusic();
   
};
#endif