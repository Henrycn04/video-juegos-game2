#ifndef CLICKABLECOMPONENT_HPP
#define CLICKABLECOMPONENT_HPP

/**
 * @struct ClickableComponent
 * @brief Represents an entity that can respond to mouse click events.
 *
 * This component is used to mark entities as interactive via mouse clicks.
 * It tracks whether the entity is currently clicked.
 */
struct ClickableComponent {
    /// Indicates whether the entity has been clicked.
    bool isClicked;
    /**
     * @brief Constructs a ClickableComponent with default state.
     * 
     * Initializes the click state to false.
     */
    ClickableComponent(){
        isClicked = false;
    }
};
#endif