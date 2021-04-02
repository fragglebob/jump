function draw()

    of.fx_rgb(0.0007)
    
    
    of.fx_grid((math.floor(of.beat()/2)%4)+1)
    -- 
    
    -- of.fx_ascii()
    -- of.feedback(true)
    -- of.fx_rgb(0.0007)
    -- of.feedback(true)
    -- of.fx_wave(9)
    -- of.fx_kale(4, ((of.int_beat())%8)*15.7)
    -- of.feedback(true)
    
    of.fx_kale(0, 15.7)
    -- of.feedback(true)
    

    of.fx_ascii((1-of.fft(10)) * 80 +  10)
    of.fx_rgb(0.0007)
    -- of.fx_grid(16)
    -- of.fx_grid(1.3)
    -- of.fx_grid(1 + of.int_beat()/10)
    
    of.feedback(true)

    
    
    -- of.fx_ascii(20)
    of.fx_bloom()
    of.fx_rgb(0.00007)
    
    
    
    -- of.blend_mode("add")

   

    local times = 4;


    for i = times,1,-1 
    do 
        of.pushMatrix()
        of.hsl((of.int_beat()) * 60 + (of.frame()+ i)/10, 1.0 - of.fft(12)/2, of.fft(3) * 0.5  + 0.2)
        of.rotate(of.frame() + i*90, 0.3, 0.2, -0.1)
        of.box( 300 * of.fft(1) + 200  )
        of.popMatrix()
    end

    
end
