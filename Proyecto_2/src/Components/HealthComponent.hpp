#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

#include <ctime>


/**
 * @struct HealthComponent
 * @brief Manages health, damage, healing, and invincibility states for an entity.
 *
 * This component tracks the current and maximum health of an entity,
 * whether it is a player or an enemy, points awarded for enemies,
 * and handles damage with optional temporary invincibility after being hit.
 */
struct HealthComponent {
    /// Current health value.
    int health;
    /// Maximum health value.
    int maxHealth;
    /// Flag indicating if the entity is a player.
    bool isPlayer;
    /// Flag indicating if the entity is an enemy.
    bool isEnemy;
    /// Points awarded (used mainly for enemies).
    int points;
    /// Timestamp of the last time damage was taken.
    time_t lastDamageTaken;
    /// Duration of temporary invincibility after receiving damage (in seconds).
    double invincibilityDuration; 

    /**
     * @brief Constructs a HealthComponent with optional parameters.
     * 
     * @param isEnemy Whether the entity is an enemy (default false).
     * @param isPlayer Whether the entity is a player (default false).
     * @param initialHealth Starting health value (default 1).
     * @param maximumHealth Maximum health value (default 1).
     * @param invincibilityTime Duration of invincibility after damage in seconds (default 0.0).
     * @param initialPoints Initial points (default 100 for enemies, 0 for players).
     */
    HealthComponent(bool isEnemy = false, bool isPlayer = false, int initialHealth = 1, int maximumHealth = 1, double invincibilityTime = 0.0, int initialPoints = 100) {
        this->isEnemy = isEnemy;
        this->isPlayer = isPlayer;
        health = initialHealth;
        maxHealth = maximumHealth;
        lastDamageTaken = 0;
        invincibilityDuration = invincibilityTime;
        if (isEnemy) {
            this->points = initialPoints;
        } else if (isPlayer) {
            this->points = 0;
        }
    }
    /**
     * @brief Checks if the entity is alive.
     * @return True if health is greater than zero, false otherwise.
     */    
    bool IsAlive() const {
        return health > 0;
    }
    /**
     * @brief Sets the entity as player or enemy.
     * @param state True to set as player; false to set as enemy.
     */    
    void SetState(bool state) {
        isPlayer = state;
        isEnemy = !state;
    }
    /**
     * @brief Attempts to apply damage to the entity.
     * 
     * Considers invincibility duration to prevent damage if invincible.
     * Updates lastDamageTaken timestamp if damage is applied.
     * 
     * @param damage Amount of damage to apply.
     * @return True if damage was applied; false if invincible or dead.
     */   
    bool DoDamage(int damage) {
        if (!IsAlive()) {
            return false; 
        }
        
        if (invincibilityDuration == 0 || !IsTemporarilyInvincible()) {

            health -= damage;
            if (health < 0) {
                health = 0;
            }
            if (invincibilityDuration > 0) {
                // Actualizar el tiempo del último daño recibido
                lastDamageTaken = time(nullptr);
            }
            return true; // Daño aplicado exitosamente
            

        } else {
            return false; 
        }
        
    }
    
    /**
     * @brief Legacy damage method for compatibility; internally calls DoDamage.
     * Outputs damage and current health to the console.
     * 
     * @param damage Amount of damage to apply.
     */
    void Damage(int damage) {
        if (DoDamage(damage))
            std::cout << "Damage applied: " << damage << ", Current Health: " << health << std::endl;
    }

    /**
     * @brief Heals the entity by a specified amount.
     * Ensures health does not exceed maxHealth.
     * 
     * @param amount Amount to heal.
     */
    void Heal(int amount) {
        health += amount;
        if (health > maxHealth) {
            health = maxHealth;
        }
    }
    /**
     * @brief Checks if the entity is currently invincible.
     * 
     * @return True if invincibility timer is active, false otherwise.
     */  
    bool IsTemporarilyInvincible() const {
        if (lastDamageTaken == 0 || invincibilityDuration == 0) {
            return false;
        }
        
        time_t currentTime = time(nullptr);
        double timeSinceLastDamage = difftime(currentTime, lastDamageTaken);
        return timeSinceLastDamage < invincibilityDuration;
    }
    /**
     * @brief Sets the duration of invincibility after damage.
     * 
     * @param duration Duration in seconds.
     */    
    void SetInvincibilityDuration(double duration) {
        invincibilityDuration = duration;
    }
    /**
     * @brief Resets the invincibility timer, making the entity vulnerable immediately.
     */   
    void ResetInvincibilityTimer() {
        lastDamageTaken = 0;
    }
    /**
     * @brief Returns the remaining time of invincibility.
     * 
     * @return Remaining invincibility time in seconds, or zero if none active.
     */   
    double GetRemainingInvincibilityTime() const {
        if (lastDamageTaken == 0) {
            return 0; // No hay invencibilidad activa
        }
        
        time_t currentTime = time(nullptr);
        double elapsed = difftime(currentTime, lastDamageTaken);
        double remaining = invincibilityDuration - elapsed;
        
        return remaining > 0 ? remaining : 0;
    }
};

#endif // HEALTHCOMPONENT_HPP