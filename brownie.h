#ifndef BROWNIE_H_INCLUDED
#define BROWNIE_H_INCLUDED

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cmath>


#include "item.h"

enum enumActions
{
    ACTION_IDLE      =  0,     // Low-energy usage. Await planned activities. Lowest priority; tries to be overwritten if condition permits.

    ACTION_SUPPLY    =  1,   // Go to shelter to retrieve items necessary for planned activities.
    ACTION_WARM      =  2,   // Go to nearby shelter or fire or build one.
    ACTION_COOL      =  3,   // Go to nearby shelter.
    ACTION_EAT       =  4,   //
    ACTION_SLEEP     =  5,
    ACTION_TALK      =  6,
    ACTION_GATHER    =  7,
    ACTION_HUNT      =  8,
    ACTION_MAINTAIN  =  9,
    ACTION_CRAFT     = 10,

    NUM_ACTIONS      = 11
};

enum enumIdleSubactions /// Make sure to add explicit interger values later
{
    SUBACTION_MEDITATE,
    SUBACTION_SHELTER,
};

enum enumWarmSubactions
{
    SUBACTION_BUILD_FIRE,
    SUBACTION_SIT_FIRE,
};

enum enumTalkSubactions
{
    SUBACTION_TELL,
    SUBACTION_ASK,
    SUBACTION_ADMIRE,
    SUBACTION_INTIMIDATE,
    SUBACTION_BOAST,
    SUBACTION_STORY,
    SUBACTION_CONTRACT,
};

enum enumGatherSubactions
{
    SUBACTION_GATHER_BERRIES,
    SUBACTION_GATHER_WOOD,
    SUBACTION_GATHER_FEATHERS,
    SUBACTION_GATHER_STONE,
};

enum enumCraftSubactions
{
    SUBACTION_CRAFT_KNIFE,
    SUBACTION_CRAFT_HATCHET,
    SUBACTION_CRAFT_SPEAR,
    SUBACTION_CRAFT_BOW,
    SUBACTION_CRAFT_CLOTHES,
    SUBACTION_CRAFT_PACK
};

class Brownie
{
    /// Biography
    std::string name;

    int ageHours;
    int ageDays;
    int ageYears;

    /// Physical condition

    float condition, conditionMax;
    float baseTemperature, effectiveTemperature, favouredTemperature, coldComfort, coldTolerance, heatComfort, heatTolerance;
    float energy, energyMax, tiredThreshold, veryTiredThreshold;
    float hydration, hydrationMax, thirstyThreshold, veryThirstyThreshold;
    float nutrition, nutritionMax, hungryThreshold, veryHungryThreshold;


    /// Psychological condition
    float sanity, sanityMax;
    float calm, calmMax, stressedThreshold, veryStressedThreshold;
    float restfulness, restfulnessMax;
    float contentment, contentmentMax;
    float purpose, purposeMax;

    /// Schedule, planning, decision making
    int decidedAction;

    float actionPotential[NUM_ACTIONS]; // Pressure to perform certain actions.

    std::vector<int>schedule;

    float foresight, foresightCD; // Ability to forsee events.
    float planning, planningCD; // Ability to schedule around forseen events.


    int dailyGoalReevaluationPeriod;
    int shortTermGoalReevaluationPeriod;
    int weeklyGoalReevaluationPeriod;

    std::vector<std::pair<int, int>>aspirations;


    /// Personal
    std::vector<Item*>inventory;

    float moderationValue; // Value general moderation of all other values.
    float extremismValue; // Value general extremism in all other values.

    float simplicityValue; // Value simple, direct answers and outcomes.
    float complexityValue; // Value layered, nuanced answers and outcomes.

    float learningValue; // Value the learning process.
    float masteryValue; // Value

    float materialismValue; // Values having a comfortable excess of goods.
    float asceticismValue; // Values abstaining from material indulgence.

    float aggressionValue; //
    float pacificmValue; //

    float physicalSecurityValue; //
    float physicalCarefreeValue; //


    float psychologicalSecurityValue;
    float psychologicalCarefreeValue;

    /// Interrelational
    std::vector<Brownie*>parents;
    std::vector<Brownie*>children;
    std::vector<Brownie*>relatives;
    std::vector<Brownie*>friends;
    std::vector<Brownie*>associates; // all other acquaintainces.

    float agreementValue; // Value tendencies in others similar from own.
    float disagreementValue; // Value tendencies in others different from own.

    float cooperationValue; // Values cooperation with others. More impressed by collective achivement.
    float autonomyValue; // Values performing tasks alone. More impressed by individual achievement.

    float expressionValue;
    float reticenceValue;


    /// Material Preferences
    // How much psychological condition is modified by consuming goods

    /// ////////////////
    friend class World;

    void Progress();
    void ProgressBiography();
    void ProgressPhysicalCondition();
    void ProgressPsychologicalCondition();

    void Forecast();
    void Schedule();

    void EvaluatePhysicalNeeds();      // Condition
    void EvaluateSecurityNeeds();      // Planning ahead
    void EvaluatePsychologicalNeeds(); // Contentment
    void EvaluateActualizationNeeds(); // Purpose and mastery

    void DecideAction();

    void SetBaseTemperature(float t);

    void DefaultGenerationStats();

    Brownie(std::string whatName);
    ~Brownie();
};



#endif // BROWNIE_H_INCLUDED
