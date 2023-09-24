**ESP32 Weather Station README**

This repository contains code for an ESP32 Weather Station
that gathers data from a connected sensor and displays it
on a web interface. The project is built using Node.js,
Socket.io, Express, and the SerialPort library. Below you
will find instructions on setting up and running the weather station.
 
![Website](weatherstation.png)

The website




## Prerequisites

Before you begin, make sure you have the following software and hardware components ready:

- **ESP32**: The ESP32 microcontroller board with a temperature and humidity sensor connected to it.

- **Temperature and Humidity Sensor**: In my project I am using a DHT22, however you can also use a DHT11 as well. You will just need to change the C++ code to define
 the sensor as a DHT11 instead of a DHT22

- **Node.js**: Ensure that Node.js is installed on your development machine. If not, you can download it from [nodejs.org](https://nodejs.org/).

- **SerialPort**: Install the SerialPort library using npm:
  
```
  npm install serialport
  ```

- **Express**: Install the Express library using npm:

  ```bash
  npm install express
  ```

- **Socket.io**: Install the Socket.io library using npm:

  ```bash
  npm install socket.io@2.0.4
  ```
- **Arduino IDE**: You will need the arduino IDE to run the ino file

  ```
  https://www.arduino.cc/en/software
  ```
- **DHT Library**: In order to use the DHT22 or DHT11 to read temperatures you will need to get the DHT adafruit library

  ```
  https://www.arduino.cc/reference/en/libraries/dht-sensor-library/
  ```


## Getting Started

1. Clone this repository to your local machine:

   ```bash
   git clone <repository-url>
   ```

2. Navigate to the project folder:
  ```bash
   cd esp32-weather-station
   ```
3. Connect ESP32 to your computer
   
4. Open the Arduino IDE

5. Upload the code in from the weather_app.ino onto your ESP32 board.
   
6. Close the IDE, to free up the port

7. Modify the `index.html` file if needed. This HTML file is served to clients and displays weather information.

8. Update the `path` property in the Node.js code (`app.js`) to match the serial port where your ESP32 is connected:

   ```javascript
   const port = new SerialPort.SerialPort({
     path: "/dev/cu.usbserial-10", // Update this path
     baudRate: 9600,
     dataBits: 8,
     parity: "none",
     stopBits: 1,
     flowControl: false,
   });
   ```

9. Run the Node.js application:

   ```bash
   node app.js
   ```

10. Access the weather station web interface by opening a web browser and navigating to `http://localhost:6900`.

## Usage

- The web interface displays temperature and humidity information received from your ESP32 in real-time.

- The temperature and humidity values are updated automatically whenever new data is received from the ESP32.

- You can customise the web interface by modifying the `index.html` file.

## Author

- Mark Lu

## Dependencies

- Node.js
- Socket.io v2.0.4
- SerialPort v12.0.0
- Express v4.18.2
- Johnny-five v2.1.0

## Acknowledgments

- Thanks to the open-source community for providing the necessary libraries and tools to build this weather station.

**Resources used:** 
- https://www.freecodecamp.org/news/how-to-write-a-good-readme-file/
- https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-web-server-arduino-ide/
- https://www.upesy.com/blogs/tutorials/dht11-humidity-temperature-sensor-with-arduino-code-on-esp32-board#
- https://medium.com/@svsh227/nodejs-with-arduino-5020489f3ec7
- https://www.engineersgarage.com/how-to-build-a-node-js-server-to-control-arduino-from-a-webpage/

**Images used:**
- https://www.flaticon.com/free-icon/thermometer_4158502
- https://www.freepik.com/icon/water-drop_3046562
