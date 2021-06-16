import { MyClient } from "./client_ssl";

let gconnectid = 1;
export class MyClientManage{
  public myClientsMap: Map<number, MyClient>;
  constructor(){
    this.myClientsMap = new Map<number, MyClient>();
  }

  public Connect(){
    let myClient = new MyClient();
    myClient.Connect();
    this.myClientsMap.set(gconnectid, myClient);
    gconnectid++;
  }

  public Send(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.Send();
    }
  }

  public Arkbroadcast(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.Arkbroadcast();
    }
  }

  public ArkbroadcastInRoom(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.ArkbroadcastInRoom();
    }
  }

  public P2S_EnterActivity(connectid){
    let myClient = this.myClientsMap.get(connectid);
    if(myClient){
      myClient.P2S_EnterActivity();
    }
  }
}