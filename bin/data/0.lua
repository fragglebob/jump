function draw()


    of.blend_mode("add")


    

    of.rotateY(of.bar() * 45)

    -- of.scale(math.pow((math.sin((math.pi * 1) * (of.bar())) + 1) / 2, 4) + 1.2)

    for i = 200,1,-1 
    do 
        of.pushMatrix()

        of.translate(
            math.sin(i * i * 0.4 + of.time() / 100000) * 1000,
            math.cos(i * 0.2 + of.time() / 100000) * 1000, 
            math.cos(i * 0.9 * i + of.time() / 50000) * 1000
        )
        of.rotate(of.frame() + i, 0.1, 0.8, 0.3)

        if i % 4 == of.int_beat() then
            of.color(220, 40, 0)
            of.box(50 + of.fft(i % 10 + 1) * 50)
        else
            of.color(220, 0, 15)
            of.box(10 + of.fft(i % 10 + 1) * 50)
        end

        

        of.popMatrix()
    end





end