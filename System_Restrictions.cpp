/*

  What restrictions do each of the sub-systems have based on other system
  choices

*/

#include "ProjectRobot.h"
#include "System_Models.h"

extern Stakeholder stakeholder[NUM_STAKEHOLDERS];
extern void GetModelNameBySystem(int nSystem, int nModel, char *strName);

// Get all system pointers through our handy macro, we don't need them all but this
// makes it a lot easier to code
#define GET_ALL_SYSTEM_POINTERS() \
   Frame *pFrame = g_pTheRobot->GetFrame(); \
   Head *pHead = g_pTheRobot->GetHead();    \
   Torso *pTorso = g_pTheRobot->GetTorso(); \
   Arm *pRightArm = g_pTheRobot->GetRightArm(); \
   Arm *pLeftArm = g_pTheRobot->GetLeftArm(); \
   Leg *pRightLeg = g_pTheRobot->GetRightLeg(); \
   Leg *pLeftLeg = g_pTheRobot->GetLeftLeg(); \
   CoolingSystem *pCoolingSystem = g_pTheRobot->GetCoolingSystem(); \
   ComputerSystem *pComputerSystem = g_pTheRobot->GetComputerSystem(); \
   EjectionSystem *pEjectionSystem = g_pTheRobot->GetEjectionSystem(); \
   HumanInterface *pHumanInterface = g_pTheRobot->GetHumanInterface(); 

// From Screen_SystemDesign.cpp
extern Robot *g_pTheRobot;

/////////////////////////////
/////// BEGIN CLASS /////////
/////////////////////////////
enum
{
  RESTRICT_MODEL,
  RESTRICT_ACC,
  RESTRICT_GUN,
  RESTRICT_MELEE,
  RESTRICT_ARMOR,
  NUM_RESTRICTS
};

// If restrict type is model, we use RestrictedSystem and RestrictedModel as the var
// If not, we ignore the system, and only use RestrictedVar to set one of the restricted values
class SystemRestriction : public LinkedList
{
  public:
    SystemRestriction(int nThisRestrictType, int nThisSysType, int nThisModel, int nNewRestrictedSystem, int nNewRestrictedItem)
    {
      nRestrictType = nThisRestrictType;
      nSystemType = nThisSysType;
      nModel = nThisModel;
      nRestrictedSystem = nNewRestrictedSystem;
      nRestrictedItem = nNewRestrictedItem;

      LinkedList::SetClassPointer(this);
    };
  
    void AddRestriction(int nRestrictType, int nThisModel, int nRestrictedSystem, int nRestrictedItem);
    void AddModelRestriction(int nThisModel, int nRestrictedSystem, int nRestrictedModel);
    void AddAccRestriction(int nThisModel, int nRestrictedItem);
    void AddGunRestriction(int nThisModel, int nRestrictedItem);
    void AddMeleeRestriction(int nThisModel, int nRestrictedItem);
    void AddArmorRestriction(int nThisModel, int nRestrictedItem);
  
    // strRes is the system and model doing the restricting
    bool RestrictsModel(int nThisSystemType, int nThisModel, int nCheckThisSystem, int nCheckThisModel, char *strRes)
    {
      strRes[0] = 0;

      if (nRestrictType == RESTRICT_MODEL && nThisSystemType == nSystemType && nThisModel == nModel && 
          nCheckThisSystem == nRestrictedSystem && nCheckThisModel == nRestrictedItem)
      {
        GetModelNameBySystem(this->nSystemType, this->nModel, strRes);
        return true;
      }
      return false;
    };
  
    bool RestrictsAcc(int nThisSystemType, int nThisModel, int nCheckThisItem, char *strRes)
    {
      strRes[0] = 0;

      if (nRestrictType == RESTRICT_ACC && nThisSystemType == nSystemType && nThisModel == nModel && 
          nCheckThisItem == nRestrictedItem)
      {
        GetModelNameBySystem(this->nSystemType, this->nModel, strRes);
        return true;
      }
      return false;
    };
    
    bool RestrictsGun(int nThisSystemType, int nThisModel, int nCheckThisItem, char *strRes)
    {
      strRes[0] = 0;

      if (nRestrictType == RESTRICT_GUN && nThisSystemType == nSystemType && nThisModel == nModel && 
          nCheckThisItem == nRestrictedItem)
      {
        GetModelNameBySystem(this->nSystemType, this->nModel, strRes);
        return true;
      }
      return false;
    };
    
    bool RestrictsMelee(int nThisSystemType, int nThisModel, int nCheckThisItem, char *strRes)
    {
      strRes[0] = 0;

      if (nRestrictType == RESTRICT_MELEE && nThisSystemType == nSystemType && nThisModel == nModel && 
          nCheckThisItem == nRestrictedItem)
      {
        GetModelNameBySystem(this->nSystemType, this->nModel, strRes);
        return true;
      }
      return false;
    };

    bool RestrictsArmor(int nThisSystemType, int nThisModel, int nCheckThisItem, char *strRes)
    {
      strRes[0] = 0;

      if (nRestrictType == RESTRICT_ARMOR && nThisSystemType == nSystemType && nThisModel == nModel && 
          nCheckThisItem == nRestrictedItem)
      {
        GetModelNameBySystem(this->nSystemType, this->nModel, strRes);
        return true;
      }
      return false;
    };
    
    // Sometimes we don't need the system type, like if we're indexing an array so we already know what
    // the system type is since the array slot is the system type
    bool RestrictsModel(int nThisModel, int nCheckThisSystem, int nCheckThisModel, char *strRes)
    {
      return RestrictsModel(nSystemType, nThisModel, nCheckThisSystem, nCheckThisModel, strRes);
    };
    
    bool RestrictsAcc(int nThisModel, int nCheckThisItem, char *strRes = 0)   { return RestrictsAcc(nSystemType, nThisModel, nCheckThisItem, strRes); };    
    bool RestrictsGun(int nThisModel, int nCheckThisItem, char *strRes = 0)   { return RestrictsGun(nSystemType, nThisModel, nCheckThisItem, strRes); };
    bool RestrictsMelee(int nThisModel, int nCheckThisItem, char *strRes = 0) { return RestrictsMelee(nSystemType, nThisModel, nCheckThisItem, strRes); };
    bool RestrictsArmor(int nThisModel, int nCheckThisItem, char *strRes = 0) { return RestrictsArmor(nSystemType, nThisModel, nCheckThisItem, strRes); };
    
  private:
  
    // Type of this system restriction, what system is doing the restricting
    int nSystemType;
    
    // Type of restriction, is it based on a model, an accessory, gun, etc.
    int nRestrictType;
    
    // The model of the system that is doing the restricting
    int nModel;
    
    // What system type this restriction "restricts" or -1 for gun/acc/melee
    int nRestrictedSystem;
    
    // The system model that this restriction "restricts" or the gun, acc, or melee depending on restrict type
    int nRestrictedItem;
};

// Generic, RestrictedSystem is not used for some items like accessories, guns, melee
void SystemRestriction::AddRestriction(int nRestrictType, int nThisModel, int nRestrictedSystem, int nRestrictedItem)
{
  SystemRestriction *NewRestr = new SystemRestriction(nRestrictType, this->nSystemType, nThisModel, nRestrictedSystem, nRestrictedItem);
  this->AddToBack(NewRestr);
}

void SystemRestriction::AddModelRestriction(int nThisModel, int nRestrictedSystem, int nRestrictedModel)
{
  this->AddRestriction(RESTRICT_MODEL, nThisModel, nRestrictedSystem, nRestrictedModel);
  
  // If they were left or right arms or legs we duplicate on both
  if (nRestrictedSystem == SYSTEM_LEG_RIGHT)
  {
    this->AddRestriction(RESTRICT_MODEL, nThisModel, SYSTEM_LEG_LEFT, nRestrictedModel);
  }
  if (nRestrictedSystem == SYSTEM_LEG_LEFT)
  {
    this->AddRestriction(RESTRICT_MODEL, nThisModel, SYSTEM_LEG_RIGHT, nRestrictedModel);
  }
  if (nRestrictedSystem == SYSTEM_ARM_RIGHT)
  {
    this->AddRestriction(RESTRICT_MODEL, nThisModel, SYSTEM_ARM_LEFT, nRestrictedModel);
  }
  if (nRestrictedSystem == SYSTEM_ARM_LEFT)
  {
    this->AddRestriction(RESTRICT_MODEL, nThisModel, SYSTEM_ARM_RIGHT, nRestrictedModel);
  }
}

void SystemRestriction::AddAccRestriction(int nThisModel, int nRestrictedItem)
{
  this->AddRestriction(RESTRICT_ACC, nThisModel, this->nSystemType, nRestrictedItem);
}

void SystemRestriction::AddGunRestriction(int nThisModel, int nRestrictedItem)
{
  this->AddRestriction(RESTRICT_GUN, nThisModel, this->nSystemType, nRestrictedItem);
}

void SystemRestriction::AddMeleeRestriction(int nThisModel, int nRestrictedItem)
{
  this->AddRestriction(RESTRICT_MELEE, nThisModel, this->nSystemType, nRestrictedItem);
}

void SystemRestriction::AddArmorRestriction(int nThisModel, int nRestrictedItem)
{
  this->AddRestriction(RESTRICT_ARMOR, nThisModel, this->nSystemType, nRestrictedItem);
}
/////////////////////////////
//////// END CLASS //////////
/////////////////////////////

class SystemRestriction *SysRestricts[NUM_SYSTEMS];

void SetupSystemRestrictions()
{
  int i = 0, j = 0;
  
  for (i = 0; i < NUM_SYSTEMS; i++)
  {
    SysRestricts[i] = new SystemRestriction(-1, i, -1, -1, -1);
  }
  
  // Model restrictions, if you have a certain system model you may not be able to
  // get other system models
  SystemRestriction *pSysRest = SysRestricts[SYSTEM_FRAME];
  pSysRest->AddModelRestriction(FRAME_TANK, SYSTEM_LEG_RIGHT, LEG_STALKER);
  pSysRest->AddModelRestriction(FRAME_TANK, SYSTEM_LEG_RIGHT, LEG_STRIDER);
  pSysRest->AddModelRestriction(FRAME_TANK, SYSTEM_LEG_RIGHT, LEG_OLYMPIAN);
  pSysRest->AddModelRestriction(FRAME_TANK, SYSTEM_LEG_RIGHT, LEG_LEAPFROG);
  pSysRest->AddModelRestriction(FRAME_TANK, SYSTEM_LEG_RIGHT, LEG_HOPPER);
  pSysRest->AddModelRestriction(FRAME_TANK, SYSTEM_LEG_RIGHT, LEG_DASHER);
  pSysRest->AddModelRestriction(FRAME_TANK, SYSTEM_LEG_RIGHT, LEG_WALKER);

  // Accessory restrictions, these work differently; if you try to put one on a 
  // system model that doesn't allow it, you can't use it.  But you might be able to use
  // it on another system model.  But in terms of how this file uses them they are added
  // the same way as model restrictions.
  
  // Heads, torsos, legs get no melee weapons
  for (i = 0; i < NUM_MELEES; i++)
  { 
    for (j = 0; j < NUM_HEADS; j++)
      SysRestricts[SYSTEM_HEAD]->AddMeleeRestriction(j, i);
    for (j = 0; j < NUM_TORSOS; j++)
      SysRestricts[SYSTEM_TORSO]->AddMeleeRestriction(j, i);
    for (j = 0; j < NUM_LEGS; j++)
      SysRestricts[SYSTEM_LEG_RIGHT]->AddMeleeRestriction(j, i);
  }
  
  // Certain guns are only usable by the arms, restrict these
  for (i = 0; i < NUM_GUNS; i++)
  { 
    if (i == GUN_DRAGON_CANNON || i == GUN_SONIC_RIFLE || i == GUN_ENERGY_RIFLE || i == GUN_ENERGY_BLASTER ||
        i == GUN_PLASMA_CANNON)
    {
      for (j = 0; j < NUM_HEADS; j++)
        SysRestricts[SYSTEM_HEAD]->AddGunRestriction(j, i);
      for (j = 0; j < NUM_TORSOS; j++)
        SysRestricts[SYSTEM_TORSO]->AddGunRestriction(j, i);
      for (j = 0; j < NUM_LEGS; j++)
        SysRestricts[SYSTEM_LEG_RIGHT]->AddGunRestriction(j, i);
    }

    // Worker torso cannot use weapons
    SysRestricts[SYSTEM_TORSO]->AddGunRestriction(TORSO_WORKER, i);
  }
  
  // Missile pack is for torso only
  for (j = 0; j < NUM_HEADS; j++)
    SysRestricts[SYSTEM_HEAD]->AddGunRestriction(j, GUN_MISSILE_PACK);
  for (j = 0; j < NUM_ARMS; j++)
    SysRestricts[SYSTEM_ARM_RIGHT]->AddGunRestriction(j, GUN_MISSILE_PACK);
  for (j = 0; j < NUM_LEGS; j++)
    SysRestricts[SYSTEM_LEG_RIGHT]->AddGunRestriction(j, GUN_MISSILE_PACK);
    
  // Arms can only use weapons and heat sinks
  for (j = 0; j < NUM_ARMS; j++)
  {
    int nSys = SYSTEM_ARM_RIGHT;
    SysRestricts[nSys]->AddAccRestriction(j, ACC_SENSOR_CAMERA);
    SysRestricts[nSys]->AddAccRestriction(j, ACC_SENSOR_AUDIO);
    SysRestricts[nSys]->AddAccRestriction(j, ACC_SENSOR_INFRARED);
    SysRestricts[nSys]->AddAccRestriction(j, ACC_SENSOR_HEAT);
    SysRestricts[nSys]->AddAccRestriction(j, ACC_SENSOR_MOVEMENT);
    SysRestricts[nSys]->AddAccRestriction(j, ACC_SENSOR_RADAR);
    SysRestricts[nSys]->AddAccRestriction(j, ACC_SENSOR_OMNI);
    SysRestricts[nSys]->AddAccRestriction(j, ACC_SER_DEFENSE);
    SysRestricts[nSys]->AddAccRestriction(j, ACC_MAGNETIC_DEFLECTOR);
  }
  
  // Worker torso cannot use weapons
  SysRestricts[SYSTEM_TORSO]->AddGunRestriction(TORSO_WORKER, ACC_GUN);

  // Worker torso gets some armor restrictions
  SysRestricts[SYSTEM_TORSO]->AddArmorRestriction(TORSO_WORKER, ARMOR_HEAVY);
  SysRestricts[SYSTEM_TORSO]->AddArmorRestriction(TORSO_WORKER, ARMOR_FLAK);
}

bool DoesSystemRestrictModel(int nThisSystemType, int nThisModel, int nCheckThisSystem, int nCheckThisModel, char *strRes)
{ 
  SystemRestriction *pSysRest = SysRestricts[nThisSystemType];
  
  while (pSysRest)
  {
    if (pSysRest->RestrictsModel(nThisModel, nCheckThisSystem, nCheckThisModel, strRes))
      return true;
    pSysRest = (SystemRestriction*)pSysRest->GetNext();
  }
  return false;
}

bool DoesSystemRestrictEquipment(int nEqType, int nThisSystemType, int nThisModel, int nCheckThisItem, char *strRes)
{ 
  SystemRestriction *pSysRest = SysRestricts[nThisSystemType];
  
  while (pSysRest)
  {
    if (nEqType == ACC_TYPE_ACC) {
      if (pSysRest->RestrictsAcc(nThisModel, nCheckThisItem, strRes))
        return true; 
    } else if (nEqType == ACC_TYPE_GUN) {
      if (pSysRest->RestrictsGun(nThisModel, nCheckThisItem, strRes))
        return true;
    } else if (nEqType == ACC_TYPE_MELEE) {
      if (pSysRest->RestrictsMelee(nThisModel, nCheckThisItem, strRes))
        return true;
    }

    pSysRest = (SystemRestriction*)pSysRest->GetNext();
  }
  return false;
}

bool DoesSystemRestrictAcc(int nThisSystemType, int nThisModel, int nCheckThisItem, char *strRes)
{ 
  return DoesSystemRestrictEquipment(ACC_TYPE_ACC, nThisSystemType, nThisModel, nCheckThisItem, strRes);
}

bool DoesSystemRestrictGun(int nThisSystemType, int nThisModel, int nCheckThisItem, char *strRes)
{ 
  return DoesSystemRestrictEquipment(ACC_TYPE_GUN, nThisSystemType, nThisModel, nCheckThisItem, strRes);
}

bool DoesSystemRestrictMelee(int nThisSystemType, int nThisModel, int nCheckThisItem, char *strRes)
{ 
  return DoesSystemRestrictEquipment(ACC_TYPE_MELEE, nThisSystemType, nThisModel, nCheckThisItem, strRes);
}

bool DoesSystemRestrictArmor(int nThisSystemType, int nThisModel, int nCheckThisItem, char *strRes)
{ 
  SystemRestriction *pSysRest = SysRestricts[nThisSystemType];

  while (pSysRest)
  {
    if (pSysRest->RestrictsArmor(nThisModel, nCheckThisItem, strRes))
      return true;
    pSysRest = (SystemRestriction*)pSysRest->GetNext();
  }
  return false;
}

bool IsEquipmentRestrictedByCurrentRobot(int nEqType, int nCheckThisSystemType, int nCheckThisItem, char *strRes)
{
  GET_ALL_SYSTEM_POINTERS();
   
  if (nCheckThisSystemType == SYSTEM_FRAME && 
      DoesSystemRestrictEquipment(nEqType, nCheckThisSystemType, pFrame->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_HEAD && 
      DoesSystemRestrictEquipment(nEqType, nCheckThisSystemType, pHead->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_TORSO && 
      DoesSystemRestrictEquipment(nEqType, nCheckThisSystemType, pTorso->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_ARM_RIGHT && 
      DoesSystemRestrictEquipment(nEqType, nCheckThisSystemType, pRightArm->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_ARM_LEFT && 
      DoesSystemRestrictEquipment(nEqType, nCheckThisSystemType, pLeftArm->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_LEG_RIGHT && 
      DoesSystemRestrictEquipment(nEqType, nCheckThisSystemType, pRightLeg->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_LEG_LEFT && 
      DoesSystemRestrictEquipment(nEqType, nCheckThisSystemType, pLeftLeg->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_COOLING && 
      DoesSystemRestrictEquipment(nEqType, nCheckThisSystemType, pCoolingSystem->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_COMPUTER && 
      DoesSystemRestrictEquipment(nEqType, nCheckThisSystemType, pComputerSystem->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_EJECTION && 
      DoesSystemRestrictEquipment(nEqType, nCheckThisSystemType, pEjectionSystem->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_HUMAN_INTERFACE && 
      DoesSystemRestrictEquipment(nEqType, nCheckThisSystemType, pHumanInterface->GetSystemModel(), nCheckThisItem, strRes))
    return true;

  return false;
}

bool IsAccRestrictedByCurrentRobot(int nCheckThisSystemType, int nCheckThisItem, char *strRes)
{
  return IsEquipmentRestrictedByCurrentRobot(ACC_TYPE_ACC, nCheckThisSystemType, nCheckThisItem, strRes);
}

bool IsGunRestrictedByCurrentRobot(int nCheckThisSystemType, int nCheckThisItem, char *strRes)
{
  return IsEquipmentRestrictedByCurrentRobot(ACC_TYPE_GUN, nCheckThisSystemType, nCheckThisItem, strRes);
}

bool IsMeleeRestrictedByCurrentRobot(int nCheckThisSystemType, int nCheckThisItem, char *strRes)
{
  return IsEquipmentRestrictedByCurrentRobot(ACC_TYPE_MELEE, nCheckThisSystemType, nCheckThisItem, strRes);
}

bool IsArmorRestrictedByCurrentRobot(int nCheckThisSystemType, int nCheckThisItem, char *strRes)
{
  GET_ALL_SYSTEM_POINTERS();
   
  if (nCheckThisSystemType == SYSTEM_FRAME && 
      DoesSystemRestrictArmor(nCheckThisSystemType, pFrame->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_HEAD && 
      DoesSystemRestrictArmor(nCheckThisSystemType, pHead->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_TORSO && 
      DoesSystemRestrictArmor(nCheckThisSystemType, pTorso->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_ARM_RIGHT && 
      DoesSystemRestrictArmor(nCheckThisSystemType, pRightArm->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_ARM_LEFT && 
      DoesSystemRestrictArmor(nCheckThisSystemType, pLeftArm->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_LEG_RIGHT && 
      DoesSystemRestrictArmor(nCheckThisSystemType, pRightLeg->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_LEG_LEFT && 
      DoesSystemRestrictArmor(nCheckThisSystemType, pLeftLeg->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_COOLING && 
      DoesSystemRestrictArmor(nCheckThisSystemType, pCoolingSystem->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_COMPUTER && 
      DoesSystemRestrictArmor(nCheckThisSystemType, pComputerSystem->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_EJECTION && 
      DoesSystemRestrictArmor(nCheckThisSystemType, pEjectionSystem->GetSystemModel(), nCheckThisItem, strRes))
    return true;
  if (nCheckThisSystemType == SYSTEM_HUMAN_INTERFACE && 
      DoesSystemRestrictArmor(nCheckThisSystemType, pHumanInterface->GetSystemModel(), nCheckThisItem, strRes))
    return true;

  return false;
}

bool IsModelRestrictedByCurrentRobot(int nCheckThisSystemType, int nCheckThisModel, char *strRes)
{
  GET_ALL_SYSTEM_POINTERS();
   
  if (DoesSystemRestrictModel(SYSTEM_FRAME, pFrame->GetSystemModel(), nCheckThisSystemType, nCheckThisModel, strRes))
    return true;
  if (DoesSystemRestrictModel(SYSTEM_HEAD, pHead->GetSystemModel(), nCheckThisSystemType, nCheckThisModel, strRes))
    return true;
  if (DoesSystemRestrictModel(SYSTEM_TORSO, pTorso->GetSystemModel(), nCheckThisSystemType, nCheckThisModel, strRes))
    return true;
  if (DoesSystemRestrictModel(SYSTEM_ARM_RIGHT, pRightArm->GetSystemModel(), nCheckThisSystemType, nCheckThisModel, strRes))
    return true;
  if (DoesSystemRestrictModel(SYSTEM_ARM_LEFT, pLeftArm->GetSystemModel(), nCheckThisSystemType, nCheckThisModel, strRes))
    return true;
  if (DoesSystemRestrictModel(SYSTEM_LEG_RIGHT, pRightLeg->GetSystemModel(), nCheckThisSystemType, nCheckThisModel, strRes))
    return true;
  if (DoesSystemRestrictModel(SYSTEM_LEG_LEFT, pLeftLeg->GetSystemModel(), nCheckThisSystemType, nCheckThisModel, strRes))
    return true;
  if (DoesSystemRestrictModel(SYSTEM_COOLING, pCoolingSystem->GetSystemModel(), nCheckThisSystemType, nCheckThisModel, strRes))
    return true;
  if (DoesSystemRestrictModel(SYSTEM_COMPUTER, pComputerSystem->GetSystemModel(), nCheckThisSystemType, nCheckThisModel, strRes))
    return true;
  if (DoesSystemRestrictModel(SYSTEM_EJECTION, pEjectionSystem->GetSystemModel(), nCheckThisSystemType, nCheckThisModel, strRes))
    return true;
  if (DoesSystemRestrictModel(SYSTEM_HUMAN_INTERFACE, pHumanInterface->GetSystemModel(), nCheckThisSystemType, nCheckThisModel, strRes))
    return true;

  return false;
}

