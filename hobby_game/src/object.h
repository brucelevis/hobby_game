#pragma once

namespace hg
{
    class ObjectScene;

    class Object
    {
    public:
        Object(ObjectScene& scene, int id);
        virtual ~Object();

        ObjectScene& get_scene() const { return m_scene; }
        int get_id() const { return m_id; }

    private:
        ObjectScene& m_scene;
        int m_id;
    };
}