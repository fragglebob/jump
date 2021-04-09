function draw()

    of.fx_rgb(0.0007)
    
    -- of.feedback(true)
    of.fx_grid((math.floor(of.beat())%4)+1)
    -- 
    of.feedback(true)
    -- of.fx_ascii()
    
    -- of.fx_rgb(0.0007)
    
    -- of.fx_wave(9)
    -- of.fx_kale(4, ((of.int_beat())%8)*15.7)
    -- of.feedback(true)
    
    -- of.feedback(true)
    
    if math.floor(of.beat()) % 2 == 0 then
        of.fx_ascii((1-of.fft(10)) * 80 +  10)
        -- of.fx_rgb(0.002)
    else 
        of.fx_ascii((of.fft(10)) * 80 +  10)
       
    end
    
    of.fx_kale(5 )
    of.fx_grid(3)
  
    -- 
    of.feedback(true)
    -- 
of.fx_rgb(0.00002)
    of.fx_matrix(
        1.001, math.sin(of.frame() / 1437 ) *-0.0005, math.sin(of.frame() / 1347 ) * 0.0005,
        -0.0005, 1.001, math.sin(of.frame()/1400 ) *0.0005
    )
    of.fx_rgb(0.00005)
    of.feedback(true)
    -- of.fx_grid(3)
    
    --   of.fx_grid(1.3)
    -- of.fx_grid(1 + of.int_beat()/10)

    
    
    -- of.fx_ascii(100)
    -- of.fx_matrix(
    --     1.01, 0.0, math.sin(of.frame() / 137 ) * 0.05,
    --     0.0, -1.01, math.sin(of.frame()/100 ) *0.05
    -- )
    of.fx_bloom()
    of.fx_rgb(0.00007)
    
    
    
    -- of.blend_mode("add")

   

    local times = math.ceil(10 * of.fft(12));

    for i = times,1,-1 
    do 
        of.pushMatrix()
        of.hsl((of.int_beat()) * 60 + (of.frame()+ i)/10, 1.0 - of.fft(12)/2, of.fft(3) * 0.5  + 0.2)
        -- of.translate(i - 60, i * 10)
        of.rotate(of.frame() + i*90 + math.sin(i*5432)*20, 0.3, 0.2, -0.1)
        
        of.box( 300 * of.fft(1) + 200  )
        of.popMatrix()
    end

    
end
