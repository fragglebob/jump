
function draw()

    -- 
of.feedback(true);
of.fx_wave(8);
    of.fx_kale(2, -0.1)
   
    -- of.fx_grid(3)
    of.feedback(true);
    -- of.fx_wave(4);
   
    
    -- 
    -- of.feedback(true);
     
    -- -- 

    of.fx_kale(2,0)
    of.fx_grid((math.floor(of.beat()/4)%2)*2+1)
    of.fx_kale(1,0)
    
    -- 
    -- 
    -- of.feedback(true);
    -- 
    -- of.fx_kale(4)
    -- of.fx_rgb(0.001)
    -- of.fx_grid(1.3)

    of.fx_bloom()
    of.fx_rgb(0.001)
    -- of.feedback(true);


    
    of.hsl(of.int_beat() * 60 + of.frame(), math.floor(of.beat())%2, 0.09 )

    of.blend_mode("add")

    local times = 1000;

    local b = of.beat()

    local bP = (  b - math.floor(b))

    local sizeMulitpler = 1200 * bP;

    for i = times,1,-1 
    do 
        of.pushMatrix()
        of.rotate(i+of.frame(), 12.3, 2.3, 5)
        of.translate(
            math.cos(i*1.637) * sizeMulitpler, 
            math.sin(i*1.637) * sizeMulitpler
    )
    of.rotate(i+of.frame(), 12.3, 2.3, 5)
        of.box(of.fft(1) * 90)
        of.popMatrix()
    end

    

end
