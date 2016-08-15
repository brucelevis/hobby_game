#include "util.h"

namespace hg
{
    void split_string(const std::string& str, const char* delim, int num_delim, std::vector<std::string>& out)
    {
        const char* c = str.data();
        const char* end = str.data() + str.size();

        auto is_delim = [&c, delim, num_delim]()
        {
            bool hit_delim = false;
            for (int i = 0; i < num_delim; ++i)
            {
                if (*c == delim[i])
                {
                    hit_delim = true;
                    break;
                }
            }

            return hit_delim;
        };

        std::string elem;
        elem.reserve(128);

        for (; c != end;)
        {
            bool hit_delim = is_delim();

            if (!hit_delim)
            {
                elem.push_back(*c);
                ++c;
            }
            else
            {
                out.push_back(elem);
                elem.clear();

                while (is_delim())
                    ++c;
            }
        }

        if (!elem.empty())
            out.push_back(elem);
    }
}