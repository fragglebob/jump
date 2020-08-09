function draw()

    -- of.fx_kale(8)
    -- of.fx_grid(12)
    -- of.fx_wave(12)

    of.blend_mode("screen")
    -- of.line_width(of.fft(1) * 6 + 1)


    of.color(200, 20, 100)


    of.rotate(of.frame(), 0.7, 0.2, 0.4)
    
    of.scale(of.fft(1) * 10)


    for i = 20,1,-1 
    do 
        of.pushMatrix()
        of.rotate(of.frame() + i * 137, 0.1, 0.2, 0.4)
        of.translate(100, 200, 0)
        of.box(100)
        of.popMatrix()
    end



end