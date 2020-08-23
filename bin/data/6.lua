function draw()

    -- of.fx_kale(1)
    -- of.fx_grid(1.3)
    -- of.fx_wave(12)

    of.blend_mode("add")
    -- of.line_width(of.fft(1) * 6 + 1)

    of.rotate(of.frame() / 10, 0.7, 0.2, 0.4)
    
    -- of.scale(0.2)

    local length = of.fft(02) * 1000 + 500

    of.color(200, 20, 100)

    local c = 200
    local hc = c / 2;

    for i = c,1,-1 
    do 

        local l = math.abs(i - hc) / 2
        
        of.hsl(
            of.time() / 100 + math.abs(i - hc), 
            math.min(math.max(of.fft(1), 0.6), 1), 
            math.cos((math.pi * 2) * of.beat() - l)
        )

        of.pushMatrix()
        of.rotateZ(-90)
        of.translate(0, (hc * -50) + i * 50, 0)
        of.rotateY(of.time()/ 60)
        of.box(length, 10, 10)
        of.rotateY(60)
        of.box(length, 10, 10)
        of.rotateY(60)
        of.box(length, 10, 10)
        of.popMatrix()

        
    end



end