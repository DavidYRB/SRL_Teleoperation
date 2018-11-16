// Auto-generated. Do not edit!

// (in-package srl_origami_manipulator.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let motorCmd = require('./motorCmd.js');

//-----------------------------------------------------------

class I2C_msg {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.setPoint = null;
      this.slaveAddress = null;
    }
    else {
      if (initObj.hasOwnProperty('setPoint')) {
        this.setPoint = initObj.setPoint
      }
      else {
        this.setPoint = [];
      }
      if (initObj.hasOwnProperty('slaveAddress')) {
        this.slaveAddress = initObj.slaveAddress
      }
      else {
        this.slaveAddress = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type I2C_msg
    // Serialize message field [setPoint]
    // Serialize the length for message field [setPoint]
    bufferOffset = _serializer.uint32(obj.setPoint.length, buffer, bufferOffset);
    obj.setPoint.forEach((val) => {
      bufferOffset = motorCmd.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [slaveAddress]
    bufferOffset = _arraySerializer.int32(obj.slaveAddress, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type I2C_msg
    let len;
    let data = new I2C_msg(null);
    // Deserialize message field [setPoint]
    // Deserialize array length for message field [setPoint]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.setPoint = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.setPoint[i] = motorCmd.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [slaveAddress]
    data.slaveAddress = _arrayDeserializer.int32(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.setPoint.forEach((val) => {
      length += motorCmd.getMessageSize(val);
    });
    length += 4 * object.slaveAddress.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'srl_origami_manipulator/I2C_msg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '12ba8230fa92ad82e9f73eadbdbea506';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    motorCmd[] setPoint
    int32[] slaveAddress
    ================================================================================
    MSG: srl_origami_manipulator/motorCmd
    int8[] motor_cmd
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new I2C_msg(null);
    if (msg.setPoint !== undefined) {
      resolved.setPoint = new Array(msg.setPoint.length);
      for (let i = 0; i < resolved.setPoint.length; ++i) {
        resolved.setPoint[i] = motorCmd.Resolve(msg.setPoint[i]);
      }
    }
    else {
      resolved.setPoint = []
    }

    if (msg.slaveAddress !== undefined) {
      resolved.slaveAddress = msg.slaveAddress;
    }
    else {
      resolved.slaveAddress = []
    }

    return resolved;
    }
};

module.exports = I2C_msg;
