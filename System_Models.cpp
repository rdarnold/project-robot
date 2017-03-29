
#include "ProjectRobot.h"
#include "System_Models.h"
#include "TextDefines.h"

RobotParameters theCorrectRobot; // What you actually want it to be like, the 'right' system

extern Stakeholder stakeholder[NUM_STAKEHOLDERS];

// The max model options for each sub-system, basically
// just used for boundary checking
int MAX_SYSTEM_MODEL[] =
{
  NUM_FRAMES-1, // SYSTEM_FRAME
  NUM_HEADS-1, // SYSTEM_HEAD
  NUM_TORSOS-1, // SYSTEM_TORSO
  NUM_ARMS-1, // SYSTEM_ARM_RIGHT
  NUM_ARMS-1, // SYSTEM_ARM_LEFT
  NUM_LEGS-1, // SYSTEM_LEG_RIGHT
  NUM_LEGS-1, // SYSTEM_LEG_LEFT
  NUM_EJECTIONS-1, // SYSTEM_EJECTION
  NUM_COOLINGS-1, // SYSTEM_COOLING
  NUM_COMPUTERS-1, // SYSTEM_COMPUTER
  NUM_HUMAN_INTS-1  // SYSTEM_HUMAN_INTERFACE
};


char *system_names[] =
{
  "Frame",
  "Head",
  "Torso",
  "Right Arm",
  "Left Arm",
  "Right Leg",
  "Left Leg",
  "Ejection System",
  "Cooling System",
  "Computer System",
  "Pilot Interface",
  ""
};

// The text for the development time measures
char *dev_times[] = 
{
 "None",
 "Three Months",
 "Six Months",
 "Nine Months",
 "One Year",
 ""
};

// Coincides with the NUM_INTERFACES enum
char *interfaces[] =
{
  "Frame",
  "Head",
  "Torso",
  "Right Arm",
  "Left Arm",
  "Right Leg",
  "Left Leg",
  "Ejection System",
  "Cooling System",
  "Computer System",
  "Human Interface",
  "Software",
  ""
};

// Coincides with INTERFACE_LEVELS define
char *interface_levels[] =
{
  //"Unknown",
  "Not confident",
  "Neutral",
  "Somewhat Confident",
  "Confident",
  "Highly confident",
  ""
};

char *armor_value_text[] =
{
  "Cost",
  "Weight",   // ARMOR_VALUE_WEIGHT,
  "Heat Resist",   // ARMOR_VALUE_HEAT,
  "Explosive Resist",   // ARMOR_VALUE_EXPLOSIVE,
  "Acid Resist",   // ARMOR_VALUE_ACID,
  "Water Resist",   // ARMOR_VALUE_WATER,
  "Impact Resist",   // ARMOR_VALUE_IMPACT,
  "Sonic Resist",   // ARMOR_VALUE_SONIC,
  "EMP Resist",   // ARMOR_VALUE_EMP,
  "Maneuverability",   // ARMOR_VALUE_MANEUVER,
  "Radiation Resist",   // ARMOR_VALUE_RADIATION,
  "Stealth",   // ARMOR_VALUE_STEALTH,
  ""
};

char *armor_value_full_text[] =
{
  "Cost",
  "Average Armor Weight",   
  "Average Heat Resistance", 
  "Average Explosive Resistance",   
  "Average Acid Resistance",  
  "Average Water Resistance",   
  "Average Impact Resistance",  
  "Average Sonic Resistance",   
  "Average Electromagnetic Pulse Resistance",   
  "Average Armor Maneuverability",  
  "Average Radiation Resistance",   
  "Average Stealth",   
  ""
};


char *gun_value_text[] =
{
  "Cost",
  "Weight",
  "Heat Atk",
  "Explosive",
  "Impact",
  "Sonic",
  "Energy",
  "EMP",
  "Radiation",
  "Range",
  "Fire Rate",
  "Power Need",
  "Cooling Need",
  "Environmental",
  ""
};

char *gun_value_full_text[] =
{
  "Cost",
  "Long Range Weight",
  "Long Range Heat Attack",
  "Long Range Explosive Attack",
  "Long Range Impact Attack",
  "Long Range Sonic Attack",
  "Long Range Energy Attack",
  "Long Range EMP Attack",
  "Long Range Radiation Attack",
  "Firing Range",
  "Long Range Fire Rate",
  "Power Need",
  "Cooling Need",
  "Environmental Impact",
  ""
};

char *melee_value_text[] =
{
  "Cost",
  "Weight",   
  "Impact",    
  "Pierce",  
  "Cut",  
  "Energy",  
  "Speed", 
  "Power Need",
  "Cooling Need",
  ""
};

char *melee_value_full_text[] =
{
  "Cost",
  "Close Range Weight",   
  "Close Range Impact Attack",    
  "Close Range Pierce Attack",  
  "Close Range Cut Attack",  
  "Close Range Energy Attack",  
  "Close Range Attack Speed",
  "Power Need", 
  "Cooling Need",
  ""
};

char *accessory_value_text[] =
{
  "Cost",
  "Weight",   
  "Sight",    
  "Audio",  
  "Infrared",  
  "Radar",  
  "Heat Sense", 
  "Motion Sense", 
  "Power Need",
  "Cooling Need",
  ""
};

char *accessory_value_full_text[] =
{
  "Cost",
  "Overall Equipment Weight",   
  "Overall Sight Sensing",    
  "Overall Audio Sensing",  
  "Overall Infrared Sensing",  
  "Overall Radar Capability",  
  "Overall Heat Sensing",
  "Overall Motion Sensing",
  "Power Need",
  "Cooling Need",
  ""
};


char *spec_value_text[] =
{
  "Weight",   
  "Speed",    
  "Maneuver",  
  "Max Carry", 
  ""
};

char *spec_value_full_text[] =
{
  "Total Weight",   
  "Total Speed Rating",    
  "Total Maneuver Rating",  
  "Max Carrying Capacity", 
  ""
};

//Cost   Wgt   Name           Desc
struct FrameType Frames[] = {
  { 0,    0,  "None",         0}, // None
  
  {10,   20,  "Basic Frame",  BasicFrameText},  // Basic
  {12,   15,  "Battle Frame", BattleFrameText}, // Battle
  {8,    25,  "Gun Frame",    GunFrameText},    // Gun
  {16,   40,  "Heavy Frame",  HeavyFrameText},  // Heavy
  {20,   50,  "Tank Frame",   TankFrameText},   // Tank
  
  {0,   0,  0}  // End
};
  
//Cost  Wgt  Eq  MaxPwr  Dev            Name           
struct HeadType Heads[] = {
  {0,   0,   0,  0,      0,             "None"}, 
  
  {8,   5,   2,  40,     THREE_MONTHS,  "Sentinel Head"},  // Good armor
  {2,   7,   1,  40,     THREE_MONTHS,  "Block Head"},     // Cheap
  {5,   5,   1,  50,     THREE_MONTHS,  "Spotter Head"},   // Great sensors
  {9,   5,   2,  60,     THREE_MONTHS,  "Crown Head"},     // Can equip heavy weapons
  {10,  5,   3,  90,     SIX_MONTHS,    "Commander Head"}, // Expensive but good
  
  {0,   0,  0}  // End
};


//Cost  Wgt  Eq  Storage Dev           Name           
struct TorsoType Torsos[] = {
  {0,   0,   0,  0,      0,            "None"}, 
  
  {7,   10,  3,  4,      THREE_MONTHS, "Knight Torso"},  
  {2,   12,  2,  10,     THREE_MONTHS, "Box Torso"},  
//  {10,  8,   1,  5,      THREE_MONTHS, "Marine Torso"},    
  //{6,   10,  3,  5,      THREE_MONTHS, "Warrior Torso"}, 
  {5,   8,   5,  8,      THREE_MONTHS, "Worker Torso"},  
  {9,   22,  4,  5,      SIX_MONTHS,   "Centurion Torso"},   
  
  {0,   0,  0}  // End
};

//Cost Wgt   MaxWgt Eq     Dev       Spd   Man  Jmp
struct LegType Legs[] = {
  {0,   0,    0,    0,  0,            0,    0,   0,  "None"}, // None
  
  {8,   10,   130,  3,  SIX_MONTHS,   2,    3,   0,  "Stalker Leg"},  // Stalker, good for heavy frames
  {5,   6,    100,  2,  SIX_MONTHS,   5,    5,   2,  "Strider Leg"},  // Strider, a stable mainstay
  {15,  8,    100,  2,  SIX_MONTHS,   8,    10,  6,  "Olympian Leg"}, // Olympian, expensive but really good
  {8,   2,    40,   3,  ONE_YEAR,     6,    8,   10, "Leapfrog Leg"}, // Leapfrog, great jump but bad defense
  {6,   4,    70,   2,  SIX_MONTHS,   8,    6,   6,  "Hopper Leg"},   // Hopper, good maneuver/jump
  {5,   5,    80,   2,  SIX_MONTHS,   10,   5,   3,  "Dasher Leg"},   // Dasher, fastest 
  {2,   3,    50,   2,  THREE_MONTHS, 4,    4,   1,  "Walker Leg"},   // Walker, cheapest
  {4,   5,    150,  0,  THREE_MONTHS, 7,    1,   0,  "Track"},    // Track, for tank frame
  
  {0,   0,  0, 0, 0, 0, 0, 0}  // End
};

  
//Cost Wgt  MaxWgt Eq     Dev       
struct ArmType Arms[] = {
  {0,   0,    0,   0,  0,            "None"}, // None
  
  {4,   10,   10,  3,  SIX_MONTHS,   "Hercules Arm"},  // High carry weight
  {5,   7,    4,   4,  SIX_MONTHS,   "Samurai Arm"},  // High armor
  {4,   3,    6,   4,  THREE_MONTHS, "Gripper Arm"},  // Can use all weapons
  {8,   14,   8,   6,  NINE_MONTHS,  "Pioneer Arm"}, // Lots of eq slots
  {6,   8,    5,   3,  SIX_MONTHS,   "Thunder Arm"},   // Built-in sonic and EMP attacks and defense
  {4,   2,    2,   5,  SIX_MONTHS,   "Assassin Arm"},   // Quick, high cost eff with knives and small guns  
  
  {0,   0,  0, 0, 0, 0 }  // End
};

//Cost Wgt  Dev       
struct EjectionType Ejections[] = {
  {0,   0,   0,             "None"}, // None
  
  {3,   1,   ONE_YEAR,      "Safety One"},  
  {3,   1,   NINE_MONTHS,   "Standard Jet"},  
  {5,   2,   ONE_YEAR,      "Cockpit Ejector"}, 
  {1,   1,   SIX_MONTHS,    "Seat Ejector"}, 
  
  {0,   0,  0 }  // End
};

//Cost Wgt  HeatReduce   HeatSinkCost HeatSinkReduce  HeatSinkWgt HeatSinkPwrCost Dev       
struct CoolingType Coolings[] = {
  {0,   0,     0,        0,           0,              0,          0,             0,             "None"}, // None
  
  {6,   1,     6,        2,           8,              2,          3,             THREE_MONTHS,  "Cryo Cooling System"},  
  {10,  2,     10,       2,           8,              2,          4,             SIX_MONTHS,    "Superfreeze Cooling System"},  
  {4,   1,     4,        1,           4,              1,          2,             THREE_MONTHS,  "Zero Degree Cooling System"}, 
  {5,   1,     4,        1,           6,              1,          1,             THREE_MONTHS,  "Arctic Cooling System"}, 
  
  {0,   0,  0 }  // End
};

int GetCoolingSystemValue(int nCoolingSystemModel, int nCoolValueDefine)
{
  switch (nCoolValueDefine)
  {
    case COOL_VALUE_COST:                 return Coolings[nCoolingSystemModel].nCost;
    case COOL_VALUE_WEIGHT:               return Coolings[nCoolingSystemModel].nWeight;
    case COOL_VALUE_HEAT_REDUCE:          return Coolings[nCoolingSystemModel].nHeatReduce;
    case COOL_VALUE_HEAT_SINK_COST:       return Coolings[nCoolingSystemModel].nHeatSinkCost;
    case COOL_VALUE_HEAT_SINK_REDUCE:     return Coolings[nCoolingSystemModel].nHeatSinkReduce;
    case COOL_VALUE_HEAT_SINK_WEIGHT:     return Coolings[nCoolingSystemModel].nHeatSinkWgt;
    case COOL_VALUE_HEAT_SINK_POWER_COST: return Coolings[nCoolingSystemModel].nHeatSinkPwrCost;
  }

  return 0;
};

// Value is actually a multiplier for the value found in the Accessories array, so if the value for radar is 2.0,
// that means it actually has a radar value of 20, or (10 * 2.0).  This is necessary because of the omni sensor.

//Cost Wgt   Pwr   Camera         Audio          Infrared       Heat            Movement       Radar          Omni             Dev       
struct ComputerType Computers[] = {
  {0,   0,   0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,     0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,      0,             "None"}, // None
  
               //Cost,Wgt,Val,Pwr

  {8,   1,   5,    3, 1, 1.0, 2,  3, 1, 1.0, 2,  4, 1, 1.2, 3,  4, 1, 1.2, 3,   3, 1, 1.0, 2,  4, 1, 1.2, 3,  10, 4, 1.0, 4,   NINE_MONTHS,   "SuperNerd Computer System"},  
  {10,  1,   8,    5, 2, 1.2, 3,  5, 2, 1.2, 3,  5, 2, 1.2, 3,  5, 2, 1.2, 3,   5, 2, 1.2, 3,  5, 2, 1.2, 4,  12, 4, 1.4, 6,   ONE_YEAR,      "Zephyr Computer System"},  
  {8,   1,   5,    4, 1, 1.2, 3,  4, 1, 1.2, 3,  3, 2, 1.0, 2,  3, 2, 1.0, 2,   4, 1, 1.2, 3,  3, 2, 1.0, 3,  10, 4, 1.0, 4,   NINE_MONTHS,   "NanoBrain Computer System"}, 
  {4,   1,   4,    1, 2, 1.0, 4,  1, 2, 1.0, 4,  1, 2, 1.0, 4,  1, 2, 1.0, 4,   1, 2, 1.0, 4,  1, 2, 1.0, 5,  8,  3, 1.0, 7,   SIX_MONTHS,    "Maverick Computer System"}, 
  
  {0,   0,  0 }  // End
};

int GetComputerSystemIntValue(int nSystemModel, int nCompValueDefine)
{
  struct ComputerType *pComp = &Computers[nSystemModel];
  switch (nCompValueDefine)
  {
    case COMP_VALUE_COST:                 return pComp->nCost;
    case COMP_VALUE_WEIGHT:               return pComp->nWeight;
    case COMP_VALUE_POWER_COST:           return pComp->nPowerCost;
    case COMP_VALUE_CAMERA_COST:          return pComp->nCameraCost;
    case COMP_VALUE_CAMERA_WEIGHT:        return pComp->nCameraWeight;
    case COMP_VALUE_CAMERA_POWER_COST:    return pComp->nCameraPowerCost;
    case COMP_VALUE_AUDIO_COST:           return pComp->nAudioCost;
    case COMP_VALUE_AUDIO_WEIGHT:         return pComp->nAudioWeight;
    case COMP_VALUE_AUDIO_POWER_COST:     return pComp->nAudioPowerCost;
    case COMP_VALUE_INFRARED_COST:        return pComp->nInfraredCost;
    case COMP_VALUE_INFRARED_WEIGHT:      return pComp->nInfraredWeight;
    case COMP_VALUE_INFRARED_POWER_COST:  return pComp->nInfraredPowerCost;
    case COMP_VALUE_HEAT_COST:            return pComp->nHeatCost;
    case COMP_VALUE_HEAT_WEIGHT:          return pComp->nHeatWeight;
    case COMP_VALUE_HEAT_POWER_COST:      return pComp->nHeatPowerCost;
    case COMP_VALUE_MOVEMENT_COST:        return pComp->nMovementCost;
    case COMP_VALUE_MOVEMENT_WEIGHT:      return pComp->nMovementWeight;
    case COMP_VALUE_MOVEMENT_POWER_COST:  return pComp->nMovementPowerCost;
    case COMP_VALUE_RADAR_COST:           return pComp->nRadarCost;
    case COMP_VALUE_RADAR_WEIGHT:         return pComp->nRadarWeight;
    case COMP_VALUE_RADAR_POWER_COST:     return pComp->nRadarPowerCost;
    case COMP_VALUE_OMNI_COST:            return pComp->nOmniCost;
    case COMP_VALUE_OMNI_WEIGHT:          return pComp->nOmniWeight;
    case COMP_VALUE_OMNI_POWER_COST:      return pComp->nOmniPowerCost;
  }

  return 0;
};

double GetComputerSystemDoubleValue(int nSystemModel, int nCompValueDefine)
{
  struct ComputerType *pComp = &Computers[nSystemModel];
  switch (nCompValueDefine)
  {
    case COMP_VALUE_CAMERA_VALUE:         return pComp->fCameraValue;
    case COMP_VALUE_AUDIO_VALUE:          return pComp->fAudioValue;
    case COMP_VALUE_INFRARED_VALUE:       return pComp->fInfraredValue;
    case COMP_VALUE_HEAT_VALUE:           return pComp->fHeatValue;
    case COMP_VALUE_MOVEMENT_VALUE:       return pComp->fMovementValue;
    case COMP_VALUE_RADAR_VALUE:          return pComp->fRadarValue;
    case COMP_VALUE_OMNI_VALUE:           return pComp->fOmniValue;
  }

  return 0;
};


//Cost Wgt  Dev       
struct HumanInterfaceType HumanInterfaces[] = {
  {0,   0,   0,             "None"}, // None
  
  {12,  1,   NINE_MONTHS,   "Flight Interface"},  
  {5,   1,   THREE_MONTHS,  "Driving Interface"},  
  {8,   1,   SIX_MONTHS,    "Video Game Interface"}, 
  {10,  1,   ONE_YEAR,      "Hybrid Interface"}, 
  
  {0,   0,  0 }  // End
};

//Cost  Dev          Wgt Heat Exp Acid  Water  Imp  Son   EMP   Man   Rad   Stealth   Name       
struct ArmorType ArmorTypes[] = {
  { 0, 0,            0,   0,  0,  0,    0,     0,   0,    0,    0,    0,    0,        "None"}, // None
  
  { 3, SIX_MONTHS,   8,   8,  7,  5,    6,     7,   2,    1,    2,    1,    6,        "Tank Armor"},  
  { 3, SIX_MONTHS,   2,   2,  4,  3,    7,     5,   6,    3,    8,    8,    8,        "Light Armor"},  
  { 3, NINE_MONTHS,  5,   5,  5,  5,    5,     5,   8,   10,    10,   5,    10,       "Flex Armor"},  
  { 3, SIX_MONTHS,   10,  6,  8,  8,    2,     8,   5,    4,    2,    10,   2,        "Heavy Armor"},  
  { 3, NINE_MONTHS,  6,   4,  10, 2,    2,    10,   10,   7,    5,    4,    5,        "Flak Armor"},  
  { 3, ONE_YEAR,     4,   10, 0,  10,   10,    0,   4,    7,    6,    10,   3,        "Elemental Armor"},  
  
  { 0 }  // End
};

int GetDefaultArmorValue(int nArmorType, int nArmorValueDefine)
{
  switch (nArmorValueDefine)
  {
    case ARMOR_VALUE_COST:      return ArmorTypes[nArmorType].nCost;
    case ARMOR_VALUE_WEIGHT:    return ArmorTypes[nArmorType].nWeight;
    case ARMOR_VALUE_HEAT:      return ArmorTypes[nArmorType].nHeat;
    case ARMOR_VALUE_EXPLOSIVE: return ArmorTypes[nArmorType].nExplosive;
    case ARMOR_VALUE_ACID:      return ArmorTypes[nArmorType].nAcid;
    case ARMOR_VALUE_WATER:     return ArmorTypes[nArmorType].nWater;
    case ARMOR_VALUE_IMPACT:    return ArmorTypes[nArmorType].nImpact;
    case ARMOR_VALUE_SONIC:     return ArmorTypes[nArmorType].nSonic;
    case ARMOR_VALUE_EMP:       return ArmorTypes[nArmorType].nEMP;
    case ARMOR_VALUE_MANEUVER:  return ArmorTypes[nArmorType].nManeuver;
    case ARMOR_VALUE_RADIATION: return ArmorTypes[nArmorType].nRadiation;
    case ARMOR_VALUE_STEALTH:   return ArmorTypes[nArmorType].nStealth;
  }

  return 0;
}

//Cost  Dev          Wgt Heat Expl Imp  Son   En    EMP   Rad   Range RoF   PwrCost, HtCost, Env, Name       
struct GunType GunTypes[] = {
  { 0,  0,           0,   0,  0,   0,   0,    0,    0,    0,    0,    0,    0,       0,      0,   "None"}, // None
  
  { 5,  0,           5,   0,  0,   10,  0,    0,    0,    0,    8,    5,    2,       2,      1,   "Panzer XII"},       // Impact
  { 5,  0,           8,   0,  0,   10,  0,    0,    0,    0,    4,    10,   2,       1,      3,   "Metal Rain"},       // Impact
  { 5,  0,           8,   0,  0,   0,   0,    10,   0,    10,   5,    1,    2,       2,      8,   "Dragon Cannon"},    // Energy/Rad
  { 5,  0,           4,   0,  0,   0,   10,   0,    0,    0,    5,    4,    2,       1,      0,   "Sonic Rifle"},      // Sonic
  { 5,  0,           1,   0,  0,   0,   8,    0,    0,    0,    2,    7,    2,       2,      1,   "Screamer"},         // Sonic
  { 5,  0,           4,   0,  0,   0,   0,    10,   0,    0,    5,    5,    6,       4,      0,   "Energy Rifle"},     // Energy
  { 4,  0,           2,   0,  0,   0,   0,    8,    0,    0,    1,    8,    4,       4,      0,   "Energy Blaster"},   // Energy
  { 5,  0,           6,   10, 0,   0,   0,    0,    0,    0,    7,    2,    5,       5,      2,   "Plasma Cannon"},    // Heat
  { 5,  0,           3,   10, 0,   0,   0,    0,    0,    0,    1,    6,    2,      10,      0,   "Firestorm"},        // Heat
  { 4,  0,           10,  0,  10,  0,   0,    0,    0,    0,    6,    8,    2,       8,      6,   "Missile Pack"},     // Expl
  { 6,  0,           8,   0,  10,  0,   0,    0,    0,    0,    10,   3,    2,       6,      5,   "Heavy Artillery"},  // Expl
  { 5,  0,           5,   0,  5,   0,   0,    0,    0,    0,    8,    6,    2,       4,      2,   "Light Artillery"},  // Expl
  { 5,  0,           3,   0,  0,   0,   0,    0,    10,   0,    8,    6,    6,       8,      3,   "EMP Missile"},      // EMP
  { 3,  0,           1,   0,  0,   0,   0,    0,    6,    0,    5,    4,    3,       2,      0,   "EMP Grenade"},      // EMP, cheap
  
  { 0 }  // End
};

int GetDefaultGunValue(int nGunType, int nGunValueDefine)
{
  switch (nGunValueDefine)
  {
    case GUN_VALUE_COST:          return GunTypes[nGunType].nCost;
    case GUN_VALUE_WEIGHT:        return GunTypes[nGunType].nWeight;
    case GUN_VALUE_HEAT:          return GunTypes[nGunType].nHeat;
    case GUN_VALUE_EXPLOSIVE:     return GunTypes[nGunType].nExplosive;
    case GUN_VALUE_IMPACT:        return GunTypes[nGunType].nImpact;
    case GUN_VALUE_SONIC:         return GunTypes[nGunType].nSonic;
    case GUN_VALUE_ENERGY:        return GunTypes[nGunType].nEnergy;
    case GUN_VALUE_EMP:           return GunTypes[nGunType].nEMP;
    case GUN_VALUE_RADIATION:     return GunTypes[nGunType].nRadiation;
    case GUN_VALUE_RANGE:         return GunTypes[nGunType].nRange;
    case GUN_VALUE_RATE_OF_FIRE:  return GunTypes[nGunType].nRateOfFire;
    case GUN_VALUE_POWER_COST:    return GunTypes[nGunType].nPwrCost;
    case GUN_VALUE_HEAT_COST:     return GunTypes[nGunType].nHeatCost;
    case GUN_VALUE_ENV:           return GunTypes[nGunType].nEnvImpact;
  }

  return 0;
}

//Cost  Dev          Wgt Imp Prc  Cut  En    Spd    PwrCost, HtCost, Name       
struct MeleeType MeleeTypes[] = {
  { 0,  0,           0,   0,  0,   0,   0,    0,    0,       0,      "None"}, // None
  
  { 1,  0,           4,   6,  0,   0,   0,    5,    0,       0,      "Steel Bar"},       
  { 3,  0,           2,   0,  5,   5,   0,    8,    0,       0,      "Battle Knife"},      
  { 3,  0,           2,   0,  2,   7,   0,   10,    1,       0,      "Saw Knife"},    
  { 3,  0,           2,   0,  0,   0,   7,    8,    3,       3,      "Energy Knife"},     
  { 4,  0,           2,   0,  0,   10,  0,    5,    0,       0,      "Nano Cutter"},        
  { 4,  0,           3,   0,  0,   0,   10,   5,    4,       3,      "Energy Blade"},     
  { 5,  0,           8,   10, 0,   0,   0,    4,    4,       2,      "Rocket Hammer"},  
  { 3,  0,           10,  0,  10,  0,   0,    3,    5,       3,      "Destroyer Drill"},    
  
  { 0 }  // End
};

int GetDefaultMeleeValue(int nMeleeType, int nMeleeValueDefine)
{
  switch (nMeleeValueDefine)
  {
    case MELEE_VALUE_COST:        return MeleeTypes[nMeleeType].nCost;
    case MELEE_VALUE_WEIGHT:      return MeleeTypes[nMeleeType].nWeight;
    case MELEE_VALUE_IMPACT:      return MeleeTypes[nMeleeType].nImpact;
    case MELEE_VALUE_PIERCE:      return MeleeTypes[nMeleeType].nPierce;
    case MELEE_VALUE_CUT:         return MeleeTypes[nMeleeType].nCut;
    case MELEE_VALUE_ENERGY:      return MeleeTypes[nMeleeType].nEnergy;
    case MELEE_VALUE_SPEED:       return MeleeTypes[nMeleeType].nSpeed;
    case MELEE_VALUE_POWER_COST:  return MeleeTypes[nMeleeType].nPwrCost;
    case MELEE_VALUE_HEAT_COST:   return MeleeTypes[nMeleeType].nHeatCost;
  }

  return 0;
}

//Cost  Dev          Wgt Sgt Aud  Inf  Rad    Heat  Mtn PwrCost, HtCost, Name       
struct AccType AccTypes[] = {
  { 0,  0,           0,   0,  0,   0,   0,    0,    0,  0,       0,      "None"}, // None
  
  { 3,  0,           1,   10, 0,   0,   0,    0,    0,  2,       2,      "Camera"},       
  { 3,  0,           1,   0,  10,  0,   0,    0,    0,  2,       2,      "Audio Sensor"},      
  { 3,  0,           1,   0,  0,   10,  0,    0,    0,  2,       2,      "Infrared Sensor"},    
  { 3,  0,           1,   0,  0,   0,   0,    10,   0,  2,       2,      "Heat Sensor"},     
  { 3,  0,           1,   0,  0,   0,   0,    0,    10, 2,       2,      "Motion Sensor"},        
  { 3,  0,           3,   0,  0,   0,   10,   0,    0,  3,       1,      "Radar"},      
  { 10, 0,           4,   2,  2,   2,   2,    2,    2,  4,       3,      "Omni Sensor"}, 
  { 5,  0,           0,   0,  0,   0,   0,    0,    0,  5,       5,      "SER Defender"},
  { 5,  0,           0,   0,  0,   0,   0,    0,    0,  5,       2,      "Magnetic Deflector"},
  { 2,  0,           0,   0,  0,   0,   0,    0,    0,  0,       0,      "Heat Sink"}, 
  { 0,  0,           0,   0,  0,   0,   0,    0,    0,  0,       0,      "Ranged Weapon"},
  { 0,  0,           0,   0,  0,   0,   0,    0,    0,  0,       0,      "Close Combat Weapon"}, 
  
  { 0 }  // End
};

int GetDefaultAccValue(int nAccType, int nAccValueDefine)
{
  switch (nAccValueDefine)
  {
    case ACC_VALUE_COST:          return AccTypes[nAccType].nCost;
    case ACC_VALUE_WEIGHT:        return AccTypes[nAccType].nWeight;
    case ACC_VALUE_SIGHT:         return AccTypes[nAccType].nSight;
    case ACC_VALUE_AUDIO:         return AccTypes[nAccType].nAudio;
    case ACC_VALUE_INFRARED:      return AccTypes[nAccType].nInfrared;
    case ACC_VALUE_RADAR:         return AccTypes[nAccType].nRadar;
    case ACC_VALUE_HEAT_SENSOR:   return AccTypes[nAccType].nHeatSensor;
    case ACC_VALUE_MOTION_SENSOR: return AccTypes[nAccType].nMotionSensor;
    case ACC_VALUE_POWER_COST:    return AccTypes[nAccType].nPwrCost;
    case ACC_VALUE_HEAT_COST:     return AccTypes[nAccType].nHeatCost;
  }

  return 0;
}



// Take the gun/armor values and translate them to text
char *TranslateValueToText(int nValue)
{
  if (nValue == 0)
    return "---";
  if (nValue <= 2)
    return "Very Low";
  else if (nValue <= 4)
    return "Low";
  else if (nValue <= 6)
    return "Avg";
  else if (nValue <= 8)
    return "High";
  else if (nValue <= 12)
    return "Very High";
  else
    return "Superb";
}

// Take the gun/armor values and translate them to text
char *TranslateApprovalToText(int nValue)
{
  if (nValue <= 20)
    return "Very Low";
  else if (nValue <= 40)
    return "Low";
  else if (nValue <= 60)
    return "Avg";
  else if (nValue <= 80)
    return "High";
  else 
    return "Very High";
}

// If everything meets or exceeds the final solution, except
// for weight (where less is more) then the score is good
// You get like X points for each thing that meets or exceeds,
// then it quadruples or something if it's all correct
void SetupFinalSolution()
{
  // Set a pointer just to make it easier
  RobotParameters *theBot = &theCorrectRobot;    

  // For weight and carryweight, the preference is a RATING,
  // not an actual weight - the rating is then translated to
  // a weight later.  This allows us to handle all preferences
  // using the same mathematical formulae, treating the pref
  // as a rating.
  int i = 0;
  for (i = ARMOR_VALUE_PREF_START; i < ARMOR_VALUE_PREF_END; i++)
    theBot->nArmorValues[i] = number(0, MAX_DESIRED_PARAMETER);

  for (i = GUN_VALUE_PREF_START; i < GUN_VALUE_PREF_END; i++)
    theBot->nGunValues[i] = number(0, MAX_DESIRED_PARAMETER);

  for (i = MELEE_VALUE_PREF_START; i < MELEE_VALUE_PREF_END; i++)
    theBot->nMeleeValues[i] = number(0, MAX_DESIRED_PARAMETER);

  for (i = ACC_VALUE_PREF_START; i < ACC_VALUE_PREF_END; i++)
    theBot->nAccValues[i] = number(0, MAX_DESIRED_PARAMETER);

  for (i = SPEC_VALUE_PREF_START; i < SPEC_VALUE_PREF_END; i++)
    theBot->nSpecValues[i] = number(2, MAX_DESIRED_PARAMETER);
}