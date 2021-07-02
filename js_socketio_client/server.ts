var io = require('socket.io')(4444);

io.on('connection', function (socket) {
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