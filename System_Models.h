
/*

System models, classes, stakeholders, enums, etc.  A lot of the basic
game framework in terms of data structures resides here.

*/

#include <stdio.h>
#include <string.h>

#define MAX_MODELS    10
#define MAX_EQ_SLOTS  10

// Number of turns per time period
enum
{
  NO_MONTHS,     
  THREE_MONTHS,  
  SIX_MONTHS,    
  NINE_MONTHS,   
  ONE_YEAR      
};

// How good can your interfaces get
#define INTERFACE_LEVELS 5

#define SYSTEM_MODEL_NONE 0

#define MAX_NUM_MODELS 20

extern char *system_names[];
extern char *dev_times[];
extern char *interfaces[];
extern char *interface_levels[];
extern char *armor_value_text[];
extern char *armor_value_full_text[];
extern char *gun_value_text[];
extern char *gun_value_full_text[];
extern char *melee_value_text[];
extern char *melee_value_full_text[];
extern char *accessory_text[];
extern char *accessory_value_text[];
extern char *accessory_value_full_text[];
extern char *spec_value_text[];
extern char *spec_value_full_text[];

#define GET_SYSTEM_NAME_TEXT(x)       (system_names[(x)])
#define GET_DEV_TIME_TEXT(x)          (dev_times[(x)])
#define GET_INTERFACE_TEXT(x)         (interfaces[(x)])
#define GET_INTERFACE_LVL_TEXT(x)     (interface_levels[(x)])
#define GET_ARMOR_VALUE_TEXT(x)       (armor_value_text[(x)])
#define GET_ARMOR_VALUE_FULL_TEXT(x)  (armor_value_full_text[(x)])
#define GET_GUN_VALUE_TEXT(x)         (gun_value_text[(x)])
#define GET_GUN_VALUE_FULL_TEXT(x)    (gun_value_full_text[(x)])
#define GET_MELEE_VALUE_TEXT(x)       (melee_value_text[(x)])
#define GET_MELEE_VALUE_FULL_TEXT(x)  (melee_value_full_text[(x)])
#define GET_ACC_VALUE_TEXT(x)         (accessory_value_text[(x)])
#define GET_ACC_VALUE_FULL_TEXT(x)    (accessory_value_full_text[(x)])
#define GET_SPEC_VALUE_TEXT(x)         (spec_value_text[(x)])
#define GET_SPEC_VALUE_FULL_TEXT(x)    (spec_value_full_text[(x)])

#define GET_ARMOR_TYPE_TEXT(x)    (ArmorTypes[(x)].strName)
#define GET_GUN_TYPE_TEXT(x)      (GunTypes[(x)].strName)
#define GET_MELEE_TYPE_TEXT(x)    (MeleeTypes[(x)].strName)
#define GET_ACC_TYPE_TEXT(x)      (AccTypes[(x)].strName)

// What is the maximum that this parameter can be required to be
#define MAX_DESIRED_PARAMETER  15

// The types of subsystems that can be switched
enum
{
  SWITCH_TYPE_ARMOR,
  SWITCH_TYPE_ACCESSORY,
  SWITCH_TYPE_GUN,
  SWITCH_TYPE_MELEE,
  NUM_SWITCH_TYPES
};

// Frames
enum 
{
  FRAME_NONE,
  FRAME_BASIC,
  FRAME_BATTLE,
  FRAME_GUN,
  FRAME_HEAVY,
  FRAME_TANK,
  NUM_FRAMES
};

// Torsos
enum 
{
  TORSO_NONE,
  TORSO_KNIGHT,
  TORSO_BOX,
//  TORSO_MARINE,
//  TORSO_WARRIOR,
  TORSO_WORKER,
  TORSO_CENTURION,
  NUM_TORSOS
};

// Heads
enum
{
  HEAD_NONE,
  HEAD_SENTINEL,
  HEAD_BLOCK,
  HEAD_SPOTTER,
  HEAD_CROWN,
  HEAD_COMMANDER,
  NUM_HEADS
};

// Legs
enum
{
  LEG_NONE,
  LEG_STALKER,
  LEG_STRIDER,
  LEG_OLYMPIAN,
  LEG_LEAPFROG,
  LEG_HOPPER,
  LEG_DASHER,
  LEG_WALKER,
  LEG_TRACK,
  NUM_LEGS
};

// Arms
enum
{
  ARM_NONE,
  ARM_HERCULES, // High carry weight
  ARM_SAMURAI,  // High armor
  ARM_GRIPPER,  // Can use all weapons
  ARM_PIONEER,  // Lots of eq slots
  ARM_THUNDER,  // Built-in sonic and EMP attacks and defense
  ARM_ASSASSIN, // Quick, high cost eff with knives and small guns
  NUM_ARMS
};

// Ejection
enum
{ 
  EJECTION_NONE,
  EJECTION_SAFETY_ONE,
  EJECTION_STANDARD_JET,
  EJECTION_COCKPIT_EJECTOR,
  EJECTION_SEAT_EJECTOR,
  NUM_EJECTIONS
};

// Cooling
enum
{ 
  COOLING_NONE,
  COOLING_CRYO,
  COOLING_SUPERFREEZE,
  COOLING_ZERO,
  COOLING_ARCTIC,
  NUM_COOLINGS
};

// Computer
enum
{ 
  COMPUTER_NONE,
  COMPUTER_HURRICANE,
  COMPUTER_ZEPHYR,
  COMPUTER_NANOBRAIN,
  COMPUTER_MAVERICK,
  NUM_COMPUTERS
};

// Human interface
enum
{ 
  HUMAN_INT_NONE,
  HUMAN_INT_FLIGHT,
  HUMAN_INT_DRIVE,
  HUMAN_INT_VIDEO,
  HUMAN_INT_HYBRID,
  NUM_HUMAN_INTS
};

extern int MAX_SYSTEM_MODEL[];

struct FrameType
{
  int nCost;
  int nWeight;
  char strName[256];
  char *strDesc;
};
extern struct FrameType Frames[];

struct HeadType
{
  int nCost;
  int nWeight;
  int nEqSlots;
  int nMaxPower;
  int nDevTime; 
  char strName[256];
};
extern struct HeadType Heads[];

struct TorsoType
{
  int nCost;
  int nWeight;
  int nEqSlots;
  int nStorage;
  int nDevTime; 
  char strName[256];
};
extern struct TorsoType Torsos[];

struct LegType
{
  int nCost;
  int nWeight;
  int nMaxWeight;  
  int nEqSlots;
  int nDevTime; 
  int nSpeed;
  int nManeuver;
  int nJump;
  char strName[256];
};
extern struct LegType Legs[];

struct ArmType
{
  int nCost;
  int nWeight;
  int nCarryWeight;  
  int nEqSlots;
  int nDevTime; 
  char strName[256];
};
extern struct ArmType Arms[];

struct EjectionType
{
  int nCost;
  int nWeight;
  int nDevTime; 
  char strName[256];
};
extern struct EjectionType Ejections[];

struct CoolingType
{
  int nCost;
  int nWeight;
  int nHeatReduce;
  int nHeatSinkCost;
  int nHeatSinkReduce;
  int nHeatSinkWgt;
  int nHeatSinkPwrCost;
  int nDevTime; 
  char strName[256];
};
extern struct CoolingType Coolings[];

// The values/parameters of the cooling system
enum
{
  COOL_VALUE_COST,
  COOL_VALUE_WEIGHT,
  COOL_VALUE_HEAT_REDUCE,
  COOL_VALUE_HEAT_SINK_COST,
  COOL_VALUE_HEAT_SINK_REDUCE,
  COOL_VALUE_HEAT_SINK_WEIGHT,
  COOL_VALUE_HEAT_SINK_POWER_COST,
  NUM_COOL_VALUES
};

// Pass in the cooling system and the value define you want, and get the result
extern int GetCoolingSystemValue(int nCoolingSystemType, int nCoolValueDefine);

struct ComputerType
{
  int nCost;
  int nWeight;
  int nPowerCost;
  int nCameraCost;
  int nCameraWeight;
  double fCameraValue;
  int nCameraPowerCost;
  int nAudioCost;
  int nAudioWeight;
  double fAudioValue;
  int nAudioPowerCost;
  int nInfraredCost;
  int nInfraredWeight;
  double fInfraredValue;
  int nInfraredPowerCost;
  int nHeatCost;
  int nHeatWeight;
  double fHeatValue;
  int nHeatPowerCost;
  int nMovementCost;
  int nMovementWeight;
  double fMovementValue;
  int nMovementPowerCost;
  int nRadarCost;
  int nRadarWeight;
  double fRadarValue;
  int nRadarPowerCost;
  int nOmniCost;
  int nOmniWeight;
  double fOmniValue;
  int nOmniPowerCost;
  int nDevTime; 
  char strName[256];
};
extern struct ComputerType Computers[];

enum
{
  COMP_VALUE_COST,
  COMP_VALUE_WEIGHT,
  COMP_VALUE_POWER_COST,
  COMP_VALUE_CAMERA_COST,
  COMP_VALUE_CAMERA_WEIGHT,
  COMP_VALUE_CAMERA_VALUE,
  COMP_VALUE_CAMERA_POWER_COST,
  COMP_VALUE_AUDIO_COST,
  COMP_VALUE_AUDIO_WEIGHT,
  COMP_VALUE_AUDIO_VALUE,
  COMP_VALUE_AUDIO_POWER_COST,
  COMP_VALUE_INFRARED_COST,
  COMP_VALUE_INFRARED_WEIGHT,
  COMP_VALUE_INFRARED_VALUE,
  COMP_VALUE_INFRARED_POWER_COST,
  COMP_VALUE_HEAT_COST,
  COMP_VALUE_HEAT_WEIGHT,
  COMP_VALUE_HEAT_VALUE,
  COMP_VALUE_HEAT_POWER_COST,
  COMP_VALUE_MOVEMENT_COST,
  COMP_VALUE_MOVEMENT_WEIGHT,
  COMP_VALUE_MOVEMENT_VALUE,
  COMP_VALUE_MOVEMENT_POWER_COST,
  COMP_VALUE_RADAR_COST,
  COMP_VALUE_RADAR_WEIGHT,
  COMP_VALUE_RADAR_VALUE,
  COMP_VALUE_RADAR_POWER_COST,
  COMP_VALUE_OMNI_COST,
  COMP_VALUE_OMNI_WEIGHT,
  COMP_VALUE_OMNI_VALUE,
  COMP_VALUE_OMNI_POWER_COST,
  NUM_COMP_VALUES
};

extern int GetComputerSystemIntValue(int nSystemModel, int nCompValueDefine);
extern double GetComputerSystemDoubleValue(int nSystemModel, int nCompValueDefine);

extern int GetSensorPowerCost(int nSensorType, int nSystemModel);
extern int GetSensorHeatCost(int nSensorType, int nSystemModel);
extern int GetSensorCost(int nSensorType, int nSystemModel);
extern int GetSensorWeight(int nSensorType, int nSystemModel);

struct HumanInterfaceType
{
  int nCost;
  int nWeight;
  int nDevTime; 
  char strName[256];
};
extern struct HumanInterfaceType HumanInterfaces[];


// The types of armor
enum
{
  ARMOR_NONE,
  ARMOR_TANK,
  ARMOR_LIGHT,
  ARMOR_FLEX,
  ARMOR_HEAVY,
  ARMOR_FLAK,       // Good against impact, sonic, EMP
  ARMOR_ELEMENTAL,  // Good against heat, water
  NUM_ARMOR_TYPES
};

// The values/parameters that each armor has
enum
{
  ARMOR_VALUE_COST,
  ARMOR_VALUE_WEIGHT,
  ARMOR_VALUE_HEAT,
  ARMOR_VALUE_EXPLOSIVE,
  ARMOR_VALUE_ACID,
  ARMOR_VALUE_WATER,
  ARMOR_VALUE_IMPACT,
  ARMOR_VALUE_SONIC,
  ARMOR_VALUE_EMP,
  ARMOR_VALUE_MANEUVER,
  ARMOR_VALUE_RADIATION,
  ARMOR_VALUE_STEALTH,
  NUM_ARMOR_VALUES
};

#define ARMOR_VALUE_PREF_START  ARMOR_VALUE_HEAT
#define ARMOR_VALUE_PREF_END    NUM_ARMOR_VALUES

struct ArmorType
{
  int nCost;
  int nDevTime; 
  int nWeight;
  int nHeat;
  int nExplosive;
  int nAcid;
  int nWater;
  int nImpact;
  int nSonic;
  int nEMP;
  int nManeuver;
  int nRadiation;
  int nStealth;
  char strName[256];
};
extern struct ArmorType ArmorTypes[];

// So we pass in something like ARMOR_VALUE_SONIC and then 
// we get back ArmorTypes[nType].nSonic
extern int GetDefaultArmorValue(int nArmorType, int nArmorValueDefine);

// Gun accessories
enum
{
  GUN_NONE,
  GUN_PANZER_XII,      
  GUN_METAL_RAIN,      
  GUN_DRAGON_CANNON,  
  GUN_SONIC_RIFLE,   
  GUN_SCREAMER,
  GUN_ENERGY_RIFLE,
  GUN_ENERGY_BLASTER,
  GUN_PLASMA_CANNON,
  GUN_FIRESTORM,
  GUN_MISSILE_PACK,
  GUN_ARTILLERY_155,
  GUN_ARTILLERY_105,
  GUN_EMP_MISSILE,
  GUN_EMP_GRENADE,
  NUM_GUNS
};

// The values/parameters that each gun has
enum
{
  GUN_VALUE_COST,
  GUN_VALUE_WEIGHT,
  GUN_VALUE_HEAT,
  GUN_VALUE_EXPLOSIVE,
  GUN_VALUE_IMPACT,
  GUN_VALUE_SONIC,
  GUN_VALUE_ENERGY,
  GUN_VALUE_EMP,
  GUN_VALUE_RADIATION,
  GUN_VALUE_RANGE,
  GUN_VALUE_RATE_OF_FIRE,
  GUN_VALUE_POWER_COST,
  GUN_VALUE_HEAT_COST,
  GUN_VALUE_ENV,
  NUM_GUN_VALUES
};

// What the preferences can start and end at
#define GUN_VALUE_PREF_START  GUN_VALUE_HEAT
#define GUN_VALUE_PREF_END    GUN_VALUE_POWER_COST

struct GunType
{
  int nCost;
  int nDevTime; 
  int nWeight;
  int nHeat;
  int nExplosive;
  int nImpact;
  int nSonic;
  int nEnergy;
  int nEMP;
  int nRadiation;
  int nRange;
  int nRateOfFire;
  int nPwrCost;
  int nHeatCost;
  int nEnvImpact;
  char strName[256];
};
extern struct GunType GunTypes[];

extern int GetDefaultGunValue(int nGunType, int nGunValueDefine);

extern char *TranslateValueToText(int nValue);
extern char *TranslateApprovalToText(int nValue);

// Close combat accessories
enum
{
  MELEE_NONE,
  MELEE_STEEL_BAR,
  MELEE_BATTLE_KNIFE,
  MELEE_SAW_KNIFE,
  MELEE_ENERGY_KNIFE,
  MELEE_NANO_CUTTER,
  MELEE_ENERGY_BLADE,
  MELEE_HAMMER,
  MELEE_DRILL,
  NUM_MELEES
};
  
// The values/parameters that each melee weapon has
enum
{
  MELEE_VALUE_COST,
  MELEE_VALUE_WEIGHT,
  MELEE_VALUE_IMPACT,
  MELEE_VALUE_PIERCE,
  MELEE_VALUE_CUT,
  MELEE_VALUE_ENERGY,
  MELEE_VALUE_SPEED,
  MELEE_VALUE_POWER_COST,
  MELEE_VALUE_HEAT_COST,
  NUM_MELEE_VALUES
};

#define MELEE_VALUE_PREF_START  MELEE_VALUE_IMPACT
#define MELEE_VALUE_PREF_END    MELEE_VALUE_POWER_COST

struct MeleeType
{
  int nCost;
  int nDevTime; 
  int nWeight;
  int nImpact;
  int nPierce;
  int nCut;
  int nEnergy;
  int nSpeed;
  int nPwrCost;
  int nHeatCost;
  char strName[256];
};
extern struct MeleeType MeleeTypes[];

extern int GetDefaultMeleeValue(int nMeleeType, int nMeleeValueDefine);

// Accessories
enum 
{
  ACC_NONE,
  ACC_SENSOR_CAMERA,
  ACC_SENSOR_AUDIO,
  ACC_SENSOR_INFRARED,
  ACC_SENSOR_HEAT,
  ACC_SENSOR_MOVEMENT,
  ACC_SENSOR_RADAR,
  ACC_SENSOR_OMNI,
  ACC_SER_DEFENSE,
  ACC_MAGNETIC_DEFLECTOR,
  ACC_HEAT_SINK,
  ACC_GUN,
  ACC_MELEE,
  NUM_ACCS
};

// Accessory types
enum
{
  ACC_TYPE_ACC,
  ACC_TYPE_GUN,
  ACC_TYPE_MELEE,
  NUM_ACC_TYPES
};

// The values/parameters that each melee weapon has
enum
{
  ACC_VALUE_COST,
  ACC_VALUE_WEIGHT,
  ACC_VALUE_SIGHT,
  ACC_VALUE_AUDIO,
  ACC_VALUE_INFRARED,
  ACC_VALUE_RADAR,
  ACC_VALUE_HEAT_SENSOR,
  ACC_VALUE_MOTION_SENSOR,
  ACC_VALUE_POWER_COST,
  ACC_VALUE_HEAT_COST,
  NUM_ACC_VALUES
};

#define ACC_VALUE_PREF_START  ACC_VALUE_SIGHT
#define ACC_VALUE_PREF_END    ACC_VALUE_POWER_COST

struct AccType
{
  int nCost;
  int nDevTime; 
  int nWeight;
  int nSight;
  int nAudio;
  int nInfrared;
  int nRadar;
  int nHeatSensor;
  int nMotionSensor;
  int nPwrCost;
  int nHeatCost;
  char strName[256];
};
extern struct AccType AccTypes[];

extern int GetDefaultAccValue(int nAccType, int nAccValueDefine);

// The spec values
enum
{
  SPEC_VALUE_WEIGHT,
  SPEC_VALUE_SPEED,
  SPEC_VALUE_MANEUVER,
  SPEC_VALUE_CARRY_WEIGHT,
  NUM_SPEC_VALUES
};

#define SPEC_VALUE_PREF_START SPEC_VALUE_SPEED
#define SPEC_VALUE_PREF_END   NUM_SPEC_VALUES

enum
{
  BASE_VALUE_EQ_SLOTS,
  BASE_VALUE_MAX_POWER,
  BASE_VALUE_MAX_WEIGHT,
  BASE_VALUE_STORAGE,
  NUM_BASE_VALUES
};

enum 
{
  SYSTEM_FRAME,
  SYSTEM_HEAD,
  SYSTEM_TORSO,
  SYSTEM_ARM_RIGHT,
  SYSTEM_ARM_LEFT,
  SYSTEM_LEG_RIGHT,
  SYSTEM_LEG_LEFT,
  SYSTEM_EJECTION,
  SYSTEM_COOLING,
  SYSTEM_COMPUTER,
  SYSTEM_HUMAN_INTERFACE,
  NUM_SYSTEMS
};

#define SYSTEM_OVERALL NUM_SYSTEMS

// Interfaces are all the systems plus any extras down here
enum
{
  INTERFACE_SOFTWARE = NUM_SYSTEMS,
  NUM_INTERFACES = INTERFACE_SOFTWARE+1
};

class Accessory
{
  public:
    Accessory(int nType, int nModel) {
      nAccessoryType = nType;
      nModelWithinType = nModel;
    };

    void SetWeight(int nNew) { nWeight = nNew; };
    int GetWeight() { return nWeight; };

    void SetExpense(int nNew) { nExpense = nNew; };
    int GetExpense() { return nExpense; };

    int GetType() { return nAccessoryType; };
    int GetModel() { return nModelWithinType; };

    int GetPowerCost()
    {
      // Check the type to see what to do
      switch (this->GetType())
      {
        case ACC_TYPE_ACC:
        {
          return GetDefaultAccValue(this->GetModel(), ACC_VALUE_POWER_COST);
        }
        case ACC_TYPE_GUN:
        {
          return GetDefaultGunValue(this->GetModel(), GUN_VALUE_POWER_COST);
        }
        case ACC_TYPE_MELEE:
        {
           return GetDefaultMeleeValue(this->GetModel(), MELEE_VALUE_POWER_COST);
        }
      }

      return 0;
    }

    // Is very easy to add environmental impact ratings to other accessories if we want to
    int GetEnvImpact()
    {
      switch (this->GetType())
      {
        case ACC_TYPE_ACC:
        {
          return 0;
        }
        case ACC_TYPE_GUN:
        {
          return GetDefaultGunValue(this->GetModel(), GUN_VALUE_ENV);
        }
        case ACC_TYPE_MELEE:
        {
           return 0;
        }
      }

      return 0;
    }

    int GetHeatCost()
    {
      // Check the type to see what to do
      switch (this->GetType())
      {
        case ACC_TYPE_ACC:
        {
          return GetDefaultAccValue(this->GetModel(), ACC_VALUE_HEAT_COST);
        }
        case ACC_TYPE_GUN:
        {
          return GetDefaultGunValue(this->GetModel(), GUN_VALUE_HEAT_COST);
        }
        case ACC_TYPE_MELEE:
        {
           return GetDefaultMeleeValue(this->GetModel(), MELEE_VALUE_HEAT_COST);
        }
      }

      return 0;
    }

    bool IsHeatSink()
    {
      if (this->GetType() == ACC_TYPE_ACC && this->GetModel() == ACC_HEAT_SINK)
        return true;
      return false;
    }

    bool IsSensor()
    {
      if (this->GetType() == ACC_TYPE_ACC && this->GetModel() >= ACC_SENSOR_CAMERA && this->GetModel() <= ACC_SENSOR_OMNI)
        return true;
      return false;
    }

    bool IsSensorOfType(int nSensorType)
    {
      if (this->GetType() == ACC_TYPE_ACC && this->GetModel() == nSensorType)
        return true;
      return false;
    }

    bool IsGun()
    {
      if (this->GetType() == ACC_TYPE_GUN)
        return true;
      return false;
    }

    bool IsMelee()
    {
      if (this->GetType() == ACC_TYPE_MELEE)
        return true;
      return false;
    }

  protected:
    int nCost;
    int nWeight;
    int nExpense; // How expensive this thing is, not in resources immediately but later on
    int nAccessoryType; // What type of accessory is this
    int nModelWithinType; // What model is this, like if the type is gun, what kind of gun is it
    int nSystemRestrictions[NUM_SYSTEMS]; // Which systems can use this accessory?
};

class System
{
  public:
    System(int nType) 
    {
      nSystemType = nType;
      nSystemModel = SYSTEM_MODEL_NONE;
      strDesc[0] = 0;
      strSystemTypeName[0] = 0;
      nTotalCost = 0;

      nDevTimeLeft = 0;

      for (int i = 0; i < NUM_INTERFACES; i++) {
        nHasInterface[i] = false;
        nInterfaceValues[i] = 0;
      }

      Reset();
    };

    // Arm, head, etc?
    int GetSystemType() {return nSystemType;};

    // What model of arm, head, etc?
    int GetSystemModel() {return nSystemModel;};
    void SetSystemModel(int nNewModel) {nSystemModel = nNewModel;};

    char *GetDesc() { return strDesc; };
    char *GetSystemTypeName() { return strSystemTypeName; };
    
    bool HasInterface(int nInterfaceNum) { return nHasInterface[nInterfaceNum]; };
    int GetInterfaceValue(int nInterfaceNum) { return nInterfaceValues[nInterfaceNum]; };
    bool ImproveInterface(int nInterfaceNum, int nImprovement) 
    { 
      if (nInterfaceValues[nInterfaceNum] < INTERFACE_LEVELS-1) {
        nInterfaceValues[nInterfaceNum]+=nImprovement; 
        if (nInterfaceValues[nInterfaceNum] > INTERFACE_LEVELS-1)
          nInterfaceValues[nInterfaceNum] = INTERFACE_LEVELS-1;
        return true;
      }
      return false;
    };

    // Total cost is how much you've spent during the entire game on this
    // system, so it includes previously selected models
    void SetTotalCost(int nNewCost) {nTotalCost += nNewCost;};
    void AddTotalCost(int nAdd) {nTotalCost += nAdd;};
    void SubTotalCost(int nSub) {nTotalCost -= nSub;};
    int GetTotalCost() { return nTotalCost; };

    void SetDevTimeLeft(int nNewDevTimeLeft) {nDevTimeLeft = nNewDevTimeLeft;};
    void DecreaseDevTimeLeft() { if (nDevTimeLeft > 0) nDevTimeLeft--; };
    int GetDevTimeLeft() { return nDevTimeLeft; };

    int GetEqSlots() { return GetBaseValue(BASE_VALUE_EQ_SLOTS); };

    int GetWeight() { return GetSpecValue(SPEC_VALUE_WEIGHT); };

    Accessory *GetEq(int nSlot) { return nEqs[nSlot]; };
    
    bool HasThisEqInThisSlot(int nSlot, int nType, int nModel)
    {
      if (nEqs[nSlot] &&
          nEqs[nSlot]->GetType() == nType &&
          nEqs[nSlot]->GetModel() == nModel)
        return true;
      return false;
    }

    // Change from nothing to an eq, or delete and change to a new eq
    void ChangeEq(int nSlot, int nType, int nModel) 
    { 
      if (nEqs[nSlot]) {
        delete nEqs[nSlot];
        nEqs[nSlot] = 0;
      }
      nEqs[nSlot] = new Accessory(nType, nModel);
      
      switch (nType)
      {
        case ACC_TYPE_ACC:
        {
          nEqs[nSlot]->SetWeight(GetDefaultAccValue(nModel, ACC_VALUE_WEIGHT));
          break;
        }
        case ACC_TYPE_GUN:
        {
          nEqs[nSlot]->SetWeight(GetDefaultGunValue(nModel, GUN_VALUE_WEIGHT));
          break;
        }
        case ACC_TYPE_MELEE:
        {
          nEqs[nSlot]->SetWeight(GetDefaultMeleeValue(nModel, MELEE_VALUE_WEIGHT));
          break;
        }
      }
    };
    
    void SetSpecValue(int nValue, int nNew) {nSpecValues[nValue] = nNew;};
    int GetSpecValue(int nValue) { return nSpecValues[nValue]; };
    
    void SetBaseValue(int nValue, int nNew) {nBaseValues[nValue] = nNew;};
    int GetBaseValue(int nValue) { return nBaseValues[nValue]; };

    
    void ResetPlusButtons()
    {
      for (int i = 0; i < MAX_PLUS_BUTTON; i++)
        nPlusButtonPressed[i] = 0;
    }

    void AddPlusButtonPress(int nIndex)
    {
      nPlusButtonPressed[nIndex]++;
    }

    int GetPlusButtonPress(int nIndex)
    {
      return nPlusButtonPressed[nIndex];
    }

    // Essentially you reset the changeable content but not
    // the stuff that is common between system models
    // So you reset the interface values, but not whether or not
    // the model has an interface since that's common
    void Reset()
    {
      int i = 0;

      ResetPlusButtons();

      for (i = 0; i < NUM_INTERFACES; i++) {
        nInterfaceValues[i] = 0;
      }

      for (i = 0; i < MAX_EQ_SLOTS; i++) {
        nEqs[i] = 0;
      }

      for (i = 0; i < NUM_SPEC_VALUES; i++) {
        nSpecValues[i] = 0;
      }

      for (i = 0; i < NUM_BASE_VALUES; i++) {
        nBaseValues[i] = 0;
      }
    };

    // This includes the system's weight and all accessories
    int GetSystemWeightWithoutArmor() 
    {
      // Take the base weight of the system
      int nTotal = this->GetWeight();

      // Add the weight of the accessories
      for (int i = 0; i < MAX_EQ_SLOTS; i++)
      {
        if (nEqs[i])
        {
          nTotal += nEqs[i]->GetWeight();
        }
      }

      return nTotal;
    };

    int GetSystemPowerCost() 
    {
      int nTotalCost = 0;

      for (int i = 0; i < MAX_EQ_SLOTS; i++)
      {
        if (nEqs[i])
        {
          nTotalCost += nEqs[i]->GetPowerCost();
        }
      }

      return nTotalCost;
    };

    int GetSystemHeatCost() 
    {
      int nTotalCost = 0;

      for (int i = 0; i < MAX_EQ_SLOTS; i++)
      {
        if (nEqs[i])
        {
          nTotalCost += nEqs[i]->GetHeatCost();
        }
      }

      return nTotalCost;
    };

    int CountHeatSinks()
    {
      int nTotalCount = 0;

      for (int i = 0; i < MAX_EQ_SLOTS; i++)
      {
        if (nEqs[i] && nEqs[i]->IsHeatSink())
        {
          nTotalCount++;
        }
      }

      return nTotalCount;
    };
    
    int CountSensors(int nSensorType)
    {
      int nTotalCount = 0;

      for (int i = 0; i < MAX_EQ_SLOTS; i++)
      {
        if (nEqs[i] && nEqs[i]->IsSensorOfType(nSensorType))
        {
          nTotalCount++;
        }
      }

      return nTotalCount;
    };

    int RemoveHeatSinks()
    {
      int nTotalCount = 0;

      for (int i = 0; i < MAX_EQ_SLOTS; i++)
      {
        if (nEqs[i] && nEqs[i]->IsHeatSink())
        {
          delete nEqs[i];
          nEqs[i] = 0;
          nTotalCount++;
        }
      }

      return nTotalCount;
    };

    int RemoveSensors()
    {
      int nTotalCount = 0;

      for (int i = 0; i < MAX_EQ_SLOTS; i++)
      {
        if (nEqs[i] && nEqs[i]->IsSensor())
        {
          delete nEqs[i];
          nEqs[i] = 0;
          nTotalCount++;
        }
      }

      return nTotalCount;
    };

    int GetSystemEnvImpact()
    {
      int nEnv = 0;

      for (int i = 0; i < MAX_EQ_SLOTS; i++)
      {
        if (nEqs[i])
        {
          nEnv += nEqs[i]->GetEnvImpact();
        }
      }

      return nEnv;
    };

    int CountGuns()
    {
      int nTotalCount = 0;

      for (int i = 0; i < MAX_EQ_SLOTS; i++)
      {
        if (nEqs[i] && nEqs[i]->IsGun())
        {
          nTotalCount++;
        }
      }

      return nTotalCount;
    };

    int CountMelees()
    {
      int nTotalCount = 0;

      for (int i = 0; i < MAX_EQ_SLOTS; i++)
      {
        if (nEqs[i] && nEqs[i]->IsMelee())
        {
          nTotalCount++;
        }
      }

      return nTotalCount;
    };
     
    virtual void SetArmorType(int nNew) = 0;
    virtual int GetArmorType() { return ARMOR_NONE; };
    virtual int GetSystemWeight() = 0;

  protected:
    char strDesc[2048];
    char strSystemTypeName[2048];

    int nSystemType;
    int nSystemModel;
    
    int nWeight;
    int nTotalCost;

    int nDevTimeLeft; // How many turns left before this is ready?
    
    bool nHasInterface[NUM_INTERFACES];
    int nInterfaceValues[NUM_INTERFACES];

    int nEqSlots;
    Accessory *nEqs[MAX_EQ_SLOTS];

    // Specification values are things that every system might have
    // and that can be desired by stakeholders, like speed, maneuver, etc
    int nSpecValues[NUM_SPEC_VALUES];

    // Base values are things that every system might have but that are NOT
    // stakeholder-preferred, such as the max carry weight of a leg, or
    // the power on a head; things that restrict the system.
    int nBaseValues[NUM_BASE_VALUES];

    // Has a plus button been pressed for this system for this quarter, normally this would be
    // like improving a certain armor value
    int nPlusButtonPressed[MAX_PLUS_BUTTON + 1];
};


// Frame doesn't have much, it's just a basic choiceb
class Frame : public System
{
  public:
    Frame() : System(SYSTEM_FRAME) {
      sprintf(strSystemTypeName, GET_SYSTEM_NAME_TEXT(SYSTEM_FRAME));
      sprintf(strDesc, 
        "The Frame is the basic structure of the Robot."); /*  The frame has a huge impact "
        "on the cost efficiences of the robot's sub-systems and capabilities, and imposes "
        "restrictions on the selection of certain components.");*/
    };
    
    void Reset() 
    {
      // TODO - these functions
      System::Reset();
    }

    // This does nothing, but I have to have it here to have the virtual function
    // in the System class
    void SetArmorType(int nNew) { };

    // Just call the base function
    int GetSystemWeight() { return GetSystemWeightWithoutArmor(); };
};

// Just a sub-class, never to be used as an actual system, this is just for
// systems that have armor values
class SystemWithArmor : public System
{
  // Protected constructor so it cannot be used unless from within another class
  protected:
    SystemWithArmor(int nType) : System(nType)
    {
      Reset();
    };

  public:
    void SetArmorType(int nNew) 
    {
      if (nNew == nArmorType)
        return;
      ResetArmorValues();
      nArmorType = nNew;

      // Now set all the values to the defaults defined in the struct
      for (int i = 0; i < NUM_ARMOR_VALUES; i++)
      {
        nArmorValues[i] = GetDefaultArmorValue(nArmorType, i);
      }
    };
    int GetArmorType() { return nArmorType; };

    void SetArmorValue(int nValue, int nNew) {nArmorValues[nValue] = nNew;};
    int GetArmorValue(int nValue) { return nArmorValues[nValue]; };

    void AddArmorValue(int nValue, int nAdd) {nArmorValues[nValue] += nAdd;};
    void SubArmorValue(int nValue, int nSub) {nArmorValues[nValue] -= nSub;};

    void ResetArmorValues()
    {
      for (int i = 0; i < NUM_ARMOR_VALUES; i++)
        nArmorValues[i] = 0;
    }

    void Reset()
    {
      nArmorType = 0;
      ResetArmorValues();
      System::Reset();
    }

    int GetSystemWeight() 
    {
      // Take the weight from the system
      int nTotal = this->GetSystemWeightWithoutArmor();

      // Then add armor weight
      nTotal += this->GetArmorValue(ARMOR_VALUE_WEIGHT);
      return nTotal;
    }

  protected:
    int nArmorType;
    int nArmorValues[NUM_ARMOR_VALUES];
};

class Head : public SystemWithArmor
{
  public:
    Head() : SystemWithArmor(SYSTEM_HEAD) {
      sprintf(strSystemTypeName, GET_SYSTEM_NAME_TEXT(SYSTEM_HEAD));
      sprintf(strDesc, 
        "The head of the Robot houses sensors, computer components, "
        "and other important features, as well as determining the max "
        "power draw allowed by all Robot sub-systems.");

      nHasInterface[SYSTEM_TORSO] = true;
      nHasInterface[INTERFACE_SOFTWARE] = true;
      nHasInterface[SYSTEM_COMPUTER] = true;
      nHasInterface[SYSTEM_COOLING] = true;
    };

    void Reset() 
    {
      // TODO - these functions
      SystemWithArmor::Reset();
    }

    // Needs equipment so that things like camera, audio, heat etc sensors can be mounted
};

class Torso : public SystemWithArmor
{
  public:
    Torso() : SystemWithArmor(SYSTEM_TORSO) {
      sprintf(strSystemTypeName, GET_SYSTEM_NAME_TEXT(SYSTEM_TORSO));
      sprintf(strDesc, 
        "The Robot Torso houses the main computer system as well as the cooling and ejection "
        "systems, and is the primary seat for the Robot's pilot.");

      // This thing interfaces with almost everything
      for (int i = 0; i < NUM_INTERFACES; i++) {
        nHasInterface[i] = true;
      }

      nHasInterface[SYSTEM_FRAME] = false;
      nHasInterface[SYSTEM_TORSO] = false;
      nHasInterface[INTERFACE_SOFTWARE] = false;
    };

    void Reset() 
    {
      // TODO - these functions
      SystemWithArmor::Reset();
    }
    
  protected:
    
    int nStorageValue;
    int nPowerSystemValue; // How good is the power system?  Can it handle everything?
};

class Arm : public SystemWithArmor
{
  public:
    Arm(int nSystem) : SystemWithArmor(nSystem) {
      nSystemType = nSystem;

      if (nSystemType == SYSTEM_ARM_RIGHT)
        sprintf(strSystemTypeName, GET_SYSTEM_NAME_TEXT(SYSTEM_ARM_RIGHT));
      else
        sprintf(strSystemTypeName, GET_SYSTEM_NAME_TEXT(SYSTEM_ARM_LEFT));

      sprintf(strDesc, 
        "The arms of the Robot are useful for carrying weapons and equipment.");

      nHasInterface[SYSTEM_TORSO] = true;
      nHasInterface[INTERFACE_SOFTWARE] = true;
      nHasInterface[SYSTEM_COOLING] = true;
    };

    void Reset() 
    {
      // TODO - these functions
      SystemWithArmor::Reset();
    }
    
  protected:
    
    // This is all in the nSpecValue thing on the System class
    // so it isn't needed anymore
    int nSuspensionValue;
    int nJointValue;
    int nManeuverValue;
    int nCarryWeight;
    int nCloseAttackStrength;  // For melee attacks
    
    // Needs equipment 
};

class Leg : public SystemWithArmor
{
  public:
    Leg(int nSystem) : SystemWithArmor(nSystem) {
      nSystemType = nSystem;

      if (nSystemType == SYSTEM_LEG_RIGHT)
        sprintf(strSystemTypeName, GET_SYSTEM_NAME_TEXT(SYSTEM_LEG_RIGHT));
      else
        sprintf(strSystemTypeName, GET_SYSTEM_NAME_TEXT(SYSTEM_LEG_LEFT));

      sprintf(strDesc, 
        "The legs of the Robot determine its speed and maneuverability, and also play a role "
        "in its maximum carrying capacity.");
      
      nHasInterface[SYSTEM_TORSO] = true;
      nHasInterface[INTERFACE_SOFTWARE] = true;
      nHasInterface[SYSTEM_COOLING] = true;
    };


    void Reset() 
    {
      // TODO - these functions
      SystemWithArmor::Reset();
    }
    
  protected:
    
    // This is all in the nSpecValue thing on the System class
    // so it isn't needed anymore
    int nSuspensionValue;
    int nJointValue;
    int nManeuverValue;
    int nSpeedValue;
    int nJumpValue;
    int nMaxSystemWeight;
    
    // Needs equipment 
};

class EjectionSystem : public System
{
  public:
    EjectionSystem() : System(SYSTEM_EJECTION) {
      sprintf(strSystemTypeName, GET_SYSTEM_NAME_TEXT(SYSTEM_EJECTION));
      sprintf(strDesc, 
        "The ejection system is an optional safety feature that provides the pilot with "
        "a way to escape in the event of imminent destruction.");

      nHasInterface[SYSTEM_TORSO] = true;
      nHasInterface[INTERFACE_SOFTWARE] = true;
    };
    
    void Reset() 
    {
      // TODO - these functions
      System::Reset();
    }

    // Does nothing
    void SetArmorType(int nNew) { };

    // Just call the base function
    int GetSystemWeight() { return GetSystemWeightWithoutArmor(); };
};

class CoolingSystem : public System
{
  public:
    CoolingSystem() : System(SYSTEM_COOLING) {
      sprintf(strSystemTypeName, GET_SYSTEM_NAME_TEXT(SYSTEM_COOLING));
      sprintf(strDesc, 
        "The cooling system prevents the Robot from overheating, shutting down, and self-detonating its own "
        "explosives.  Each extra weapon or sub-system attached to the Robot produces a certain amount of heat; "
        "each cooling system will reduce heat by a certain amount by default, and will affect the amount of "
        "heat by which each heat sink accessory will reduce the total system heat.");

      nHasInterface[SYSTEM_TORSO] = true;
      nHasInterface[SYSTEM_HEAD] = true;
      nHasInterface[SYSTEM_ARM_RIGHT] = true;
      nHasInterface[SYSTEM_ARM_LEFT] = true;
      nHasInterface[SYSTEM_LEG_RIGHT] = true;
      nHasInterface[SYSTEM_LEG_LEFT] = true;
      nHasInterface[SYSTEM_COMPUTER] = true;
      nHasInterface[INTERFACE_SOFTWARE] = true;
    };
    
    void Reset() 
    {
      // TODO - these functions
      System::Reset();
    }
    
    // Does nothing
    void SetArmorType(int nNew) { };

    // Just call the base function
    int GetSystemWeight() { return GetSystemWeightWithoutArmor(); };

  protected:

    
    // This should all be in the nSpecValue thing on the System class
    // so it isn't needed anymore
    int nHeatSinkValue;  // The type depends only on the system selected
//    int nFanValue;
    int nLiquidCoolingType;
    int nLiquidCoolingValue;
    int nThermostatType; // Better in water, better on land
    
    int nWaterCoolingValue;
    int nLandCoolingValue;
    int nAirCoolingValue;
    int nWeaponCoolingValue;
    int nJointCoolingValue;
    int nComputerCoolingValue;
};

class ComputerSystem : public System
{
  public:
    ComputerSystem() : System(SYSTEM_COMPUTER) {
      sprintf(strSystemTypeName, GET_SYSTEM_NAME_TEXT(SYSTEM_COMPUTER));
      sprintf(strDesc, 
        "The computer system houses all the computer software and hardware of the Robot.  It is used to determine the effectiveness "
        "and cost of the sensors.");
      
      nHasInterface[SYSTEM_TORSO] = true;
      nHasInterface[SYSTEM_HEAD] = true;
      nHasInterface[INTERFACE_SOFTWARE] = true;
      nHasInterface[SYSTEM_COOLING] = true;
    };

    void Reset() 
    {
      // TODO - these functions
      System::Reset();
    }

    // Does nothing
    void SetArmorType(int nNew) { };

    // Just call the base function
    int GetSystemWeight() { return GetSystemWeightWithoutArmor(); };
    
  protected:
    // Software
    int nCommunications;
    int nBallistics;
    int nController;
    int nOS;
    int nPilotInterface;
    int nDatabase;
    
    // Hardware
    int nProcessor;
    int nRAM;
    int nHardDiskType; // Solid state or subatomic
    int nHardDiskSpace;  // SSD costs less for space, subatomic costs more?
};

class HumanInterface : public System
{
  public:
    HumanInterface() : System(SYSTEM_HUMAN_INTERFACE) {
    
      sprintf(strSystemTypeName, GET_SYSTEM_NAME_TEXT(SYSTEM_HUMAN_INTERFACE));
      sprintf(strDesc, 
        "The Pilot System is the interface between the operator and the Robot, including levers, "
        "switches, buttons, and screens.");

      nHasInterface[SYSTEM_TORSO] = true;
      nHasInterface[INTERFACE_SOFTWARE] = true;
      nHasInterface[SYSTEM_EJECTION] = true;
    };

    void Reset()
    {
      nControlType = 0;
      nLayout = 0;
      nScreen = 0;
      nBuckle = 0;
      nSuit = 0;
      nControllerHookup = 0;
      System::Reset();
    }

    // Does nothing
    void SetArmorType(int nNew) { };

    // Just call the base function
    int GetSystemWeight() { return GetSystemWeightWithoutArmor(); };
    
  protected:
    int nControlType; // wheel, joystick, video game controller, etc
    int nLayout;
    int nScreen;
    int nBuckle;
    int nSuit;
    int nControllerHookup;
};

// Terrains
enum
{
  TERRAIN_ROCKY,  // High jump legs
  TERRAIN_ROUGH,  // Legs with a blend of jump and maneuver are good
  TERRAIN_FLAT,   // Track is best for this
  TERRAIN_FORESTED, // Legs with higher maneuver are better
  NUM_TERRAINS
};

// Temperature types
enum
{
  TEMP_COLD,      // Heat sinks can be 1/2
  TEMP_MODERATE,  // Heat sinks normal
  TEMP_VARIED,     // Heat sinks should be double
  NUM_TEMPS
};

// Efficiencies/deficiencies for contractors
// most of them coincide to systems, the last bunch
// are with sub-systems
enum
{
  EFF_FRAME,
  EFF_HEAD,
  EFF_TORSO,
  EFF_ARM,
  EFF_LEG,
  EFF_EJECTION,
  EFF_COOLING,
  EFF_COMPUTER,
  EFF_HUMAN_INTERFACE,
  EFF_INTERFACES,
  EFF_GUNS,
  EFF_MELEE,
  EFF_ARMOR,
  EFF_SENSORS,
  NUM_EFFS 
};

#define MIN_EFFS 2
#define MAX_EFFS 3

// The trainer preferences/experiences for current fielded systems
enum
{
  TRAINER_EXP_MANEUVER,
  TRAINER_EXP_FIREPOWER,
  TRAINER_EXP_CLOSE_COMBAT,
  TRAINER_EXP_MID_WEIGHT,
  TRAINER_EXP_LIGHT,
  TRAINER_EXP_HEAVY,
  NUM_TRAINER_EXPS
};

#define MAX_VACATIONS          3
#define ENUM_DOES_NOT_CARE    -1
#define VALUE_DOES_NOT_CARE    0

#define MAX_SUS_SYSTEMS 4
#define MAX_INTEGRATE_SYSTEMS 2
#define MAX_ARMOR_RES_GEN 2

// The data set used as the "true requirements" of both
// the system as a whole and the stakeholders.  This is
// what you compare the system params to to see if they are
// correct or in line with stakeholder needs, and basically
// contains everything the Robot has.  
struct RobotParameters
{
    // All the defaults set to "DOES_NOT_CARE" then we
    // specify who cares about what later
    RobotParameters()
    {
      nCost = VALUE_DOES_NOT_CARE;  
      nCostMax = VALUE_DOES_NOT_CARE; 
      nCostMin = VALUE_DOES_NOT_CARE; 

      int i = 0;
      for (i = 0; i < NUM_ARMOR_VALUES; i++)
        nArmorValues[i] = VALUE_DOES_NOT_CARE;

      for (i = 0; i < NUM_GUN_VALUES; i++)
        nGunValues[i] = VALUE_DOES_NOT_CARE;

      for (i = 0; i < NUM_MELEE_VALUES; i++)
        nMeleeValues[i] = VALUE_DOES_NOT_CARE;

      for (i = 0; i < NUM_ACC_VALUES; i++)
        nAccValues[i] = VALUE_DOES_NOT_CARE;

      for (i = 0; i < NUM_SPEC_VALUES; i++)
        nSpecValues[i] = VALUE_DOES_NOT_CARE;
      
      nUserInterface = VALUE_DOES_NOT_CARE;
     
      nUserInterfaceType = ENUM_DOES_NOT_CARE; 

      nTerrain = ENUM_DOES_NOT_CARE;
      nTemperature = VALUE_DOES_NOT_CARE;
      bTemperatureRevealed = false;

      nMaxEnvImpact = VALUE_DOES_NOT_CARE;
      nMaxEnvImpactBottom = VALUE_DOES_NOT_CARE;
      nMaxEnvImpactTop = VALUE_DOES_NOT_CARE;

      for (i = 0; i < MAX_SUS_SYSTEMS; i++)
      {
        nSustainableSystemType[i] = VALUE_DOES_NOT_CARE;
        nSustainableSystemModel[i] = VALUE_DOES_NOT_CARE;
      }

      for (i = 0; i < NUM_EFFS; i++)
      {
        nEfficiencies[i] = 0;
        nDeficiencies[i] = 0;
      }

      for (i = 0; i < NUM_TRAINER_EXPS; i++)
        nTrainerExp[i] = 0;

      for (i = 0; i < MAX_INTEGRATE_SYSTEMS; i++)
        nIntegrationExp[i] = 0;

      for (i = 0; i < MAX_ARMOR_RES_GEN; i++)
        nArmorResourceGen[i] = 0;

      for (i = 0; i < MAX_VACATIONS; i++)
        nVacationMonths[i] = 0;
    };
    // The parameters that each system has overall.
    // These are the final things that the stakeholders look at, the other
    // systems and sub-systems are all just ways of getting to these

    int nCost;    // High cost makes some stakeholders unhappy 

    // Overall defenses
    int nArmorValues[NUM_ARMOR_VALUES];

    // Overall attacks
    int nGunValues[NUM_GUN_VALUES];
    int nMeleeValues[NUM_MELEE_VALUES];

    // Overall accessory vals, like sensors
    int nAccValues[NUM_ACC_VALUES];

    // Overall system spec values like weight and speed
    int nSpecValues[NUM_SPEC_VALUES];

    // User experience
    int nUserInterface;  // How much dev has been put into the UI

    // Preferences
    int nUserInterfaceType; // Which type does the user want

    // Operating environment
    int nTerrain;
    int nTemperature;
    bool bTemperatureRevealed; // Has the temperature question been asked yet

    // Environmental impact
    int nMaxEnvImpact;
    int nMaxEnvImpactBottom;
    int nMaxEnvImpactTop;

    // Sustainability prefs
    int nSustainableSystemType[MAX_SUS_SYSTEMS];
    int nSustainableSystemModel[MAX_SUS_SYSTEMS];

    // Contractor efficiencies
    int nEfficiencies[NUM_EFFS];
    int nDeficiencies[NUM_EFFS];

    // Trainer system prefs
    int nTrainerExp[NUM_TRAINER_EXPS];

    // Gov't developer/integrator
    int nIntegrationExp[MAX_INTEGRATE_SYSTEMS];  
    int nArmorResourceGen[MAX_ARMOR_RES_GEN];

    // Supervisor
    int nCostMin; // The supervisor's estimation of what the min should be
    int nCostMax; // The supervisor's estimation of what the max could be
    int nVacationMonths[MAX_VACATIONS];  // Months that a lot of people will be out
};

class Robot
{
  public:
    Robot() {
      objFrame =          new Frame();
      objHead =           new Head();
      objTorso =          new Torso();
      objRightArm =       new Arm(SYSTEM_ARM_RIGHT);
      objLeftArm =        new Arm(SYSTEM_ARM_LEFT);
      objRightLeg =       new Leg(SYSTEM_LEG_RIGHT);
      objLeftLeg =        new Leg(SYSTEM_LEG_LEFT);
      objEjection =       new EjectionSystem();
      objCooling =        new CoolingSystem();
      objComputer =       new ComputerSystem();
      objHumanInterface = new HumanInterface();
    };

    // Remove heat sinks from all systems and then report how many were removed
    int RemoveAllHeatSinks()
    {
      int nNumHeatSinks = 0;
      System *pTempSys = 0;
      if (this->GetHead())
        nNumHeatSinks += this->GetHead()->RemoveHeatSinks();
      if (this->GetTorso())
        nNumHeatSinks += this->GetTorso()->RemoveHeatSinks();
      if (this->GetRightArm())
        nNumHeatSinks += this->GetRightArm()->RemoveHeatSinks();
      if (this->GetLeftArm())
        nNumHeatSinks += this->GetLeftArm()->RemoveHeatSinks();
      if (this->GetRightLeg())
        nNumHeatSinks += this->GetRightLeg()->RemoveHeatSinks();
      if (this->GetLeftLeg())
        nNumHeatSinks += this->GetLeftLeg()->RemoveHeatSinks();

      return nNumHeatSinks;
    }

    int RemoveAllSensors()
    {
      int nNum = 0;
      System *pTempSys = 0;
      if (this->GetHead())
        nNum += this->GetHead()->RemoveSensors();
      if (this->GetTorso())
        nNum += this->GetTorso()->RemoveSensors();
      if (this->GetRightArm())
        nNum += this->GetRightArm()->RemoveSensors();
      if (this->GetLeftArm())
        nNum += this->GetLeftArm()->RemoveSensors();
      if (this->GetRightLeg())
        nNum += this->GetRightLeg()->RemoveSensors();
      if (this->GetLeftLeg())
        nNum += this->GetLeftLeg()->RemoveSensors();

      return nNum;
    }

    void ResetAllPlusButtons()
    {
      if (this->GetHead())
        this->GetHead()->ResetPlusButtons();
      if (this->GetTorso())
        this->GetTorso()->ResetPlusButtons();
      if (this->GetRightArm())
        this->GetRightArm()->ResetPlusButtons();
      if (this->GetLeftArm())
        this->GetLeftArm()->ResetPlusButtons();
      if (this->GetRightLeg())
        this->GetRightLeg()->ResetPlusButtons();
      if (this->GetLeftLeg())
        this->GetLeftLeg()->ResetPlusButtons();
      if (this->GetEjectionSystem())
        this->GetEjectionSystem()->ResetPlusButtons();
      if (this->GetCoolingSystem())
        this->GetCoolingSystem()->ResetPlusButtons();
      if (this->GetComputerSystem())
        this->GetComputerSystem()->ResetPlusButtons();
      if (this->GetHumanInterface())
        this->GetHumanInterface()->ResetPlusButtons();
    }

    void ResetSystem(int nSystem)
    {
      if (nSystem == SYSTEM_FRAME)            { objFrame->Reset(); };
      if (nSystem == SYSTEM_HEAD)             { objHead->Reset(); };
      if (nSystem == SYSTEM_TORSO)            { objTorso->Reset(); };
      if (nSystem == SYSTEM_ARM_RIGHT)        { objRightArm->Reset(); };
      if (nSystem == SYSTEM_ARM_LEFT)         { objLeftArm->Reset(); };
      if (nSystem == SYSTEM_LEG_RIGHT)        { objRightLeg->Reset(); };
      if (nSystem == SYSTEM_LEG_LEFT)         { objLeftLeg->Reset(); };
      if (nSystem == SYSTEM_EJECTION)         { objEjection->Reset(); };
      if (nSystem == SYSTEM_COOLING)          { objCooling->Reset(); };
      if (nSystem == SYSTEM_COMPUTER)         { objComputer->Reset(); };
      if (nSystem == SYSTEM_HUMAN_INTERFACE)  { objHumanInterface->Reset(); };
    }
    Frame *GetFrame()                   { return objFrame; };
    Head *GetHead()                     { return objHead; };
    Torso *GetTorso()                   { return objTorso; };
    Arm *GetRightArm()                  { return objRightArm; };
    Arm *GetLeftArm()                   { return objLeftArm; };
    Leg *GetRightLeg()                  { return objRightLeg; };
    Leg *GetLeftLeg()                   { return objLeftLeg; };
    EjectionSystem *GetEjectionSystem() { return objEjection; };
    CoolingSystem *GetCoolingSystem()   { return objCooling; };
    ComputerSystem *GetComputerSystem() { return objComputer; };
    HumanInterface *GetHumanInterface() { return objHumanInterface; };

    ~Robot() {
      delete objFrame;
      delete objHead;
      delete objTorso;
      delete objRightArm;
      delete objLeftArm;
      delete objRightLeg;
      delete objLeftLeg;
      delete objEjection;
      delete objCooling;
      delete objComputer;
      delete objHumanInterface;
    };
   
    struct RobotParameters TotalSystemParams;

    System *GetSystemByType(int nType)
    {
      switch (nType)
      {
        case SYSTEM_FRAME:
          return this->GetFrame();
        case SYSTEM_HEAD:
          return this->GetHead();
        case SYSTEM_TORSO:
          return this->GetTorso();
        case SYSTEM_ARM_RIGHT:
          return this->GetRightArm();
        case SYSTEM_ARM_LEFT:
          return this->GetLeftArm();
        case SYSTEM_LEG_RIGHT:
          return this->GetRightLeg();
        case SYSTEM_LEG_LEFT:
          return this->GetLeftLeg();
        case SYSTEM_EJECTION:
          return this->GetEjectionSystem();
        case SYSTEM_COOLING:
          return this->GetCoolingSystem();
        case SYSTEM_COMPUTER:
          return this->GetComputerSystem();
        case SYSTEM_HUMAN_INTERFACE:
          return this->GetHumanInterface();
      }

      return 0;
    }

    int GetTotalHeatCost() 
    {
      int nTotalCost = 0;

      if (this->GetHead())
        nTotalCost += this->GetHead()->GetSystemHeatCost();
      if (this->GetTorso())
        nTotalCost += this->GetTorso()->GetSystemHeatCost();
      if (this->GetRightArm())
        nTotalCost += this->GetRightArm()->GetSystemHeatCost();
      if (this->GetLeftArm())
        nTotalCost += this->GetLeftArm()->GetSystemHeatCost();
      if (this->GetRightLeg())
        nTotalCost += this->GetRightLeg()->GetSystemHeatCost();
      if (this->GetLeftLeg())
        nTotalCost += this->GetLeftLeg()->GetSystemHeatCost();

       // And the sensor heat costs
      if (this->GetComputerSystem())
      {
        int nVal = 0;
        for (int i = ACC_SENSOR_CAMERA; i <= ACC_SENSOR_OMNI; i++)
        {
          nVal = 
            GetSensorHeatCost(i, this->GetComputerSystem()->GetSystemModel());

          if (this->GetHead())
            nTotalCost += this->GetHead()->CountSensors(i) * nVal;
          if (this->GetTorso())
            nTotalCost += this->GetTorso()->CountSensors(i) * nVal;
          if (this->GetRightArm())
            nTotalCost += this->GetRightArm()->CountSensors(i) * nVal;
          if (this->GetLeftArm())
            nTotalCost += this->GetLeftArm()->CountSensors(i) * nVal;
          if (this->GetRightLeg())
            nTotalCost += this->GetRightLeg()->CountSensors(i) * nVal;
          if (this->GetLeftLeg())
            nTotalCost += this->GetLeftLeg()->CountSensors(i) * nVal;
        }
      }
     
      return nTotalCost;
    }

    int GetMaxHeatCost() 
    {
      if (this->GetCoolingSystem() == 0)
        return 0;

      int nMaxAllowedHeat = 0;
        
      int nModel = this->GetCoolingSystem()->GetSystemModel();

      nMaxAllowedHeat += GetCoolingSystemValue(nModel, COOL_VALUE_HEAT_REDUCE);

      int nVal = GetCoolingSystemValue(nModel, COOL_VALUE_HEAT_SINK_REDUCE);

      if (this->GetHead())
        nMaxAllowedHeat += this->GetHead()->CountHeatSinks() * nVal;
      if (this->GetTorso())
        nMaxAllowedHeat += this->GetTorso()->CountHeatSinks() * nVal;
      if (this->GetRightArm())
        nMaxAllowedHeat += this->GetRightArm()->CountHeatSinks() * nVal;
      if (this->GetLeftArm())
        nMaxAllowedHeat += this->GetLeftArm()->CountHeatSinks() * nVal;
      if (this->GetRightLeg())
        nMaxAllowedHeat += this->GetRightLeg()->CountHeatSinks() * nVal;
      if (this->GetLeftLeg())
        nMaxAllowedHeat += this->GetLeftLeg()->CountHeatSinks() * nVal;

      return nMaxAllowedHeat;
    };

    int GetTotalPowerCost() 
    {
      int nTotalCost = 0;

      if (this->GetHead())
        nTotalCost += this->GetHead()->GetSystemPowerCost();
      if (this->GetTorso())
        nTotalCost += this->GetTorso()->GetSystemPowerCost();
      if (this->GetRightArm())
        nTotalCost += this->GetRightArm()->GetSystemPowerCost();
      if (this->GetLeftArm())
        nTotalCost += this->GetLeftArm()->GetSystemPowerCost();
      if (this->GetRightLeg())
        nTotalCost += this->GetRightLeg()->GetSystemPowerCost();
      if (this->GetLeftLeg())
        nTotalCost += this->GetLeftLeg()->GetSystemPowerCost();
     
      // But now we have to add all the heat sink power costs,
      // since they depend on the cooling system
      if (this->GetCoolingSystem())
      {
        int nVal = 
          GetCoolingSystemValue(this->GetCoolingSystem()->GetSystemModel(), COOL_VALUE_HEAT_SINK_POWER_COST);

        if (this->GetHead())
          nTotalCost += this->GetHead()->CountHeatSinks() * nVal;
        if (this->GetTorso())
          nTotalCost += this->GetTorso()->CountHeatSinks() * nVal;
        if (this->GetRightArm())
          nTotalCost += this->GetRightArm()->CountHeatSinks() * nVal;
        if (this->GetLeftArm())
          nTotalCost += this->GetLeftArm()->CountHeatSinks() * nVal;
        if (this->GetRightLeg())
          nTotalCost += this->GetRightLeg()->CountHeatSinks() * nVal;
        if (this->GetLeftLeg())
          nTotalCost += this->GetLeftLeg()->CountHeatSinks() * nVal;
      }

      // And the sensor power costs
      if (this->GetComputerSystem())
      {
        int nVal = 0;
        for (int i = ACC_SENSOR_CAMERA; i <= ACC_SENSOR_OMNI; i++)
        {
          nVal = 
            GetSensorPowerCost(i, this->GetComputerSystem()->GetSystemModel());

          if (this->GetHead())
            nTotalCost += this->GetHead()->CountSensors(i) * nVal;
          if (this->GetTorso())
            nTotalCost += this->GetTorso()->CountSensors(i) * nVal;
          if (this->GetRightArm())
            nTotalCost += this->GetRightArm()->CountSensors(i) * nVal;
          if (this->GetLeftArm())
            nTotalCost += this->GetLeftArm()->CountSensors(i) * nVal;
          if (this->GetRightLeg())
            nTotalCost += this->GetRightLeg()->CountSensors(i) * nVal;
          if (this->GetLeftLeg())
            nTotalCost += this->GetLeftLeg()->CountSensors(i) * nVal;
        }
      }
  
      return nTotalCost;
    }

    // Jump isn't a spec value, so we just take the values directly from
    // the struct.  This is because nobody has a "jump preference" but it's
    // used in terms of terrain
    int GetTotalJump()
    {
      int nTotal = 0;

      if (this->GetRightLeg())
        nTotal += Legs[this->GetRightLeg()->GetSystemModel()].nJump;
      if (this->GetLeftLeg())
        nTotal += Legs[this->GetLeftLeg()->GetSystemModel()].nJump;

      return nTotal;
    }

    int GetTotalManeuver()
    {
      int nTotal = 0;

      if (this->GetRightLeg())
        nTotal += this->GetRightLeg()->GetSpecValue(SPEC_VALUE_MANEUVER);

      if (this->GetLeftLeg())
        nTotal += this->GetLeftLeg()->GetSpecValue(SPEC_VALUE_MANEUVER);

      // Is not averaged, it's just the total
      //nTotal /= 2;
      return nTotal;
    }

    int GetTotalSpeed()
    {
      int nTotal = 0;

      if (this->GetRightLeg())
        nTotal += this->GetRightLeg()->GetSpecValue(SPEC_VALUE_SPEED);

      if (this->GetLeftLeg())
        nTotal += this->GetLeftLeg()->GetSpecValue(SPEC_VALUE_SPEED);

      // Is not averaged, it's just the total
      //nTotal /= 2;
      return nTotal;
    }

    // This is just looking at the head and using that
    int GetMaxPowerCost() 
    {
      if (GetHead() == 0)
        return 0;

      return Heads[GetHead()->GetSystemModel()].nMaxPower;
    };

    int GetMaxWeight()
    {
      int nMaxWeight = 0;
      
      if (GetRightLeg())
      {
        nMaxWeight += Legs[GetRightLeg()->GetSystemModel()].nMaxWeight;
      }

      if (GetLeftLeg())
      {
        nMaxWeight += Legs[GetLeftLeg()->GetSystemModel()].nMaxWeight;
      }

      return nMaxWeight;
    };

    int GetTotalWeight()
    {
      int nWeight = 0;

      // Add up all the weights of the systems
      if (this->GetFrame())
        nWeight += this->GetFrame()->GetSystemWeight();
      if (this->GetHead())
        nWeight += this->GetHead()->GetSystemWeight();
      if (this->GetTorso())
        nWeight += this->GetTorso()->GetSystemWeight();
      if (this->GetRightArm())
        nWeight += this->GetRightArm()->GetSystemWeight();
      if (this->GetLeftArm())
        nWeight += this->GetLeftArm()->GetSystemWeight();
      if (this->GetRightLeg())
        nWeight += this->GetRightLeg()->GetSystemWeight();
      if (this->GetLeftLeg())
        nWeight += this->GetLeftLeg()->GetSystemWeight();
      if (this->GetCoolingSystem())
        nWeight += this->GetCoolingSystem()->GetSystemWeight();
      if (this->GetComputerSystem())
        nWeight += this->GetComputerSystem()->GetSystemWeight();
      if (this->GetEjectionSystem())
        nWeight += this->GetEjectionSystem()->GetSystemWeight();
      if (this->GetHumanInterface())
        nWeight += this->GetHumanInterface()->GetSystemWeight();

      return nWeight;
    };

    int GetTotalEnvImpact()
    {
      int nEnv = 0;
      
      if (this->GetHead())
        nEnv += this->GetHead()->GetSystemEnvImpact();
      if (this->GetTorso())
        nEnv += this->GetTorso()->GetSystemEnvImpact();
      if (this->GetRightArm())
        nEnv += this->GetRightArm()->GetSystemEnvImpact();
      if (this->GetLeftArm())
        nEnv += this->GetLeftArm()->GetSystemEnvImpact();
      if (this->GetRightLeg())
        nEnv += this->GetRightLeg()->GetSystemEnvImpact();
      if (this->GetLeftLeg())
        nEnv += this->GetLeftLeg()->GetSystemEnvImpact();

      return nEnv;
    }

    int CountTotalGuns()
    {
      int nNum = 0;
      
      if (this->GetHead())
        nNum += this->GetHead()->CountGuns();
      if (this->GetTorso())
        nNum += this->GetTorso()->CountGuns();
      if (this->GetRightArm())
        nNum += this->GetRightArm()->CountGuns();
      if (this->GetLeftArm())
        nNum += this->GetLeftArm()->CountGuns();
      if (this->GetRightLeg())
        nNum += this->GetRightLeg()->CountGuns();
      if (this->GetLeftLeg())
        nNum += this->GetLeftLeg()->CountGuns();

      return nNum;
    }

    int CountTotalMelees()
    {
      int nNum = 0;
      
      if (this->GetHead())
        nNum += this->GetHead()->CountMelees();
      if (this->GetTorso())
        nNum += this->GetTorso()->CountMelees();
      if (this->GetRightArm())
        nNum += this->GetRightArm()->CountMelees();
      if (this->GetLeftArm())
        nNum += this->GetLeftArm()->CountMelees();
      if (this->GetRightLeg())
        nNum += this->GetRightLeg()->CountMelees();
      if (this->GetLeftLeg())
        nNum += this->GetLeftLeg()->CountMelees();

      return nNum;
    }

  private:

    // All of the systems on this mecha
    Frame           *objFrame;
    Head            *objHead;
    Torso           *objTorso;
    Arm             *objRightArm;
    Arm             *objLeftArm;
    Leg             *objRightLeg;
    Leg             *objLeftLeg;
    EjectionSystem  *objEjection;
    CoolingSystem   *objCooling;
    ComputerSystem  *objComputer;
    HumanInterface  *objHumanInterface;
};


/////////////////////////
/////////////////////////
/// STAKEHOLDER STUFF ///
/////////////////////////
/////////////////////////
enum
{
  STAKEHOLDER_SUPERVISOR,  
  STAKEHOLDER_PM,          
  STAKEHOLDER_TRAINER,     
  STAKEHOLDER_DEVELOPER,   
  STAKEHOLDER_CONTRACTOR,  
  STAKEHOLDER_SENATOR,     
  STAKEHOLDER_USER,        
  NUM_STAKEHOLDERS 
};

// An enum denoting the specific preference arrays of each stakeholder
enum
{
  PREF_ARRAY_GUN,
  PREF_ARRAY_MELEE,
  PREF_ARRAY_ACC,
  PREF_ARRAY_ARMOR,
  PREF_ARRAY_SPEC,
  NUM_PREF_ARRAYS
};

extern const char *Stakeholder_Types[];

#define MAX_QUESTIONS 7

class Stakeholder
{
  public:
  
    // Constructor
    Stakeholder(); 
    
    // Setup a stakeholder for use
    void SetupStakeholder(int type);
    
    void SetType(int type) { nType = type; };    
    int  GetType()         { return nType; };
    
    void AddApproval(int add) { nApproval += add; if (nApproval > 100) nApproval = 100; if (nApproval < 0) nApproval = 0; }; 
    void SubApproval(int sub) { nApproval -= sub;  if (nApproval < 0) nApproval = 0; };    
    int  GetApproval()        { return nApproval; };

    int GetQuestionState(int nQues) { return nQuestionStates[nQues]; };
    void IncreaseQuestionState(int nQues) { nQuestionStates[nQues]++; };
    
    const char *GetName(); 
    const char *GetPrevName(); 
    const char *GetShortName(); 
    char *GetQuestion(int nQuestionNum) { return strQuestions[nQuestionNum];};

    int GetPerson() { return nPerson; };
    int GetPrevPerson() { return nPrevPerson; };
    void SetPrevPerson(int nNewPrevPerson) { nPrevPerson = nNewPrevPerson; };

    // Clear all the values from a stakeholder
    void Clear();

    int PrintAnswerToQuestion(int nQuestionNum, char *strAnswer);

    int FindSupervisorAnswer(int nQuestionNum, char *strAnswer);
    int FindPMAnswer(int nQuestionNum, char *strAnswer);
    int FindTrainerAnswer(int nQuestionNum, char *strAnswer);
    int FindDeveloperAnswer(int nQuestionNum, char *strAnswer);
    int FindContractorAnswer(int nQuestionNum, char *strAnswer);
    int FindSenatorAnswer(int nQuestionNum, char *strAnswer);
    int FindUserAnswer(int nQuestionNum, char *strAnswer);

    // Helper functions for the "FindXAnswer" functions
    void PrintSupervisorVacs(int nQuestionNum, char *strAnswer, int nTotalCount);
    void PrintTrainerExps(int nQuestionNum, char *strAnswer, int nTotalCount);
    void PrintEffDefs(int nQuestionNum, char *strAnswer, int nTotalCount, bool bEff);

    // Contractor eff/defs
    int GetEfficiency(int nEnum) { return RobotPreferences.nEfficiencies[nEnum]; }
    int GetDeficiency(int nEnum) { return RobotPreferences.nDeficiencies[nEnum]; }

    int HasIntegrationExpForSystem(int nSystemNum) 
    {
      for (int i = 0; i < MAX_INTEGRATE_SYSTEMS; i++)
      {
        if (RobotPreferences.nIntegrationExp[i])
          return true;
      }
      return false;
    }

    int IsVacationMonth(int nQuarter) 
    { 
      // There is never a vacation month on the first quarter, it's always later
      if (nQuarter == 0)
        return false;
      return ArrayContains(RobotPreferences.nVacationMonths, MAX_VACATIONS, nQuarter);
    }

    struct RobotParameters RobotPreferences; // Which parameters does this stakeholder want?
    
    // Deconstructor
    ~Stakeholder();
    
  private:
    const char *GetNameText(int nThisPerson);

    int nPerson;        // Which person is this stakeholder?
    int nType;          // Which type of stakeholder is this (military, user, etc) ?
    int nApproval;      // Stakeholder's approval rating of Systems Engineer's actions thus far

    int nQuestionStates[MAX_QUESTIONS]; // Where in each 'question line' is this stakeholder? 
    
    char strQuestions[MAX_QUESTIONS][256];

    int nPrevPerson;    // If the stakeholder changed, who was it before this?
};

///////////////////////////
///////////////////////////
// END STAKEHOLDER STUFF //
///////////////////////////
///////////////////////////

/*
struct SystemModel
{
  SystemModel()
  {
    nCost = 0;
    nWeight = 0;
    nMaxWeight = 0;
    nEqSlots = 0;
    nDevTime = 0;
    
    nDesc[0] = 0;
    
    for (int i = 0; i < MAX_SYSTEM_ATTS; i++)
      nSystemAtts[i] = 0;
      
    nSonicDef = 0;
    nImpactDef = 0;
    nFireDef = 0;
    nExplosiveDef = 0;
    nEMPDef = 0;
    nNuclearDef = 0;
  };
  
  int nCost;
  char nDesc[2048];
  
  int nWeight;
  // Means different things on diff systems, for arms this is max carrying, 
  // for legs this is max total robot weight, for head this is max weight of
  // armor and sensors, etc.
  int nMaxWeight;  
  int nEqSlots;
  int nDevTime; // Development time, in 'turns'
  
  // The system-specific attributes, like in a computer
  // system, the hardware specs.  In the torso, the carrying
  // capacity, etc.  In the ejection system, the safety factor.
  int nSystemAtts[MAX_SYSTEM_ATTS];
  
  // Attacks
  
  
  // Defenses
  int nSonicDef;
  int nImpactDef;
  int nFireDef;
  int nExplosiveDef;
  int nEMPDef;
  int nNuclearDef;*/