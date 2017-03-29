
#include "ProjectRobot.h"
#include "System_Models.h"
#include "Screen_SystemDesign.h"
#include "System_Restrictions.h"
#include "System_Development.h"
#include "PopupWindow.h"
#include "SubScreen.h"

extern Robot *g_pTheRobot;
extern System *g_pCurrentSystem;

// Right now this isn't really anything except for a container
// for a button list.  It could be much much more.
SubScreen *pSubScreen = 0;

// From stakeholder screen, this works here too
extern void ToggleSelectedButtonImage(int nButtonID);

extern int PrintParamText(char *text, int x, int y, GameFont *gf = 0);
extern void RecalculateTotalSystemParams();

extern int g_nEqSlotToSwitch;
extern int g_nEqTypeToSwitch;

// Locals
int g_nChangeSubSystemPanelX = 0;
int g_nChangeSubSystemPanelY = 0;

// Which piece of eq did we click on on the screen
int g_nNewEqSelected = DEFAULT_NEG_ONE;

void UntoggleAllSubSystemButtons()
{
  for (int i = BUTTON_SUBSYSTEM_1; i < MAX_SUBSYSTEM_BUTTON; i++)
    buttons[i]->SetBackFrames(0, 1);
}

void StartChangeSubSystemScreen()
{
  // Just disable them
  DisableAllButtons();

  g_nChangeSubSystemPanelX = wObj.Wid()/2 - sprites[SPRITE_END_TURN_PANEL]->Wid()/2;
  g_nChangeSubSystemPanelY = wObj.Hgt()/2 - sprites[SPRITE_END_TURN_PANEL]->Hgt()/2;

  g_nNewEqSelected = DEFAULT_NEG_ONE;

  buttons[BUTTON_OK]->ShowButton();
  buttons[BUTTON_OK]->EnableButton();
  buttons[BUTTON_OK]->MoveButton(
      wObj.Wid()/2 - buttons[BUTTON_OK]->GetWidth()/2 - 100,
      g_nChangeSubSystemPanelY + sprites[SPRITE_END_TURN_PANEL]->Hgt() - buttons[BUTTON_OK]->GetHeight() - 18);
  
  buttons[BUTTON_CANCEL]->ShowButton();
  buttons[BUTTON_CANCEL]->EnableButton();
  buttons[BUTTON_CANCEL]->MoveButton(
      wObj.Wid()/2 - buttons[BUTTON_CANCEL]->GetWidth()/2 + 100,
      buttons[BUTTON_OK]->GetY());
  
  int x = g_nChangeSubSystemPanelX + 25;
  int y = g_nChangeSubSystemPanelY + 35;
  int nLineHeight = 15;

  // Reset all the frames in case we toggled earlier
  UntoggleAllSubSystemButtons();

  int i = 0;

  // Hide all the buttons too
  for (i = BUTTON_SUBSYSTEM_1; i <= MAX_SUBSYSTEM_BUTTON; i++)
  {
    buttons[i]->HideButton();
  }

  // So if it's armor, we display the armor type buttons
  if (g_nEqTypeToSwitch == SWITCH_TYPE_ARMOR)
  {
    for (i = 0; i < NUM_ARMOR_TYPES; i++)
    {
      buttons[i + BUTTON_SUBSYSTEM_1]->SetButtonText(GET_ARMOR_TYPE_TEXT(i));
      buttons[i + BUTTON_SUBSYSTEM_1]->MoveButton(x, y);
      buttons[i + BUTTON_SUBSYSTEM_1]->EnableButton();
      buttons[i + BUTTON_SUBSYSTEM_1]->ShowButton();
      y += nLineHeight;
    }
  }
  // If it's an accessory we display the accessory/gun/melee buttons
  else if (g_nEqTypeToSwitch == SWITCH_TYPE_ACCESSORY)
  {
    int nButtonID = BUTTON_SUBSYSTEM_1;
    for (i = 0; i < NUM_ACCS; i++)
    {
      buttons[nButtonID]->SetButtonText(GET_ACC_TYPE_TEXT(i));
      buttons[nButtonID]->MoveButton(x, y);
      buttons[nButtonID]->EnableButton();
      buttons[nButtonID]->ShowButton();
      nButtonID++;
      y += nLineHeight;
    }

    // We move the rest of the buttons so that we can use them for positioning,
    // even though they aren't displayed on screen.  This is important only if
    // the user enters the Close Combat Weapons screen without first entering
    // the gun screen.
    for (i = NUM_ACCS; i < NUM_GUNS; i++)
    {
      buttons[nButtonID]->MoveButton(x, y);
      nButtonID++;
      y += nLineHeight;
    }
  }
  else if (g_nEqTypeToSwitch == SWITCH_TYPE_GUN)
  {
    int nButtonID = BUTTON_SUBSYSTEM_1;
    for (i = 1; i < NUM_GUNS; i++)
    {
      buttons[nButtonID]->SetButtonText(GET_GUN_TYPE_TEXT(i));
      buttons[nButtonID]->MoveButton(x, y);
      buttons[nButtonID]->EnableButton();
      buttons[nButtonID]->ShowButton();
      nButtonID++;
      y += nLineHeight;
    }
  }
  else if (g_nEqTypeToSwitch == SWITCH_TYPE_MELEE)
  {
    int nButtonID = BUTTON_SUBSYSTEM_1;
    for (i = 1; i < NUM_MELEES; i++)
    {
      buttons[nButtonID]->SetButtonText(GET_MELEE_TYPE_TEXT(i));
      buttons[nButtonID]->MoveButton(x, y);
      buttons[nButtonID]->EnableButton();
      buttons[nButtonID]->ShowButton();
      nButtonID++;
      y += nLineHeight;
    }

    // We move the rest of the buttons so that we can use them for positioning,
    // even though they aren't displayed on screen.  This is important only if
    // the user enters the Close Combat Weapons screen without first entering
    // the gun screen.
    for (i = NUM_MELEES; i < NUM_GUNS; i++)
    {
      buttons[nButtonID]->MoveButton(x, y);
      nButtonID++;
      y += nLineHeight;
    }
  } 

  // Set up the subscreen which is really just a button list
  // right now
  if (pSubScreen)
  {
    delete pSubScreen;
  }

  pSubScreen = new SubScreen();

  pSubScreen->AddButton(buttons[BUTTON_OK]);
  pSubScreen->AddButton(buttons[BUTTON_CANCEL]);
  for (i = BUTTON_SUBSYSTEM_1; i <= MAX_SUBSYSTEM_BUTTON; i++)
  {
    pSubScreen->AddButton(buttons[i]);
  }
  // End subscreen setup
}


void RestartSubSystemScreen(int nNewType)
{
  g_nNewEqSelected = DEFAULT_NEG_ONE;

  g_nEqTypeToSwitch = nNewType;

  StartChangeSubSystemScreen();
}

bool CanChooseHeatSink()
{
  CoolingSystem *pCoolingSystem = g_pTheRobot->GetCoolingSystem();
  if (!pCoolingSystem || pCoolingSystem->GetSystemModel() == COOLING_NONE)
  { 
    ShowPopup("You cannot select a heat sink without first selecting a Cooling System!");
    return false;
  }
  return true;
}

int GetHeatSinkReduceForTheRobot()
{
  int nNum = 0;

  CoolingSystem *pCoolingSystem = g_pTheRobot->GetCoolingSystem();
  nNum = GetCoolingSystemValue(pCoolingSystem->GetSystemModel(), COOL_VALUE_HEAT_SINK_REDUCE);

  return nNum;
}


int GetHeatSinkCostForTheRobot()
{
  int nCost = 0;

  CoolingSystem *pCoolingSystem = g_pTheRobot->GetCoolingSystem();
  nCost = GetCoolingSystemValue(pCoolingSystem->GetSystemModel(), COOL_VALUE_HEAT_SINK_COST);

  DetermineResCost(COST_CODE_COOLING, nCost);

  return nCost;
}

int GetHeatSinkPowerCostForTheRobot()
{
  int nNum = 0;

  CoolingSystem *pCoolingSystem = g_pTheRobot->GetCoolingSystem();
  nNum = GetCoolingSystemValue(pCoolingSystem->GetSystemModel(), COOL_VALUE_HEAT_SINK_POWER_COST);

  return nNum;
}

int GetHeatSinkWeightForTheRobot()
{
  int nNum = 0;

  CoolingSystem *pCoolingSystem = g_pTheRobot->GetCoolingSystem();
  nNum = GetCoolingSystemValue(pCoolingSystem->GetSystemModel(), COOL_VALUE_HEAT_SINK_WEIGHT);

  return nNum;
}

bool IsSensorModel(int nEqModel)
{
  if (nEqModel >= ACC_SENSOR_CAMERA && 
      nEqModel <= ACC_SENSOR_OMNI)
    return true;

  return false;
}

bool CanChooseSensor()
{
  ComputerSystem *pComputerSystem = g_pTheRobot->GetComputerSystem();
  if (!pComputerSystem || pComputerSystem->GetSystemModel() == COMPUTER_NONE)
  { 
    ShowPopup("You cannot select a sensor without first selecting a Computer System!");
    return false;
  }
  return true;
}

int GetSensorCost(int nSensorType, int nSystemModel)
{
  int nCost = 0;

  if (nSystemModel == COMPUTER_NONE)
    return 0;

  switch (nSensorType)
  {
    case ACC_SENSOR_CAMERA:
      nCost = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_CAMERA_COST);
      break;
    case ACC_SENSOR_AUDIO:
      nCost = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_AUDIO_COST);
      break;
    case ACC_SENSOR_INFRARED:
      nCost = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_INFRARED_COST);
      break;
    case ACC_SENSOR_HEAT:
      nCost = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_HEAT_COST);
      break;
    case ACC_SENSOR_MOVEMENT:
      nCost = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_MOVEMENT_COST);
      break;
    case ACC_SENSOR_RADAR:
      nCost = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_RADAR_COST);
      break;
    case ACC_SENSOR_OMNI:
      nCost = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_OMNI_COST);
      break;
  }

  DetermineResCost(COST_CODE_SENSORS, nCost);

  return nCost;
}

int GetSensorCostForTheRobot(int nSensorType)
{
  int nNum = 0;

  ComputerSystem *pComputerSystem = g_pTheRobot->GetComputerSystem();
  if (!pComputerSystem)
    return 0;

  return GetSensorCost(nSensorType, pComputerSystem->GetSystemModel());
}

int GetSensorWeight(int nSensorType, int nSystemModel)
{
  int nNum = 0;

  if (nSystemModel == COMPUTER_NONE)
    return 0;

  switch (nSensorType)
  {
    case ACC_SENSOR_CAMERA:
      nNum = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_CAMERA_WEIGHT);
      break;
    case ACC_SENSOR_AUDIO:
      nNum = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_AUDIO_WEIGHT);
      break;
    case ACC_SENSOR_INFRARED:
      nNum = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_INFRARED_WEIGHT);
      break;
    case ACC_SENSOR_HEAT:
      nNum = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_HEAT_WEIGHT);
      break;
    case ACC_SENSOR_MOVEMENT:
      nNum = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_MOVEMENT_WEIGHT);
      break;
    case ACC_SENSOR_RADAR:
      nNum = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_RADAR_WEIGHT);
      break;
    case ACC_SENSOR_OMNI:
      nNum = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_OMNI_WEIGHT);
      break;
  }

  return nNum;
}

int GetSensorWeightForTheRobot(int nSensorType)
{
  int nNum = 0;

  ComputerSystem *pComputerSystem = g_pTheRobot->GetComputerSystem();
  if (!pComputerSystem)
    return 0;

  return GetSensorWeight(nSensorType, pComputerSystem->GetSystemModel());
}


int GetSensorPowerCost(int nSensorType, int nSystemModel)
{
  int nNum = 0;

  if (nSystemModel == COMPUTER_NONE)
    return 0;

  switch (nSensorType)
  {
    case ACC_SENSOR_CAMERA:
      nNum = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_CAMERA_POWER_COST);
      break;
    case ACC_SENSOR_AUDIO:
      nNum = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_AUDIO_POWER_COST);
      break;
    case ACC_SENSOR_INFRARED:
      nNum = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_INFRARED_POWER_COST);
      break;
    case ACC_SENSOR_HEAT:
      nNum = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_HEAT_POWER_COST);
      break;
    case ACC_SENSOR_MOVEMENT:
      nNum = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_MOVEMENT_POWER_COST);
      break;
    case ACC_SENSOR_RADAR:
      nNum = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_RADAR_POWER_COST);
      break;
    case ACC_SENSOR_OMNI:
      nNum = GetComputerSystemIntValue(nSystemModel, COMP_VALUE_OMNI_POWER_COST);
      break;
  }

  return nNum;
}

int GetSensorPowerCostForTheRobot(int nSensorType)
{
  int nNum = 0;

  ComputerSystem *pComputerSystem = g_pTheRobot->GetComputerSystem();
  if (!pComputerSystem)
    return 0;

  return GetSensorPowerCost(nSensorType, pComputerSystem->GetSystemModel());
}

// This just uses the default acc value for now unless I want to change it, but I have it
// here for the sake of consistency and maintainance
int GetSensorHeatCost(int nSensorType, int nSystemModel)
{
  if (nSystemModel == COMPUTER_NONE)
    return 0;

  int nNum = GetDefaultAccValue(nSensorType, ACC_VALUE_HEAT_COST);
  switch (nSensorType)
  {
    case ACC_SENSOR_CAMERA:
      break;
    case ACC_SENSOR_AUDIO:
      break;
    case ACC_SENSOR_INFRARED:
      break;
    case ACC_SENSOR_HEAT:
      break;
    case ACC_SENSOR_MOVEMENT:
      break;
    case ACC_SENSOR_RADAR:
      break;
    case ACC_SENSOR_OMNI:
      break;
  }

  return nNum;
}

int GetSensorHeatCostForTheRobot(int nSensorType)
{
  int nNum = 0;

  ComputerSystem *pComputerSystem = g_pTheRobot->GetComputerSystem();
  if (!pComputerSystem)
    return 0;

  return GetSensorHeatCost(nSensorType, pComputerSystem->GetSystemModel());
}


// So an example is GetSensorValue(ACC_SENSOR_CAMERA, ACC_VALUE_SIGHT)
// this can actually be used for any value, like ACC_VALUE_WEIGHT
int GetSensorValue(int nSensorType, int nAccValueNum, int nSystemModel)
{
  if (nSystemModel == COMPUTER_NONE)
    return 0;

  // Get the default which is then multiplied by the computer system value for 
  // each sensor type
  double fAccValue = (double)GetDefaultAccValue(nSensorType, nAccValueNum);

  // If we're not looking for a sensing value, we get one of the other values or
  // or return the default from the table
  if (nAccValueNum < ACC_VALUE_SIGHT || nAccValueNum > ACC_VALUE_MOTION_SENSOR)
  {
    if (nAccValueNum == ACC_VALUE_COST)
      return GetSensorCost(nSensorType, nSystemModel);
    else if (nAccValueNum == ACC_VALUE_WEIGHT)
      return GetSensorWeight(nSensorType, nSystemModel);
    else if (nAccValueNum == ACC_VALUE_POWER_COST)
      return GetSensorPowerCost(nSensorType, nSystemModel);
    else if (nAccValueNum == ACC_VALUE_HEAT_COST)
      return GetSensorHeatCost(nSensorType, nSystemModel);

    return (int)fAccValue;
  }

  switch (nSensorType)
  {
    case ACC_SENSOR_CAMERA:
      fAccValue *= GetComputerSystemDoubleValue(nSystemModel, COMP_VALUE_CAMERA_VALUE);
      break;
    case ACC_SENSOR_AUDIO:
      fAccValue *= GetComputerSystemDoubleValue(nSystemModel, COMP_VALUE_AUDIO_VALUE);
      break;
    case ACC_SENSOR_INFRARED:
      fAccValue *= GetComputerSystemDoubleValue(nSystemModel, COMP_VALUE_INFRARED_VALUE);
      break;
    case ACC_SENSOR_HEAT:
      fAccValue *= GetComputerSystemDoubleValue(nSystemModel, COMP_VALUE_HEAT_VALUE);
      break;
    case ACC_SENSOR_MOVEMENT:
      fAccValue *= GetComputerSystemDoubleValue(nSystemModel, COMP_VALUE_MOVEMENT_VALUE);
      break;
    case ACC_SENSOR_RADAR:
      fAccValue *= GetComputerSystemDoubleValue(nSystemModel, COMP_VALUE_RADAR_VALUE);
      break;
    case ACC_SENSOR_OMNI:
      fAccValue *= GetComputerSystemDoubleValue(nSystemModel, COMP_VALUE_OMNI_VALUE);
      break;
  }

  return (int)fAccValue;
}

int GetSensorValueForTheRobot(int nSensorType, int nAccValueNum)
{
  int nNum = 0;

  ComputerSystem *pComputerSystem = g_pTheRobot->GetComputerSystem();
  if (!pComputerSystem)
    return 0;

  return GetSensorValue(nSensorType, nAccValueNum, pComputerSystem->GetSystemModel());
}

void PrintSensorValueString(char *text, int nSensorType, int nValueNum)
{
  sprintf(text, "???");

  if (!g_pTheRobot->GetComputerSystem() || g_pTheRobot->GetComputerSystem()->GetSystemModel() == COMPUTER_NONE)
    return;

  sprintf(text, "%d", GetSensorValueForTheRobot(nSensorType, nValueNum));
}

void OKChangeSubSystemScreen()
{
  // If we don't have anything selected just go back
  // to the system design screen
  if (g_nNewEqSelected == DEFAULT_NEG_ONE)
  {
    ChangeScreen(SCREEN_SYSTEM_DESIGN);
    return;
  }

  int nResources = theGame.GetResources();

  switch (g_nEqTypeToSwitch)
  {
    case SWITCH_TYPE_ARMOR:
    {
      if (g_pCurrentSystem->GetArmorType() == g_nNewEqSelected)
        break;

      char strRes[256];
      strRes[0] = 0;
      if (IsArmorRestrictedByCurrentRobot(g_pCurrentSystem->GetSystemType(), g_nNewEqSelected, strRes))
      {
        // TODO - message box here?  Or play a "beep" noise to say you can't do it?
        if (strRes[0])
          sprintf(buff, "This armor type is restricted by %s.", strRes);
        else
          sprintf(buff, "This armor type is restricted by other components of your Robot.");
        ShowPopup(buff);
        return;
      }

      int nCost = ArmorTypes[g_nNewEqSelected].nCost;
      DetermineResCost(COST_CODE_ARMOR, nCost);
      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      
      theGame.SubResources(nCost);

      // This sets the type and resets all the values
      g_pCurrentSystem->SetArmorType(g_nNewEqSelected);
      break;
    }

    case SWITCH_TYPE_ACCESSORY:
    { 
      if (g_pCurrentSystem->HasThisEqInThisSlot(g_nEqSlotToSwitch, ACC_TYPE_ACC, g_nNewEqSelected))
        break;

      if (IsAccRestrictedByCurrentRobot(g_pCurrentSystem->GetSystemType(), g_nNewEqSelected, buff))
      {
        // TODO - Play a "beep" noise to say you can't do it?
        ShowPopup("This accessory is restricted by other components of your Robot.");
        return;
      }

      int nCost = AccTypes[g_nNewEqSelected].nCost;
      if (IsSensorModel(g_nNewEqSelected))
      {
        if (!CanChooseSensor())
          return;

        nCost = GetSensorCostForTheRobot(g_nNewEqSelected);
      }

      // Heat sinks base cost on cooling system
      if (g_nNewEqSelected == ACC_HEAT_SINK)
      {
        if (!CanChooseHeatSink())
          return;

        nCost = GetHeatSinkCostForTheRobot();
      } 

      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      
      theGame.SubResources(nCost);
      g_pCurrentSystem->ChangeEq(g_nEqSlotToSwitch, ACC_TYPE_ACC, g_nNewEqSelected);

      // If it's a heat sink, we need to change the weight based on cooling system.  Otherwise
      // the weight is selected based on the correct default value for the accessory.  But
      // since heat sinks vary based on cooling system we need to address that here.
      if (g_nNewEqSelected == ACC_HEAT_SINK)
      {
        Accessory *pEq = g_pCurrentSystem->GetEq(g_nEqSlotToSwitch);
        if (pEq && g_pTheRobot->GetCoolingSystem())
        {
          int nVal = GetCoolingSystemValue(
            g_pTheRobot->GetCoolingSystem()->GetSystemModel(), COOL_VALUE_HEAT_SINK_WEIGHT);
          pEq->SetWeight(nVal);
        }
      }
      // Same with sensors, they base weight on computer system
      else if (IsSensorModel(g_nNewEqSelected))
      {
        Accessory *pEq = g_pCurrentSystem->GetEq(g_nEqSlotToSwitch);
        if (pEq && g_pTheRobot->GetComputerSystem())
        {
          int nVal = 
            GetSensorWeightForTheRobot(g_nNewEqSelected);
          pEq->SetWeight(nVal);
        }
      }
      break;
    }

    case SWITCH_TYPE_GUN:
    {
      if (g_pCurrentSystem->HasThisEqInThisSlot(g_nEqSlotToSwitch, ACC_TYPE_GUN, g_nNewEqSelected))
        break;

      if (IsGunRestrictedByCurrentRobot(g_pCurrentSystem->GetSystemType(), g_nNewEqSelected, buff))
      {
        // TODO - message box here?  Or play a "beep" noise to say you can't do it?
        ShowPopup("This long range weapon is restricted by other components of your Robot.");
        return;
      }

      int nCost = GunTypes[g_nNewEqSelected].nCost;
      DetermineResCost(COST_CODE_GUNS, nCost);
      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      
      theGame.SubResources(nCost);

      g_pCurrentSystem->ChangeEq(g_nEqSlotToSwitch, ACC_TYPE_GUN, g_nNewEqSelected);
      break;
    }

    case SWITCH_TYPE_MELEE:
    { 
      if (g_pCurrentSystem->HasThisEqInThisSlot(g_nEqSlotToSwitch, ACC_TYPE_MELEE, g_nNewEqSelected))
        break;

      if (IsMeleeRestrictedByCurrentRobot(g_pCurrentSystem->GetSystemType(), g_nNewEqSelected, buff))
      {
        // TODO - message box here?  Or play a "beep" noise to say you can't do it?
        ShowPopup("This close range weapon is restricted by other components of your Robot.");
        return;
      }

      int nCost = MeleeTypes[g_nNewEqSelected].nCost;
      DetermineResCost(COST_CODE_MELEE, nCost);
      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      
      theGame.SubResources(nCost);

      g_pCurrentSystem->ChangeEq(g_nEqSlotToSwitch, ACC_TYPE_MELEE, g_nNewEqSelected);
      break;
    }
  }

  // Now update the total system params
  RecalculateTotalSystemParams();

  ChangeScreen(SCREEN_SYSTEM_DESIGN);
}

void BackChangeSubSystemScreen()
{
  if (g_nEqTypeToSwitch == SWITCH_TYPE_GUN || 
      g_nEqTypeToSwitch == SWITCH_TYPE_MELEE)
  {
    RestartSubSystemScreen(SWITCH_TYPE_ACCESSORY);
    return;
  }

  ChangeScreen(SCREEN_SYSTEM_DESIGN);
}

void SwitchSubSystem(int wmId)
{
  UntoggleAllSubSystemButtons();
  ToggleSelectedButtonImage(wmId);

  int nSelected = wmId - BUTTON_SUBSYSTEM_1;

  g_nNewEqSelected = nSelected;

  // Gun and Melee don't display the zeroth value,
  // which is "None" so we need to do a +1 here
  if (g_nEqTypeToSwitch == SWITCH_TYPE_GUN ||
      g_nEqTypeToSwitch == SWITCH_TYPE_MELEE)
    g_nNewEqSelected++;

  // If we hit the "gun" or "melee" button from accessory screen,
  // switch to one of the other types
  if (g_nEqTypeToSwitch == SWITCH_TYPE_ACCESSORY)
  {
    if (g_nNewEqSelected == ACC_GUN)
    {
      RestartSubSystemScreen(SWITCH_TYPE_GUN);
      return;
    }
    else if (g_nNewEqSelected == ACC_MELEE)
    {
      RestartSubSystemScreen(SWITCH_TYPE_MELEE);
      return;
    }
  }
}

// Button handler for Change Subsystem screen
void HandleButtonChangeSubSystem(int wmId)
{
  if (wmId >= BUTTON_SUBSYSTEM_1 && wmId <= MAX_SUBSYSTEM_BUTTON)
  {
    objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_4);
    SwitchSubSystem(wmId);
    return;
  }

  switch (wmId)
  {
    // Show the info screen variation
    case BUTTON_OK:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2);
      OKChangeSubSystemScreen();
      break;
    }
    case BUTTON_CANCEL:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2);
      BackChangeSubSystemScreen();
      break;
    }
  }
}

void DrawChangeSubSystemScreen()
{
  // Start by drawing the underlying screen, then we draw this screen
  DrawSystemDesignScreen();

  sprites[SPRITE_END_TURN_PANEL]->DrawFrame(wObj.getBackHDC(), FRAME_ZERO, g_nChangeSubSystemPanelX, g_nChangeSubSystemPanelY);
  
  int x = g_nChangeSubSystemPanelX;
  int nRightBound = g_nChangeSubSystemPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid() - 20;
  int y = g_nChangeSubSystemPanelY + 20;
  int nLineHeight = 15;

  int nBottomBound = 
    g_nChangeSubSystemPanelY + sprites[SPRITE_END_TURN_PANEL]->Hgt() - buttons[BUTTON_OK]->GetHeight() - 25;
  
  int nStartX = x;
  int nStartY = y;

  // So if it's armor, we display the description/parameters of the selected armor type
  if (g_nEqTypeToSwitch == SWITCH_TYPE_ARMOR)
  {
    sprintf(buff, "Select New Armor Type:");
    PrintParamText(buff, x + sprites[SPRITE_END_TURN_PANEL]->Wid()/2 - GameFont6->GetTextWidth(buff)/2, y);

    y = buttons[BUTTON_SUBSYSTEM_1 + NUM_ARMOR_TYPES-1]->GetY();
    y += buttons[BUTTON_SUBSYSTEM_1]->GetHeight();

    x = buttons[BUTTON_SUBSYSTEM_1]->GetX();
    y = PrintParamText("-------------------------------------------", x, y, GameFont7);
  
    nStartY = y;

    for (int i = ARMOR_VALUE_WEIGHT; i < NUM_ARMOR_VALUES; i++)
    {
      if (y >= nBottomBound)
      {
        y = nStartY;
        x += buttons[BUTTON_SUBSYSTEM_1]->GetWidth() + 10;
      }

      sprintf(buff, "%s: ", GET_ARMOR_VALUE_TEXT(i));
      PrintParamText(buff, x, y, GameFont7);
    
      // Print the value to the right of the actual text so it lines up
      sprintf(buff, "%s", TranslateValueToText(GetDefaultArmorValue(g_nNewEqSelected, i)));
      y = PrintParamText(buff, x + 220, y, GameFont8);
    }

    x = buttons[BUTTON_SUBSYSTEM_1]->GetX() + 220;
    y = g_nChangeSubSystemPanelY + 20 + (nLineHeight*4);

    // Now draw resource cost, overheat, power cost
    sprintf(buff, "%s: ", GET_ARMOR_VALUE_TEXT(ARMOR_VALUE_COST));
    y = PrintParamText(buff, x, y, GameFont7);

    int nCost = GetDefaultArmorValue(g_nNewEqSelected, ARMOR_VALUE_COST);
    DetermineResCost(COST_CODE_ARMOR, nCost);
    sprintf(buff, "%d", nCost);
    y = PrintParamText(buff, x, y, GameFont8);
    y+=nLineHeight;
  }
  // If it's an accessory we display the accessory selection
  else if (g_nEqTypeToSwitch == SWITCH_TYPE_ACCESSORY)
  {
    sprintf(buff, "Select New Accessory:");
    PrintParamText(buff, x + sprites[SPRITE_END_TURN_PANEL]->Wid()/2 - GameFont6->GetTextWidth(buff)/2, y);

    y = buttons[BUTTON_SUBSYSTEM_1 + NUM_ACCS]->GetY();
    y += buttons[BUTTON_SUBSYSTEM_1]->GetHeight();

    x = buttons[BUTTON_SUBSYSTEM_1]->GetX();
    y = PrintParamText("-------------------------------------------", x, y, GameFont7);

    nStartY = y;
    for (int i = ACC_VALUE_WEIGHT; i < ACC_VALUE_POWER_COST; i++)
    {
      if (y >= nBottomBound)
      {
        y = nStartY;
        x += 180;
      }

      sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(i));
      PrintParamText(buff, x, y, GameFont7);
    
      // Print the value to the right of the actual text so it lines up
      //sprintf(buff, "%s", TranslateValueToText(GetDefaultAccValue(g_nNewEqSelected, i)));
      if (IsSensorModel(g_nNewEqSelected))
      {
        PrintSensorValueString(buff, g_nNewEqSelected, i);
      }
      else if (g_nNewEqSelected == ACC_HEAT_SINK && i == ACC_VALUE_WEIGHT)
      {
        // Now have to display the heat sink special text
        CoolingSystem *pCoolingSystem = g_pTheRobot->GetCoolingSystem();
        if (pCoolingSystem && pCoolingSystem->GetSystemModel() != COOLING_NONE)
        {
          sprintf(buff, "%d", GetHeatSinkWeightForTheRobot());
        }
        else
        {
          sprintf(buff, "???");
        }
      }
      else
      { 
        sprintf(buff, "%d", GetDefaultAccValue(g_nNewEqSelected, i));
      }
      y = PrintParamText(buff, x + 130, y, GameFont8);
    }

    if (g_nNewEqSelected == ACC_HEAT_SINK)
    {
      sprintf(buff, "Special:");
      y = GameFont7->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound, y);

      // Now have to display the heat sink special text
      CoolingSystem *pCoolingSystem = g_pTheRobot->GetCoolingSystem();
      if (pCoolingSystem && pCoolingSystem->GetSystemModel() != COOLING_NONE)
      {
        sprintf(buff, "+%d Max Cool Need", GetHeatSinkReduceForTheRobot());
        y = PrintParamText(buff, x, y, GameFont8);
      }
      else
      {   
        sprintf(buff, "+?? Max Cool Need");
        y = PrintParamText(buff, x, y, GameFont8);
      }
    }
    else if (g_nNewEqSelected == ACC_SER_DEFENSE)
    {
      sprintf(buff, "Special:");
      GameFont7->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound, y);
      sprintf(buff, "+3 Defense");
      y = PrintParamText(buff, x + 75, y, GameFont8);

      sprintf(buff, "in Sonic, EMP, and Radiation");
      y = GameFont8->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound, y);
    }
    else if (g_nNewEqSelected == ACC_MAGNETIC_DEFLECTOR)
    {
      sprintf(buff, "Special:");
      GameFont7->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound, y);
      sprintf(buff, "+3 Defense");
      y = PrintParamText(buff, x + 75, y, GameFont8);

      sprintf(buff, "in Maneuver, Impact, Stealth");
      y = GameFont8->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound, y);
    }

    x = buttons[BUTTON_SUBSYSTEM_1]->GetX() + 220;
    y = g_nChangeSubSystemPanelY + 20 + (nLineHeight*4);
    
    if (g_nNewEqSelected == ACC_HEAT_SINK)
    {
      // Now have to display the heat sink special text
      CoolingSystem *pCoolingSystem = g_pTheRobot->GetCoolingSystem();
      if (pCoolingSystem && pCoolingSystem->GetSystemModel() != COOLING_NONE)
      {

        sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_COST));
        y = PrintParamText(buff, x, y, GameFont7);
        sprintf(buff, "%d", GetHeatSinkCostForTheRobot());
        y = PrintParamText(buff, x, y, GameFont8);
        y+=nLineHeight;

        sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_HEAT_COST));
        y = PrintParamText(buff, x, y, GameFont7);
        sprintf(buff, "0");
        y = PrintParamText(buff, x, y, GameFont8);
        y+=nLineHeight;
    
        sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_POWER_COST));
        y = PrintParamText(buff, x, y, GameFont7);
        sprintf(buff, "%d", GetHeatSinkPowerCostForTheRobot());
        y = PrintParamText(buff, x, y, GameFont8);
      }
      else
      {
        sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_COST));
        y = PrintParamText(buff, x, y, GameFont7);
        y = PrintParamText("???", x, y, GameFont8);
        y+=nLineHeight;

        sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_HEAT_COST));
        y = PrintParamText(buff, x, y, GameFont7);
        y = PrintParamText("???", x, y, GameFont8);
        y+=nLineHeight;
    
        sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_POWER_COST));
        y = PrintParamText(buff, x, y, GameFont7);
        y = PrintParamText("???", x, y, GameFont8);
      }
    }
    else if (IsSensorModel(g_nNewEqSelected))
    {
      if (g_pTheRobot->GetComputerSystem() && g_pTheRobot->GetComputerSystem()->GetSystemModel() != COOLING_NONE)
      {

        sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_COST));
        y = PrintParamText(buff, x, y, GameFont7);
        sprintf(buff, "%d", GetSensorCostForTheRobot(g_nNewEqSelected));
        y = PrintParamText(buff, x, y, GameFont8);
        y+=nLineHeight;

        sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_HEAT_COST));
        y = PrintParamText(buff, x, y, GameFont7);
        sprintf(buff, "%d", GetSensorHeatCostForTheRobot(g_nNewEqSelected));
        y = PrintParamText(buff, x, y, GameFont8);
        y+=nLineHeight;
    
        sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_POWER_COST));
        y = PrintParamText(buff, x, y, GameFont7);
        sprintf(buff, "%d", GetSensorPowerCostForTheRobot(g_nNewEqSelected));
        y = PrintParamText(buff, x, y, GameFont8);
      }
      else
      {
        sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_COST));
        y = PrintParamText(buff, x, y, GameFont7);
        y = PrintParamText("???", x, y, GameFont8);
        y+=nLineHeight;

        sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_HEAT_COST));
        y = PrintParamText(buff, x, y, GameFont7);
        y = PrintParamText("???", x, y, GameFont8);
        y+=nLineHeight;
    
        sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_POWER_COST));
        y = PrintParamText(buff, x, y, GameFont7);
        y = PrintParamText("???", x, y, GameFont8);
      } 
    } 
    else
    {
      // Now draw resource cost, overheat, power cost
      sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_COST));
      y = PrintParamText(buff, x, y, GameFont7);
      sprintf(buff, "%d", GetDefaultAccValue(g_nNewEqSelected, ACC_VALUE_COST));
      y = PrintParamText(buff, x, y, GameFont8);
      y+=nLineHeight;

      sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_HEAT_COST));
      y = PrintParamText(buff, x, y, GameFont7);
      sprintf(buff, "%d", GetDefaultAccValue(g_nNewEqSelected, ACC_VALUE_HEAT_COST));
      y = PrintParamText(buff, x, y, GameFont8);
      y+=nLineHeight;
    
      sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(ACC_VALUE_POWER_COST));
      y = PrintParamText(buff, x, y, GameFont7);
      sprintf(buff, "%d", GetDefaultAccValue(g_nNewEqSelected, ACC_VALUE_POWER_COST));
      y = PrintParamText(buff, x, y, GameFont8);
    }
  } 
  else if (g_nEqTypeToSwitch == SWITCH_TYPE_GUN)
  {
    sprintf(buff, "Select New Ranged Weapon:");
    PrintParamText(buff, x + sprites[SPRITE_END_TURN_PANEL]->Wid()/2 - GameFont6->GetTextWidth(buff)/2, y);

    y = buttons[BUTTON_SUBSYSTEM_1 + NUM_GUNS-1]->GetY();
    //y += buttons[BUTTON_SUBSYSTEM_1]->GetHeight();

    x = buttons[BUTTON_SUBSYSTEM_1]->GetX();
    y = PrintParamText("-------------------------------------------", x, y, GameFont7);
  
    nStartY = y;
    for (int i = GUN_VALUE_WEIGHT; i < GUN_VALUE_POWER_COST; i++)
    {
      if (y >= nBottomBound)
      {
        y = nStartY;
        x += 180;
      }

      sprintf(buff, "%s: ", GET_GUN_VALUE_TEXT(i));
      PrintParamText(buff, x, y, GameFont7);
    
      // Print the value to the right of the actual text so it lines up
      sprintf(buff, "%s", TranslateValueToText(GetDefaultGunValue(g_nNewEqSelected, i)));
      y = PrintParamText(buff, x + 90, y, GameFont8);
    }

    x = buttons[BUTTON_SUBSYSTEM_1]->GetX() + 220;
    y = g_nChangeSubSystemPanelY + (nLineHeight*4);

    // Now draw resource cost, overheat, power cost
    sprintf(buff, "%s: ", GET_GUN_VALUE_TEXT(GUN_VALUE_COST));
    y = PrintParamText(buff, x, y, GameFont7);
    sprintf(buff, "%d", GetDefaultGunValue(g_nNewEqSelected, GUN_VALUE_COST));
    y = PrintParamText(buff, x, y, GameFont8);
    y+=nLineHeight;

    sprintf(buff, "%s: ", GET_GUN_VALUE_TEXT(GUN_VALUE_HEAT_COST));
    y = PrintParamText(buff, x, y, GameFont7);
    sprintf(buff, "%d", GetDefaultGunValue(g_nNewEqSelected, GUN_VALUE_HEAT_COST));
    y = PrintParamText(buff, x, y, GameFont8);
    y+=nLineHeight;
    
    sprintf(buff, "%s: ", GET_GUN_VALUE_TEXT(GUN_VALUE_POWER_COST));
    y = PrintParamText(buff, x, y, GameFont7);
    sprintf(buff, "%d", GetDefaultGunValue(g_nNewEqSelected, GUN_VALUE_POWER_COST));
    y = PrintParamText(buff, x, y, GameFont8);
    y+=nLineHeight;

    sprintf(buff, "%s: ", GET_GUN_VALUE_TEXT(GUN_VALUE_ENV));
    y = PrintParamText(buff, x, y, GameFont7);
    sprintf(buff, "%d", GetDefaultGunValue(g_nNewEqSelected, GUN_VALUE_ENV));
    y = PrintParamText(buff, x, y, GameFont8);
  } 
  else if (g_nEqTypeToSwitch == SWITCH_TYPE_MELEE)
  {
    sprintf(buff, "Select New Close Combat Weapon:");
    PrintParamText(buff, x + sprites[SPRITE_END_TURN_PANEL]->Wid()/2 - GameFont6->GetTextWidth(buff)/2, y);

    y = buttons[BUTTON_SUBSYSTEM_1 + NUM_GUNS-1]->GetY();
    y += buttons[BUTTON_SUBSYSTEM_1]->GetHeight();

    x = buttons[BUTTON_SUBSYSTEM_1]->GetX();
    y = PrintParamText("-------------------------------------------", x, y, GameFont7);
  
    nStartY = y;

    for (int i = MELEE_VALUE_WEIGHT; i < MELEE_VALUE_POWER_COST; i++)
    {
      if (y >= nBottomBound)
      {
        y = nStartY;
        x += 180;
      }

      sprintf(buff, "%s: ", GET_MELEE_VALUE_TEXT(i));
      PrintParamText(buff, x, y, GameFont7);
    
      // Print the value to the right of the actual text so it lines up
      sprintf(buff, "%s", TranslateValueToText(GetDefaultMeleeValue(g_nNewEqSelected, i)));
      y = PrintParamText(buff, x + 90, y, GameFont8);
    }

    x = buttons[BUTTON_SUBSYSTEM_1]->GetX() + 220;
    y = g_nChangeSubSystemPanelY + 20 + (nLineHeight*4);

    // Now draw resource cost, overheat, power cost
    sprintf(buff, "%s: ", GET_MELEE_VALUE_TEXT(MELEE_VALUE_COST));
    y = PrintParamText(buff, x, y, GameFont7);
    sprintf(buff, "%d", GetDefaultMeleeValue(g_nNewEqSelected, MELEE_VALUE_COST));
    y = PrintParamText(buff, x, y, GameFont8);
    y+=nLineHeight;

    sprintf(buff, "%s: ", GET_MELEE_VALUE_TEXT(MELEE_VALUE_HEAT_COST));
    y = PrintParamText(buff, x, y, GameFont7);
    sprintf(buff, "%d", GetDefaultMeleeValue(g_nNewEqSelected, MELEE_VALUE_HEAT_COST));
    y = PrintParamText(buff, x, y, GameFont8);
    y+=nLineHeight;
    
    sprintf(buff, "%s: ", GET_MELEE_VALUE_TEXT(MELEE_VALUE_POWER_COST));
    y = PrintParamText(buff, x, y, GameFont7);
    sprintf(buff, "%d", GetDefaultMeleeValue(g_nNewEqSelected, MELEE_VALUE_POWER_COST));
    y = PrintParamText(buff, x, y, GameFont8);
  } 

  //DrawEnabledButtons();
  if (pSubScreen)
  {
    pSubScreen->DrawScreen(wObj.getBackHDC());
  }
}