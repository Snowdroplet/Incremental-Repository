#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>


#include "brownie.h"
#include "item.h"

#include "world.h"

World *world;

bool simulationExit = false;
bool awaitingUserInput = true;
std::string userInputString;

int main(int argc, char*argv[])
{

    world = new World();

    while(!simulationExit)
    {
        if(awaitingUserInput)
        {
            std::cin >> userInputString;

            // Convert input to all lowercase.
            std::transform(userInputString.begin(), userInputString.end(), userInputString.begin(),
                           [](unsigned char c)
            {
                return std::tolower(c);
            } );

            awaitingUserInput = false;
        }

        if(!awaitingUserInput)
        {
            if(userInputString == "exit")
            {
                simulationExit = true;
            }

            else if(userInputString == "h" || userInputString == "hour")
            {
                world->Progress(1);
            }
            else if(userInputString == "d" || userInputString == "day")
            {
                world->Progress(24);
            }
            else if(userInputString == "w" || userInputString == "week")
            {
                world->Progress(168);
            }
            else if(userInputString == "m" || userInputString == "month")
            {
                world->Progress(672); // 24h x 28d
            }
            else if(userInputString == "y" || userInputString == "year")
            {
                world->Progress(8064); // 24h x 28d x 12m
            }
            else
            {
                std::cout << "Input string " << userInputString << " is unrecognized." << std::endl;
            }

            awaitingUserInput = true;
        }

    }

    delete world;

    std::cin.get();

    return 0;
}
