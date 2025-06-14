#ifndef TAGCOMPONENT_HPP
#define TAGCOMPONENT_HPP
#include <string>

struct TagComponent {
    std::string tag;

    TagComponent(const std::string& tag = ""){
        this->tag = tag;
    }
};
#endif