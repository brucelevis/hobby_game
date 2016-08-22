#pragma once

#include "object_scene.h"
#include "component_type.h"
#include "audio_scene.h"
#include "physics_scene.h"
#include "render_scene.h"
#include "behavior_scene.h"

namespace hg
{
    class Game;
    class Entity;
    class Component;

    class Level
        : public ObjectScene
    {
    public:
        Level();

        int create_entity();
        void destroy_entity(int id);
        Entity* get_entity(int id) const;

        void destroy_component(ComponentType type, int id);
        Component* get_component(ComponentType type, int id) const;

        Component* get_component_of(int entity_id, ComponentType type) const;

        Game* get_game() const { return m_game; }

        AudioScene& get_audio() { return m_audio; }
        const AudioScene& get_audio() const { return m_audio; }

        PhysicsScene& get_physics() { return m_physics; }
        const PhysicsScene& get_physics() const { return m_physics; }

        RenderScene& get_render() { return m_render; }
        const RenderScene& get_render() const { return m_render; }

        BehaviorScene& get_behavior() { return m_behavior; }
        const BehaviorScene& get_behavior() const { return m_behavior; }

    protected:
        friend class Game;

        void init(Game& game);
        void destroy();

        void tick(float dt);
        void render();

    private:
        Game* m_game;

        AudioScene m_audio;
        PhysicsScene m_physics;
        RenderScene m_render;
        BehaviorScene m_behavior;
    };
}