#include "bitmap.h"

#include <SDL2/SDL_image.h>

#include "exception.h"

namespace hg
{
    Bitmap::Bitmap()
        : m_bpp()
        , m_pitch()
        , m_width()
        , m_height()
    {

    }

    void Bitmap::load(const std::string& file_name)
    {
        auto surf = IMG_Load(file_name.c_str());
        if (!surf)
            throw Exception(SDL_GetError());

        m_bpp = surf->format->BytesPerPixel;
        m_width = surf->w;
        m_height = surf->h;
        m_pitch = m_width * 4;
        m_pixels.resize(m_height * m_pitch);

        auto spxls = (ubyte*)surf->pixels;
        auto dpxls = m_pixels.data();
        int min_pitch = m_pitch < surf->pitch ? m_pitch : surf->pitch;
        for (int i = 0; i < m_height; ++i)
        {
            int sx = i * surf->pitch;
            int dx = i * m_pitch;
            memcpy(dpxls + dx, spxls + sx, min_pitch);
        }
    }
}