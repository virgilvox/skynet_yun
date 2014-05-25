// establish skynet connection

var io = require('socket.io-client')
socket = io.connect('http://skynet.im', {
    port: 80
});


// set up serialport to connect to the onboard atmega32u4
var com = require("serialport");
var serialPort = new com.SerialPort("/dev/ttyATH0", {
  baudrate: 9600,
  parser: com.parsers.readline('\r\n')
});


socket.on('connect', function(){
  console.log('Requesting websocket connection to SkyNet');
// Replace 623dd....112c with your uuid and replace the token as well.
  socket.on('identify', function(data){
    console.log('Websocket connecting to SkyNet with socket id: ' + data.socketid);
    console.log('Sending device uuid: 623dd4e1-dc84-11e3-a7cd-6fa4d6a0112c');
    socket.emit('identity', {uuid: '623dd4e1-dc84-11e3-a7cd-6fa4d6a0112c', socketid: data.socketid, token: '0i14qdl0qext7qfreo6pl35wlar1kyb9'});
  });

  socket.on('notReady', function(data){
    if (data.status == 401){
      console.log('Device not authenticated with SkyNet');
    }
  });
  socket.on('ready', function(data){
    if (data.status == 201){
      console.log('Device authenticated with SkyNet');


serialPort.on("open", function () {
  console.log('open');

  });

  serialPort.on('data', function(data) {
    console.log('data received: ' + data);


// Have not tested this properly yet
    // Send/Receive messages
      socket.emit("message",{
        "devices": 'C4638FE1-AA7D-11E3-A656-E511295817AD',
        "payload": {
          "serialin": data}
      });

  });


 socket.on('message', function(msg){
//       console.log('message received', msg);

console.log(msg.payload);

// Writing msg.payload directly to the serialport produces weird 
// results. Instead we check the message and send out the right number to be sure.

if(msg.payload == "1"){

serialPort.write("1");
}else if(msg.payload == "2"){

serialPort.write("2");
}else if(msg.payload == "3"){

serialPort.write("3");
}else if(msg.payload == "0"){

serialPort.write("0");
}
      
     


   });

  


    }
  });
});
