#include "playGround.h"
#include "actuator.h"
#include <vector>
#include <cmath>
#include "srl_origami_manipulator/I2C_msg.h"

using std::vector;

playGround::playGround(int segment_num, int ee_num, const std::vector<int> seg_addr, const std::vector<int> ee_addr)
{
    this->segment_num = segment_num;
    this->ee_num = ee_num;

    // create segment list with their address
    for (int i = 0; i < segment_num; i++)
    {
        Actuator a(seg_addr[i]);
        actuator_list.push_back(a);
        output_cmd.slaveAddress.push_back(seg_addr[i]);
    }
    activited_actuator.assign(segment_num, 0);
    std::cout << "Initialize actuators: " << actuator_list.size() << std::endl;
    std::cout << "Initialize active list: " << activited_actuator.size() << std::endl;

    // create end effector list with their address
    for (int i = 0; i < ee_num; i++)
    {
        endEffector ee(ee_addr[i]);
        ee_list.push_back(ee);
    }
    std::cout << "Initialize effector: " << ee_list.size() << std::endl;

    for (int i = 0; i < mode_list.size(); i++)
    {
        buttons[mode_list[i]] = mode_index[i];
    }

    for (int i = 0; i < position_list.size(); i++)
    {
        axes[position_list[i]] = position_index[i];
    }

    axes_buffer.resize(8);
    axes_buffer[2] = 1.0;
    axes_buffer[5] = 1.0;
    buttons_buffer.resize(11);
    std::cout << "Initialize input vectors: " << std::endl;

    k_avg = 0;
    phi_avg = 0;

    output_cmd.setPoint.resize(3);
}

void playGround::updateInput(const sensor_msgs::Joy::ConstPtr &msg)
{
    //std::cout << "new input" << std::endl;
    vector<int32_t> temp_buttons = msg->buttons;
    vector<float> temp_axes = msg->axes;

    // if(temp_buttons != buttons_buffer){
    //     std::cout << "new buttons: ";
    //     printVec(temp_buttons);
    //     std::cout << "old buttons: ";
    //     printVec(buttons_buffer);
    // }

    if (temp_axes != axes_buffer)
    {
        // std::cout << "new values: ";
        // printVecF(temp_axes);
        // std::cout << "old values: ";
        // printVecF(axes_buffer);
        CMD_CHANGED = true;
    }

    buttons_buffer = temp_buttons;
    axes_buffer = temp_axes;

    // TODO: this numbers are need to be decide later//
    if(buttons_buffer[buttons["home"]] == 1){
        if(GO_HOME == true){
            std::cout << "Exiting Homing" << std::endl;
            GO_HOME = false;
        }
        else{
            GO_HOME = true;
            std::cout << "Entering Homing" << std::endl;
        }
    }
    input_x = axes_buffer[axes["x"]];
    input_y = axes_buffer[axes["y"]];
    input_z = axes_buffer[axes["z"]];

    input_x = -sqrt(3) / 2 * input_x + 0.5 * input_y;
    input_y = 0.5 * input_x + sqrt(3) / 2 * input_y;

    // check the control mode for actuators
    vector<int> new_mode;
    new_mode.resize(segment_num);
    if (buttons_buffer[buttons["single"]] == 1)
    {
        LIST_CHANGED = true;
        if (single_mode == false)
        {
            std::cout << "single mode now, please select segments" << std::endl;
            single_mode = true;
            new_mode.assign(segment_num, 0);
            segment_index = 0;
        }
        else
        {
            new_mode[segment_index] = 1;
            single_mode = false;
            std::cout << "segment is set to: " << segment_index << std::endl;
            for (int i = 0; i < activited_actuator.size(); i++)
            {
                activited_actuator[i] = new_mode[i];
            }
        }
    }

    if (single_mode)
    {
        if (buttons_buffer[buttons["switch_seg"]] == 1)
        {
            LIST_CHANGED = true;
            segment_index = (segment_index + 1) % segment_num;
            std::cout << "current segment: " << segment_index << std::endl;
            std::cout << "currently in single mode, press button to exit or change segment" << std::endl;
        }
        // else{
        //     std::cout << "haven't finish single mode configuration" << std::endl;
        // }
    }
    else
    {
        if (buttons_buffer[buttons["mode_1"]] == 1)
        {
            LIST_CHANGED = true;
            activited_actuator = {1, 1, 0};
            // assignList(temp, new_mode);
            std::cout << "current mode: actuator 0, and actuator 1" << std::endl;
        }
        else if (buttons_buffer[buttons["mode_2"]] == 1)
        {
            LIST_CHANGED = true;
            activited_actuator = {0, 1, 1};
            // assignList(temp, new_mode);
            std::cout << "current mode: actuator 1, and actuator 2" << std::endl;
        }
        else if (buttons_buffer[buttons["mode_3"]] == 1)
        {
            LIST_CHANGED = true;
            activited_actuator = {1, 1, 1};
            // assignList(temp, new_mode);
            std::cout << "current mode: all actuators moves" << std::endl;
        }
        // check if the gripper button is pressed
        else if (buttons_buffer[buttons["gripper"]] == 1)
        {
            if (ee_list[0].getOpenFlag() == false)
            {
                ee_list[0].setOpenFlag(true);
                std::cout << "Open End Effector" << std::endl;
            }
            else
            {
                ee_list[0].setOpenFlag(false);
                std::cout << "Close End Effector" << std::endl;
            }
        }
    }
}

void playGround::calculateParameters()
{
    int length = 0;
    double sum_ki = 0;
    double sum_phi = 0;
    for (int i = 0; i < activited_actuator.size(); i++)
    {
        if (activited_actuator[i] == 1)
        {
            length++;
            sum_ki += actuator_list[i].k;
            sum_phi += actuator_list[i].phi;
        }
    }

    double new_k_avg = k_avg;
    double new_phi_avg = phi_avg;

    if (length > 0)
    {
        k_avg = sum_ki / length;
        phi_avg = sum_phi / length;
    }
}

void playGround::updateOutputCmd()
{
    // update the command of activated segments TO DO: change the updated segemnts

    //output_cmd.setPoint.clear();
    for (int i = 0; i < activited_actuator.size(); i++)
    {
        if (activited_actuator[i] == 1)
        {
            Actuator temp = actuator_list[i];
            if(GO_HOME){
                temp.home();
            }
            else{
                temp.updateParameters(k_avg, phi_avg, input_x, input_y, input_z);
            }
            temp.IKSolver();
            temp.commdConvert();
            output_cmd.setPoint[i] = temp.final_cmd;
        }
    }
}

srl_origami_manipulator::I2C_msg playGround::getActuatorCmd()
{
    return output_cmd;
}

int playGround::getEECmd()
{
    return ee_list[0].getOpenFlag();
}

void playGround::assignList(std::vector<int> &reference, std::vector<int> &target)
{
    for (int i = 0; i < reference.size(); i++)
    {
        target[i] = reference[i];
    }
}

void playGround::printVec(const std::vector<int> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;
}

void playGround::printVecF(const std::vector<float> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;
}

void playGround::printCMD()
{
    std::cout << "new command is: " << std::endl;
    for (int i = 0; i < output_cmd.setPoint.size(); i++)
    {
        std::cout << "motor " << i << " : ";
        for (int j = 0; j < output_cmd.setPoint[i].motor_cmd.size(); j++)
        {
            std::cout << static_cast<int16_t>(output_cmd.setPoint[i].motor_cmd[j]) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void playGround::printActivatedList()
{
    std::cout << "activate actuator list: ";
    for (int i = 0; i < activited_actuator.size(); i++)
    {
        std::cout << activited_actuator[i] << " ";
    }
    std::cout << std::endl;
}

bool playGround::isCmdChanged()
{
    return CMD_CHANGED;
}

bool playGround::isListChanged()
{
    return LIST_CHANGED;
}

bool playGround::isSingleMode()
{
    return single_mode;
}

void playGround::resetListFlag()
{
    LIST_CHANGED = false;
}

void playGround::resetCmdFlag()
{
    CMD_CHANGED = false;
}