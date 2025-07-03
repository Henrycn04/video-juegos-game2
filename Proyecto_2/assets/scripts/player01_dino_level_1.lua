
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


powerup_active = false
powerup_timer = 0

damage_timer = 0
damage_active = false
damage_duration = 10

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

    if get_health(this) == 0 or get_time() > 500000 then
        set_check(0,0)  
        set_current_life(0) 
        set_check(50,50) 
        go_to_scene("defeat1")      
    end

    if powerup_active then
        powerup_timer = powerup_timer + 1
        if powerup_timer > 350 then
            powerup_active = false
            powerup_timer = 0
            player_speed = 3.0 * 64.0
            change_animation(this, "player01_dino_run")
        end
    end

    if damage_active then
        damage_timer = damage_timer + 1
        if damage_timer >= damage_duration then
            damage_active = false
            damage_timer = 0
            if powerup_active then
                change_animation(this, "player01_dino_run_powerup")
            else 
                change_animation(this, "player01_dino_run")
            end
        end
    end

    local x, y = get_position(this)
    if x < 0 or y < 0 then
        do_damage_to_self(this)
        set_current_life(get_health(this)) 
        if get_health(this) == 0 then
            set_check(50,50) 
            go_to_scene("defeat1")
        else   
        go_to_scene("level_01")  
        end   
    end

end


function on_collision(other)
     -- check
     if get_tag(other) == "check"  then
        local x,y = get_position(other)
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
            local initHP = get_health(this)
            do_damage(this, other) -- aplicar daño al jugador
            set_current_life(get_health(this))
            if get_health(this) < initHP then
                damage_active = true
                damage_timer = 0
                change_animation(this, "player01_dino_run_damage_taken")
            end
    end
    -- Dano po caida
    if get_tag(other) == "damage"  then 
        do_damage(this, other)
        set_current_life(get_health(this)) 
        if get_health(this) == 0 then
            set_check(50,50) 
            go_to_scene("defeat1")
        else  
        go_to_scene("level_01")  
        end   
    end
    -- gane
    if get_tag(other) == "win"  then
        set_check(0,0)  
        set_current_life(0) 
        go_to_scene("win1")    
    end

    -- powerup
    if get_tag(other) == "powerup"  then
        powerup_active = true
        powerup_timer = 0
        player_speed = 5.0 * 64.0
        change_animation(this, "player01_dino_run_powerup")
        kill_entity(other) 
    end
end

function update_animation_state()
    local x_vel, y_vel = get_velocity(this)


    -- no se mueve
    if -0.001 < x_vel and x_vel < 0.001 then
        if player_state ~= player_states["idle"] then
            player_state = player_states["idle"]
            if powerup_active then
                change_animation(this, "player01_dino_idle_powerup")
            else
                change_animation(this, "player01_dino_idle")
            end
        end
    end


    -- hacia la derecha
    if x_vel >= 0.001 then
        flip_sprite(this, false)
        if player_state ~= player_states["run"] then
            player_state = player_states["run"]
            if powerup_active then
                change_animation(this, "player01_dino_run_powerup")
            else
                change_animation(this, "player01_dino_run")
            end
        end
    end


    -- izquierda
    if x_vel <= -0.001 then
        flip_sprite(this, true)
        if player_state ~= player_states["run"] then
            player_state = player_states["run"]
            if powerup_active then
                change_animation(this, "player01_dino_run_powerup")
            else
                change_animation(this, "player01_dino_run")
            end
        end
    end

    x,y = get_position(this)

end