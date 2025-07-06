#ifndef CLICKEVENT_HPP
#define CLICKEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

/**
 * @class ClickEvent
 * @brief Represents a mouse click event, including button and position data.
 *
 * This event can be emitted and handled to react to mouse click actions
 * in the ECS system. It inherits from the base Event class.
 */
class ClickEvent : public Event {
    public:
    /**
     * @brief Mouse button code (e.g., SDL_BUTTON_LEFT).
     */
    int buttonCode;
    /**
     * @brief X position of the mouse when the click occurred.
     */
    int posX;
    /**
     * @brief Y position of the mouse when the click occurred.
     */
    int posY;
    /**
     * @brief Constructs a ClickEvent with specified button code and mouse position.
     * @param buttonCode Integer representing the mouse button.
     * @param posX X coordinate of the click.
     * @param posY Y coordinate of the click.
     */
    ClickEvent(int buttonCode = 0, int posX = 0, int posY = 0){
        this->buttonCode = buttonCode;
        this->posX = posX;
        this->posY = posY;
    }
};

#endif