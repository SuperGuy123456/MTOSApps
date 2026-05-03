-- Clear screen to black
clearScreen(0x0000)
delay(500)

-- Cycle colors
clearScreen(0xF800)   -- red
delay(500)

clearScreen(0x07E0)   -- green
delay(500)

clearScreen(0x001F)   -- blue
delay(500)

-- Draw some text
printText("Hello from Lua!",
    10, 10,
    0xFFFF, 0x0000,
    2, true, false)

-- Touch test loop
while true do
    local t = pollTouch()
    if t then
        clearScreen(0x0000)
        printText("Touched!", t.x, t.y,
            0xFFFF, 0x0000,
            2, true, false)
    end

    delay(16)
end
