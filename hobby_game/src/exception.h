#pragma once

#include <string>
#include <exception>

namespace hg
{
    class Exception 
        : public std::exception
    {
    public:
        Exception();
        explicit Exception(const char* what);
        explicit Exception(const std::string& what);

        virtual const char* what() const override;

    private:
        std::string m_what;
    };
}