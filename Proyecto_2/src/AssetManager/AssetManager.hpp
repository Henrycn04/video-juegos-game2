#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

class AssetManager{
 private:
  std::map<std::string, SDL_Texture*> textures;
  std::map<std::string, TTF_Font*> fonts;
    /// Map of music IDs to Mix_Music pointers.
  std::map<std::string, Mix_Music*> musics;

  /// Currently playing music.
  Mix_Music* currentMusic = nullptr;

 public:
  AssetManager();
  ~AssetManager();

  void ClearAssets();

  void AddTexture(SDL_Renderer* renderer, const std::string& textureId
    , const std::string& filePath);

  SDL_Texture* GetTexture(const std::string& textureId);

  void AddFont(const std::string& fontId, const std::string& filePath
  , int fontSize);
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