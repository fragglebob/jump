-- function draw()

 

--     local time = of.frame();

--     local pro = of.beat() - math.floor(of.beat());

--     of.color(100, 100, 0)

--     for i = 60,1,-1 
--     do 

--         local posz = i/60 + (of.frame())*0.0005
--         posz = posz - math.floor(posz)

--         of.pushMatrix()
--         of.scale(10)
--         of.translate(
--             math.sin(math.pi * 2 * posz )* 10, 
--             20, 
--             posz * 1600 - 1500
--         )
--         of.box(30, 1, 10 + of.fft(6) * 6)
--         of.popMatrix()
        
--     end




-- end
function draw()

    of.feedback(true)
    of.fx_kale(1.2)
    of.fx_grid(1.1)
    of.fx_wave(6)

    -- if math.floor(of.frame() / 60) % 2 > 0 then
        
    -- end
    
  
    of.rotateX(90)
    of.rotate(of.frame() / 10, 0.2,0.5,1)
    
    -- of.scale(
    --     1,
    --     1,
    --     of.fft(10) * 2
    -- )

    of.color(250, 0, 20)
    for i = 32,1,-1 
    do 
        of.pushMatrix()
        of.rotateZ(i * 173)
        of.translate(100, 200, math.sin(i * 49) * 10)
        of.box(10, 10, of.fft(1) * 1000 + 400)
        of.popMatrix()
    end

    
    of.color(0, 50, math.sin(of.frame() / 100) * 100 + 100)
    for i = 82,1,-1 
    do 
        of.pushMatrix()
        of.rotateZ(i * 10.3)
        of.translate(350, 180, -900 + i * 20)
        of.rotate(of.frame() + i * i)
        of.box(5, 50, of.fft(i % 10 + 5) * 600 + 100)
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

-- function draw()

--     -- of.fx_grid(1.3)

--     of.rotateX(of.frame())
--     of.box(of.fft(7) * 500 + 400)

-- end

-- function draw()

--     of.fx_kale(of.lerp(1, 10, of.slider(0)))
--     of.fx_grid(of.lerp(1, 16, of.slider(1)))
--     -- of.fx_wave(of.lerp(1, 32, of.slider(2)))

--     of.blend_mode("add")
--     of.line_width(of.fft(1) * 16 + 1)

--     local f = of.frame()
--     local times = math.floor(of.fft(1) * 140) + 20
--     local spread = of.fft(6) + 2

--     local maxSize = 1000

--     for i = times,1,-1 
--     do 
--         of.color((i / times) * 254.9, 100.1, 200.1)
--         of.line(
--             math.sin((f + i * spread) / 31.0) * maxSize, 
--             math.cos((f + i * spread) / 46.0) * maxSize, 
--             math.cos((f + i * spread) / 67.0) * maxSize, 
--             math.sin((f + i * spread) / 142.0) * maxSize
--         )
--     end

--     maxSize = 500

--     f = f + 1000

--     for i = times,1,-1 
--     do 
--         of.color(100.1, (i / times) * 254.9, 100.1)
--         of.line(
--             math.sin((f + i * spread) / 81.0) * maxSize, 
--             math.cos((f + i * spread) / 42.0) * maxSize, 
--             math.cos((f + i * spread) / 54.0) * maxSize, 
--             math.sin((f + i * spread) / 69.0) * maxSize
--         )
--     end

--     f = f + 1000

--     maxSize = 800

--     for i = times,1,-1 
--     do 
--         of.color(50.1, 200.1, (i / times) * 254.9)
--         of.line(
--             math.sin((f + i * spread) / 211.0) * maxSize, 
--             math.cos((f + i * spread) / 133.0) * maxSize, 
--             math.cos((f + i * spread) / 111.0) * maxSize, 
--             math.sin((f + i * spread) / 269.0) * maxSize
--         )
--     end
 
-- end