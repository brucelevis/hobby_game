AssetType = {}
AssetType.bitmap = 1
AssetType.texture = 2
AssetType.tilemap = 3
AssetType.sound_clip = 4

-- Stores references to all the assets in the game.
assets = {}

assets.bitmaps = {}
assets.sound_clips = {}
assets.textures = {}
assets.tilemaps = {}

local bitmaps = assets.bitmaps
local sound_clips = assets.sound_clips
local textures = assets.textures
local tilemaps = assets.tilemaps

-- Bitmaps
bitmaps.test_tiles = api.load_asset(AssetType.bitmap, "test_tiles.lua")

-- Sound clips
sound_clips.test = api.load_asset(AssetType.sound_clip, "test.lua")

-- Textures
textures.test_tiles = api.load_asset(AssetType.texture, "test_tiles.lua")

-- Tilemaps
tilemaps.test = api.load_asset(AssetType.tilemap, "test.lua")