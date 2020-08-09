function draw()

    -- of.fx_kale(8)
    -- of.fx_grid(3)
    -- of.fx_wave(12)

    of.blend_mode("add")
    -- of.line_width(of.fft(1) * 6 + 1)




    of.rotateX(90)
    of.rotate(of.frame() / 10, 0.1,0.1,1)
    
    -- of.scale(
    --     of.fft(7) * 2 ,
    --     of.fft(7) * 2 ,
    --     1
    -- )

    of.color(250, 0, 20)
    for i = 32,1,-1 
    do 
        of.pushMatrix()
        of.rotateZ(i * 173)
        of.translate(100, 200, 0)
        of.box(10, 10, of.fft(1) * 1000 + 400)
        of.popMatrix()
    end

    
    of.color(0, 50, 200)
    for i = 82,1,-1 
    do 
        of.pushMatrix()
        of.rotateZ(i * 10.3)
        of.translate(350, 180, -900 + i * 20)
        of.rotate(of.frame() + i * i)
        of.box(5, 50, of.fft(5) * 600 + 100)
        of.popMatrix()
    end

    of.color(200, 50, 0)
    for i = 190,1,-1 
    do 
        of.pushMatrix()
        of.rotateZ(i * 17.5982)

        of.translate(150, 1000, math.sin(i* 55) * 200)
        of.rotate(of.frame() * 2 + i * i * 10)
        of.box(10, 10, of.fft(7) * 200 + 50)
        
        of.popMatrix()
    end

    of.color(200, 50, 0)
    for i = 20,1,-1 
    do 
        of.pushMatrix()
        of.rotateZ(i * 97.5982)

        of.translate(350, 500, math.cos(i* 66) * 200)
        of.rotate(of.frame() + i * i)
        
        of.box(5, 60, of.fft(7) * 800 + 100)
        
        of.popMatrix()
    end

end