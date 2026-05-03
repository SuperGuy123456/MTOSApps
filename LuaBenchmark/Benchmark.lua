print("=== LUA RECT BENCHMARK ===")

-- Clear screen benchmark
local t0 = getTime()
clearScreen(0x0000)
local t1 = getTime()
print("ClearScreen: "..(t1 - t0).." ms")

-- Text benchmark
t0 = getTime()
printText("Benchmarking...", 10, 10, 0xFFFF, 0, 2, true, false)
t1 = getTime()
print("DrawText: "..(t1 - t0).." ms")

-- Rectangle benchmark
local RECT_COUNT = 50
local start = getTime()

for i = 1, RECT_COUNT do
    local x = random(0, 319)
    local y = random(0, 239)
    local w = random(5, 60)
    local h = random(5, 60)
    local color = random(0, 65535)

    fillRect(x, y, w, h, color)
end

local finish = getTime()
local total = finish - start

print("Rect total: "..total.." ms")
print("Rect avg: "..(total / RECT_COUNT).." ms")

-- FPS test (clear only)
local frameStart = getTime()
local frames = 0

while getTime() - frameStart < 1000 do

    clearScreen(0x0000)
    frames = frames + 1
end

print("FPS (clear only): "..frames)

-- Try at draw fps
local t0 = getTime()
for i = 1, 100 do
    clearScreen(0)
end
local t1 = getTime()

local avg = (t1 - t0) / 100
local fps = 1000 / avg

print("Lua real FPS: "..fps)

print("=== END BENCH ===")
