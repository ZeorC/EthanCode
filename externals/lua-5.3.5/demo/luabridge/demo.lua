
local a = 99
local b = 88
local c = Engine.Add(a,b)

print(c)

local pPlayer = Engine.GetPlayerByUin(345121276)
print(pPlayer:GetUin())
local pPlayerInfo = pPlayer:GetPlayerInfoPtr()
print(pPlayerInfo.m_uiExp)
print(pPlayerInfo.m_uiMoney)
pPlayerInfo.m_uiMoney = 30
