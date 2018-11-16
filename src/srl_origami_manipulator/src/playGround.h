#ifndef PLAY_GROUND_H
#define PLAY_GROUND_H

#include <vector>
#include <map>
#include <string>
#include "actuator.h"
#include "sensor_msgs/Joy.h"
#include "srl_origami_manipulator/motorCmd.h"
#include "srl_origami_manipulator/I2C_msg.h"

class playGround
{
  private:
    /* data */
    std::vector<Actuator> actuator_list;
    std::vector<int> activited_actuator;

    std::vector<endEffector> ee_list;
    std::vector<int> activited_ee;

    std::vector<std::string> mode_list{"single", "mode_1", "mode_2", "mode_3", "gripper", "switch_seg", "home"};
    std::vector<int> mode_index{0, 1, 2, 3, 4, 5, 8};

    std::vector<std::string> position_list{"x", "y", "z"};
    std::vector<int> position_index{0, 1, 2};

    std::map<std::string, float> axes;
    std::map<std::string, int> buttons;

    std::vector<int32_t> buttons_buffer;
    std::vector<float> axes_buffer;

    srl_origami_manipulator::I2C_msg output_cmd;

    double k_avg;
    double phi_avg;
    double input_x;
    double input_y;
    double input_z;

    bool single_mode = false;
    int segment_index = 0;
    bool ready_to_go = false;

    int segment_num;
    int ee_num;
    
    bool CMD_CHANGED = false;
    bool LIST_CHANGED = false;
    bool GO_HOME = false;

  public:
    playGround(int segment_num, int ee_num, const std::vector<int> seg_addr, const std::vector<int> ee_addr);
    void updateInput(const sensor_msgs::Joy::ConstPtr& msg);
    void updateActivitedList();
    void calculateParameters();
    void updateOutputCmd();
    srl_origami_manipulator::I2C_msg getActuatorCmd();
    int getEECmd();
    void assignList(std::vector<int>& reference, std::vector<int>& target);
    void printVec(const std::vector<int>& vec);
    void printVecF(const std::vector<float>& vec);
    void printCMD();
    void printActivatedList();
    bool isSingleMode();
    bool isCmdChanged();
    bool isListChanged();
    void resetListFlag();
    void resetCmdFlag();
};

#endif