  #include "AssetManager.hpp"
  #include <SDL2/SDL_image.h>
  #include <iostream>
  
  AssetManager::AssetManager(){
      std::cout<< "[AssetManager] Se ejecuta constructor" << std::endl;
  }
  AssetManager::~AssetManager(){
    std::cout<< "[AssetManager] Se ejecuta destructor" << std::endl;
  }

  void AssetManager::ClearAssets(){
    for (auto texture : textures){
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();
    for (auto font: fonts){
      TTF_CloseFont(font.second);
    }
    fonts.clear();
     ClearMusic();
    std::cout << "LIMPIA ASSETS: " << std::endl;

  }

  void AssetManager::AddTexture(SDL_Renderer* renderer, const std::string& textureId
    , const std::string& filePath){
        SDL_Surface* surface = IMG_Load(filePath.c_str());
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        textures.emplace(textureId, texture);
    }

  SDL_Texture* AssetManager::GetTexture(const std::string& textureId){
    return textures[textureId];
  }

 void AssetManager::AddFont(const std::string& fontId, const std::string& filePath
  , int fontSize){
    TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
    if(font == NULL){
      std::string error = TTF_GetError();
      std::cerr << "[AssetManager]"<< std::endl;
      return;
    }
    fonts.emplace(fontId, font);
  }

TTF_Font* AssetManager::GetFont(const std::string& fontId){
  return fonts[fontId];
}
void AssetManager::LoadMusic(const std::string& musicId, const std::string& filePath) {
    Mix_Music* music = Mix_LoadMUS(filePath.c_str());
    if (!music) {
        SDL_Log("Error cargando música %s: %s", filePath.c_str(), Mix_GetError());
        return;
    }
    musics[musicId] = music;
}

void AssetManager::PlayMusic(const std::string& musicId, int loops) {
    auto it = musics.find(musicId);
    if (it != musics.end()) {
        if (Mix_PlayingMusic()) {
            Mix_HaltMusic();
        }
        currentMusic = it->second;
        Mix_PlayMusic(currentMusic, loops);
    }
}

void AssetManager::StopMusic() {
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
}

void AssetManager::ClearMusic() {
    StopMusic();
    for (auto& pair : musics) {
        Mix_FreeMusic(pair.second);
    }
    musics.clear();
    currentMusic = nullptr;
}

void AssetManager::PauseMusic() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}

void AssetManager::ResumeMusic() {
    if (Mix_PausedMusic()) {
      Mix_ResumeMusic();
  }
}
   
   