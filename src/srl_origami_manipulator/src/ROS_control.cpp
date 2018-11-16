#include <ros/ros.h>
#include <cmath>
#include <vector>
#include <string>
#include <sensor_msgs/Joy.h>
#include <srl_origami_manipulator/motorCmd.h>
#include <srl_origami_manipulator/I2C_msg.h>
#define PI 3.14159265

class OrigamiSegment{
    private:
        const int gearRatio = 300;
        const int encoder_multiplier = 12;
        const double s_max = 15.0;
        const double s_min = 0.06;
        const double k_max = 0.14;
        const double height_offset = 0.011;
        const double diameter = 32.5 * 0.001;
        const double motor_shaft_hub_diameter = 0.0054;
        const double motor_shaft_hub_circum = PI * motor_shaft_hub_diameter;
        const int I2CBytes = 2;
        const int cable_num = 3;
        
        int addr;
        
    public:
        double s;
        double k;
        double phi;
        srl_origami_manipulator::motorCmd final_command;
        std::vector<double> cable_length; 
        std::vector<int> motor_command;

        OrigamiSegment(const int& address){
            std::cout << "intializing segement" << std::endl;
            addr = address;
            cable_length.resize(3);
            motor_command.resize(3);
        }

        void updateSettingPoints(double input_x, double input_y, double input_z, double k_avg_x, double k_avg_y, double phi_avg){
            // std::cout << "Updating setting points " << std::endl;
            // udpate k parameter
            double temp = sqrt(pow(input_x, 2) + pow(input_y, 2));
            if(temp == 0){
                temp = 1/2;
            }
            temp = temp < 0 ? 0 : 1;
            double k_x = temp * k_avg_x - k * cos(phi) / (2 * k_max);
            double k_y = temp * k_avg_y - k * sin(phi) / (2 * k_max);
            k = sqrt(pow(k_x, 2) + pow(k_y, 2));
            if(k > k_max){
                k = k_max;
            }
            // update phi parameter
            phi = atan2(k_y, k_x);
            // update s parameter
            s = s_min + input_z * (s_max - s_min);
        }

        void IKSolverCables(){            
            s = s - height_offset;

            cable_length[0] = s * (1 - k*diameter * sin(phi));
            cable_length[1] = s * (1 + k*diameter * sin(PI/3 + phi));
            cable_length[2] = s * (1 - k*diameter * sin(PI/6 + phi));

            
            for(int i = 0; i < 3; i++){
                motor_command[i] = (int) ceil((s_max - cable_length[i]) / motor_shaft_hub_circum * gearRatio * encoder_multiplier);
            }
        }

        void motorCommandCovert(){
            srl_origami_manipulator::motorCmd temp;
            for(int i = 0; i < 3; i++){
                if(motor_command[i] < 0){
                    ROS_ERROR_STREAM("Warning, cannot increase curvature further! Need to decrease arc length!");
                    motor_command[i] = 0;
                }
                // it should not be pushed back, will make it longer and longer 
                temp.motor_cmd.push_back(motor_command[i] >> 8);
                temp.motor_cmd.push_back(motor_command[i] & 0xff);
            }
            final_command.motor_cmd = temp.motor_cmd;
        }

};

class JoyStickPlatform{
    private:
        std::vector<int> buttons;
        std::vector<float> axes;
        
    public:
        double x;
        double y;
        double z;
        int mode = 0;
        double delta = 0.1;
        std::vector<OrigamiSegment> segmentList;
        JoyStickPlatform(){
            buttons.resize(10);
            axes.resize(3);
        }

        void configHardware(const std::vector<int>& addrList){
            for(int i = 0; i < addrList.size(); i++){     
                OrigamiSegment temp(addrList[i]);       
                segmentList.push_back(temp);
            }
        }

        void getInput(const sensor_msgs::Joy::ConstPtr& msg){
            buttons = msg->buttons;
            axes = msg->axes;
            // std::cout << "buttons: "; 
            // for(auto i : buttons){
            //     std::cout << i << ' ';
            // }
            // std::cout << std::endl;
            // std::cout << "axes: "; 
            // for(auto i : axes){
            //     std::cout << i << ' ';
            // }
            // std::cout << std::endl;
            // select mode, 
            if(buttons[5] == 1){
                mode = 1;
            }
            else if(buttons[6] == 1){
                mode = 2;
            }
            else if(buttons[7] == 1){
                mode = 3;
            }
            else if(buttons[8] == 1){
                mode = 4;
            }
            // generate x, y, z value
            x = -sqrt(3) / 2 * axes[0] + 0.5 * axes[1];
            y = 0.5 * axes[0] + sqrt(3) / 2 * axes[1];
            z = axes[2]; 
            std::cout << "current mode: " << mode << std::endl;
        }

        std::vector<int> findActiveModules(){
            std::vector<int> activeModuleList;
            if(mode == 1){
                activeModuleList.push_back(1);
            }
            else if(mode == 2){
                activeModuleList.push_back(1);
                activeModuleList.push_back(2);
            }
            else if(mode == 3){
                activeModuleList.push_back(2);
                activeModuleList.push_back(3);
            }
            else if(mode == 4){
                activeModuleList.push_back(1);
                activeModuleList.push_back(2);
                activeModuleList.push_back(3);
            }
            return activeModuleList;
            std::cout << "active module size: " << activeModuleList.size() << std::endl;
        }        

};

void printInfo(srl_origami_manipulator::I2C_msg pub_cmd);

int main(int argc, char **argv){
    ros::init(argc, argv, "JSPlatform");
    ros::NodeHandle n;
    double sum_k = 0;
    double sum_phi = 0;
    double k_avg = 0;
    double k_avg_x = 0;
    double k_avg_y = 0;
    double phi_avg = 0;

    // int masterAddress = 
    int module1_addr = 0x08;
    int module2_addr = 0x09;
    int module3_addr = 0x0A;
    int gripper_addr = 0x64;
    std::vector<int> deviceAddrList = {module1_addr, module2_addr, module3_addr, gripper_addr};
    JoyStickPlatform playGround;
    std::cout << "create Platform" << std::endl;
    playGround.configHardware(deviceAddrList);
    std::cout << "size of segements: " << playGround.segmentList.size() << std::endl;
    srl_origami_manipulator::I2C_msg pub_cmd;
    srl_origami_manipulator::I2C_msg pub_record;

    pub_cmd.slaveAddress = deviceAddrList;
    srl_origami_manipulator::motorCmd defaultCommand;
    defaultCommand.motor_cmd = {0, 0, 0, 0, 0, 0};
    // need to make sure a vector can be pushed back to another vector
    for(int i = 0; i<playGround.segmentList.size(); i++){
        pub_cmd.setPoint.push_back(defaultCommand);
    }
    
    ros::Publisher command_pub = n.advertise<srl_origami_manipulator::I2C_msg>("motorCommand", 1);
    //ros::Rate loop_rate(10)
    ros::Subscriber sub = n.subscribe("joy", 10, &JoyStickPlatform::getInput, &playGround);

    while(ros::ok()){
        std::vector<int> activeList = playGround.findActiveModules();
        // std::cout << "activate list: " ;
        // for(auto i : activeList){
        //     std::cout << i << ' ';
        // }
        // std::cout << std::endl;
        sum_k = 0;
        sum_phi = 0;
        pub_cmd.setPoint.clear();

        if(playGround.mode == 0){
            for(int i = 0; i<playGround.segmentList.size(); i++){
                pub_cmd.setPoint.push_back(defaultCommand);
            }
        }
        else if(activeList.size() != 0){
            for(int module : activeList){
                sum_k += playGround.segmentList[module].k;
                sum_phi += playGround.segmentList[module].phi;       
            }
            k_avg = sum_k / activeList.size();
            phi_avg = sum_phi / activeList.size();
            k_avg_x = k_avg * cos(phi_avg) + playGround.x * playGround.delta;
            k_avg_y = k_avg * sin(phi_avg) + playGround.y * playGround.delta;
            
            //for(int i = 0; i < activeList.size(); i++){
            for(int module : activeList){
                playGround.segmentList[module].updateSettingPoints(playGround.x, playGround.y, playGround.z, k_avg_x, k_avg_y, phi_avg);
                playGround.segmentList[module].IKSolverCables();
                playGround.segmentList[module].motorCommandCovert();
                pub_cmd.setPoint[module] = playGround.segmentList[module].final_command;
            }
        }
        if(pub_record != pub_cmd){
            pub_record = pub_cmd;
            printInfo(pub_record);
            
        }
        command_pub.publish(pub_cmd);
        ros::spinOnce();
    }

    return 0;
}

void printInfo(srl_origami_manipulator::I2C_msg pub_cmd){
    for(int i = 0; i < pub_cmd.setPoint.size(); i++){
        std::cout << "segment " << i << ": ";
        srl_origami_manipulator::motorCmd temp = pub_cmd.setPoint.at(i);
        for(int j = 0; j < temp.motor_cmd.size(); j++){
            std::cout <<  temp.motor_cmd[j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}