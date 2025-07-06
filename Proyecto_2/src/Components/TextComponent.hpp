#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include <SDL2/SDL.h>

#include <string>

/**
 * @struct TextComponent
 * @brief Represents text to be rendered on screen with font and color properties.
 *
 * This component stores the text string, font identifier, color,
 * dimensions, and whether the text is static or dynamic.
 */
struct TextComponent{
    /// The text string to display.
    std::string text;
    /// Identifier of the font used for rendering the text.
    std::string fontId;
    /// Color of the text.
    SDL_Color color;
    /// Width of the rendered text in pixels.
    int width;
    /// Height of the rendered text in pixels.
    int height;
    /// Flag indicating if the text is static (does not change).
    bool isStatic;

    /**
     * @brief Constructs a TextComponent with optional parameters.
     * 
     * @param text The text string (default empty).
     * @param fontId The font identifier (default empty).
     * @param r Red component of text color (default 0).
     * @param g Green component of text color (default 0).
     * @param b Blue component of text color (default 0).
     * @param a Alpha (opacity) component of text color (default 0).
     * @param isStatic Whether the text is static (default false).
     */
    TextComponent(const std::string& text="", const std::string& fontId = "",
    u_char r = 0, u_char g = 0, u_char b = 0, u_char a = 0, bool isStatic = false){
     this->text = text;
     this->fontId = fontId;
     this->color.r = r;
     this->color.g = g;
     this->color.b = b;
     this->color.a = a;
     this->width = 0;
     this->height = 0;
        this->isStatic = isStatic;
    }
};
#endif