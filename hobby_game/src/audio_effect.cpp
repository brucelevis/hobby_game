#include "audio_effect.h"

namespace hg
{
    AudioEffect::AudioEffect(AudioScene& scene, int id, Level& level, int entity_id)
        : AudioComponent(scene, id, level, entity_id)

        , m_sound_clip_asset()
    {

    }

    void AudioEffect::play()
    {

    }
}