function draw()

    -- of.fx_kale(8)
    -- of.fx_grid(1.3)
    -- of.fx_wave(12)

    of.blend_mode("add")
    -- of.line_width(of.fft(1) * 6 + 1)

    -- of.rotate(of.frame() / 10, 0.7, 0.2, 0.4)
    
    -- of.scale(of.fft(7) * 2 + 1)

    local length = of.fft(2) * 1000 + 500

    of.color(200, 20, 100)
    for i = 54,1,-1 
    do 

        local l = math.abs(i - 27) / 2
        
        of.hsl(
            of.time() / 100 + math.abs(i - 27), 
            math.min(math.max(of.fft(1), 0.6), 1), 
            math.cos((math.pi * 2) * (of.beat() + of.knob(1)) / (of.knob(0) + 1) - l)
        )

        of.pushMatrix()
        of.rotateZ(-90)
        of.translate(0, -1400 + i * 50, 0)
        of.rotateY(of.time()/ 60)
        of.box(length, 10, 10)
        of.rotateY(60)
        of.box(length, 10, 10)
        of.rotateY(60)
        of.box(length, 10, 10)
        of.popMatrix()

        
    end



end