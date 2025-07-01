#ifndef ENEMYDATACOMPONENT_HPP
#define ENEMYDATACOMPONENT_HPP

struct EnemyDataComponent 
{
    // Tipo de enemigo (1, 2, 3, 4)
    int enemy_type = 1;
    
    // Variables de estado común
    bool is_not_dead = true;
    
    // Variables de movimiento (Enemy01, Enemy03, Enemy04)
    float player_speed = 1.0f * 64.0f;
    float timer = 0.0f;
    int direction = 1; // 1 para derecha, -1 para izquierda
    
    // Variables de salto (Enemy03)
    bool can_jump = false;
    float jump_force = -700.0f * 64.0f;
    bool prev_jump = false;
    
    // Variables de disparo (Enemy02)
    float last_arrow_time = 0.0f;
    float arrow_cooldown = 10000.0f;
    
    // Constructor por defecto
    EnemyDataComponent() = default;
    
    // Constructor con tipo específico
    EnemyDataComponent(int type) : enemy_type(type)
    {
        InitializeByType();
    }
    
    // Inicializar variables según el tipo
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
                // Valores por defecto (Enemy01)
                player_speed = 1.0f * 64.0f;
                timer = 0.0f;
                direction = 1;
                is_not_dead = true;
                break;
        }
    }
};

#endif // ENEMYDATACOMPONENT_HPP