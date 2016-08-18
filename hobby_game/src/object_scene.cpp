#include "object_scene.h"

#include "object.h"

namespace hg
{
    ObjectScene::ObjectScene()
        : m_next_object_id(1)
    {

    }

    ObjectScene::~ObjectScene()
    {
        for (auto s : m_objects)
            delete s;

        if (!m_objects.empty())
            m_objects.clear();
    }

    int ObjectScene::create_object(Object* object)
    {
        m_objects.push_back(object);
        return object->get_id();
    }

    void ObjectScene::destroy_object(int id)
    {
        for (auto it = m_objects.begin(); it != m_objects.end(); ++it)
        {
            if ((*it)->get_id() == id)
            {
                delete *it;
                m_objects.erase(it);
                break;
            }
        }
    }

    Object* ObjectScene::get_object(int id) const
    {
        for (auto s : m_objects)
        {
            if (s->get_id() == id)
                return s;
        }

        return nullptr;
    }

    void ObjectScene::clear()
    {
        for (auto o : m_objects)
            delete o;

        if (!m_objects.empty())
            m_objects.clear();
    }
}