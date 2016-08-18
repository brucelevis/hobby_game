#pragma once

#include <vector>

namespace hg
{
    class Object;

    class ObjectScene
    {
    public:
        ObjectScene();
        virtual ~ObjectScene();

        void clear();

        Object* const * get_objects() const { return m_objects.data(); }
        int get_num_objects() const { return (int)m_objects.size(); }
    
    protected:
        int new_object_id() { return m_next_object_id++; }

        virtual int create_object(Object* object);
        virtual void destroy_object(int id);
        virtual Object* get_object(int id) const;

    private:
        int m_next_object_id;
        std::vector<Object*> m_objects;
    };
}