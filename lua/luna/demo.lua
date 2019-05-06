
key = ""                                                                                                                   
function PrintTable(table , level)                                                                                         
    level = level or 1                                                                                                       
    if level > 5 then
        return
    end

    local indent = ""                                                                                                        
    for i = 1, level do                                                                                                      
        indent = indent.."  "                                                                                                  
    end                                                                                                                      

    if key ~= "" then                                                                                                        
        if (type(key) == "string") then
            print(indent..key.." ".."=".." ".."{")                                                                                 
        elseif (type(key) == "userdata") then
            print(indent.."lightuserdata".." ".."=".." ".."{")                                                                                 
        else
            print(indent.."Unknow".." ".."=".." ".."{")                                                                                 
        end
    else                                                                                                                     
        print(indent .. "{")                                                                                                   
    end                                                                                                                      
    local metaTable = getmetatable(table)
    if metaTable ~= nil then
        key = "_metatable"
        PrintTable(metaTable, level+1)
    end

    key = ""                                                                                                                 
    for k,v in pairs(table) do                                                                                               
        if type(v) == "table" then                                                                                            
            key = k                                                                                                            
            if key ~= 1 and key ~= 2 and key ~="_LOADED" and key ~= "FILE*" and key ~="_PRELOAD" then
                PrintTable(v, level + 1)                                                                                           
            end
        else                                                                                                                  
            local content = string.format("%s%s = %s", indent .. "  ",tostring(k), tostring(v))                                
            print(content)                                                                                                       
        end                                                                                                                  
    end                                                                                                                      
    print(indent .. "}")                                                                                                     
end                  

function printRegistry()
    tabReg = debug.getregistry();
    PrintTable(tabReg);
end

--printRegistry()

local a = 99
local b = 88
local c = Add(a,b)

print(c)

local pPlayer = GetPlayerByUin(345121276)

--printRegistry()
print(pPlayer:GetUin())
print(pPlayer.m_uiUin)
local pPlayerInfo = pPlayer:GetPlayerInfoPtr()

--printRegistry()
print(pPlayerInfo.m_uiExp)
print(pPlayerInfo.m_uiMoney)
pPlayerInfo.m_uiMoney = 30

printRegistry()
