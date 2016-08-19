#include "audio_effect.h"

#include "level.h"
#include "game.h"

#include "sound_clip_asset.h"

namespace hg
{
    AudioEffect::AudioEffect(AudioScene& scene, int id, Level& level, int entity_id)
        : AudioComponent(scene, id, level, entity_id)

        , m_sound_clip_asset()
    {

    }

    void AudioEffect::play()
    {
        m_source.play();
    }

    void AudioEffect::set_sound_clip_asset(int asset)
    {
        if (m_sound_clip_asset != asset)
        {
            m_sound_clip_asset = asset;

            auto game = get_level().get_game();
            auto assets = game->get_assets();
            auto sound_clip = assets.get_sound_clip(m_sound_clip_asset);

            m_source.set_buffer(sound_clip->get_sound_clip().get_buffer());
        }
    }

    int AudioEffect::get_sound_clip_asset() const
    {
        return m_sound_clip_asset;
    }
}