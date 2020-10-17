#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include<iostream>
#include<iomanip>
#include<vector>
#include<cmath>

#include "brownie.h"

#define PI 3.1415
#define TAU 6.2830

class World
{
    std::vector<Brownie*>population;

    float month; // counts from 1-12
    float date;  // counts from 1-28
    float hour;  // counts from 1-24

    float dayOfYear; // counts from 1-338 (28days x 12months)

    float temperature;


public:

    void Progress(int hours);
    void CalculateTemperature();

    void UpdateDayOfYear();

    World();
    ~World();
};
#endif // WORLD_H_INCLUDED
