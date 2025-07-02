#ifndef RENDERTEXTSYSTEM_HPP
#define RENDERTEXTSYSTEM_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>

#include "../AssetManager/AssetManager.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../ECS/ECS.hpp"

class RenderTextSystem : public System {
 public:
    RenderTextSystem(){
        RequireComponent<TextComponent>();
        RequireComponent<TransformComponent>();
    }

    void Update(SDL_Renderer* renderer, const std::unique_ptr<AssetManager>& assetManager, const SDL_Rect& camera){
        for(auto entity : GetSystemEntities()){
            auto& text = entity.GetComponent<TextComponent>();
            auto& transform = entity.GetComponent<TransformComponent>();
            
            SDL_Surface* surface = TTF_RenderText_Blended(
                assetManager->GetFont(text.fontId), text.text.c_str(), text.color);
            
            text.width = surface->w;
            text.height = surface->h;
            
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            
            SDL_Rect dstRect;
            bool puntaje = false;
            if (entity.GetComponent<TagComponent>().tag == "player") {
                puntaje = entity.GetComponent<HealthComponent>().isPlayer;
            }

            if (puntaje) {
                // Texto para el jugador - Se muestra fijo en la pantalla (UI)
                dstRect = {
                    static_cast<int>(425.0),
                    static_cast<int>(5.0),
                    text.width * static_cast<int>(transform.scale.x),
                    text.height * static_cast<int>(transform.scale.y)
                };
            } else if (text.isStatic) {
                // Texto estático (UI) - No se ve afectado por la cámara
                dstRect = {
                    static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    text.width * static_cast<int>(transform.scale.x),
                    text.height * static_cast<int>(transform.scale.y)
                };
            } else {
                // Texto dinámico - Se ve afectado por la cámara
                dstRect = {
                    static_cast<int>(transform.position.x - camera.x),
                    static_cast<int>(transform.position.y - camera.y),
                    text.width * static_cast<int>(transform.scale.x),
                    text.height * static_cast<int>(transform.scale.y)
                };
            }

            
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
            SDL_DestroyTexture(texture);
        }
    }
};
#endif