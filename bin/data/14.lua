function draw()

    local times = 100;

    

    local ilongbeat = math.floor(of.beat())

    for i = times,1,-1 
    do 


        of.hsl(350 + of.int_beat() * 30 + math.sin(i) * 3, 1-of.fft(10)/8, 0.7);

        local x = i*543.279 + math.sin(i*93.87)
        x = ((x - math.floor(x)) - 0.5) * 2 * 1200;

        local y = 0;

        y = (math.abs(math.sin(math.cos(i*13.59)*29.123 + (of.frame()/200) * math.sin(i) * 2 + ilongbeat)) - 0.5) * 2 *600

        of.pushMatrix()
        of.translate(x, y)
        of.rotate(of.frame() + math.sin(i)*9123, 0.1, 0.3, -0.1)
        of.box(20 * of.fft(0))
        of.popMatrix()

    end

    of.fx_grid((math.floor(of.beat())%4)+1)

    of.feedback(true)
    of.fx_ascii((1-of.fft(10)) * 80 +  10)
    of.fx_wave(12)
    -- of.fx_grid(11)
    
    
    
    
    -- of.fx_rgb(0.001)

    of.feedback(true)

    of.fx_matrix(
        0.95, math.cos(of.frame() / 1000) * 0.01, 0,
        math.sin(of.frame() / 500) * 0.01, 0.95, 0
    )


    

    of.feedback(true)



    

    of.rotate(of.frame(), 0.1, 0.3, -0.1)
    of.box( 180 * of.fft(0))

    --  

    -- of.fx_grid((math.floor(of.beat()-2)%4)+2)

    -- of.feedback(true)

    -- of.fx_bloom()

end
