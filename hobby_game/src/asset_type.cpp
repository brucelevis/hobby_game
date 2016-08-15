#include "asset_type.h"

namespace hg
{
    const char* get_asset_type_dir(AssetType type)
    {
        switch (type)
        {
        case AssetType::undefined:
            return "";
        case AssetType::bitmap:
            return "assets/bitmaps/";
        case AssetType::texture:
            return "assets/textures/";
        case AssetType::tilemap:
            return "assets/tilemaps/";
        }
    }
}