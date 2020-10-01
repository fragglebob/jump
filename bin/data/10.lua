function draw()

    -- of.fx_kale(4)
    -- of.fx_grid(3)

    -- of.fx_wave(12)

    -- of.blend_mode("add")
    -- of.line_width(of.fft(1) * 6 + 1)

    
    
    local c  = 10

    

    for i = c,1,-1 
    do 

        of.pushMatrix()

        of.translate(i * 200 - 1100, 0 ,0)

        of.rotateY(of.frame() / 2)

        of.hsl(of.frame() + i * 23, 0.7, math.sin(math.pi * 2 *of.beat() + i ))

        of.box(100, 550 + of.fft(6) * 280, 100)

        of.popMatrix()


    end




end