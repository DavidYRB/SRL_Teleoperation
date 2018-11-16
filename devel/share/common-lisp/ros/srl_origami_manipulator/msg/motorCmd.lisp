; Auto-generated. Do not edit!


(cl:in-package srl_origami_manipulator-msg)


;//! \htmlinclude motorCmd.msg.html

(cl:defclass <motorCmd> (roslisp-msg-protocol:ros-message)
  ((motor_cmd
    :reader motor_cmd
    :initarg :motor_cmd
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass motorCmd (<motorCmd>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <motorCmd>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'motorCmd)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name srl_origami_manipulator-msg:<motorCmd> is deprecated: use srl_origami_manipulator-msg:motorCmd instead.")))

(cl:ensure-generic-function 'motor_cmd-val :lambda-list '(m))
(cl:defmethod motor_cmd-val ((m <motorCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader srl_origami_manipulator-msg:motor_cmd-val is deprecated.  Use srl_origami_manipulator-msg:motor_cmd instead.")
  (motor_cmd m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <motorCmd>) ostream)
  "Serializes a message object of type '<motorCmd>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'motor_cmd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    ))
   (cl:slot-value msg 'motor_cmd))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <motorCmd>) istream)
  "Deserializes a message object of type '<motorCmd>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'motor_cmd) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'motor_cmd)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256)))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<motorCmd>)))
  "Returns string type for a message object of type '<motorCmd>"
  "srl_origami_manipulator/motorCmd")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'motorCmd)))
  "Returns string type for a message object of type 'motorCmd"
  "srl_origami_manipulator/motorCmd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<motorCmd>)))
  "Returns md5sum for a message object of type '<motorCmd>"
  "091b2c9cf1f930ed90809c60dc039030")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'motorCmd)))
  "Returns md5sum for a message object of type 'motorCmd"
  "091b2c9cf1f930ed90809c60dc039030")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<motorCmd>)))
  "Returns full string definition for message of type '<motorCmd>"
  (cl:format cl:nil "int8[] motor_cmd~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'motorCmd)))
  "Returns full string definition for message of type 'motorCmd"
  (cl:format cl:nil "int8[] motor_cmd~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <motorCmd>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'motor_cmd) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <motorCmd>))
  "Converts a ROS message object to a list"
  (cl:list 'motorCmd
    (cl:cons ':motor_cmd (motor_cmd msg))
))
