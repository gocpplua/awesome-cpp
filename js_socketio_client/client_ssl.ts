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
  socket_:any;
  public Connect(id){
      let socket = io.connect(uri, options);

      this.socket_ = socket;
      this.socket_.gid = id;
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
        console.log(`connect ${socket.id} gid:${this.socket_.gid}`);
        socket.on('message',(data)=>{
          console.log(this.socket_.gid, data)
        })
      
        setInterval(()=>{
          socket.emit("ping")
        }, 10000)
      
        socket.on('arkbroadcast',(data)=>{
          console.log(this.socket_.gid, data)
        })
      
        socket.on('arkbroadcasttoworld',(data)=>{
          console.log(this.socket_.gid, data)
        })
      
        socket.on('arkbroadcasttoothers',(data)=>{
          console.log(this.socket_.gid, data)
        })

        socket.on('S2P_SyncScene', (data)=>{
          console.log('S2P_SyncScene', this.socket_.gid)
          let jData = JSON.parse(data)
          let jActor = JSON.parse(jData.actor);
          console.log("=========jActor==========")
          for (const value of jActor) {
            console.log(value.pos[0])
          }
          let jNpc = JSON.parse(jData.npc)

          let jPoi = JSON.parse(jData.poi)
          for (const value of jPoi) {
            console.log(value)
          }
        })

        socket.on('S2B_EnterPlay', (data) =>{
          console.log('S2B_EnterPlay', this.socket_.gid, data);
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
      this.socket_.emit("P2S_EnterActivity", `{"actId":"100001", "pos":[1,2,3]}`)
    }

    public P2S_LeaveActivity(){
      this.socket_.emit("P2S_LeaveActivity", `{"actId":"100001"}`)
    }

    public Send(){
      this.socket_.emit("message", `{"message":"message"}`)
    }

    public ArkbroadcastToOthers(){
      this.socket_.emit("arkbroadcasttoothers", `{"ArkbroadcastToOthers":"ArkbroadcastToOthers"}`)
    }

    public Arkbroadcast(){
      this.socket_.emit("arkbroadcast", `{"arkbroadcast":"arkbroadcast"}`)
    }

    public ArkbroadcastToWorld(){
      this.socket_.emit("arkbroadcasttoworld", `{"ArkbroadcastToWorld":"ArkbroadcastToWorld"}`)
    }
}