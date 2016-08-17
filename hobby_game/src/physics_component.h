#pragma once

#include "component.h"

#include <vecmath/vector.hpp>

namespace hg
{
    class PhysicsScene;

    enum class PhysicsComponentType
    {
        empty,
        box,
        circle,
        grid
    };

    class PhysicsComponent
        : public Component
    {
    public:
        PhysicsComponent(PhysicsScene& scene, int id, Level& level, int entity_id);
        virtual ~PhysicsComponent();

        void set_mass(float mass) { m_mass = mass; }
        void set_position(const vcm::vec2& position) { m_position = position; }
        void set_velocity(const vcm::vec2& velocity) { m_velocity = velocity; }

        ComponentType get_component_type() const override { return ComponentType::physics; }

        virtual PhysicsComponentType get_physics_type() const = 0;

        float get_mass() const { return m_mass; }
        const vcm::vec2& get_position() const { return m_position; }
        const vcm::vec2& get_velocity() const { return m_velocity; }

    protected:
        friend class PhysicsScene;

        float m_mass;
        vcm::vec2 m_position;
        vcm::vec2 m_velocity;
    };
}