#pragma once

#include "audio_component.h"

namespace hg
{
    class AudioEffect
        : public AudioComponent
    {
    public:
        AudioEffect(AudioScene& scene, int id, Level& level, int entity_id);

        void play();

        void set_sound_clip_asset(int sound_clip_asset) { m_sound_clip_asset = sound_clip_asset; }
        int get_sound_clip_asset() const { return m_sound_clip_asset; }

        AudioComponentType get_audio_type() const override { return AudioComponentType::effect; }

    private:
        int m_sound_clip_asset;
    };
}