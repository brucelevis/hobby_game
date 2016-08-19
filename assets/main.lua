require 'assets'

--[[
local entity = api.create_entity()
local effect = api.create_audio_effect(entity)
api.set_audio_effect_sound_clip(effect, api.get_asset_id(AssetType.sound_clip, "test.lua"))
]]