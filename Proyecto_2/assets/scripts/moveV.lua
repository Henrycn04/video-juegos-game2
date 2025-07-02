
timerV = 0
dirV = -1
function update()


    timerV = timerV + 1

    if timerV<= 2000 then
        local x, y = get_position(this)
        set_position(this, x, y + dirV)
    else
        timerV = 0
        dirV = -dirV
    end

end
