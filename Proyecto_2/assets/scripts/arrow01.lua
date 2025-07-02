
function update()

end

arrow01_is_not_dead = true

function on_collision(other)
    this_tag = get_tag(this)
    other_tag = get_tag(other)
    
    if other_tag == "player" then
        local hay_choque1 = right_collision(this, other)
        local hay_choque2 = left_collision(this, other)

        local hay_choque = (hay_choque1 or hay_choque2)

        if hay_choque and arrow01_is_not_dead then

            arrow01_is_not_dead = false
            
            -- Obtener posición y velocidad del que rebota (this)
            local this_x, this_y = get_position(this)
            local this_vel_x, this_vel_y = get_velocity(this)

            -- Definir fuerza base de salto
            local jump_force = 1500 * 64.0 * 8

            -- Aplicar salto a 'this' (el que fue pisado o interactuado)
            add_force(other, jump_force, 0)

            -- Procesar rebote para 'other' (el que cae encima)
            local other_vel_x, other_vel_y = get_velocity(other)
            -- Desactivar colisiones temporalmente
            deactivate_collisions(this)
            kill_entity(this)
        end
    end
    if other_tag == "damage" or other_tag == "floor" or other_tag == "wall" 
            or other_tag == "bounce" or other_tag == "trembling" or other_tag == "moveH" or other_tag == "moveV"  then
        kill_entity(this)
    end
end