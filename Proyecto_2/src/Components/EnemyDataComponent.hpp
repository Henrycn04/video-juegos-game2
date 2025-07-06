#ifndef ENEMYDATACOMPONENT_HPP
#define ENEMYDATACOMPONENT_HPP

/**
 * @struct EnemyDataComponent
 * @brief Stores data specific to enemy behavior and state.
 *
 * This component holds various parameters related to enemy types, movement,
 * jumping ability, attack cooldowns, and life status.
 */
struct EnemyDataComponent 
{
    /// Enemy type identifier (valid values: 1 to 4).
    int enemy_type = 1;
    
    /// Flag indicating if the enemy is alive (true) or dead (false).  
    bool is_not_dead = true;
    
    /// Movement speed of the enemy (units per second).
    float player_speed = 1.0f * 64.0f;
    /// Generic timer used for internal enemy logic.
    float timer = 0.0f;
    /// Direction of movement (1 = right, -1 = left).
    int direction = 1; 
    
    /// Indicates whether the enemy can jump.
    bool can_jump = false;
    /// Force applied when the enemy jumps.
    float jump_force = -700.0f * 64.0f;
    /// Tracks the previous jump state.
    bool prev_jump = false;
    
    /// Time elapsed since the last arrow was shot (for ranged enemies).
    float last_arrow_time = 0.0f;
    /// Cooldown time between arrows in milliseconds.
    float arrow_cooldown = 10000.0f;
    

    /**
     * @brief Default constructor.
     */
    EnemyDataComponent() = default;
    
    /**
     * @brief Constructs an EnemyDataComponent with a specified type and initializes its data.
     * @param type The enemy type (1 to 4).
     */   
    EnemyDataComponent(int type) : enemy_type(type)
    {
        InitializeByType();
    }
    

    /**
     * @brief Initializes enemy properties based on the enemy_type.
     * 
     * Enemy types:
     * - 1: Basic enemy 
     * - 2: Ranged enemy with arrow cooldown
     * - 3: Jump enemy
     * - 4: Flying enemy
     * - Default: Same as type 1.
     */
    void InitializeByType()
    {
        switch(enemy_type)
        {
            case 1: // Enemy01
                player_speed = 1.0f * 64.0f;
                timer = 0.0f;
                direction = 1;
                is_not_dead = true;
                break;
                
            case 2: // Enemy02
                last_arrow_time = 0.0f;
                arrow_cooldown = 10000.0f;
                is_not_dead = true;
                break;
                
            case 3: // Enemy03
                can_jump = false;
                jump_force = -700.0f * 64.0f;
                prev_jump = false;
                player_speed = 0.5f * 64.0f;
                timer = 0.0f;
                direction = 1;
                is_not_dead = true;
                break;
                
            case 4: // Enemy04
                player_speed = 1.0f * 64.0f;
                timer = 0.0f;
                direction = 1;
                is_not_dead = true;
                break;
                
            default:
                player_speed = 1.0f * 64.0f;
                timer = 0.0f;
                direction = 1;
                is_not_dead = true;
                break;
        }
    }
};

#endif // ENEMYDATACOMPONENT_HPP