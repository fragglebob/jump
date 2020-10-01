function draw()

 

    local time = of.frame();

    local pro = of.beat() - math.floor(of.beat());

    of.color(100, 100, 0)

    for i = 60,1,-1 
    do 

        local posz = i/60 + (of.frame())*0.0005
        posz = posz - math.floor(posz)

        of.pushMatrix()
        of.scale(10)
        of.translate(
            math.sin(math.pi * 2 * posz )* 10, 
            20, 
            posz * 1600 - 1500
        )
        of.box(30, 1, 10 + of.fft(6) * 6)
        of.popMatrix()
        
    end




end