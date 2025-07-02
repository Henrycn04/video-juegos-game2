#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

#include <ctime>

struct HealthComponent {
    int health;
    int maxHealth;
    bool isPlayer;
    bool isEnemy;

    int points;
    
    time_t lastDamageTaken;
    double invincibilityDuration; // duración de invencibilidad después de recibir daño
    
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
    
    bool IsAlive() const {
        return health > 0;
    }
    
    void SetState(bool state) {
        isPlayer = state;
        isEnemy = !state;
    }
    
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
    
    // Método legacy para compatibilidad (ahora usa DoDamage internamente)
    void Damage(int damage) {
        if (DoDamage(damage))
            std::cout << "Damage applied: " << damage << ", Current Health: " << health << std::endl;
    }
    
    void Heal(int amount) {
        health += amount;
        if (health > maxHealth) {
            health = maxHealth;
        }
    }
    
    bool IsTemporarilyInvincible() const {
        if (lastDamageTaken == 0 || invincibilityDuration == 0) {
            return false;
        }
        
        time_t currentTime = time(nullptr);
        double timeSinceLastDamage = difftime(currentTime, lastDamageTaken);
        return timeSinceLastDamage < invincibilityDuration;
    }
    
    void SetInvincibilityDuration(double duration) {
        invincibilityDuration = duration;
    }
    
    void ResetInvincibilityTimer() {
        lastDamageTaken = 0;
    }
    
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