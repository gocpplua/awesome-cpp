"use strict";
exports.__esModule = true;
exports.MyClient = void 0;
var io = require('socket.io-client');
var host = "https://127.0.0.1";
var port = 4002;
var options = {
    secure: true,
    //reconnect: true,
    rejectUnauthorized: false,
    transportOptions: {
        polling: {
            extraHeaders: {
                'Authorization': 'chenqi'
            }
        }
    }
};
var uri = host + ":" + port + "?token=abc";
var oneActorEngineId = null; // 进入场景后，随机记录一个actor的enginedId
function GetActorEngineId() {
    return oneActorEngineId;
}
function SetActorEngineId(id) {
    oneActorEngineId = id;
}
var MyClient = /** @class */ (function () {
    function MyClient() {
    }
    MyClient.prototype.Connect = function (id) {
        var _this = this;
        var socket = io.connect(uri, options);
        this.socket_ = socket;
        this.socket_.gid = id;
        socket.on('connect_error', function (err) {
            console.log("connect_error " + err + " ");
        });
        socket.on('connect_timeout', function () {
            console.log("connect_timeout " + socket.id);
        });
        socket.on('reconnect', function () {
            console.log("reconnect " + socket.id);
        });
        socket.on('reconnect_error', function () {
            console.log("reconnect_error " + socket.id);
        });
        socket.on('reconnect_failed', function () {
            console.log("reconnect_failed " + socket.id);
        });
        socket.on('connect', function () {
            console.log("connect " + socket.id + " gid:" + _this.socket_.gid);
            socket.on('message', function (data) {
                console.log(_this.socket_.gid, data);
            });
            setInterval(function () {
                socket.emit("ping");
            }, 20000);
            socket.on('S2P_SyncPlayer', function (data) {
                console.log('S2P_SyncPlayer', _this.socket_.gid, data);
            });
            socket.on('arkbroadcast', function (data) {
                console.log(_this.socket_.gid, data);
            });
            socket.on('arkbroadcasttoworld', function (data) {
                console.log(_this.socket_.gid, data);
            });
            socket.on('arkbroadcasttoothers', function (data) {
                console.log(_this.socket_.gid, data);
            });
            socket.on('S2P_EnterExperience', function (data) {
                console.log(_this.socket_.gid, data);
            });
            socket.on('S2P_SyncScene', function (data) {
                console.log('S2P_SyncScene', _this.socket_.gid);
                var jData = JSON.parse(data);
                var jActor = jData.actor;
                for (var _i = 0, jActor_1 = jActor; _i < jActor_1.length; _i++) {
                    var value = jActor_1[_i];
                    if (!GetActorEngineId()) {
                        SetActorEngineId(value.engineId);
                        console.log('oneActorEngineId', GetActorEngineId());
                    }
                }
                var jNpc = jData.npc;
                var jPoi = jData.resource;
            });
            socket.on('S2B_ActorDie', function (data) {
                console.log('S2B_ActorDie', _this.socket_.gid);
                var jData = JSON.parse(data);
                //console.log(jData)
            });
            socket.on('S2B_FireBullet', function (data) {
                console.log('S2B_FireBullet', _this.socket_.gid);
                var jData = JSON.parse(data);
                console.log(jData);
            });
            socket.on('S2B_SyncActor', function (data) {
                var jData = JSON.parse(data);
                console.log('S2B_SyncActor', _this.socket_.gid, jData.length);
                for (var _i = 0, jData_1 = jData; _i < jData_1.length; _i++) {
                    var value = jData_1[_i];
                    if (!GetActorEngineId()) {
                        SetActorEngineId(value.engineId);
                        console.log('oneActorEngineId', GetActorEngineId());
                    }
                }
            });
            socket.on('S2P_LeaveScene', function (data) {
                console.log('S2P_LeaveScene', _this.socket_.gid, data);
            });
            socket.on('S2P_LeaveExperience', function (data) {
                console.log('S2P_LeaveExperience', _this.socket_.gid, data);
            });
            socket.on('S2B_SyncPlayer', function (data) {
                console.log('S2B_SyncPlayer', _this.socket_.gid, data);
            });
            socket.on('S2B_LeavePlay', function (data) {
                console.log('S2B_LeavePlay', _this.socket_.gid, data);
            });
            socket.on('S2B_KillOffPlayer', function (data) {
                console.log('S2B_KillOffPlayer', _this.socket_.gid, data);
            });
            socket.on('S2P_TEST', function (data) {
                console.log('S2P_TEST', _this.socket_.gid, data);
            });
        });
        socket.on('disconnect', function () {
            console.log("disconnect " + _this.socket_.gid);
        });
        socket.on('error', function () {
            console.log("error " + _this.socket_.gid);
        });
        return socket;
    };
    MyClient.prototype.P2S_EnterActivity = function () {
        this.socket_.emit("P2S_EnterExperience", "{\"experienceId\":\"100001\", \"pos\":[1,2,3]}");
    };
    MyClient.prototype.P2S_LeaveActivity = function () {
        this.socket_.emit("P2S_LeaveExperience", "{\"experienceId\":\"100001\"}");
    };
    MyClient.prototype.P2S_SyncScene = function () {
        this.socket_.emit("P2S_SyncScene", "{\"actId\":\"100001\"}");
    };
    MyClient.prototype.P2S_ActorDie = function () {
        console.log('actor die:', oneActorEngineId);
        this.socket_.emit("P2S_ActorDie", "{\"engineId\":\"" + oneActorEngineId + "\"}");
        SetActorEngineId(null);
    };
    MyClient.prototype.P2S_FireBullet = function () {
        this.socket_.emit("P2S_FireBullet", "{\"pos\":[1,2,3], \"towards\":[10,20,30]}");
    };
    MyClient.prototype.Send = function () {
        this.socket_.emit("message", "{\"message\":\"message\"}");
    };
    MyClient.prototype.ArkbroadcastToOthers = function () {
        this.socket_.emit("arkbroadcasttoothers", "{\"ArkbroadcastToOthers\":\"ArkbroadcastToOthers\"}");
    };
    MyClient.prototype.Arkbroadcast = function () {
        this.socket_.emit("arkbroadcast", "{\"arkbroadcast\":\"arkbroadcast\"}");
    };
    MyClient.prototype.ArkbroadcastToWorld = function () {
        this.socket_.emit("arkbroadcasttoworld", "{\"ArkbroadcastToWorld\":\"ArkbroadcastToWorld\"}");
    };
    MyClient.prototype.TEST_RoomInfo = function () {
        this.socket_.emit("TEST_RoomInfo");
    };
    MyClient.prototype.TEST_SavePlayer = function () {
        this.socket_.emit("TEST_SavePlayer");
    };
    return MyClient;
}());
exports.MyClient = MyClient;
