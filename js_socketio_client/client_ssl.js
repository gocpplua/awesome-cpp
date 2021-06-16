const io = require('socket.io-client')
const host = "https://127.0.0.1"
const port =  3002;
console.log(io.connect)
const options = {
  secure:true,
  //reconnect: true,
  rejectUnauthorized : false,
  transportOptions: {
    polling: {
      extraHeaders: {
        'Authorization': 'chenqi',
      },
    },
  }
  };
const uri = `${host}:${port}?token=abc`
const socket = io.connect(uri, options);
console.log(uri)

let last;
function send (client) {
  last = new Date();
  
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
  socket.on('message',(data, data1)=>{
    console.log(data, data1)
  })

  setTimeout(()=>{
    socket.emit("P2S_EnterActivity", `{"actid":"100001"}`)
  }, 5000)

  socket.on('broadcast',(data)=>{
    console.log(data)
  })

  socket.on('broadcastinroom',(data)=>{
    console.log(data)
  })

  socket.on('S2P_EnterActivity', (data)=>{
    console.log(data)
  })
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


