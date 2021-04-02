function draw()

    of.fx_rgb(0.0007)
    
    
    -- of.fx_grid((math.floor(of.beat()/2)%4)+1)
    -- 
    -- of.feedback(true)
    -- of.fx_wave(9)
    of.fx_kale(4, ((of.int_beat())%8)*15.7)
    of.feedback(true)
    
    -- of.fx_kale(1, 15.7)
    
    
    
    
    of.fx_ascii(100)
    of.fx_rgb(0.0007)
    of.fx_bloom()
    
    
    
    -- of.blend_mode("add")

    local times = 400;


    for i = times,1,-1 
    do 
        of.pushMatrix()

        

        local phatness = of.fft(i%20) * 50 + 20;
        
        local temp1 = i*1.223 + of.frame()/400;
        local z = ((temp1 - math.floor(temp1)) * 2 - 1)
        -- local z = math.sin(i*(of.knob(1)+1) + (of.frame()*of.knob(2)/10));

        local apt = (z + 1) / 2;

        of.translate(
            math.sin(i) * 1000 * math.pow(apt,2) + 1 + (math.cos(i*1.732)*100*apt), 
            math.cos(i)* 1000 * math.pow(apt, 1) + 1 + (math.sin(i*1.343)*100*apt),

            -2000 + z * 4000
        )



        of.scale(math.pow(math.max(apt, 0.1), 1));

        of.hsl((of.int_beat()) * 90, 0.8, math.pow(1.4-apt, 2) )

        -- of.rotate(of.beat()*4 + math.sin(i * 40), math.cos(i*3), math.cos(i*1.443), math.sin(i*1.343))
        of.box( (500 * of.fft((i+3)%20)) + 100 , phatness, phatness )



        of.popMatrix()
    end
end
