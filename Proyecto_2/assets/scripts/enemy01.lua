function on_awake()
    set_velocity(this, -50, 0)
end


is_not_dead = true

function on_collision(other)
    this_tag = get_tag(this)
    other_tag = get_tag(other)
    
    if other_tag == "player" then
        if top_collision(this, other) and is_not_dead then
            is_not_dead = false
            print("El lado superior de "..this_tag.." colisiona con "..other_tag)
            
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

                print("Velocidad de caída: " .. other_vel_y)
                print("Rebote aplicado (delta): " .. delta)

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
                
                print("Velocidad de caída: " .. other_vel_y)
                print("Rebote aplicado (delta): " .. delta)

                add_force(other, 0, delta)
            end




            
            
            
            -- Desactivar colisiones temporalmente
            deactivate_collisions(this)
        end
    end
end