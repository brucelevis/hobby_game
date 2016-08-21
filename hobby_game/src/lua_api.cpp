#include "lua_api.h"

#include "lua.h"
#include "lua_value.h"
#include "lua_script.h"

#include "exception.h"

#include "game.h"

#include <lua.hpp>

#include "audio_effect.h"
#include "physics_component.h"
#include "render_sprite.h"

namespace hg
{
    static AssetBank* asset_bank = nullptr;
    static Game* game = nullptr;

    LuaApi::LuaApi()
        : m_game()
    {

    }

    class LuaNumArgException : public Exception
    {
    public:
        LuaNumArgException(const std::string& func_name)
            : Exception(func_name + ": bad number of arguments.")
        {

        }
    };

    static int LUA_load_asset(lua_State* L)
    {
        int top = lua_gettop(L);
        if (top < 2)
        {
            throw LuaNumArgException("load_asset");
        }

        int asset_type = lua_tointeger(L, 1);
        std::string asset_file_name = lua_tostring(L, 2);

        int asset_id = asset_bank->load_asset((AssetType)asset_type, asset_file_name);

        lua_pushinteger(L, asset_id);
        return 1;
    }

    static int LUA_get_asset_id(lua_State* L)
    {
        int top = lua_gettop(L);
        if (top < 2)
        {
            throw LuaNumArgException("get_asset_id");
        }

        int asset_type = lua_tointeger(L, 1);
        std::string asset_name = lua_tostring(L, 2);

        int asset_id = asset_bank->get_asset_id((AssetType)asset_type, asset_name);

        lua_pushinteger(L, asset_id);
        return 1;
    }

    static int LUA_create_entity(lua_State* L)
    {
        int entity = game->get_level().create_entity();

        lua_pushinteger(L, entity);

        return 1;
    }

    static int LUA_create_audio_effect(lua_State* L)
    {
        int top = lua_gettop(L);
        if (top < 1)
        {
            throw LuaNumArgException("create_audio_effect");
        }

        int entity_id = lua_tointeger(L, 1);
        int effect_id = game->get_level().get_audio().create_effect(entity_id);

        lua_pushinteger(L, effect_id);
        return 1;
    }

    static int LUA_set_audio_effect_sound_clip(lua_State* L)
    {
        int top = lua_gettop(L);
        if (top < 2)
        {
            throw LuaNumArgException("set_audio_effect_sound_clip");
        }

        int effect_id = lua_tointeger(L, 1);
        int asset_id = lua_tointeger(L, 2);

        auto effect = game->get_level().get_audio().get_effect(effect_id);
        if (effect)
        {
            effect->set_sound_clip_asset(asset_id);
        }
        else
        {
            throw Exception("Tried to set_audio_effect_sound_clip on null audio effect.");
        }

        return 0;
    }

    static int LUA_play_audio_effect(lua_State* L)
    {
        int top = lua_gettop(L);
        if (top < 1)
            throw LuaNumArgException("play_audio_effect");

        int effect_id = lua_tointeger(L, 1);

        auto effect = game->get_level().get_audio().get_effect(effect_id);
        if (effect)
        {
            effect->play();
        }
        else
        {
            throw Exception("Tried to play_audio_effect on null audio effect.");
        }

        return 0;
    }

    static int LUA_create_physics_empty(lua_State* L)
    {
        int top = lua_gettop(L);
        if (top < 1)
        {
            throw LuaNumArgException("create_physics_empty");
        }

        int entity_id = lua_tointeger(L, 1);
        int empty_id = game->get_level().get_physics().create_empty(entity_id);

        lua_pushinteger(L, empty_id);

        return 1;
    }

    static int LUA_set_physics_position(lua_State* L)
    {
        int top = lua_gettop(L);
        if (top < 3)
        {
            throw LuaNumArgException("set_physics_position");
        }

        int physics_id = lua_tointeger(L, 1);
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L, 3);

        auto physics_comp = (PhysicsComponent*)game->get_level().get_physics().get_component(physics_id);
        if (physics_comp)
        {
            physics_comp->set_position(vcm::vec2(x, y));
        }
        else
        {
            throw Exception("Tried to set_physics_position on null physics component.");
        }

        return 0;
    }

    static int LUA_create_render_sprite(lua_State* L)
    {
        int top = lua_gettop(L);
        if (top < 1)
            throw LuaNumArgException("create_render_sprite");

        int entity_id = lua_tointeger(L, 1);
        int sprite_id = game->get_level().get_render().create_sprite(entity_id);

        lua_pushinteger(L, sprite_id);

        return 1;
    }

    static int LUA_set_sprite_texture(lua_State* L)
    {
        int top = lua_gettop(L);
        if (top < 2)
            throw LuaNumArgException("set_sprite_texture");

        int sprite_id = lua_tointeger(L, 1);
        int asset_id = lua_tointeger(L, 2);

        auto sprite = game->get_level().get_render().get_sprite(sprite_id);
        if (sprite)
        {
            sprite->set_texture_asset(asset_id);
        }
        else
        {
            throw Exception("Tried to set_sprite_texture on null RenderSprite.");
        }

        return 0;
    }

    static luaL_Reg lua_functions[] =
    {
        { "load_asset", &LUA_load_asset },
        { "get_asset_id", &LUA_get_asset_id },

        { "create_entity", &LUA_create_entity },

        { "create_audio_effect", &LUA_create_audio_effect },
        { "set_audio_effect_sound_clip", &LUA_set_audio_effect_sound_clip },
        { "play_audio_effect", &LUA_play_audio_effect },

        { "create_physics_empty", &LUA_create_physics_empty },
        { "set_physics_position", &LUA_set_physics_position },

        { "create_render_sprite", &LUA_create_render_sprite },
        { "set_sprite_texture", &LUA_set_sprite_texture }
    };

    void LuaApi::init(Game& game_, Lua& lua, AssetBank& assets)
    {
        m_game = &game_;
        game = &game_;

        asset_bank = &assets;

        auto L = (lua_State*)lua.get_L();

        lua_newtable(L);
        
        for (const auto& reg : lua_functions)
        {
            lua_pushstring(L, reg.name);
            lua_pushcfunction(L, reg.func);
            lua_rawset(L, -3);
        }

        lua_setglobal(L, "api");
    }

    void LuaApi::destroy()
    {

    }
}