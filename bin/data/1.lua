function draw()

    of.fx_kale(of.lerp(1, 10, of.slider(0)))
    of.fx_grid(of.lerp(1, 16, of.slider(1)))
    -- of.fx_wave(of.lerp(1, 32, of.slider(2)))

    of.blend_mode("add")
    of.line_width(of.fft(1) * 16 + 1)

    local f = of.frame()
    local times = math.floor(of.fft(1) * 140) + 20
    local spread = of.fft(6) + 2

    local maxSize = 1000

    for i = times,1,-1 
    do 
        of.color((i / times) * 254.9, 100.1, 200.1)
        of.line(
            math.sin((f + i * spread) / 31.0) * maxSize, 
            math.cos((f + i * spread) / 46.0) * maxSize, 
            math.cos((f + i * spread) / 67.0) * maxSize, 
            math.sin((f + i * spread) / 142.0) * maxSize
        )
    end

    maxSize = 500

    f = f + 1000

    for i = times,1,-1 
    do 
        of.color(100.1, (i / times) * 254.9, 100.1)
        of.line(
            math.sin((f + i * spread) / 81.0) * maxSize, 
            math.cos((f + i * spread) / 42.0) * maxSize, 
            math.cos((f + i * spread) / 54.0) * maxSize, 
            math.sin((f + i * spread) / 69.0) * maxSize
        )
    end

    f = f + 1000

    maxSize = 800

    for i = times,1,-1 
    do 
        of.color(50.1, 200.1, (i / times) * 254.9)
        of.line(
            math.sin((f + i * spread) / 211.0) * maxSize, 
            math.cos((f + i * spread) / 133.0) * maxSize, 
            math.cos((f + i * spread) / 111.0) * maxSize, 
            math.sin((f + i * spread) / 269.0) * maxSize
        )
    end
 
end