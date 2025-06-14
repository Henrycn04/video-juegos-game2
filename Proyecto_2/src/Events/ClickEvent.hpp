#ifndef CLICKEVENT_HPP
#define CLICKEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

class ClickEvent : public Event {
    public:
    int buttonCode;
    int posX;
    int posY;

    ClickEvent(int buttonCode = 0, int posX = 0, int posY = 0){
        this->buttonCode = buttonCode;
        this->posX = posX;
        this->posY = posY;
    }
};

#endif