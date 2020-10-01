function draw()

    of.fx_kale(4)
    of.fx_grid(1.337)

    of.fx_wave(12)

    -- of.blend_mode("add")
    -- of.line_width(of.fft(1) * 6 + 1)

    of.rotateY(of.frame() / 2)
    
    -- of.scale(0.3)

    

    local c = 360

    local spr = of.lerp(2, 10, of.slider(2));

    for i = c,1,-1 
    do 
        of.pushMatrix()

        of.hsl(i + of.frame(), 0.9, 0.9)

        of.rotateY(i*5)
        of.translate(0, (i * spr) - c/2 * spr, 0)

        local h = math.sin(
            (math.pi * 2 * of.beat() / 4) + 
            math.pi * 2 * (i/6)
        ) * 10 + 11

        of.box(1000 + h * 10 * of.fft(1), h, 35)


        -- of.ball(w)
        of.popMatrix()
    end




end