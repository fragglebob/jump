function draw()

    -- 

    of.texture_start("fish-fingers.jpg");


    local c = 50

    local s = math.pow(of.beat()%1, 4)

    for i = c,1,-1 
    do 
        of.pushMatrix();

        of.translate(
            math.sin(i * 13.3 + of.frame() / 100) * 1200, 
            math.cos(i * 26.9 + of.frame() / 100) * 600
        )

        of.rotate(i + of.frame(), 0.5, 0.2, 0.8)
        of.hsl((of.int_beat()) * 60 + (of.frame()+ i)/10, 1.0 - of.fft(12)/3, of.fft(3) * 0.4 + 0.1)
        of.box(200 * s * of.fft(5));

        of.popMatrix();
    end

    of.texture_end("fish-fingers.jpg");


    of.fx_rgb(0.0013)

    of.feedback(true)
    
    

    -- of.fx_kale(4, ((of.int_beat())%16)*15.7)
    -- of.fx_grid(1.3)

    -- of.feedback(true);
    
    -- of.fx_bloom()
    
end
