state = {}

function update()
    local id = get_id(this)
    if id == nil then return end

    local t = state[id]
    if t == nil then return end

    if t.start_timer then
        t.timer = t.timer + 1
        if t.timer > 1 then
            local x, y = get_position(this)
            set_position(this, x, y + 1)
            deactivate_collisions(this)
            t.start_timer = false  
        end
    end
end

function on_collision(other)
    local other_tag = get_tag(other)
    if other_tag ~= "player" then return end

    local id = get_id(this)
    if id == nil then return end

    local t = state[id]
    if t == nil then
        t = {timer = 0, start_timer = false}
    end

    if not t.start_timer then
        local hay_choque = top_collision(this, other)
        if hay_choque then
            t.start_timer = true
            t.timer = 0
        end
    end

    state[id] = t
end