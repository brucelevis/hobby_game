#pragma once

namespace hg
{
    class Bitmap;
    class TextureImpl;
    class TextureAsset;

    class Texture
    {
    public:
        Texture();
        ~Texture();

        /*
            Creates a texture from a bitmap.
        */
        void create(const Bitmap& bitmap);
        void create(const TextureAsset& texture_asset);
        void destroy();

        /*
            Binds the texture for later rendering.
        */
        void use(unsigned slot = 0) const;

        bool exists() const;
        int get_width() const;
        int get_height() const;

    private:
        TextureImpl* m_impl;
    };
}