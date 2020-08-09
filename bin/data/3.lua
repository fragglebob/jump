function draw()

    -- of.fx_kale(8)
    -- of.fx_grid(12)
    -- of.fx_wave(12)

    of.blend_mode("add")
    -- of.line_width(of.fft(1) * 6 + 1)

    local frame = of.frame() / 10

   

    local spread = 40
    local xTimes = 10;
    local xStart = -(xTimes * spread / 2);
    local yTimes = 10;
    local yStart = -(yTimes * spread / 2);
    local zTimes = 10;
    local zStart = -(zTimes * spread / 2);

    local size = of.fft(1) * 40 + 10;

    of.pushMatrix()

    of.translate(0,0,-800)
    of.rotate(frame, 0.1, 0.5, 0.23);
    of.scale(4)

    for x = xTimes,1,-1 
    do
        of.pushMatrix()
        of.scale(2, of.fft(x + xTimes) * 2 + 0.4, of.fft(x + xTimes) * 2  + 0.4)

            for y = yTimes,1,-1 
            do
        
                for z = zTimes,1,-1 
                do

                    of.pushMatrix()

                    of.translate(
                        xStart + x * spread, 
                        yStart + y * spread, 
                        zStart + z * spread
                    )

                    of.rotate(-frame, 0.4, 0.1, 0.6);

                    of.color(
                        math.max(math.cos((frame + x + y) / 46) * 250.0, 100), 
                        math.max(math.abs(math.cos((frame + x + y) / 37)) * 250.0, 50), 
                        math.max(math.sin((frame + x + y) / 23) * 250.0, 20)
                    )
            
                    of.box(
                        size
                    );

                    of.popMatrix()
                end

            end
            of.popMatrix()
    end
    of.popMatrix()


end