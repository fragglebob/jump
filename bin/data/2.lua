function draw()

    -- of.fx_kale(of.lerp(1, 10, of.slider(0)))
    -- of.fx_grid(of.lerp(1, 16, of.slider(1)))
    -- of.fx_wave(of.lerp(1, 32, of.slider(2)))

    of.blend_mode("add")
    -- of.line_width(of.fft(1) * 6 + 1)

    -- of.color(250, 200, 100)

    local time = of.frame();

    for i = 60,1,-1 
    do 
        local t = (time + i * 20) / 1000;
        local scale = math.pow((t - (math.floor(t))) * 2, 10) * of.fft(4);
        of.color(250 * i/60, of.fft(1) * 200, 100)

        of.line_width(scale* 5)

        of.line(-100 * scale, -100 * scale, -100 * scale, 100 * scale)
        of.line(-100 * scale, -100 * scale, 100 * scale, -100 * scale)
        of.line(100 * scale, -100 * scale, 100 * scale, 100 * scale)
        of.line(100 * scale, 100 * scale, -100 * scale, 100 * scale)
    end




end