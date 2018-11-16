
(cl:in-package :asdf)

(defsystem "srl_origami_manipulator-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "I2C_msg" :depends-on ("_package_I2C_msg"))
    (:file "_package_I2C_msg" :depends-on ("_package"))
    (:file "motorCmd" :depends-on ("_package_motorCmd"))
    (:file "_package_motorCmd" :depends-on ("_package"))
  ))