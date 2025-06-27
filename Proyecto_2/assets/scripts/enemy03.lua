enemy03_can_jump = false
enemy03_jump_force = -700.0 * 64.0

enemy03_prev_jump = false

enemy03_player_speed = 0.5 * 64.0

enemy03_timer = 0
enemy03_direction = 1  -- 1 para derecha, -1 para izquierda
function update()
    local x_vel, y_vel = get_velocity(this)
    
    -- Incrementar el contador de tiempo
    enemy03_timer = enemy03_timer + 1
    

    if enemy03_timer >= 80 then
        enemy03_timer = 0
        enemy03_direction = enemy03_direction * -1  -- Invertir dirección
        print("Cambiando dirección a: " .. enemy03_direction)
    end
    if enemy03_can_jump then
        add_force(this, 0, enemy03_jump_force)
        enemy03_can_jump = false
    end
    
    x_vel = enemy03_player_speed * enemy03_direction
    set_velocity(this, x_vel, y_vel)
    enemy03_can_jump = false
end

is_not_dead_03 = true

function on_collision(other)
    this_tag = get_tag(this)
    other_tag = get_tag(other)
    if get_tag(other) == "floor" or get_tag(other) == "trembling"  or get_tag(other) == "damage" then
        local x_vel, y_vel = get_velocity(this)
        if y_vel == 0 then
            enemy03_can_jump = true 
        end
    end
    if other_tag == "player" then
        local hay_choque = top_collision(this, other)
        if hay_choque and is_not_dead_03 then
            is_not_dead_03 = false
            -- TODO: que no salga volando ////////////////////////////////
            -- TODO: creo que se soluciona matando la suma de fuerzas
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