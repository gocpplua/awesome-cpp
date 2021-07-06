
# Socket.IO Example

### 一、环境搭建
1、 下载源码:
```
git clone https://github.com/gocpplua/awesome-cpp.git
```

2、下载相关包:
```
npm install
```

3、编译:
```
tsc cli.ts
```

4、运行:
```
node cli.js
```

5、展现如下:
```
$ node cli.js 
Test> 

```

### 二、cli工具使用
进入命令行模式后，查看支持的命令，输入:help
```
Test> help
[ 'connect', 'p2se', 'p2sl', 'p2ss', 'p2sd', 'p2sf', 'troominfo' ]
Test> 
```
1、命令说明:
- connect: 连接服务器
- p2se: P2S_EnterActivity
- p2sl: P2S_LeaveActivity
- p2ss: P2S_SyncScene
- p2sd: P2S_ActorDie
- p2sf: P2S_FireBullet
- troominfo: TEST_RoomInfo // 我自己调试用的，用于查看Room信息

2、命令使用
- 2.1 connect 和 p2se
```
$ node cli.js 
Test> connect  // 连接服务器.connector gid 1
connect VjmTt0mBRclZRylgAAAD gid:1
S2P_SyncPlayer 1 {"ret":0,"engineId":"PLA9ER-D80D-870B-4F8353C6C70"}
Test> connect// 连接服务器.connector gid 2
connect 5MKLTpBocBdCulJzAAAE gid:2
S2P_SyncPlayer 2 {"ret":0,"engineId":"PLABER-2C37-964E-4891715142C"}
Test> p2se 1 // gid:1 的连接发送 P2S_EnterActivity
S2P_SyncScene 1
```

- 2.2 其他
在执行 connect 和 p2se 以后，就可以使用其他命令


### 三、文件说明
cli工具我们在用作arkts客户端的时候，只会用到三个文件:
- cli.ts: 终端控制
- clientManage.ts: 连接管理
- client_ssl.ts: 单个连接，用于和服务器交互。相关的ip,port都在此文件设置。

参考:https://github.com/miguelgrinberg/python-socketio