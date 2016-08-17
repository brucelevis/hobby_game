#include "audio_component.h"

#include "audio_scene.h"

namespace hg
{
    AudioComponent::AudioComponent(AudioScene& scene, int id, Level& level, int entity_id)
        : Component(scene, id, level, entity_id)
    {

    }

    AudioComponent::~AudioComponent()
    {

    }
}