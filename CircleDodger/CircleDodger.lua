local SCREEN_W = 320
local SCREEN_H = 240

local PLAYER_R = 10
local PLAYER_COLOR = 0x001F   -- blue
local ENEMY_R = 8
local ENEMY_COLOR = 0xF800    -- red
local BG_COLOR = 0x0000       -- black
local TEXT_COLOR = 0xFFFF     -- white

local SPAWN_INTERVAL = 1500
local SPEED = 1.2

local enemies = {}
local alive = true
local score = 0

local px = SCREEN_W // 2
local py = SCREEN_H // 2

-- spawn enemy WITHOUT table.insert
local function spawnEnemy()
    local side = random(1, 4)
    local ex, ey

    if side == 1 then
        ex = random(0, SCREEN_W)
        ey = -20
    elseif side == 2 then
        ex = SCREEN_W + 20
        ey = random(0, SCREEN_H)
    elseif side == 3 then
        ex = random(0, SCREEN_W)
        ey = SCREEN_H + 20
    else
        ex = -20
        ey = random(0, SCREEN_H)
    end

    enemies[#enemies + 1] = {
        x = ex,
        y = ey,
        dx = (px - ex) * 0.05 * SPEED,
        dy = (py - ey) * 0.05 * SPEED
    }
end

-- update enemies WITHOUT ipairs
local function updateEnemies()
    for i = 1, #enemies do
        local e = enemies[i]
        e.x = e.x + e.dx
        e.y = e.y + e.dy

        local dx = e.x - px
        local dy = e.y - py

        if dx*dx + dy*dy <= (PLAYER_R + ENEMY_R)*(PLAYER_R + ENEMY_R) then
            alive = false
        end
    end
end

local function draw()
    clearScreen(BG_COLOR)

    -- draw player
    fillCircle(px, py, PLAYER_R, PLAYER_COLOR)

    -- draw enemies (force integer coords)
    for i = 1, #enemies do
        local e = enemies[i]

        local ix = e.x - (e.x % 1)
        local iy = e.y - (e.y % 1)

        fillCircle(ix, iy, ENEMY_R, ENEMY_COLOR)
    end

    printText("Score: " .. score, 5, 5, TEXT_COLOR, BG_COLOR, 2, false, false)
end

local function handleTouch()
    local t = pollTouch()
    if t then
        px = t.x
        py = t.y
    end
end

local elapsed = 0
local lastSpawn = 0

while alive do
    handleTouch()
    updateEnemies()
    draw()

    delay(16)
    elapsed = elapsed + 16

    if elapsed - lastSpawn >= SPAWN_INTERVAL then
        spawnEnemy()
        lastSpawn = elapsed

        if SPAWN_INTERVAL > 300 then
            SPAWN_INTERVAL = SPAWN_INTERVAL - 50
        end

        SPEED = SPEED + 0.05
    end

    score = elapsed // 100
end

clearScreen(BG_COLOR)
printText("GAME OVER", 60, 80, ENEMY_COLOR, BG_COLOR, 3, false, false)
printText("Score: " .. score, 60, 120, TEXT_COLOR, BG_COLOR, 2, false, false)
delay(2000)
