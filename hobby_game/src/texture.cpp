#include "texture.h"
#include "bitmap.h"

#include <GL/glew.h>

#include "exception.h"
#include "texture_asset.h"
#include "asset_bank.h"
#include "bitmap_asset.h"

namespace hg
{
    class TextureImpl
    {
    public:
        TextureImpl();

        void create();
        void bind(GLuint slot) const;

        void upload(TextureFormat format, TextureWrap wrap_mode, TextureFilter filter_mode,
            const ubyte* data, int width, int height, int bpp);

        void upload(const ubyte* data, int width, int height, int bpp);
        void destroy();

        GLuint get_handle() const { return m_handle; }
        int get_width() const { return m_width; }
        int get_height() const { return m_height; }

    private:
        GLuint m_handle;
        int m_width;
        int m_height;
    };

    TextureImpl::TextureImpl()
        : m_handle()
        , m_width()
        , m_height()
    {

    }

    void TextureImpl::create()
    {
        if (!m_handle)
        {
            glGenTextures(1, &m_handle);
            if (!m_handle)
            {
                int e = glGetError();
                throw Exception("Could not generate a texture. OpenGL error code: " + std::to_string(e));
            }
        }
    }

    void TextureImpl::bind(GLuint slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_handle);
    }

    void TextureImpl::upload(TextureFormat format, TextureWrap wrap_mode, TextureFilter filter_mode,
        const ubyte* data, int width, int height, int bpp)
    {
        GLenum ifmt, efmt;
        switch (bpp)
        {
        case 1:
            ifmt = GL_R8;
            efmt = GL_RED;
            break;
        case 3:
            ifmt = GL_RGB8;
            efmt = GL_RGB;
            break;
        case 4:
        default:
            ifmt = GL_RGBA8;
            efmt = GL_RGBA;
            break;
        }

        /*
            If the format is specified, set internal format to desired format.
            Otherwise use defaults ^^
        */
        if (format != TextureFormat::undefined)
        {
            switch (format)
            {
            case TextureFormat::r:
                ifmt = GL_R8;
                break;
            case TextureFormat::rgb:
                ifmt = GL_RGB8;
                break;
            case TextureFormat::rgba:
                ifmt = GL_RGBA8;
                break;
            }
        }

        m_width = width;
        m_height = height;

        GLenum gl_filter = GL_LINEAR, gl_wrap = GL_REPEAT;
        
        if (filter_mode != TextureFilter::undefined)
        {
            switch (filter_mode)
            {
            case TextureFilter::nearest:
                gl_filter = GL_NEAREST;
                break;
            case TextureFilter::linear:
                gl_filter = GL_LINEAR;
                break;
            }
        }

        if (wrap_mode != TextureWrap::undefined)
        {
            switch (wrap_mode)
            {
            case TextureWrap::clamp:
                gl_wrap = GL_CLAMP_TO_EDGE;
                break;
            case TextureWrap::repeat:
                gl_wrap = GL_REPEAT;
                break;
            }
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl_wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl_wrap);

        glTexImage2D(GL_TEXTURE_2D, 0, ifmt, width, height, 0, efmt, GL_UNSIGNED_BYTE, data);
    }

    void TextureImpl::upload(const ubyte* data, int width, int height, int bpp)
    {
        upload(TextureFormat::undefined, TextureWrap::undefined, TextureFilter::undefined,
            data, width, height, bpp);
    }

    void TextureImpl::destroy()
    {
        if (m_handle)
        {
            glDeleteTextures(1, &m_handle);
            m_handle = 0;
            m_width = m_height = 0;
        }
    }

    Texture::Texture()
        : m_impl()
    {
        m_impl = new TextureImpl();
    }

    Texture::~Texture()
    {
        delete m_impl;
    }

    void Texture::create(const Bitmap& bitmap)
    {
        m_impl->create();
        m_impl->bind(0);
        m_impl->upload(bitmap.get_pixels(), bitmap.get_width(), bitmap.get_height(), bitmap.get_bpp());
    }

    void Texture::create(const TextureAsset& texture_asset)
    {
        auto bitmap_asset = texture_asset.get_bank().get_bitmap(texture_asset.get_bitmap_asset());
        if (!bitmap_asset)
            throw Exception("Tried to create a texture from an invalid texture asset.");

        m_impl->create();
        m_impl->bind(0);

        const Bitmap& bitmap = bitmap_asset->get_bitmap();
        m_impl->upload(texture_asset.get_format(),
            texture_asset.get_wrap_mode(), texture_asset.get_filter_mode(),
            bitmap.get_pixels(), bitmap.get_width(), bitmap.get_height(), bitmap.get_bpp());
    }

    void Texture::destroy()
    {
        m_impl->destroy();
    }

    void Texture::use(unsigned slot) const
    {
        m_impl->bind(slot);
    }

    bool Texture::exists() const
    {
        return m_impl->get_handle() ? true : false;
    }

    int Texture::get_width() const
    {
        return m_impl->get_width();
    }

    int Texture::get_height() const
    {
        return m_impl->get_height();
    }
}