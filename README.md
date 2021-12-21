# JUMP

Live Coding visuals with Lua, powered by openframeworks.

It some fft and tempo matching fun built in.

# Required Shared Libaries

* lua5.1
* audio - for the realtime tempo stuff
* asound
* gstreamer
* boost_filesystem
* boost_system
* rtaudio
* plus anything required by open frameworks

# Running

Firstly there are a few settings that can be configured in a `settings.xml` file in the `data` directory.

```xml
<settings>
    <audioIn>Scarlett 2i4 USB</audioIn><!-- For configuring your audio in -->
</settings>
```

In the `data` directory, is the main fun. The file `0.lua`. Inside of it should be a function called `draw` this will be called when openframeworks wants to draw. The file is auto reloaded when you make changes.

# Example Visual

```lua
function draw()
    of.fx_kale(of.lerp(1, 10, of.slider(0)))
    of.fx_grid(of.lerp(1, 16, of.slider(1)))

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
end
```

# Lua Functions Avalible

All of the standard math library is enabled in the lua env along with all these functions for do fun stuff with. 

```lua
// utilities
of.frame() // returns number of frames passed
of.time() // returns amount of timetime passed
of.fft(number0to12) // returns the fft value

of.slider(number) // akai midimix slider value
of.knob(number) // akai midimix knob value

of.lerp(min, max, amt)

of.beat() // returns the current beat as a float
of.int_beat() // returns the current beat as a int

of.bar() // returns the current bar as a float
of.int_bar() // returns the current bar as a int

// lines
of.line(x1, y1, x2, y2)
of.line(x1, y1, z1, x2, y2, z2)

of.line_width(size)

// boxes
of.box(size)
of.box(width, heigth, depth)
of.box(x, y, z, size)
of.box(x, y, z, width, heigth, depth)

// balls
of.ball(size)
of.ball(x, y, z, size)

// postfx
of.fx_wave(segments)
of.fx_kale(segments)
of.fx_kale(segments, time)
of.fx_grid(gridSize)
of.fx_rgb(amount)
of.fx_bloom()

of.feedback()

// style
of.pushStyle()
of.popStyle()

of.color(r, g, b) // 0 - 255
of.color(r, g, b, a) // 0 - 255
of.color(grey) // 0 - 255

of.hsl(h, s, l)

of.blend_mode(blendMode) // "add", "alpha", "multiply", "screen", "off"

// transforms

of.pushMatrix()
of.popMatrix()

of.rotate(degrees) // z
of.rotate(degrees, vecX, vecY, vecZ)

of.rotateX(degrees)
of.rotateY(degrees)
of.rotateZ(degrees)

of.rotateRad(rad) // z
of.rotateRad(rad, vecX, vecY, vecZ)

of.rotateXRad(rad)
of.rotateYRad(rad)
of.rotateZRad(rad)

of.scale(amount)
of.scale(xAmount, yAmount, zAmount)

of.translate(x, y)
of.translate(x, y, z)
```


# Building

Currently only got builds working on linux with cmake. Adapated it from ofxCmake but changes to work with the new version of openframeworks.

## Required Addons

* ofxPostProcessing
* ofxMidi
* ofxXmlSettings - included with openframeworks

## Credits

bin/data/fish-fingers.jpg - © Superbass / CC-BY-SA-4.0 (via Wikimedia Commons) - https://commons.wikimedia.org/wiki/File:Fishfinger_classic_fried_2.jpg