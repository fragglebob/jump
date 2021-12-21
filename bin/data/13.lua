function draw()

    -- of.blend_mode("multiply")

    of.blend_mode("")
    local times = 4;

    for i = times,1,-1 
    do 
        of.pushMatrix()
        of.hsl((of.int_beat()) * 60 + (of.frame()+ i)/10, 1.0 - of.fft(12)/2, of.fft(3) * 0.5  + 0.2)
        -- of.translate(i - 60, i * 10)
        of.rotate(of.frame() + i*90 + math.sin(i*5432)*20, 0.3, 0.2, -0.1)
        
        of.box( 300 * of.fft(1) + 200  )
        of.popMatrix()
    end



    of.fx_rgb(0.0007)
    
    
    of.fx_grid((math.floor(of.beat())%4)+1)
    -- 


    
    -- of.feedback(true)
   
    -- of.fx_ascii()
    
    -- of.fx_rgb(0.0007)
    
    -- of.fx_wave(9)
    -- 
    -- of.feedback(true)
    
    -- of.feedback(true)
    
    if math.floor(of.bar()) % 2 == 0 then
        of.fx_ascii((1-of.fft(10)) * 80 +  10)
        -- of.fx_rgb(0.002)
    else 
        of.fx_ascii((of.fft(10)) * 80 +  10)
       
    end
    
    
    -- of.fx_grid(3)

    -- -- 
    -- of.feedback(true) 


    of.fx_rgb(0.00002)
    of.fx_matrix(
        0.999, math.sin(of.frame() / 1437 ) *-0.0005, math.sin(of.frame() / 1347 ) * 0.0005,
        -0.0005, 0.999, math.sin(of.frame()/1400 ) *0.0005
    )
    of.fx_rgb(0.00007)
    of.feedback(true)


    -- of.feedback(true)

    
    
    

    -- of.fx_ascii(15)

    -- of.blend_mode("add")

    
    -- -- of.fx_grid(3)
    
    --   
    -- of.fx_grid(1 + of.int_beat()/10)

    
    --
    -- of.fx_grid(3)
    

    local ltimes = 60;
    local f = of.frame()
    local spread = 5
    local maxSize = 700
    of.line_width(10)
    -- of.blend_mode("add")
    for i = ltimes,1,-1 
    do 
        of.hsl((of.int_beat() + 4) * 60 + (of.frame())/10, 1.0 - of.fft(12)/2, of.fft(3) * 0.5  + 0.2)
        of.line(
            math.sin((f + i * spread) / 31.0) * maxSize, 
            math.cos((f + i * spread) / 46.0) * maxSize, 
            math.cos((f + i * spread) / 67.0) * maxSize, 
            math.sin((f + i * spread) / 142.0) * maxSize
        )
    end

    -- of.fx_kale(2, ((of.int_beat())%8)*15.7)
    of.fx_kale(2, 0)

    of.fx_rgb(0.002)
    
    -- of.fx_matrix(
    --     1.01, 0.0, math.sin(of.frame() / 137 ) * 0.05,
    --     0.0, -1.01, math.sin(of.frame()/100 ) *0.05
    -- )
    
    of.color(math.min(255 - of.fft(1) * 255, 255));
    of.pushMatrix()
    of.rotate(of.frame() + 90 + math.sin(5432)*20, 0.3, 0.2, -0.1)
    of.box( 100 * of.fft(4) + 150 * of.int_beat() + 20)
    of.popMatrix()

    
    
    -- of.feedback(true)
    of.fx_bloom()
    -- of.fx_rgb(0.002)
end
