#include "actuator.h"
#include <cmath>
#include <vector>
#include "srl_origami_manipulator/motorCmd.h"

using std::vector;

Actuator::Actuator(int address){
    addr = address;
    s = s_max;
    phi = 0;
    k = 0;
    max_length = s_max;
    cabels_vec.resize(3);
    motor_cmd.resize(3);
    
}

void Actuator::updateParameters(const double& new_k, const double& new_phi, const double& x, const double& y, const double& z){
    double temp =  heaviside(x, y);
    double new_k_x = new_k * cos(new_phi) + x * delta;
    double new_k_y = new_k * cos(new_phi) + y * delta;
    double delta_x = temp * (new_k_x - k * cos(phi)) / (2 * k_max);
    double delta_y = temp * (new_k_y - k * sin(phi)) / (2 * k_max);
    double k_x = k * cos(phi) + (x + delta_x) * delta;
    double k_y = k * sin(phi) + (y + delta_y) * delta;

    k = sqrt(pow(k_x, 2) + pow(k_y, 2));
    if(k > k_max){
        k = k_max;
    }

    phi = atan2(k_x, k_y);
    s = s_min + z * (s_max - s_min);
    //std::cout << "update actuator params" << std::endl;
}

void Actuator::IKSolver(){
    s = s - height_offset;
    cabels_vec[0] = s * (1 - k * diameter * sin(phi));
    cabels_vec[1] = s * (1 + k * diameter * sin(PI/3 + phi));
    cabels_vec[2] = s * (1 - k * diameter * cos(PI/6 + phi));

    for(int i = 0; i < 3; i++){
        motor_cmd[i] = std::ceil((max_length - cabels_vec[i]) / motor_shaft_hub_circum * gearRatio * encoder_multiplier);
    }
    //std::cout << "ik solver" << std::endl;
}

void Actuator::commdConvert(){
    final_cmd.motor_cmd.clear();
    // std::cout << "motor cmd: ";
    for(int i = 0; i < 3; i++){
        int temp = motor_cmd[i] >> 8;
        final_cmd.motor_cmd.push_back(temp);
        //std::cout << " low: " << static_cast<int16_t>(temp);
        temp = motor_cmd[i] & 255;
        //std::cout << " high: " << static_cast<int16_t>(temp);
        final_cmd.motor_cmd.push_back(temp);
    }
    // std::cout << std::endl;
    //std::cout << "convert command" << std::endl;
}

double Actuator::heaviside(double x, double y){
    double temp = std::sqrt(pow(x, 2) + pow(y, 2));
    if(temp == 0.0){
        return 0.5;
    }
    return temp < 0 ? 0 : 1;
}

void Actuator::home(){
    s = s_max;
    k = 0;
    phi = 0;
}

endEffector::endEffector(const int addr){
    address = addr;
}

void endEffector::setOpenFlag(bool operation){
      isOpen = operation;
}

bool endEffector::getOpenFlag(){
      return isOpen;
}

