// Auto-generated. Do not edit!

// (in-package srl_origami_manipulator.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class motorCmd {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.motor_cmd = null;
    }
    else {
      if (initObj.hasOwnProperty('motor_cmd')) {
        this.motor_cmd = initObj.motor_cmd
      }
      else {
        this.motor_cmd = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type motorCmd
    // Serialize message field [motor_cmd]
    bufferOffset = _arraySerializer.int8(obj.motor_cmd, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type motorCmd
    let len;
    let data = new motorCmd(null);
    // Deserialize message field [motor_cmd]
    data.motor_cmd = _arrayDeserializer.int8(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.motor_cmd.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'srl_origami_manipulator/motorCmd';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '091b2c9cf1f930ed90809c60dc039030';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8[] motor_cmd
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new motorCmd(null);
    if (msg.motor_cmd !== undefined) {
      resolved.motor_cmd = msg.motor_cmd;
    }
    else {
      resolved.motor_cmd = []
    }

    return resolved;
    }
};

module.exports = motorCmd;
