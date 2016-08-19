#include "level.h"

#include "game.h"

#include "entity.h"
#include "component.h"

#include "asset_bank.h"
#include "sound_clip_asset.h"

#include <AL/al.h>
#include <AL/alc.h>

#include "physics_component.h"

#include "sound_source.h"
#include "sound_buffer.h"

#include "audio_effect.h"

#include <SDL2/SDL.h>

namespace hg
{
    Level::Level()
        : m_game()
    {

    }

    void Level::init(Game& game)
    {
        m_game = &game;

        m_physics.init(*this);
        m_audio.init(*this);

        int test_entity = create_entity();
        int audio_effect = m_audio.create_effect(test_entity);
        auto effect = (AudioEffect*)m_audio.get_effect(audio_effect);
        effect->set_sound_clip_asset(get_game()->get_assets().get_asset_id(AssetType::sound_clip, "test.lua"));
        effect->play();
    }

    void Level::destroy()
    {
        m_audio.clear();
        m_physics.clear();
    }

    void Level::tick(float dt)
    {
        
    }

    int Level::create_entity()
    {
        Entity* e = new Entity(*this, new_object_id());
        return create_object(e);
    }

    void Level::destroy_entity(int id)
    {
        destroy_object(id);
    }

    Entity* Level::get_entity(int id) const
    {
        return (Entity*)get_object(id);
    }

    void Level::destroy_component(ComponentType type, int id)
    {
        switch (type)
        {
        case ComponentType::physics:
            m_physics.destroy_object(id);
            break;
        }
    }

    Component* Level::get_component(ComponentType type, int id) const
    {
        switch (type)
        {
        case ComponentType::physics:
            return (Component*)m_physics.get_object(id);
        }

        return nullptr;
    }

    Component* Level::get_component_of(int entity_id, ComponentType type) const
    {
        switch (type)
        {
        case ComponentType::physics:
            return m_physics.get_component_of(entity_id);
        }

        return nullptr;
    }
}