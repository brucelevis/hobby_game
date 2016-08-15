local tilemap = {}

tilemap.texture = "test_tiles.lua"
tilemap.width = 20
tilemap.height = 20
tilemap.tile_width = 32
tilemap.tile_height = 32

tilemap.tiles = {}

for i = 1, tilemap.width do
    for j = 1, tilemap.height do
        table.insert(tilemap.tiles, math.floor(math.random() * (15 * 8)))
    end
end

return tilemap