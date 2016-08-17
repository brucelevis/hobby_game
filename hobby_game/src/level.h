#pragma once

#include "object_scene.h"
#include "component_type.h"
#include "physics_scene.h"

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

    protected:
        friend class Game;

        void init(Game& game);

        void tick(float dt);

    private:
        Game* m_game;

        PhysicsScene m_physics;
    };
}