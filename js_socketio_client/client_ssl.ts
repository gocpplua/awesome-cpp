let io = require('socket.io-client')
let host = "https://127.0.0.1"
let port =  3002;
let options = {
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
let uri = `${host}:${port}?token=abc`
export class MyClient{
  socket_:any
    public Connect(){
      let socket = io.connect(uri, options);
      this.socket_ = socket;
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
        socket.on('message',(data)=>{
          console.log(data)
        })
      
        setInterval(()=>{
          socket.emit("ping")
        }, 10000)
      
        socket.on('arkbroadcast',(data)=>{
          console.log(data)
        })
      
        socket.on('arkbroadcastinroom',(data)=>{
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
      return socket;
    }

    public P2S_EnterActivity(){
      this.socket_.emit("P2S_EnterActivity", `{"actid":"100001"}`)
    }

    public Send(){
      this.socket_.emit("message", `{"message":"message"}`)
    }

    public Arkbroadcast(){
      this.socket_.emit("arkbroadcast", `{"arkbroadcast":"arkbroadcast"}`)
    }

    public ArkbroadcastInRoom(){
      this.socket_.emit("arkbroadcastinroom", `{"arkbroadcastinroom":"arkbroadcastinroom"}`)
    }
}