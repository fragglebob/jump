function draw()

    -- of.fx_kale(of.lerp(1, 10, of.slider(2)))
    -- of.fx_grid(3)

    -- of.fx_wave(12)

    of.blend_mode("add")
    -- of.line_width(of.fft(1) * 6 + 1)

    -- of.rotate(of.frame() / 10, 0.7, 0.2, 0.4)
    
    -- of.scale(0.2)

    of.color(200, 20, 100)

    local c = 200
    local hc = c / 2;

    

    -- 

    local c = 1000

    local l = of.fft(0) * 500 + 100;
    local w = of.fft(4) * 30 + 10

    for i = c,1,-1 
    do 
        of.pushMatrix()


        local temp1 = i*(of.knob(1)/10+1) + (of.frame()*of.knob(2)/10);
        local z = ((temp1 - math.floor(temp1)) * 2 - 1)
        -- local z = math.sin(i*(of.knob(1)+1) + (of.frame()*of.knob(2)/10));

        local apt = (z + 1) / 2;


        of.hsl(
            i/15+of.frame()/10, 
            math.min(math.max(of.fft(1), 0.6), 1), 
            math.max(math.cos((math.pi * (of.slider(1) + 1)) * (of.beat() + of.slider(0) - apt)), 0.03)
        )

        of.translate(
            (math.sin(i) * 500 * apt + 1) + math.sin((math.pi * 2) * apt + of.frame() / 77)  * 400 * (1-apt), 
            math.cos(i) * 500 * apt + 1 + math.cos((math.pi * 2) * apt + of.frame() / 100)  * 500  * (1-apt), 
            -3000 + z * 4000
        )

        of.scale(math.max(apt, 0.35));
        -- of.rotateX(of.frame())


        of.box(w, w, l)
        -- of.ball(w)
        of.popMatrix()
    end




end