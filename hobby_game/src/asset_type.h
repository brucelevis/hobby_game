#pragma once

namespace hg
{
    /*
        Used to prefix the asset file_names with the right folder.
    */
    enum class AssetType
    {
        undefined,

        bitmap,
        texture,
        tilemap
    };

    /*
        Returns the folder path prefix assigned to each AssetType.
        Turns "assets/tilemaps/test.lua" into "test.lua" for the user of a load function in AssetBank
    */
    const char* get_asset_type_dir(AssetType type);
}