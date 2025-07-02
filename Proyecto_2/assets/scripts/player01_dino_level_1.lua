
player_states = {
    idle = 1,
    run = 2,
    jump = 3,
    fall = 4,
}

player_state = player_states["idle"]
player_can_jump = false
player_jump_force = -1500.0 * 64.0
default_jump_force = -1500.0 * 64.0
bouncing_jump_force = -1800.0 * 64.0 
player_speed = 3.0 * 64.0


prev_jump = false


function update()
    local x_vel, y_vel = get_velocity(this)
    x_vel = 0

    local current_jump = is_action_activated("jump")
    local just_pressed_jump = current_jump and not prev_jump

    if just_pressed_jump and player_can_jump then
        add_force(this, 0, player_jump_force)
        player_can_jump = false
    end

    if is_action_activated("left") then
        x_vel = -player_speed
    elseif is_action_activated("right") then
        x_vel = player_speed
    end

    set_velocity(this, x_vel, y_vel)
    update_animation_state()
    prev_jump = current_jump
    player_can_jump = false

    if get_health(this) == 0 or get_time() > 48000 then
        set_check(0,0)  
        set_current_life(0) 
        go_to_scene("menu")      
    end
end


function on_collision(other)
     -- check
     if get_tag(other) == "check"  then
        local x,y = get_position(other)
        print(x)
        print(y)
        set_check(x+32,y-32)       
    end
    
    if get_tag(other) == "floor" or get_tag(other) == "trembling" or get_tag(other) == "moveV"  or get_tag(other) == "moveH"   then
        local x_vel, y_vel = get_velocity(this)
        if y_vel == 0 then
            player_can_jump = true 
        end
    end

    if get_tag(other) == "bounce" then
        local x_vel, y_vel = get_velocity(this)

        -- Rebote automático si cae fuerte
        if y_vel > 200 then
            set_velocity(this, x_vel, bouncing_jump_force) -- rebote inmediato
        end

        player_can_jump = true
        player_jump_force = bouncing_jump_force  -- salto más fuerte si salta manualmente

    end
    -- Enemigos
    if get_tag(other) == "enemy01" or  get_tag(other) == "enemy02" or get_tag(other) == "enemy03" or  get_tag(other) == "enemy04" then
            
            do_damage(this, other) -- aplicar daño al jugador
            set_current_life(get_health(this))  
    end
    -- Dano po caida
    if get_tag(other) == "damage"  then 
        do_damage(this, other)
        set_current_life(get_health(this)) 
        if get_health(this) == 0 then
            go_to_scene("menu")
        else  
        go_to_scene("level_01")  
        end   
    end
    -- gane
    if get_tag(other) == "win"  then
        set_check(0,0)  
        set_current_life(0) 
        go_to_scene("level_02")    
    end
end

function update_animation_state()
    local x_vel, y_vel = get_velocity(this)


    -- no se mueve
    if -0.001 < x_vel and x_vel < 0.001 then
        if player_state ~= player_states["idle"] then
            player_state = player_states["idle"]
            change_animation(this, "player01_dino_idle")
        end
    end


    -- hacia la derecha
    if x_vel >= 0.001 then
        flip_sprite(this, false)
        if player_state ~= player_states["run"] then
            player_state = player_states["run"]
            change_animation(this, "player01_dino_run")
        end
    end


    -- izquierda
    if x_vel <= -0.001 then
        flip_sprite(this, true)
        if player_state ~= player_states["run"] then
            player_state = player_states["run"]
            change_animation(this, "player01_dino_run")
        end
    end

end