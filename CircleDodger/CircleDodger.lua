local SCREEN_W = 320
local SCREEN_H = 240

local PLAYER_R = 10
local PLAYER_COLOR = 0x001F   -- blue (565)
local ENEMY_R = 8
local ENEMY_COLOR = 0xF800    -- red
local BG_COLOR = 0x0000       -- black
local TEXT_COLOR = 0xFFFF     -- white

local SPAWN_INTERVAL = 1500   -- ms-ish, we’ll just use delay-based timing
local SPEED = 1.2

local enemies = {}
local lastSpawn = 0
local score = 0
local alive = true

local px = SCREEN_W // 2
local py = SCREEN_H // 2

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

    table.insert(enemies, {
        x = ex,
        y = ey,
        dx = (px - ex) * 0.05 * SPEED,
        dy = (py - ey) * 0.05 * SPEED
    })
end

local function updateEnemies()
    for _, e in ipairs(enemies) do
        e.x = e.x + e.dx
        e.y = e.y + e.dy

        local dx = e.x - px
        local dy = e.y - py
        if dx*dx + dy*dy <= (PLAYER_R + ENEMY_R)^2 then
            alive = false
        end
    end
end

local function draw()
    clearScreen(BG_COLOR)

    fillCircle(px, py, PLAYER_R, PLAYER_COLOR)

    for _, e in ipairs(enemies) do
        fillCircle(e.x, e.y, ENEMY_R, ENEMY_COLOR)
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
local lastSpawnTime = 0

while alive do
    handleTouch()
    updateEnemies()
    draw()

    delay(16)
    elapsed = elapsed + 16

    if elapsed - lastSpawnTime >= SPAWN_INTERVAL then
        spawnEnemy()
        lastSpawnTime = elapsed
        SPAWN_INTERVAL = math.max(300, SPAWN_INTERVAL - 50)
        SPEED = SPEED + 0.05
    end

    score = elapsed // 100

end

clearScreen(BG_COLOR)
printText("GAME OVER", 60, 80, ENEMY_COLOR, BG_COLOR, 3, false, false)
printText("Score: " .. score, 60, 120, TEXT_COLOR, BG_COLOR, 2, false, false)
delay(2000)
