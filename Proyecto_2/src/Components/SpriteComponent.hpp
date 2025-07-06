#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include <SDL2/SDL.h>

#include <string>

/**
 * @struct SpriteComponent
 * @brief Represents the graphical sprite of an entity.
 *
 * This component stores the texture identifier, size, source rectangle for rendering,
 * and whether the sprite should be flipped horizontally.
 */
struct SpriteComponent {
    /// Identifier of the texture used for this sprite.
    std::string textureId;
    /// Width of the sprite in pixels.
    int width;
    /// Height of the sprite in pixels.
    int height;
    /// Source rectangle within the texture for rendering.
    SDL_Rect srcRect;
    /// Flag indicating if the sprite should be flipped horizontally.
    bool flip = false;

    /**
     * @brief Constructs a SpriteComponent with optional parameters.
     * 
     * @param textureId Texture identifier string (default: "none").
     * @param width Width of the sprite (default: 0).
     * @param height Height of the sprite (default: 0).
     * @param srcRectX X coordinate of the source rectangle in the texture (default: 0).
     * @param srcRectY Y coordinate of the source rectangle in the texture (default: 0).
     */
    SpriteComponent(const std::string& textureId = "none", int width = 0
    , int height = 0, int srcRectX = 0, int srcRectY = 0){
        this->textureId = textureId;
        this->width = width;
        this->height = height;
        this->srcRect = {srcRectX, srcRectY, width, height};
    }
};

#endif