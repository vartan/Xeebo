#!/usr/bin/env node
"use strict";
var Q = require("q");
// Open a new message handler
var serialIdentifier = process.argv[2] || "/dev/ttyUSB0";
var messageHandler = require("serialmessages")(serialIdentifier);

var messageList = getMessageProperties();

// echo all received characters back to command line
messageHandler.serialPort.on("data", echo(messageHandler.serialPort));

for(var message_name in messageList) {
  var mp = messageList[message_name];
  mp.messageHandler = messageHandler.addHandler({
    id:     mp.id,
    name:   mp.name,
    length: mp.receiveLength
  });
  if(mp.receiveHandler !== null) {
    mp.messageHandler.on("message", mp.receiveHandler);
  }
}
Q.when(messageHandler.open())
  .then(sendNewMotion( {
      surge:100,
      sway:0,
      heave:0,
      roll:0,
      yaw:0,
      pitch:0
    }));


function sendNewMotion(motionData) {


      //String.fromCharCode(messageList.NEW_MOTION.id)
      return messageHandler.sendMessage(new Buffer(
        messageList.NEW_MOTION.id,
          motionData.surge,
          motionData.sway,
          motionData.heave,
          motionData.roll,
          motionData.yaw,
          motionData.pitch
        ));
  }
/*
Q.when(messageHandler.open())                                                //1
  .then(messageHandler.sendMessage("test\r\n"))                              //2
  .then(function handleSentMessage(messageLength) {                          //3
    console.log("sent message which was "+messageLength+" characters long.");
  })
  .then(testHandler.receive())                                               //4
  .then(function handleFirstMessage(event) {                                 //5
    console.log("Finally received expected message 1: "+event.data);               
  })
  .then(testHandler2.receive())                                              //6
  .then(function handleSecondMessage(event) {                                //7
    console.log("Finally received expected message 2: "+event.data);            
  })  
  .finally(function logFinished() {                                          //8
    console.log("Finished!");
  })
  .catch(function(error){console.log(error);});
*/


/*************************** Misc. Functions Below ***************************/

/**
 * Log received messages to command line, and notify user via bell.
 * @param  {Buffer} event Event received over serial
 */
function logMessageHandler(event) {
  console.log("(" + event.messageHandler.name + ": " + event.data + ")\u0007");
}

/**
 * Used to echo received data back over serial.
 * @param  {Buffer} serialPort SerialPort to echo to
 */
function echo(serialPort) {
  /**
   * Echo to serial port
   * @param  {Buffer} data Data to send over port
   */
  return function echoToPort(data) {
    var i;
    for (i = 0; i < data.length; i += 1) {
      var char = data[i];
      if (char === "\r".charCodeAt(0)) {
        serialPort.write("\r\n", function(){});
      } else if (char === 0x7f) {
        serialPort.write("\b \b", function(){});
      } else {
        serialPort.write(String.fromCharCode(char),function(){});
      }
    }
  };
}
/**
 * Send New Line
 * Sends a line break over serial, for debugging purposes
 * @return {Promise} Promise to send new newline character
 */
function sendNewLine() {
  return Q.fcall(messageHandler.sendMessage("\r\n")); 
}

function ascii (char){
  return char.charCodeAt(0);
}

function getMessageProperties() {
  return {
    /** 
     * Do nothing; Send (MAX(num bytes)) times to flush out messages if out of sync.
     * 
     * @property FLUSH
     */
    FLUSH: {
      id:            0x00,
      name:          "FLUSH",
      receiveLength: 0,
      sendLength:    0,
      receiveHandler: null,
    },
    /** 
     * Send a ping to verify that the line is valid
     * 
     * @property PING
     */
    PING: {
      id:            0x01,
      name:          "PING",
      receiveLength: 1,
      sendLength:    1,
      receiveHandler: null,
    },
    /** 
     * Reply to a ping with a pong
     * 
     * @property PONG
     */
    PONG: {
      id:            0x02,
      name:          "PONG",
      receiveLength: 1,
      sendLength:    1,
      receiveHandler: null,
    },
    /** 
     * Update the motion vectors to move the robot
     * 
     * @property NEW_MOTION
     */
    NEW_MOTION: {
      id:            0x03,
      name:          "NEW_MOTION",
      receiveLength: 0,
      sendLength:    6,
      receiveHandler: null,
    },
    /** 
     * Request the motion vector state controlling the motors
     * 
     * @property GET_MOTION
     */
    GET_MOTION: {
      id:            0x04,
      name:          "GET_MOTION",
      receiveLength: 6,
      sendLength:    0,
      receiveHandler: null,
    },
    /** 
     * Request the current battery life
     * 
     * @property GET_BATTERY
     */
    GET_BATTERY: {
      id:            0x05,
      name:          "GET_BATTERY",
      receiveLength: 1,
      sendLength:    0,
      receiveHandler: null,
    },
  };
}

