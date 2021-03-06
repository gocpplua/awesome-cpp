import { MyClient } from "./client_ssl";

let gconnectid = 1;
export class MyClientManage{
  public myClientsMap: Map<number, MyClient>;
  constructor(){
    this.myClientsMap = new Map<number, MyClient>();
  }

  public Connect(){
    let myClient = new MyClient();
    myClient.Connect(gconnectid);
    this.myClientsMap.set(gconnectid, myClient);
    gconnectid++;
  }

  public Send(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.Send();
    }
  }

  public ArkbroadcastToOthers(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.ArkbroadcastToOthers();
    }
  }

  public Arkbroadcast(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.Arkbroadcast();
    }
  }

  public ArkbroadcastToWorld(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.ArkbroadcastToWorld();
    }
  }

  public P2S_EnterActivity(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.P2S_EnterActivity();
    }
  }

  public P2S_LeaveActivity(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.P2S_LeaveActivity();
    }
  }

  public P2S_SyncScene(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.P2S_SyncScene();
    }
  }

  public P2S_ActorDie(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.P2S_ActorDie();
    }
  }

  public P2S_FireBullet(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.P2S_FireBullet();
    }
  }

  public TEST_RoomInfo(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.TEST_RoomInfo();
    }
  }

  public TEST_SavePlayer(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.TEST_SavePlayer();
    }
  }
}