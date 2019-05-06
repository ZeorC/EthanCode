
#include <stdio.h>
#include "demo.h"
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"

CPlayer* g_pPlayer = NULL;

void regiser_engine(lua_State* L)
{
    luabridge::getGlobalNamespace(L)    
        .beginNamespace("Engine")
            .addFunction("Add", Add)
            .beginClass <STPlayerInfo> ("STPlayerInfo")
                .addData("m_uiExp", &STPlayerInfo::m_uiExp)
                .addData("m_uiMoney", &STPlayerInfo::m_uiMoney)
                .addData("m_szNickName", &STPlayerInfo::m_szNickName)
            .endClass()
            .beginClass <CPlayer> ("CPlayer")
                .addFunction("GetUin", &CPlayer::GetUin)
                .addFunction("GetPlayerInfoPtr", &CPlayer::GetPlayerInfoPtr)
            .endClass()
            .addFunction("GetPlayerByUin", GetPlayerByUin)
        .endNamespace();
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

