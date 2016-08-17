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

        int test_entity = create_entity();
        /*
        create_component(ComponentType::physics, test_entity);
        auto physics = (PhysicsComponent*)get_component_of(test_entity, ComponentType::physics);
        physics->set_position(vcm::vec2(100, 100));
        */

        int sound_id = game.get_assets().get_asset_id(AssetType::sound_clip, "test.lua");
        auto sound_asset = game.get_assets().get_sound_clip(sound_id);
        
        SoundBuffer buffer;
        buffer.create(*sound_asset);
        SoundSource source;
        source.create();
        source.set_buffer(buffer);
        source.play();
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