var http = require('http');
// Import the built-in 'http' module to create an HTTP server
var fs = require('fs');
// Import the built-in 'fs' (file system) module to read files


var index = fs.readFileSync('index.html');

const SerialPort = require("serialport");
// Import the 'serialport' library for serial port communication
const { ReadlineParser } = require("@serialport/parser-readline");


// Define a constant 'parsers' that holds the parsers from the 'SerialPort' object
const parsers = SerialPort.parsers;
const parser = new ReadlineParser({ delimiter: "\r\n" });


const port = new SerialPort.SerialPort({
  path: "/dev/cu.usbserial-10",
  //Change depending on the port you are using
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

// Set up a WebSocket server using 'socket.io' and bind it to the existing HTTP server
var io = require('socket.io')(app);

parser.on("data", (data) => {
  console.log(data);
  const dataArray = data.split(","); // Split the data into an array based on the comma (',') delimiter
  if (dataArray.length === 2) {
    const humidity = dataArray[0];
    const temperature = dataArray[1];
    io.emit('data', { humidity, temperature });
  }
});

// Start the HTTP server on port 6900
app.listen(6900);
