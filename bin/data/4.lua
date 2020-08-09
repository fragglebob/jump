function draw()

    -- of.fx_kale(8)
    -- of.fx_grid(12)
    -- of.fx_wave(12)

    of.blend_mode("add")
    -- of.line_width(of.fft(1) * 6 + 1)




    of.rotate(of.frame() / 10, 0.7, 0.2, 0.4)
    
    of.scale(of.fft(7) * 2 + 1)

    local length = of.fft(6) * 1000 + 100

    of.color(200, 20, 100)
    for i = 22,1,-1 
    do 
        of.pushMatrix()
        of.rotateZ(of.frame() + i * 137)
        of.translate(80, 200, 0)
        of.rotateY(of.frame()  * 3 + i * 33)
        of.box(length, 10, 10)
        of.popMatrix()
    end


    of.color(0, 100, 200)
    for i = 97,1,-1 
    do 
        of.pushMatrix()
        of.rotateZ(of.frame() + i * (47 + i * i))
        of.translate(200 - i, 350  + i, 0)
        of.rotateY(of.frame()  * 2 + i * 33)
        of.box(length, 10, 10)
        of.popMatrix()
    end


    of.color(201, 50, 0)
    for i = 9,1,-1 
    do 
        of.pushMatrix()
        of.rotateZ(of.frame() + i * 33 * i)
        of.translate(30, 50, 0)
        of.rotateY(of.frame()  * 2 + i * i * 33)
        of.box(length, 10, 10)
        of.popMatrix()
    end

end