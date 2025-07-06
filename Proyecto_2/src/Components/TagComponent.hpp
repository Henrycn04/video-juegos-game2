#ifndef TAGCOMPONENT_HPP
#define TAGCOMPONENT_HPP
#include <string>


/**
 * @struct TagComponent
 * @brief Provides a simple string tag identifier for an entity.
 *
 * This component is used to assign a textual tag or label
 * to an entity for identification or categorization purposes.
 */
struct TagComponent {
    /// The string tag of the entity.
    std::string tag;

    /**
     * @brief Constructs a TagComponent with an optional tag.
     * 
     * @param tag The tag string (default is an empty string).
     */
    TagComponent(const std::string& tag = ""){
        this->tag = tag;
    }
};
#endif