#include "level.h"

#include "game.h"
#include "asset_bank.h"

#include "sound_clip_asset.h"

#include <AL/al.h>
#include <AL/alc.h>

namespace hg
{
    Level::Level()
        : m_game()
    {

    }

    static bool check_rects(const vcm::vec4& a, const vcm::vec4& b)
    {
        if (a.x + a.z < b.x)
            return false;
        if (a.y + a.w < b.y)
            return false;
        if (a.x > b.x + b.z)
            return false;
        if (a.y > b.y + b.w)
            return false;

        return true;
    }

    void Level::init(Game& game)
    {
        m_game = &game;

        m_player.init(*this);
        
        int tilemap_asset_id = game.get_assets().get_asset_id(AssetType::tilemap, "test.lua");
        auto tilemap_asset = game.get_assets().get_tilemap(tilemap_asset_id);
        m_tilemap.create(*tilemap_asset);

        int sound_id = game.get_assets().get_asset_id(AssetType::sound_clip, "test.lua");
        auto sound_asset = game.get_assets().get_sound_clip(sound_id);
        
        const auto& wav_file = sound_asset->get_wav_file();
        
        /*
        TODO: replace with abstract way

        ALuint buffer;
        alGenBuffers(1, &buffer);

        alBufferData(buffer, AL_FORMAT_STEREO16, wav_file.get_data(), wav_file.get_data_size(), wav_file.get_sample_rate());

        ALuint source;
        alGenSources(1, &source);
        alSourceQueueBuffers(source, 1, &buffer);
        alSourcePlay(source);
        */
    }

    void Level::tick(float dt)
    {
        m_player.tick(dt);
    }
}