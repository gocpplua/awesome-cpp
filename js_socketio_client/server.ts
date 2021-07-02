var io = require('socket.io')(4444,{
    path: '/aaa'
});

io.set('authorization', function (handshake, callback) {
    console.log('authorization', handshake.headers.authorization)
    if (handshake.headers.authorization == 'chenqi') {
        return callback(null, true);
    }
    return callback(new Error('authentication '));
});

io.of('/nss').on('connection', function (socket) {
    console.log('connection')
  socket.on('ferret', function (data, fn) {
    console.log(Date.now(), data)
    fn('s2c ack ferret');
  });

  setTimeout(()=>{
    socket.emit('ferret', 's2c message', function(data){
        console.log(Date.now(), data)
    })
  }, 2000)
});


