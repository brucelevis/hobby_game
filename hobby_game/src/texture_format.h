#pragma once

namespace hg
{
    enum class TextureFormat
    {
        undefined,
        r,
        rgb,
        rgba
    };

    enum class TextureWrap
    {
        undefined,
        clamp,
        repeat
    };

    enum class TextureFilter
    {
        undefined,
        nearest,
        linear
    };
}