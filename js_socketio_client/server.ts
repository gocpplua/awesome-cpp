var io = require('socket.io')(4444);

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