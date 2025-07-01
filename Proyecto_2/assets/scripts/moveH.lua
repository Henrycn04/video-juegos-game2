
timer = 0
dir = 1
function update()


    timer = timer + 1

    if timer<= 40000 then
        local x, y = get_position(this)
        set_position(this, x+ dir, y)
    else
        timer = 0
        dir = -dir
    end

end
