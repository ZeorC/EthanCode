
#include <stdio.h>
#include "demo.h"
#include "lua.hpp"

CPlayer* g_pPlayer = NULL;

lua_member_item* CPlayer::lua_get_meta_data() 
{ 
    typedef CPlayer class_type; 
    static lua_member_item s_member_list[] = 
    {
        { "SetUin", lua_member_type::member_function, 0, 0, false, lua_adapter(&class_type::SetUin) },
        { "GetUin", lua_member_type::member_function, 0, 0, false, lua_adapter(&class_type::GetUin) },
        { "GetPlayerInfoPtr", lua_member_type::member_function, 0, 0, false, lua_adapter(&class_type::GetPlayerInfoPtr) },
        { "m_uiUin", lua_member_type::member_int, __builtin_offsetof ( class_type , m_uiUin) , sizeof(class_type::m_uiUin), false, nullptr},
        { nullptr, lua_member_type::member_none , 0, 0, false, nullptr} 
    }; 
    return s_member_list; 
}

lua_member_item* STPlayerInfo::lua_get_meta_data() { 
    typedef STPlayerInfo class_type; 
    static lua_member_item s_member_list[] = 
    {
        {"m_uiExp", lua_member_type::member_int, __builtin_offsetof ( class_type , m_uiExp) , sizeof(class_type::m_uiExp), false, nullptr},
        {"m_uiMoney", lua_member_type::member_int, __builtin_offsetof ( class_type , m_uiMoney) , sizeof(class_type::m_uiMoney), false, nullptr},
        { nullptr, lua_member_type::member_none , 0, 0, false, nullptr} 
    };
    return s_member_list; 
}

/*
EXPORT_CLASS_BEGIN(CPlayer)
    EXPORT_LUA_FUNCTION(SetUin)
    EXPORT_LUA_FUNCTION(GetUin)
    EXPORT_LUA_FUNCTION(GetPlayerInfoPtr)
    EXPORT_LUA_INT(m_uiUin)
EXPORT_CLASS_END()

EXPORT_CLASS_BEGIN(STPlayerInfo)
    EXPORT_LUA_INT(m_uiExp)
    EXPORT_LUA_INT(m_uiMoney)
EXPORT_CLASS_END()
*/

void regiser_engine(lua_State* L)
{
    lua_register_function(L, "GetPlayerByUin", GetPlayerByUin);
    lua_register_function(L, "Add", Add);
}

lua_State* init_lua(const char* file)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    //luaopen_demo(L);
    regiser_engine(L);
    if (luaL_dofile(L, file))
    {
        printf("dofile failed: %s\n", lua_tostring(L, -1));
        return NULL;
    }
    return L;	
}

int Add(int a, int b)
{
    return (a+b);
}

CPlayer* GetPlayerByUin(unsigned int uiUin)
{
    printf("g_pPlayer:%p\n", g_pPlayer);
    g_pPlayer->SetUin(345121276);
    return g_pPlayer;
}


int main()
{
    g_pPlayer = new CPlayer;
    g_pPlayer->GetPlayerInfoPtr()->m_uiExp = 100;
    g_pPlayer->GetPlayerInfoPtr()->m_uiMoney = 9999;

    lua_State* L = init_lua("demo.lua");
    if (NULL == L)
    {
        return -1;
    }

    printf("AfterLuaCall, Uin:%u Exp:%u Money:%u\n", 
            g_pPlayer->GetUin(),
            g_pPlayer->GetPlayerInfoPtr()->m_uiExp,
            g_pPlayer->GetPlayerInfoPtr()->m_uiMoney);
    return 0;
}

