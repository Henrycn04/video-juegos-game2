-- Estado global para almacenar variables por ID
state = state or {}

-- Inicialización de variables específicas para cada instancia
function on_awake()
    local id = get_id(this)
    
    -- Inicializar estado para esta instancia
    state[id] = {
        enemy04_player_speed = 1.0 * 64.0,
        enemy04_timer = 0,
        enemy04_direction = 1, -- 1 para derecha, -1 para izquierda
        is_not_dead_04 = true
    }
end

function update()
    local id = get_id(this)
    local t = state[id]
    
    if not t then
        -- Si no existe el estado, crearlo (por seguridad)
        t = {
            enemy04_player_speed = 1.0 * 64.0,
            enemy04_timer = 0,
            enemy04_direction = 1,
            is_not_dead_04 = true
        }
        state[id] = t
    end
    
    local x_vel, y_vel = get_velocity(this)
    
    -- Incrementar el contador de tiempo
    t.enemy04_timer = t.enemy04_timer + 1
    
    if t.enemy04_timer >= 120 then
        t.enemy04_timer = 0
        t.enemy04_direction = t.enemy04_direction * -1 -- Invertir dirección
        flip_sprite(this, t.enemy04_direction == -1) -- Voltear sprite según la dirección
        
    end
    
    x_vel = t.enemy04_player_speed * t.enemy04_direction
    set_velocity(this, x_vel, y_vel)
end

function on_collision(other)
    local id = get_id(this)
    local t = state[id]
    
    if not t then return end -- Si no existe el estado, salir
    
    this_tag = get_tag(this)
    other_tag = get_tag(other)
    
    if other_tag == "player" then
        local hay_choque = top_collision(this, other)
        
        if hay_choque and t.is_not_dead_04 then
            t.is_not_dead_04 = false
            
            -- Obtener posición y velocidad del que rebota (this)
            set_velocity(this, 0, 0)
            
            -- Definir fuerza base de salto
            local jump_force = -1500 * 64.0
            
            -- Aplicar salto a 'this' (el que fue pisado o interactuado)
            add_force(this, 0, jump_force)
            
            -- Procesar rebote para 'other' (el que cae encima)
            local other_vel_x, other_vel_y = get_velocity(other)
            
            if not other.player_can_jump and other_vel_y > 0 then
                -- VA BAJANDO
                -- Calcula la diferencia entre la fuerza de salto y la velocidad actual
                local delta = jump_force + (other_vel_y * 64.0)
                
                -- Limitar para evitar rebotes exagerados
                local max_bounce_force = -jump_force * 1.2
                if delta < max_bounce_force then
                    delta = max_bounce_force
                end
                
                if delta > 0 then
                    delta = -delta
                end
                
                add_force(other, 0, delta)
                
            elseif not other.player_can_jump and other_vel_y < 0 then
                -- VA SUBIENDO
                local delta = jump_force - (other_vel_y * 64.0) -- delta es negativo
                
                -- Limitar para evitar rebotes exagerados
                local max_bounce_force = jump_force -- es negativo
                if delta < max_bounce_force then
                    delta = max_bounce_force
                end
                
                if delta > 0 then
                    delta = -delta
                end
                
                delta = delta/3
                add_force(other, 0, delta)
            end
            
            -- Desactivar colisiones temporalmente
            deactivate_collisions(this)
            add_points(this, other)
        end
    end
    if other_tag == "damage"  then
        kill_entity(this)
        print("Enemy04 killed")
    end
end