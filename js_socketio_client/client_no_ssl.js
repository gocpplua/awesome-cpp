const io = require('socket.io-client')
const port =  4444;
const options = {
  path: '/aaa',
  secure:true,
  rejectUnauthorized : false,
  transportOptions: {
    polling: {
      extraHeaders: {
        authorization: 'chenqi',
      },
    },
  }
  };
const socket = io.connect(`http://127.0.0.1:${port}/nss`, options);
console.log(`connect http://127.0.0.1:${port}/nss`)

socket.on('connect', () => {
  console.log(`connect ${socket.id}`);
  // send();
       
  socket.on('ferret', function (data, fn) {
    console.log(Date.now(), data); // data will be 'woot'
    fn('c2s ack ferret')
  });

  setTimeout(()=>{
    socket.emit('ferret', 'c2s message', function (data) {
      console.log('ferret', Date.now(), data); // data will be 'woot'
    });
  }, 1000)

});

