;; Auto-generated. Do not edit!


(when (boundp 'srl_origami_manipulator::I2C_msg)
  (if (not (find-package "SRL_ORIGAMI_MANIPULATOR"))
    (make-package "SRL_ORIGAMI_MANIPULATOR"))
  (shadow 'I2C_msg (find-package "SRL_ORIGAMI_MANIPULATOR")))
(unless (find-package "SRL_ORIGAMI_MANIPULATOR::I2C_MSG")
  (make-package "SRL_ORIGAMI_MANIPULATOR::I2C_MSG"))

(in-package "ROS")
;;//! \htmlinclude I2C_msg.msg.html


(defclass srl_origami_manipulator::I2C_msg
  :super ros::object
  :slots (_setPoint _slaveAddress ))

(defmethod srl_origami_manipulator::I2C_msg
  (:init
   (&key
    ((:setPoint __setPoint) (let (r) (dotimes (i 0) (push (instance srl_origami_manipulator::motorCmd :init) r)) r))
    ((:slaveAddress __slaveAddress) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _setPoint __setPoint)
   (setq _slaveAddress __slaveAddress)
   self)
  (:setPoint
   (&rest __setPoint)
   (if (keywordp (car __setPoint))
       (send* _setPoint __setPoint)
     (progn
       (if __setPoint (setq _setPoint (car __setPoint)))
       _setPoint)))
  (:slaveAddress
   (&optional __slaveAddress)
   (if __slaveAddress (setq _slaveAddress __slaveAddress)) _slaveAddress)
  (:serialization-length
   ()
   (+
    ;; srl_origami_manipulator/motorCmd[] _setPoint
    (apply #'+ (send-all _setPoint :serialization-length)) 4
    ;; int32[] _slaveAddress
    (* 4    (length _slaveAddress)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; srl_origami_manipulator/motorCmd[] _setPoint
     (write-long (length _setPoint) s)
     (dolist (elem _setPoint)
       (send elem :serialize s)
       )
     ;; int32[] _slaveAddress
     (write-long (length _slaveAddress) s)
     (dotimes (i (length _slaveAddress))
       (write-long (elt _slaveAddress i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; srl_origami_manipulator/motorCmd[] _setPoint
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _setPoint (let (r) (dotimes (i n) (push (instance srl_origami_manipulator::motorCmd :init) r)) r))
     (dolist (elem- _setPoint)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; int32[] _slaveAddress
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _slaveAddress (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _slaveAddress i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get srl_origami_manipulator::I2C_msg :md5sum-) "12ba8230fa92ad82e9f73eadbdbea506")
(setf (get srl_origami_manipulator::I2C_msg :datatype-) "srl_origami_manipulator/I2C_msg")
(setf (get srl_origami_manipulator::I2C_msg :definition-)
      "motorCmd[] setPoint
int32[] slaveAddress
================================================================================
MSG: srl_origami_manipulator/motorCmd
int8[] motor_cmd
")



(provide :srl_origami_manipulator/I2C_msg "12ba8230fa92ad82e9f73eadbdbea506")


