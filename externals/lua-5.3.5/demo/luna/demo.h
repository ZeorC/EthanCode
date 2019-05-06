
#include "luna11.h"

#define MAX_NICKNAME_LEN 17

struct STPlayerInfo
{
    unsigned int m_uiExp;
    unsigned int m_uiMoney;
public:
    DECLARE_LUA_CLASS(STPlayerInfo);
    void __gc()
    {
        // lua gc时,如果存在本函数,那么会调用本函数取代默认的delete
        printf("STPlayerInfo::__gc(): this=%p\n", this);
    }
};

class CPlayer final
{
    public:
        DECLARE_LUA_CLASS(CPlayer);
        void __gc()
        {
            // lua gc时,如果存在本函数,那么会调用本函数取代默认的delete
            printf("CPlayer::__gc(): this=%p\n", this);
        }
public:
    void SetUin(unsigned int uiUin) { m_uiUin = uiUin; }
    unsigned int GetUin() { return m_uiUin; }
    STPlayerInfo* GetPlayerInfoPtr() { return &m_stPlayerInfo; }
private:
    unsigned int m_uiUin;
    STPlayerInfo m_stPlayerInfo;
};

CPlayer* GetPlayerByUin(unsigned int uiUin);

int Add(int a, int b);
