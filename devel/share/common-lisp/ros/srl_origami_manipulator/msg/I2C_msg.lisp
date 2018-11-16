; Auto-generated. Do not edit!


(cl:in-package srl_origami_manipulator-msg)


;//! \htmlinclude I2C_msg.msg.html

(cl:defclass <I2C_msg> (roslisp-msg-protocol:ros-message)
  ((setPoint
    :reader setPoint
    :initarg :setPoint
    :type (cl:vector srl_origami_manipulator-msg:motorCmd)
   :initform (cl:make-array 0 :element-type 'srl_origami_manipulator-msg:motorCmd :initial-element (cl:make-instance 'srl_origami_manipulator-msg:motorCmd)))
   (slaveAddress
    :reader slaveAddress
    :initarg :slaveAddress
    :type (cl:vector cl:integer)
   :initform (cl:make-array 0 :element-type 'cl:integer :initial-element 0)))
)

(cl:defclass I2C_msg (<I2C_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <I2C_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'I2C_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name srl_origami_manipulator-msg:<I2C_msg> is deprecated: use srl_origami_manipulator-msg:I2C_msg instead.")))

(cl:ensure-generic-function 'setPoint-val :lambda-list '(m))
(cl:defmethod setPoint-val ((m <I2C_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader srl_origami_manipulator-msg:setPoint-val is deprecated.  Use srl_origami_manipulator-msg:setPoint instead.")
  (setPoint m))

(cl:ensure-generic-function 'slaveAddress-val :lambda-list '(m))
(cl:defmethod slaveAddress-val ((m <I2C_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader srl_origami_manipulator-msg:slaveAddress-val is deprecated.  Use srl_origami_manipulator-msg:slaveAddress instead.")
  (slaveAddress m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <I2C_msg>) ostream)
  "Serializes a message object of type '<I2C_msg>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'setPoint))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'setPoint))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'slaveAddress))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'slaveAddress))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <I2C_msg>) istream)
  "Deserializes a message object of type '<I2C_msg>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'setPoint) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'setPoint)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'srl_origami_manipulator-msg:motorCmd))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'slaveAddress) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'slaveAddress)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296)))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<I2C_msg>)))
  "Returns string type for a message object of type '<I2C_msg>"
  "srl_origami_manipulator/I2C_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'I2C_msg)))
  "Returns string type for a message object of type 'I2C_msg"
  "srl_origami_manipulator/I2C_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<I2C_msg>)))
  "Returns md5sum for a message object of type '<I2C_msg>"
  "12ba8230fa92ad82e9f73eadbdbea506")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'I2C_msg)))
  "Returns md5sum for a message object of type 'I2C_msg"
  "12ba8230fa92ad82e9f73eadbdbea506")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<I2C_msg>)))
  "Returns full string definition for message of type '<I2C_msg>"
  (cl:format cl:nil "motorCmd[] setPoint~%int32[] slaveAddress~%================================================================================~%MSG: srl_origami_manipulator/motorCmd~%int8[] motor_cmd~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'I2C_msg)))
  "Returns full string definition for message of type 'I2C_msg"
  (cl:format cl:nil "motorCmd[] setPoint~%int32[] slaveAddress~%================================================================================~%MSG: srl_origami_manipulator/motorCmd~%int8[] motor_cmd~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <I2C_msg>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'setPoint) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'slaveAddress) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <I2C_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'I2C_msg
    (cl:cons ':setPoint (setPoint msg))
    (cl:cons ':slaveAddress (slaveAddress msg))
))
