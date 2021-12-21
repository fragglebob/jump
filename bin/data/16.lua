function draw()


    local f = of.frame()
    local times = math.max(math.min(math.pow(of.fft(12), 4) * 10 + 10, 200), 50)
    local spread = of.beat() % 1 * 40 + 30

    local maxSizeX = 1400
    local maxSizeY = 800

    of.line_width(16)

    for i = times,1,-1 
    do 

        of.hsl((of.int_beat()) * 60 + (of.frame()+ i)/10, 1.0 - of.fft(12)/3, of.fft(3) * 0.4 + 0.1)
        -- of.color((i / times) * 254.9, 100.1, 200.1)

        local index1 = f + (i * spread)
        local index2 = f + ((i + 1) * spread) 

        of.line(
            math.sin(index1 / 20.0) * maxSizeX, 
            math.sin(index1 / 22.0) * maxSizeY, 
            math.cos(index2 / 20.0) * maxSizeX, 
            math.cos(index2 / 22.0) * maxSizeY
        )
    end


    --
    
     -- 
    of.feedback(true)

    of.fx_grid(1.5)
    -- 

    of.fx_ascii((of.fft(10)) * 30 +  10)

    of.feedback(true)

    of.fx_matrix(
        0.999, math.sin(of.frame() / 1437 ) *-0.0005, math.sin(of.frame() / 1347 ) * 0.0005,
        -0.0005, 0.999, math.sin(of.frame()/1400 ) *0.0005
    )

    of.feedback(true)

    -- 
    -- of.fx_kale(4, ((of.int_beat())%16)*15.7)
    
   
    -- of.feedback(true)
    

    of.fx_rgb(0.001)

    
    of.fx_bloom()

end
