#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "actuator.h"
#include "playGround.h"
#include <vector>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "Manipulator");
    ros::NodeHandle nh;
    
    int segment_num = 3;
    int ee_num = 1;
    std::vector<int> segment_addr_vec{0x08, 0x09, 0x0A};
    std::vector<int> ee_addr_vec{0x64};
    bool NeedPrint = false;

    playGround manipulator(3, 1, segment_addr_vec, ee_addr_vec);

    ros::Publisher actuatorPub = nh.advertise<srl_origami_manipulator::I2C_msg>("actuatorCmd", 1000);
    ros::Publisher eePub = nh.advertise<std_msgs::Int32>("eeCmd", 1);
    ros::Subscriber sub = nh.subscribe("joy", 1, &playGround::updateInput, &manipulator);
    std::cout << "Initialization finished" << std::endl;
    while(ros::ok()){
        //manipulator.updateActivitedList();
        if(!manipulator.isSingleMode()){
            manipulator.calculateParameters();
            manipulator.updateOutputCmd();
            if(manipulator.isCmdChanged()){
                manipulator.printCMD();
                manipulator.resetCmdFlag(); 
            }
        }
        if(manipulator.isListChanged()){
            manipulator.printActivatedList();
            manipulator.resetListFlag();
        }
        actuatorPub.publish(manipulator.getActuatorCmd());
        bool eeMove = manipulator.getEECmd();
        // std::cout << eeMove << std::endl;
        std_msgs::Int32 msg;
        if(eeMove){
            msg.data = 1;
            eePub.publish(msg);
            // std::cout << "sending " << eeMove << std::endl;
        }
        else{
            msg.data = 0;
            eePub.publish(msg);
            // std::cout << "sending " << eeMove << std::endl;
        }
        ros::spinOnce();
    }
    return 0;
}
