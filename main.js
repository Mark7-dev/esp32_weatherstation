var http = require('http');
var fs = require('fs');

var index = fs.readFileSync('index.html');

const SerialPort = require("serialport");
const { ReadlineParser } = require("@serialport/parser-readline");

const parsers = SerialPort.parsers;
const parser = new ReadlineParser({ delimiter: "\r\n" });


const port = new SerialPort.SerialPort({
  path: "/dev/cu.usbserial-10",
  //change depending on the port you are using
  baudRate: 9600,
  dataBits: 8,
  parity: "none",
  stopBits: 1,
  flowControl: false,
});

port.pipe(parser);

var app = require('http').createServer(function(req, res){
  res.writeHead(200,{'Content-Type': 'text/html'});
  res.end(index);
});

var io = require('socket.io')(app);

parser.on("data", (data) => {
  console.log(data);
  const dataArray = data.split(",");
  if (dataArray.length === 2) {
    const humidity = dataArray[0];
    const temperature = dataArray[1];
    io.emit('data', { humidity, temperature });
  }
});

app.listen(6900);
