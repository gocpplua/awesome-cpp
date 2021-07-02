const io = require('socket.io-client')
const port =  4444;
const socket = io.connect('http://127.0.0.1:' + port);
console.log(`connect http://127.0.0.1:${port}`)
let last;
function send () {
  last = new Date();
  socket.emit('ping_from_client');
}

socket.on('connect_error', (err) => {
  console.log(`connect_error ${err} `);
});

socket.on('connect_timeout', () => {
  console.log(`connect_timeout ${socket.id}`);
});

socket.on('reconnect', () => {
  console.log(`reconnect ${socket.id}`);
});

socket.on('reconnect_error', () => {
  console.log(`reconnect_error ${socket.id}`);
});

socket.on('reconnect_failed', () => {
  console.log(`reconnect_failed ${socket.id}`);
});

socket.on('connect', () => {
  console.log(`connect ${socket.id}`);
  // send();
       
  socket.on('ferret', function (data, fn) {
    console.log(Date.now(), data); // data will be 'woot'
    fn('c2s ack ferret')
  });

  socket.emit('ferret', 'c2s message', function (data) {
    console.log(Date.now(), data); // data will be 'woot'
  });
});

socket.on('disconnect', () => {
  console.log(`disconnect ${socket.id}`);
});

socket.on('error', () =>{
  console.log(`error ${socket.id}`);
})
socket.on('pong_from_server', () => {
  const latency = new Date() - last;
  console.log('latency is ' + latency + ' ms');
  setTimeout(send, 1000);
});

socket.on('message',(data)=>{
  console.log(data)
})
