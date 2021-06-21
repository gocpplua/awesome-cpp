import { MyClientManage } from './clientManage';
let manage = new MyClientManage();
var readline = require('readline');
var  rl = readline.createInterface(process.stdin, process.stdout);

/*
*  方法setPromat(promat)，就是给每一行设置一个提示符，就好比window命令行的> ，我们这里设置的是Test>
*  promat()可以算是最重要的方法了，因为它才体现了Readline的核心作用，以行为单位读取数据，premat方法就是在等待用户输入数据
*  这里又监听了’line’ 事件，因为promat方法调用一次就只会读取一次数据，所以，在这个方法又调用了一次promat方法，这样就可以继续读取用户输入，从而达到一种命令行的效果
*/

rl.setPrompt('Test> ');
rl.prompt();

let netEvents = ["connect", "p2se", "p2sl", "p2sh", "p2sf", "troominfo"];
//let netEvents = ["connect", "send", "arkbto", "arkb", "arkbtw", "p2se", "p2sl", "p2sh", "p2sf"];
let errTip = function(){
  console.log('没有找到命令！ 查看:help');
}

rl.on('line', function(line) {
  line = line.trim();
  let delay = 1;
  let splitted = line.split(" ", 2);
  if(splitted.length > 0){
    const index = netEvents.findIndex(event => event === splitted[0]);
    if(index >= 0) delay = 300;
  }

  if(splitted.length == 1){
    switch(splitted[0]){
      case 'help':
        console.log(netEvents)
        break;
      case 'connect':
        manage.Connect();
        break;
      default:
        errTip();
        break;
    }
  }
  else if(splitted.length == 2){
    switch(splitted[0]) {
      case 'copy':
          console.log("复制");
          break;
      case 'hello':
          console.log('world!');
          break;
      case 'close':
          rl.close();
          break;
      case 'send':
        manage.Send(Number(splitted[1]));
        break;
      case 'arkbto':
        manage.ArkbroadcastToOthers(Number(splitted[1]))
        break;
      case 'arkb':
        manage.Arkbroadcast(Number(splitted[1]));
        break;
      case 'arkbtw':
        manage.ArkbroadcastToWorld(Number(splitted[1]));
        break;
      case 'p2se':
        manage.P2S_EnterActivity(Number(splitted[1]));
        break;
      case 'p2sl':
        manage.P2S_LeaveActivity(Number(splitted[1]));
        break;
      case 'p2sh':
        manage.P2S_HitActor(Number(splitted[1]));
        break;
      case 'p2sf':
        manage.P2S_FireBullet(Number(splitted[1]));
        break;
      case 'troominfo':
        manage.TEST_RoomInfo(Number(splitted[1]))
        break;
      default:
        errTip();
        break;
    }
  }
  else{
    errTip();
  }
  setTimeout(()=>{
    rl.prompt();
  }, delay)
  
});

rl.on('close', function() {
    console.log('bye bye!');
    process.exit(0);
});
