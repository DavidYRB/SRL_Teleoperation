#ifndef ACTUATOR_H
#define ACTUATOR_H

#define PI 3.14159265

#include "srl_origami_manipulator/motorCmd.h"
#include <vector>

class Actuator
{
  private:
    /* data */
    const int gearRatio = 300;
    const int encoder_multiplier = 12;
    const double delta = 0.1;
    const double s_max = 15.0;
    const double s_min = 0.06;
    const double k_max = 0.14;

    const double height_offset = 0.011;
    const double diameter = 32.5 * 0.001;
    double max_length;

    const double motor_shaft_hub_diameter = 0.0054;
    const double motor_shaft_hub_circum = PI * motor_shaft_hub_diameter;
    const int I2CBytes = 2;
    const int cable_num = 3;

  public:
    int addr;
    double s;
    double k;
    double phi;
    std::vector<double> cabels_vec;
    std::vector<int> motor_cmd;
    srl_origami_manipulator::motorCmd final_cmd;

  public:
    Actuator(int address);
    void updateParameters(const double& new_k, const double& new_phi, const double& x, const double& y, const double& z);
    void IKSolver();
    void commdConvert();
    double heaviside(double x, double y);
    void home();
};

class endEffector{
  private:
    bool isOpen = true;
    int address;
  
  public:
    endEffector(const int addr);
    void setOpenFlag(bool operation);
    bool getOpenFlag();
};

#endif