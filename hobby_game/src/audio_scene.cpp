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
}