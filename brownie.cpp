#include "brownie.h"

Brownie::Brownie(std::string whatName)
{
    name = whatName;

    DefaultGenerationStats();

}

Brownie::~Brownie()
{

}

void Brownie::DefaultGenerationStats()
{
    ageHours = ageDays = ageYears = 0;

    condition = conditionMax = 100;

    favouredTemperature = 20;
    coldTolerance = 0;
    coldTolerance = 10;
    heatComfort = 30;
    heatTolerance = 40;

    energy = energyMax = 100;
    tiredThreshold = 40;
    veryTiredThreshold = 20;

    hydration = hydrationMax = 100;
    thirstyThreshold = 40;
    veryThirstyThreshold = 20;

    nutrition = 100;
    nutritionMax = 140;
    hungryThreshold = 40;
    veryHungryThreshold = 20;


    sanity = sanityMax = 100;
    calm = calmMax = 100;
    restfulness = restfulnessMax = 100;
    contentment = contentmentMax = 100;
    purpose = purposeMax = 100;

    decidedAction = ACTION_IDLE;
    decidedSubaction = SUBACTION_IDLE;

    foresight = foresightCD = 24;
    planning = planningCD = 24;

    for(int i = 0; i < NUM_ACTIONS; i++)
    {
        actionPotential[i] = 0;
    }
}

void Brownie::ProgressBiography()
{
    ageHours++;
    ageDays = ageHours%24;
    ageYears = ageDays%336; // 12m x 28d
}

void Brownie::ProgressPhysicalCondition()
{

    // Passive loss.
    hydration -= 5;
    energy    -= 6;
    nutrition -= 7;

    if(effectiveTemperature < coldTolerance)
        condition -= (effectiveTemperature*(-0.5));

    if(effectiveTemperature > heatTolerance)
        condition -= (effectiveTemperature*(0.5));


    if(hydration < 0)
    {
        hydration = 0;
        condition -= 3;
    }
    if(energy < 0)
    {
        energy = 0;
        condition -= 5;
    }
    if(nutrition < 0)
    {
        nutrition = 0;
        condition -= 1;
    }

}

void Brownie::ProgressPsychologicalCondition()
{
    foresight ++;
    if(foresight >= foresightCD)
    {
        Forecast();
        foresight = 0;
    }

    planning ++;
    if(planning >= planningCD)
    {
        Schedule();
        planning = 0;
    }

    if(effectiveTemperature < coldComfort)
    {
        calm -= 1;
    }
    if(effectiveTemperature < coldTolerance)
    {
        calm -= 4;
    }

    if(effectiveTemperature > heatComfort)
    {
        calm -= 1;
    }
    if(effectiveTemperature > heatTolerance)
    {
        calm -= 4;
    }


    // Passive loss, before accounting for activity
    calm -= 2;
    restfulness -= 5;
    contentment -= 2;
    purpose -= 1;

    if(calm < 0)
    {
        calm = 0;
        sanity -= 2;
    }

    if(restfulness < 0)
    {
        restfulness = 0;
        sanity -= 4;
    }

    if(contentment < 0)
    {
        contentment = 0;
        sanity -= 4;
    }
    if(purpose < 0)
    {
        purpose = 0;
        sanity -= 8;
    }
}

void Brownie::Progress()
{

    std::cout << "    " << name << ":" << std::endl;

    EvaluatePhysicalNeeds(1.0);
    EvaluateSecurityNeeds(1.0);
    EvaluatePsychologicalNeeds(1.0);
    EvaluateActualizationNeeds(1.0);

    DecideAction();

    std::cout << "Action: ";

    if(decidedAction == ACTION_IDLE)
    {
        decidedSubaction = SUBACTION_IDLE;
        std::cout << "Idle." << std::endl;
    }
    else if(decidedAction == ACTION_SUPPLY)
    {
        std::cout << "Supply." << std::endl;
    }
    else if(decidedAction == ACTION_WARM)
    {
        decidedSubaction = SUBACTION_DEBUG_WARMING;
        std::cout << "DEBUG warming." << std::endl;

        effectiveTemperature += 10;

    }
    else if(decidedAction == ACTION_COOL)
    {
        decidedSubaction = SUBACTION_DEBUG_COOLING;
        std::cout << "DEBUG cooling." << std::endl;

        effectiveTemperature -= 10;

    }

    ProgressBiography();
    ProgressPhysicalCondition();
    ProgressPsychologicalCondition();

    std::cout << "Condition: " << condition << "% || Temp: " << effectiveTemperature << "C / " << baseTemperature << "C || Hydrated: " << hydration << "% || Energy: " << energy << "% || Nutrition: " << nutrition << "%" << std::endl;
    std::cout << "Sanity: " << sanity << "% || Calm: " << calm << "% || Restful: " << restfulness << "% || Content: " << contentment << "% || Purpose: " << purpose << "%" << std::endl;
    std::cout << std::endl;


}


void Brownie::SetTemperature(float t)
{
    effectiveTemperature = baseTemperature = t;
}

void Brownie::Forecast()
{

}

void Brownie::Schedule()
{

}

void Brownie::EvaluatePhysicalNeeds(float physMod)
{

    /// Temperature
    // If temperature is different than favoured temperature, increase pressure to regulate temperature proportional to difference.
    if(effectiveTemperature < favouredTemperature)
    {
        actionPotential[ACTION_COOL] = 0;
        actionPotential[ACTION_WARM] += 0.5*std::fabs(effectiveTemperature-favouredTemperature);

        if(effectiveTemperature < coldComfort)
        {
            actionPotential[ACTION_WARM] += 2*std::fabs(effectiveTemperature-favouredTemperature);

            if(effectiveTemperature < coldTolerance)
            {
                actionPotential[ACTION_WARM] += 5*std::fabs(effectiveTemperature-favouredTemperature);
            }
        }
    }

    if(effectiveTemperature > favouredTemperature)
    {
        actionPotential[ACTION_WARM] = 0;
        actionPotential[ACTION_COOL] += 0.5*std::fabs(effectiveTemperature-favouredTemperature);

        if(effectiveTemperature > heatComfort)
        {
            actionPotential[ACTION_COOL] += 5*std::fabs(effectiveTemperature-favouredTemperature);

            if(effectiveTemperature > heatTolerance)
            {
                actionPotential[ACTION_COOL] += 5*std::fabs(effectiveTemperature-favouredTemperature);
            }

        }
    }

    /// Thirst

    /// Hunger



}

void Brownie::EvaluateSecurityNeeds(float secuMod)
{

}

void Brownie::EvaluatePsychologicalNeeds(float psycMod)
{

}

void Brownie::EvaluateActualizationNeeds(float actuMod)
{

}

void Brownie::DecideAction()
{
    float highestPotential = 0;

    for(int i = 0; i < NUM_ACTIONS; i++)
    {
        if(actionPotential[i] > highestPotential)
        {
            highestPotential = actionPotential[i];
            decidedAction = i;
        }
    }

    if(highestPotential == 0)
        decidedAction = ACTION_IDLE;
}

