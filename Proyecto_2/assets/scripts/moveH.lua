state = {}

function update()
    local id = get_id(this)
    local t = state[id] or {timer = 0, direction = 1}

    t.timer = t.timer + 1

    if t.timer <= 150 then  
        local x, y = get_position(this)
        set_position(this, x + t.direction, y)
    else
        t.timer = 0
        t.direction = -t.direction 
    end

    state[id] = t
end

