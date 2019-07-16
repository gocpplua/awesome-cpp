local socket = require("socket.core")
local tcp = socket.tcp()
local host = host or '127.0.0.1'
local port = '8182'
local clicon = tcp:connect(host,port)
tcp:settimeout(4) -- /*阻塞4s*/
if(clicon) then
   print('connect '..host..' ok')
else
    print('connect error')
    return
end

while true do
    local s, status, partial = tcp:receive()
    print("s:  " .. tostring(s) )
    print("status:  " .. tostring(status) )
    print("partial:  " .. tostring(partial) )
    print(s or partial)
    if status == "closed" then
      break
    end
end

--[[
    function rec_msg()
    --local tcprev = tcp:receive(13)
    local tcprev = tcp:receive(13)
    if(tcprev) then
        print('tcprev:'..tcprev)
    else
        print('tcp rec err')
    end
end
--]]

--[[ 
    while 1 do
    local tcpsend = tcp:send('hello 111111111')
    if(tcpsend) then
        print('tcpsend ok')
        rec_msg()
        --break
    else
        print('tcpsend err')
    end
end
--]]
tcp:close()
