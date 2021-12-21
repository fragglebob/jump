function draw()

    of.pushMatrix()

    of.hsl((of.int_beat()) * 30 + (of.frame()+120)/5, 1.0 - of.fft(12)/3, of.fft(3) * 0.4 + 0.1)
    of.rotate(of.frame(), 0.1, 0.3, -0.1)
    of.box( 480 * of.fft(10))

    of.popMatrix()

    of.feedback(true)

    local f = of.frame()
    local times = math.min(math.pow(of.fft(12), 4) * 30 + 10, 1000)
    local spread = math.pow(of.fft(6), 2) * 10 + 10

    local maxSize = 1600

    of.line_width(16)

    for i = times,1,-1 
    do 

        of.hsl((of.int_beat()) * 60 + (of.frame()+ i)/10, 1.0 - of.fft(12)/3, of.fft(3) * 0.4 + 0.1)
        -- of.color((i / times) * 254.9, 100.1, 200.1)

        local index1 = f + (i * spread)
        local index2 = f + ((i + 1) * spread) 

        of.line(
            math.sin(index1 / 31.0) * maxSize, 
            math.cos(index1 / 46.0) * maxSize, 
            math.sin(index2 / 31.0) * maxSize, 
            math.cos(index2 / 46.0) * maxSize
        )
    end

    

      of.fx_matrix(
        0.999, math.sin(of.frame() / 1437 ) *-0.0005, math.sin(of.frame() / 1347 ) * 0.0005,
        -0.0005, 0.999, math.sin(of.frame()/1400 ) *0.0005
    )


    of.fx_rgb(0.0002)

    of.feedback(true)
    
    

    of.fx_kale(4, ((of.int_beat())%16)*15.7)


    

    -- 

    -- of.fx_grid((math.floor(of.beat())%4)*3+1)
    of.fx_grid(1.5)

    of.fx_kale(1.3, of.frame()/200)

    
 

    of.fx_rgb(0.0009)
    of.fx_bloom()

end
