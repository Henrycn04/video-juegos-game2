-- Estado global para almacenar variables por ID
state = {}

-- Inicialización de variables específicas para cada instancia
function on_awake()
    local id = get_id(this)
    
    -- Inicializar estado para esta instancia
    state[id] = {
        last_arrow_time = 0,
        arrow_cooldown = 10000,
        is_not_dead_02 = true
    }
end

function update()
    local id = get_id(this)
    local t = state[id]
    
    if not t then
        -- Si no existe el estado, crearlo (por seguridad)
        t = {
            last_arrow_time = 0,
            arrow_cooldown = 10000,
            is_not_dead_02 = true
        }
        state[id] = t
    end
    
    local current_time = get_ticks()
    
    if current_time - t.last_arrow_time >= t.arrow_cooldown then
        create_arrow(this) -- 'this' es la entidad completa
        t.last_arrow_time = current_time
    end
end

function on_collision(other)
    local id = get_id(this)
    local t = state[id]
    
    if not t then return end -- Si no existe el estado, salir
    
    this_tag = get_tag(this)
    other_tag = get_tag(other)
    
    if other_tag == "player" then
        local hay_choque = top_collision(this, other)
        
        if hay_choque and t.is_not_dead_02 then
            t.is_not_dead_02 = false
            
            -- Obtener posición y velocidad del que rebota (this)
            local this_x, this_y = get_position(this)
            local this_vel_x, this_vel_y = get_velocity(this)
            
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
        end
    end
end