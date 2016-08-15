#pragma once

#include "types.h"

#include <vector>
#include <string>

namespace hg
{
    class Bitmap
    {
    public:
        Bitmap();
        
        /*
            Loads a bitmap from a file.
            Throws.
        */
        void load(const std::string& file_name);

        const ubyte* get_pixels() const { return m_pixels.data(); }
        int get_bpp() const { return m_bpp; }
        int get_width() const { return m_width; }
        int get_height() const { return m_height; }

    private:
        std::vector<ubyte> m_pixels;
        int m_bpp; //bytes per pixel
        int m_pitch; //length of a row of pixels in bytes
        int m_width;
        int m_height;
    };
}