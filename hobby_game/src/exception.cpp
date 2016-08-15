#include "exception.h"

namespace hg
{
    Exception::Exception()
    {

    }

    Exception::Exception(const char* what)
        : m_what(what)
    {

    }

    Exception::Exception(const std::string& what)
        : m_what(what)
    {

    }

    const char* Exception::what() const
    {
        return m_what.c_str();
    }
}