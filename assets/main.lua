require 'assets'

local entity = api.create_entity()

local effect = api.create_audio_effect(entity)
api.set_audio_effect_sound_clip(effect, api.get_asset_id(AssetType.sound_clip, "test.lua"))
api.play_audio_effect(effect)

local empty = api.create_physics_empty(entity)
api.set_physics_position(empty, 200.0, 100.0)

local sprite = api.create_render_sprite(entity)
api.set_sprite_texture(sprite, api.get_asset_id(AssetType.texture, "test_tiles.lua"))