
enemy01_player_speed = 1.0 * 64.0

enemy01_timer = 0
direction = 1  -- 1 para derecha, -1 para izquierda
function update()
    local x_vel, y_vel = get_velocity(this)
    
    -- Incrementar el contador de tiempo
    enemy01_timer = enemy01_timer + 1
    

    if enemy01_timer >= 20 then
        enemy01_timer = 0
        direction = direction * -1  -- Invertir dirección
        print("Cambiando dirección a: " .. direction)
    end
    
    x_vel = enemy01_player_speed * direction
    set_velocity(this, x_vel, y_vel)
end

is_not_dead_01 = true

function on_collision(other)
    this_tag = get_tag(this)
    other_tag = get_tag(other)
    
    if other_tag == "player" then
        local hay_choque = top_collision(this, other)
        if hay_choque and is_not_dead_01 then
            is_not_dead_01 = false
            
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
        end
    end
end