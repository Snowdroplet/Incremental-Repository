#include "world.h"


World::World()
{
    hour = 6;
    date = 1;
    month = 9;
    UpdateDayOfYear();

    CalculateTemperature();

    population.push_back(new Brownie("Arec"));
    population.push_back(new Brownie("Bera"));
    population.push_back(new Brownie("Ceil"));
    //population.push_back(new Brownie("Dama"));
    //population.push_back(new Brownie("Ewok"));

}

World::~World()
{
    // delete population
    for(std::vector<Brownie*>::iterator it = population.begin(); it != population.end();)
    {
        delete *it;
        population.erase(it);
    }
}

void World::Progress(int hours)
{

    for(int i = 0; i < hours; i++)
    {
        hour++;
        if(hour > 24)
        {
            hour = 1;
            date ++;

            if(date > 28)
            {
                date = 1;
                month++;

                if(month > 12)
                {
                    month = 1;
                }
            }

            UpdateDayOfYear();
        }

        UpdateDayOfYear();

        CalculateTemperature();

        std::cout << "=== Hour " << hour <<  " of Day " << date << " of Month " << month << " || Day " << dayOfYear << " of the current year." << std::endl;
        std::cout << "=== Air temperature: " << temperature << "C." << std::endl;

        for(std::vector<Brownie*>::iterator it = population.begin(); it != population.end(); ++it)
        {
            (*it)->SetTemperature(temperature);
            (*it)->Progress();

        }

        std::cout << "=======" << std::endl;
    }

}

void World::CalculateTemperature()
{
    float dateMod, hourMod;
    float dateRads, hourRads;

    dateRads = dayOfYear/336 * 2*PI;
    hourRads = hour/24 * 2*PI;

    dateMod =  -20*  cos(dateRads);
    hourMod =  - 7*  cos(hourRads);

    temperature = 10 + dateMod + hourMod;
    //temperature = hourMod; // debug

}

void World::UpdateDayOfYear()
{
    dayOfYear = (month-1)*28 + date;
}
