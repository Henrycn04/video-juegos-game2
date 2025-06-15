
player_states = {
    idle = 1,
    run = 2,
    jump = 3,
    fall = 4,
}

player_state = player_states["idle"]
player_can_jump = false
player_jump_force = -1500.0 * 64.0
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
end


function on_collision(other)
    
    if get_tag(other) == "floor" then
        local x_vel, y_vel = get_velocity(this)
        if y_vel == 0 then
            player_can_jump = true
        end
        
    end
end

function update_animation_state()
    local x_vel, y_vel = get_velocity(this)


    -- no se mueve
    if -0.001 < x_vel and x_vel < 0.001 then
        if player_state ~= player_states["idle"] then
            player_state = player_states["idle"]
            change_animation(this, "player_frog_idle")
        end
    end


    -- hacia la derecha
    if x_vel >= 0.001 then
        flip_sprite(this, false)
        if player_state ~= player_states["run"] then
            player_state = player_states["run"]
            change_animation(this, "player_frog_run")
        end
    end


    -- izquierda
    if x_vel <= -0.001 then
        flip_sprite(this, true)
        if player_state ~= player_states["run"] then
            player_state = player_states["run"]
            change_animation(this, "player_frog_run")
        end
    end


    -- caida
    if y_vel >= 0.001 then
        if player_state ~= player_states["fall"] then
            player_state = player_states["fall"]
            change_animation(this, "player_frog_fall")
        end
    end

    -- saltando
    if y_vel <= -0.001 then
        if player_state ~= player_states["jump"] then
            player_state = player_states["jump"]
            change_animation(this, "player_frog_jump")
        end
    end
end