#pragma once

#include "component.h"
#include "sound_source.h"

namespace hg
{
    class AudioScene;

    enum class AudioComponentType
    {
        effect,
        music
    };

    class AudioComponent
        : public Component
    {
    public:
        AudioComponent(AudioScene& scene, int id, Level& level, int entity_id);
        virtual ~AudioComponent();

        ComponentType get_component_type() const override { return ComponentType::audio; }

        virtual AudioComponentType get_audio_type() const = 0;

    protected:
        SoundSource m_source;
    };
}