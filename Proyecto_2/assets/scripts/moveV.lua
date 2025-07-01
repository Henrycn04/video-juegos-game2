
timer = 0
dir = -1
function update()


    timer = timer + 1

    if timer<= 100000 then
        local x, y = get_position(this)
        set_position(this, x, y + dir)
    else
        timer = 0
        dir = -dir
    end

end
