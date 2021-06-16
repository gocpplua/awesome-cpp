"use strict";
exports.__esModule = true;
exports.MyClient = void 0;
var io = require('socket.io-client');
var host = "https://127.0.0.1";
var port = 3002;
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
var MyClient = /** @class */ (function () {
    function MyClient() {
    }
    MyClient.prototype.Connect = function () {
        var socket = io.connect(uri, options);
        this.socket_ = socket;
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
            console.log("connect " + socket.id);
            socket.on('message', function (data) {
                console.log(data);
            });
            setInterval(function () {
                socket.emit("ping");
            }, 10000);
            socket.on('arkbroadcast', function (data) {
                console.log(data);
            });
            socket.on('arkbroadcastinroom', function (data) {
                console.log(data);
            });
            socket.on('S2P_EnterActivity', function (data) {
                console.log(data);
            });
        });
        socket.on('disconnect', function () {
            console.log("disconnect " + socket.id);
        });
        socket.on('error', function () {
            console.log("error " + socket.id);
        });
        return socket;
    };
    MyClient.prototype.P2S_EnterActivity = function () {
        this.socket_.emit("P2S_EnterActivity", "{\"actid\":\"100001\"}");
    };
    MyClient.prototype.Send = function () {
        this.socket_.emit("message", "{\"message\":\"message\"}");
    };
    MyClient.prototype.Arkbroadcast = function () {
        this.socket_.emit("arkbroadcast", "{\"arkbroadcast\":\"arkbroadcast\"}");
    };
    MyClient.prototype.ArkbroadcastInRoom = function () {
        this.socket_.emit("arkbroadcastinroom", "{\"arkbroadcastinroom\":\"arkbroadcastinroom\"}");
    };
    return MyClient;
}());
exports.MyClient = MyClient;
