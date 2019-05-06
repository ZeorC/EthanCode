
#define MAX_NICKNAME_LEN 17

struct STPlayerInfo
{
    unsigned int m_uiExp;
    char m_szNickName[MAX_NICKNAME_LEN];
    unsigned int m_uiMoney;
};

class CPlayer
{
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
