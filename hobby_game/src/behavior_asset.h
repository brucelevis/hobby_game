#pragma once

#include "asset.h"

namespace hg
{
    class BehaviorAsset
        : public Asset
    {
    public:
        BehaviorAsset(AssetBank& bank, int id);

        AssetType get_type() const override { return AssetType::behavior; }
        
    protected:
        friend class AssetBank;

        void load(const std::string& file_name) override;

    private:

    };
}