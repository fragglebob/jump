
function draw()

    of.fx_kale(2)
    
    
    of.fx_wave(9);
    of.feedback(true);
    
    
    of.fx_kale(1)
    of.feedback(true);
    of.fx_grid(4)
    -- of.feedback(true);
    
    
-- of.feedback(true);

    
   
    of.fx_kale(1.2)

   
    
    -- of.fx_grid(1.1)

    -- of.feedback(true);

    -- of.feedback(true);
    -- of.rotate(of.frame(), 0.5, 0.2, 0.1337)

    
    of.hsl(of.int_beat() * 60 + of.frame(), 1, 1 )

    of.blend_mode("add")

    local times = 50;

    local b = of.beat()

    local bP = (  b - math.floor(b))

    local sizeMulitpler = 900 * bP;

    for i = times,1,-1 
    do 
        of.pushMatrix()
        of.rotate(i+of.frame(), 12.3, 2.3, 5)
        of.translate(
            math.cos(i*1.637) * sizeMulitpler, 
            math.sin(i*1.637) * sizeMulitpler
    )
    of.rotate(i+of.frame(), 12.3, 2.3, 5)
        of.box(of.fft(6) * 50)
        of.popMatrix()
    end

    

end
