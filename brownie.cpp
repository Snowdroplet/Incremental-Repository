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

    // Passive loss, before accounting for activity

    effectiveTemperature = baseTemperature; // (Account for clothing later)
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

    ProgressBiography();
    ProgressPhysicalCondition();
    ProgressPsychologicalCondition();

    DecideAction();

    if(decidedAction == ACTION_IDLE)
    {

    }
    else if(decidedAction == ACTION_SUPPLY)
    {

    }

    std::cout << name << ":" << std::endl;
    std::cout << "Condition: " << condition << "% || Temp: " << effectiveTemperature << "C || Hydrated: " << hydration << "% || Energy: " << energy << "% || Nutrition: " << nutrition << "%" << std::endl;
    std::cout << "Sanity: " << sanity << "% || Calm: " << calm << "% || Restful: " << restfulness << "% || Content: " << contentment << "% || Purpose: " << purpose << "%" << std::endl;

}


void Brownie::SetBaseTemperature(float t)
{
    baseTemperature = t;
}

void Brownie::Forecast()
{

}

void Brownie::Schedule()
{

}

void Brownie::EvaluatePhysicalNeeds()
{

    /// Temperature
    // If temperature is different than favoured temperature, increase pressure to regulate temperature proportional to difference.
    if(effectiveTemperature < favouredTemperature)
    {
        actionPotential[ACTION_COOL] = 0;
        actionPotential[ACTION_WARM] += 0.5*std::abs(effectiveTemperature-favouredTemperature);

        if(effectiveTemperature < coldComfort)
        {
            actionPotential[ACTION_WARM] += 2*std::abs(effectiveTemperature-favouredTemperature);

            if(effectiveTemperature < coldTolerance)
            {
                actionPotential[ACTION_WARM] += 5*std::abs(effectiveTemperature-favouredTemperature);
            }
        }
    }
    if(effectiveTemperature > favouredTemperature)
    {
        actionPotential[ACTION_WARM] = 0;
        actionPotential[ACTION_COOL] += 0.5*std::abs(effectiveTemperature-favouredTemperature);

        if(effectiveTemperature > heatComfort)
        {
            actionPotential[ACTION_COOL] += 5*std::abs(effectiveTemperature-favouredTemperature);

            if(effectiveTemperature > heatTolerance)
            {
                actionPotential[ACTION_COOL] += 20*std::abs(effectiveTemperature-favouredTemperature);
            }

        }
    }

}

void Brownie::EvaluateSecurityNeeds()
{

}

void Brownie::EvaluatePsychologicalNeeds()
{

}

void Brownie::EvaluateActualizationNeeds()
{

}

void Brownie::DecideAction()
{
    /// Physiological urgency

}

