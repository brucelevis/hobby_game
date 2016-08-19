#include "audio_scene.h"

#include "audio_effect.h"

namespace hg
{
    AudioScene::AudioScene()
    {

    }

    int AudioScene::create_effect(int entity_id)
    {
        auto effect = new AudioEffect(*this, new_object_id(), *get_level(), entity_id);
        return create_object(effect);
    }

    AudioEffect* AudioScene::get_effect(int id) const
    {
        auto o = (AudioComponent*)get_object(id);
        if (o->get_audio_type() == AudioComponentType::effect)
            return (AudioEffect*)o;

        return nullptr;
    }
}