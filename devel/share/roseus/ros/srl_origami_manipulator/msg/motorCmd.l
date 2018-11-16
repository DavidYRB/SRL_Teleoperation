;; Auto-generated. Do not edit!


(when (boundp 'srl_origami_manipulator::motorCmd)
  (if (not (find-package "SRL_ORIGAMI_MANIPULATOR"))
    (make-package "SRL_ORIGAMI_MANIPULATOR"))
  (shadow 'motorCmd (find-package "SRL_ORIGAMI_MANIPULATOR")))
(unless (find-package "SRL_ORIGAMI_MANIPULATOR::MOTORCMD")
  (make-package "SRL_ORIGAMI_MANIPULATOR::MOTORCMD"))

(in-package "ROS")
;;//! \htmlinclude motorCmd.msg.html


(defclass srl_origami_manipulator::motorCmd
  :super ros::object
  :slots (_motor_cmd ))

(defmethod srl_origami_manipulator::motorCmd
  (:init
   (&key
    ((:motor_cmd __motor_cmd) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _motor_cmd __motor_cmd)
   self)
  (:motor_cmd
   (&optional __motor_cmd)
   (if __motor_cmd (setq _motor_cmd __motor_cmd)) _motor_cmd)
  (:serialization-length
   ()
   (+
    ;; int8[] _motor_cmd
    (* 1    (length _motor_cmd)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8[] _motor_cmd
     (write-long (length _motor_cmd) s)
     (dotimes (i (length _motor_cmd))
       (write-byte (elt _motor_cmd i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8[] _motor_cmd
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _motor_cmd (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _motor_cmd i) (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> (elt _motor_cmd i) 127) (setf (elt _motor_cmd i) (- (elt _motor_cmd i) 256)))
     ))
   ;;
   self)
  )

(setf (get srl_origami_manipulator::motorCmd :md5sum-) "091b2c9cf1f930ed90809c60dc039030")
(setf (get srl_origami_manipulator::motorCmd :datatype-) "srl_origami_manipulator/motorCmd")
(setf (get srl_origami_manipulator::motorCmd :definition-)
      "int8[] motor_cmd
")



(provide :srl_origami_manipulator/motorCmd "091b2c9cf1f930ed90809c60dc039030")


