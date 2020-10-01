function draw()


    of.blend_mode("add")


    

    of.rotateY(0.01 * of.time())

    -- of.scale(math.pow((math.sin((math.pi * 1) * (of.bar())) + 1) / 2, 4) + 1.2)

    local t = of.time()
    local s = of.beat() / 4

    for i = 1000,1,-1 
    do 
        of.pushMatrix()

        of.translate(
            math.sin(i * i * 0.4 + t / 100000) * 1000,
            math.cos(i * 0.2 + t / 100000) * 1000, 
            math.cos(i * 0.9 * i + t / 50000) * 1000
        )
        of.rotate(of.frame() + i, 0.1, 0.8, 0.3)

        if i % 4 == of.int_beat() then
            of.hsl(0, 0.1, 0.9)
            of.box(50)
        else
            of.hsl(100 + s * 120, 0.8, 0.5)
            of.box(20)
        end

        

        of.popMatrix()
    end





end