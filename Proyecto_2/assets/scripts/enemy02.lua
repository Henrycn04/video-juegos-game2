function on_awake()
    set_velocity(this, -50, 0)
end

local last_arrow_time = 0
local arrow_cooldown = 10000

function update()
    local current_time = get_ticks()
    
    if current_time - last_arrow_time >= arrow_cooldown then
        create_arrow(this) -- 'this' es la entidad completa
        last_arrow_time = current_time
    end
end

is_not_dead_02 = true

function on_collision(other)
    this_tag = get_tag(this)
    other_tag = get_tag(other)
    
    if other_tag == "player" then
        local hay_choque = top_collision(this, other)
        if hay_choque and is_not_dead_02 then

            is_not_dead_02 = false
            
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