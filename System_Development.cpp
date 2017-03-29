
#include "ProjectRobot.h"
#include "System_Models.h"
#include "System_Development.h"
#include "PopupWindow.h"

extern Stakeholder stakeholder[NUM_STAKEHOLDERS];

// From Screen_SystemDesign.cpp
extern Robot *g_pTheRobot;
extern System *g_pCurrentSystem;
extern int g_nSystemSelected;
extern int g_nModelShownOnScreen;

extern int g_nSystemParamsX;
extern int g_nSystemParamsY;
extern int g_nSystemParamsRightBound;

// This keeps track of where some of the buttons are for our drawing and button movement.
// It is transient.
int g_nTempPlusButtonID = 0;
int g_nTempSwitchButtonID = 0;

int g_nEqSlotToSwitch = -1;
int g_nEqTypeToSwitch = -1; // Armor, accessory, etc?

// This struct exists so that we can use the draw functions to
// also locate which variables are associated with which plus or
// switch buttons
struct VarFinder
{
  VarFinder()
  {
    nType = 0;
    nCount = 0;
    nIndexOfVar = 0;
  };

  int nType;  // Plus, switch?
  int nCount; // Current count of how many values we've looked at
  int nIndexOfVar; // What the count should equal when we've found our variable
};

VarFinder *pVF = 0;

// Helper functions for the VarFinder
bool CheckForPlusVar()
{
  bool retv = false;
  if (pVF && pVF->nType == 0)
  {
    if (pVF->nCount == pVF->nIndexOfVar)
      retv = true;
    pVF->nCount++;
  }  
  return retv;
}

bool CheckForSwitchVar()
{
  bool retv = false;
  if (pVF && pVF->nType == 1)
  {
    if (pVF->nCount == pVF->nIndexOfVar)
      retv = true;
    pVF->nCount++;
  }  
  return retv;
}

// Just a quicker way to draw the text, change the font, etc.
// Defaults to font 6.
int PrintParamText(char *text, int x, int y, GameFont *gf = 0)
{
  // If we have a VarFinder we don't want to draw anything
  if (pVF) {
    return y;
  }
  GameFont *DrawFont = gf;
  if (!gf)
  {
    DrawFont = GameFont6;
  }
  int newy = DrawFont->DrawBoundedText(wObj.getBackHDC(), text, x, g_nSystemParamsRightBound, y);
  return newy + 2;
}

int GetParamTextWidth(char *text)
{
  return GameFont6->GetTextWidth(text);
}

// Hide all the plus buttons when we select a new system 
void HideAllSystemImprovementButtons()
{  
  for (int i = BUTTON_PLUS_1; i <= MAX_PLUS_BUTTON; i++)
  {
    buttons[i]->HideButton();
  }
  for (i = BUTTON_SWITCH_1; i <= MAX_SWITCH_BUTTON; i++)
  {
    buttons[i]->HideButton();
  }
}
  

// Place a plus button at these coordinates, show it if it isn't already visible
void PlacePlusButtonHere(int x, int y, bool bShow = true)
{
  // Do nothing if we have a VarFinder
  if (pVF) {
    return;
  }

  if (bShow == false)
  {   
    buttons[g_nTempPlusButtonID]->HideButton();
  }
  else
  {
    System *pSys = g_pTheRobot->GetSystemByType(g_nSystemSelected);
    if (pSys->GetPlusButtonPress(g_nTempPlusButtonID - BUTTON_PLUS_1) <= 0)
    {
      buttons[g_nTempPlusButtonID]->ShowButton();
    }
    else
    {
      buttons[g_nTempPlusButtonID]->HideButton();
    }
  }

  buttons[g_nTempPlusButtonID]->MoveButton(x, y);
  g_nTempPlusButtonID++;
}

// Place a switch button at these coordinates, show it if it isn't already visible
void PlaceSwitchButtonHere(int x, int y)
{
  // Do nothing if we have a VarFinder
  if (pVF) {
    return;
  }

  // Using the GameButton functions ensures that this button
  // doesn't redraw if it doesn't have to - ShowButton only shows
  // if it isn't visible already
  buttons[g_nTempSwitchButtonID]->ShowButton();
  buttons[g_nTempSwitchButtonID]->MoveButton(x, y);
  g_nTempSwitchButtonID++;
}

// Some parameters are common to all systems, this draws them
int DrawCommonParameters(System *pTheSystem, int nYPos = 0)
{
  int x = g_nSystemParamsX;
  int y = g_nSystemParamsY;

  // You don't have to include YPos; if you don't, it just defaults
  // to the system params y.  But if you need to position it differently
  // just include the y in the system parameters.
  if (nYPos > 0)
    y = nYPos;

  // If it's not fully integrated yet, the time left before it's integrated
  if (pTheSystem->GetDevTimeLeft() > 0) {
    sprintf(buff, "Development Time: %s", GET_DEV_TIME_TEXT(pTheSystem->GetDevTimeLeft()));
    y = PrintParamText(buff, x, y);
    return 0;
  }

  y = PrintParamText("Development Time: Completed", x, y);

  // Non-changeable specs such as a total cost, total weight (base + armor + accessories)
  // and accessory slots used up
  sprintf(buff, "Total Cost: %d", pTheSystem->GetTotalCost());
  y = PrintParamText(buff, x, y);

  sprintf(buff, "Total Weight: %d", pTheSystem->GetSystemWeight());
  y = PrintParamText(buff, x, y);

  return y;
}

// For all items affected by contractor efficiency
void DetermineResCost(int nCode, int &nRes, char *strCostText, bool bPrintCostText)
{
  if (bPrintCostText)
    strCostText[0] = 0;

  Stakeholder *pContr = &stakeholder[STAKEHOLDER_CONTRACTOR];
  switch (nCode)
  {
    case COST_CODE_FRAME:
    case COST_CODE_HEAD:
    case COST_CODE_TORSO:
    case COST_CODE_ARM:
    case COST_CODE_LEG:
    case COST_CODE_EJECTION:
    case COST_CODE_COOLING:
    case COST_CODE_COMPUTER:
    case COST_CODE_HUMAN_INTERFACE:
    case COST_CODE_GUNS:
    case COST_CODE_MELEE:
    case COST_CODE_ARMOR:
    case COST_CODE_SENSORS:
    {
      // We can do this since the other codes are added at the end,
      // so the beginning codes match up to the EFF_X enum
      if (pContr->GetEfficiency(nCode))
      {
        nRes++; // If it's odd, make it even then divide, if it's even, doesn't matter because it'll round
        nRes/=2;
        //if (bPrintCostText)
          //strcat(strCostText, "x0.5");
      }
      else if (pContr->GetDeficiency(nCode))
      {
        float fNum = (float)nRes;
        fNum*=1.5;
        nRes = (int)fNum;
        //if (bPrintCostText)
          //strcat(strCostText, "x1.5");
      }
      break;
    }
    case COST_CODE_INTERFACES:
    {
      if (pContr->GetDeficiency(EFF_INTERFACES))
      {
        nRes++;
      }
      break;
    }
    case COST_CODE_ARMOR_PLUS:
    {
      if (pContr->GetDeficiency(EFF_ARMOR))
      {
        nRes++;
      }
      break;
    }
  };

  if (nRes <= 0)
    nRes = 1;

  // If it is a quarter that people are on vacation, all costs are doubled
  if (stakeholder[STAKEHOLDER_SUPERVISOR].IsVacationMonth(theGame.GetTurn()))
  {
    if (bPrintCostText)
    {
      if (strCostText[0])
      {
        strcat(strCostText, ", x2");
      }
      else
      {
        strcat(strCostText, "x2");
      }
    }
    nRes *= 2;
  }

  // Surround it by parentheses if we have it
  if (bPrintCostText && strCostText[0])
  {
    char temp[256];
    sprintf(temp, " %s", strCostText);
    sprintf(strCostText, "%s", temp);
  }
}

// For items that have increased improvement based on efficiency
void DetermineResCostAndImprovement(int nCode, int &nRes, int &nImprove)
{
  Stakeholder *pContr = &stakeholder[STAKEHOLDER_CONTRACTOR];
  switch (nCode)
  {
    case COST_CODE_ARMOR_PLUS:
    {
      if (pContr->GetEfficiency(EFF_ARMOR))
      {
        nImprove++;
      }
      break;
    }
    case COST_CODE_INTERFACES:
    {
      if (pContr->GetEfficiency(EFF_INTERFACES))
      {
        nImprove++;
      }
      break;
    }
  };
  DetermineResCost(nCode, nRes);
}

// Interfaces are common to all systems
int DrawInterfaces(int nXPos, int nYPos, System *pTheSystem)
{
  int x = nXPos;
  int y = nYPos;

  y = PrintParamText("Interface confidence levels:", x, y);
  x += 20;
  for (int i = 0; i < NUM_INTERFACES; i++)
  {
    if (pTheSystem->HasInterface(i))
    {
      bool bShowButton = true;
      if (pTheSystem->GetInterfaceValue(i) == INTERFACE_LEVELS-1)
        bShowButton = false;

      PlacePlusButtonHere(x + 175, y - 2, bShowButton);

      if (CheckForPlusVar())
      {
        int nRes = 1;
        int nImprove = 1;
        DetermineResCostAndImprovement(COST_CODE_INTERFACES, nRes, nImprove);
        if (theGame.GetResources() >= nRes)
        {
          if (stakeholder[STAKEHOLDER_DEVELOPER].HasIntegrationExpForSystem(pTheSystem->GetSystemType()))
            nImprove++;

          if (pTheSystem->ImproveInterface(i, nImprove))
          {
            theGame.SubResources(nRes);
            pTheSystem->AddTotalCost(nRes);
          }
        }
        else
        {
          ShowPopup(CANNOT_AFFORD);
        } 
      }
  
      sprintf(buff, "%s: ", GET_INTERFACE_TEXT(i));
      PrintParamText(buff, x, y);

      y = PrintParamText(GET_INTERFACE_LVL_TEXT(pTheSystem->GetInterfaceValue(i)), x + 195, y);
    }
  }

  return y;
}

// Some systems have common armor
int DrawArmorValues(int nXPos, int nYPos, SystemWithArmor *pTheSystem)
{
  int x = nXPos;
  int y = nYPos;

  // Check to see if we clicked on the switch armor type button
  if (CheckForSwitchVar())
  {
    g_nEqSlotToSwitch = 0;
    g_nEqTypeToSwitch = SWITCH_TYPE_ARMOR;
  }

  // First draw the armor type
  sprintf(buff, "Armor Type: %s", GET_ARMOR_TYPE_TEXT(pTheSystem->GetArmorType()));  

  PlaceSwitchButtonHere(x + GetParamTextWidth(buff) + 10, y - 2);
  y = PrintParamText(buff, x, y);

  if (pTheSystem->GetArmorType() == ARMOR_NONE)
    return y;

  y = PrintParamText("Armor Attributes:", x, y);
  x += 20;
  for (int i = ARMOR_VALUE_WEIGHT; i < NUM_ARMOR_VALUES; i++)
  {
    sprintf(buff, "%s: ", GET_ARMOR_VALUE_TEXT(i));
    PrintParamText(buff, x, y);
    
    PlacePlusButtonHere(x + 230, y - 2);
    
    if (CheckForPlusVar())
    {
      int nRes = 1;
      int nImprove = 2;
      DetermineResCostAndImprovement(COST_CODE_ARMOR_PLUS, nRes, nImprove);
      if (theGame.GetResources() > nRes) 
      {
        pTheSystem->AddArmorValue(i, nImprove);
        theGame.SubResources(nRes);
        pTheSystem->AddTotalCost(nRes);
      }
      else
      {
        ShowPopup(CANNOT_AFFORD);
      } 
    }

    // Print the value to the right of the actual text so it lines up
    sprintf(buff, "%d : %s", pTheSystem->GetArmorValue(i), TranslateValueToText(pTheSystem->GetArmorValue(i)));
    y = PrintParamText(buff, x + 250, y);
  }

  return y;
}

// Some systems have common accessories
int DrawAccessories(int nXPos, int nYPos, System *pTheSystem)
{
  int x = nXPos;
  int y = nYPos;

  if (pTheSystem->GetEqSlots() <= 0)
    return y;

  y = PrintParamText("Equipment:", x, y);
  x += 20;
  for (int i = 0; i < pTheSystem->GetEqSlots(); i++)
  {
    sprintf(buff, "Slot %d:", i);
    PrintParamText(buff, x, y);

    // We print the equipment to the right of the Slot X:  text
    // so that it is lined up
    int nEqDrawX = x + 80;

    // If we're looking for which variable coincides with a switch button,
    // check for it
    if (CheckForSwitchVar())
    {
      g_nEqSlotToSwitch = i;
      g_nEqTypeToSwitch = SWITCH_TYPE_ACCESSORY;
    }

    if (pTheSystem->GetEq(i)) 
    {
      int nType = pTheSystem->GetEq(i)->GetType();
      int nModel = pTheSystem->GetEq(i)->GetModel();

      buff[0] = 0;
      switch (nType)
      {
        case ACC_TYPE_ACC:
          sprintf(buff, "%s", GET_ACC_TYPE_TEXT(nModel));
          break;
        case ACC_TYPE_GUN:
          sprintf(buff, "%s", GET_GUN_TYPE_TEXT(nModel));
          break;
        case ACC_TYPE_MELEE:
          sprintf(buff, "%s", GET_MELEE_TYPE_TEXT(nModel));
          break;
      }

      PlaceSwitchButtonHere(nEqDrawX + GetParamTextWidth(buff) + 10, y - 2);
      y = PrintParamText(buff, nEqDrawX, y);
    } 
    else 
    {  
      sprintf(buff, "None", i);
      PlaceSwitchButtonHere(nEqDrawX + GetParamTextWidth(buff) + 10, y - 2);
      y = PrintParamText(buff, nEqDrawX, y);
    }
  }

  return y;
}

void DrawFrameParameters(int nYPos = 0)
{
  // We should probably draw the default stuff that the frame has here, like restrictions,
  // base weight, etc.
}

void DrawHeadParameters(int nYPos = 0)
{
  Head *pThisSystem = g_pTheRobot->GetHead();

  int x = g_nSystemParamsX;
  int y = nYPos;

  if ((y = DrawCommonParameters(pThisSystem, y)) == 0)
    return;

  // Armor
  y = DrawArmorValues(x, y, pThisSystem);

  // Accessories in each slot
  y = DrawAccessories(x, y, pThisSystem);

  // Interfaces
  y = DrawInterfaces(x, y, pThisSystem);
}

void DrawTorsoParameters(int nYPos = 0)
{
  Torso *pThisSystem = g_pTheRobot->GetTorso();

  int x = g_nSystemParamsX;
  int y = nYPos;

  if ((y = DrawCommonParameters(pThisSystem, y)) == 0)
    return;

  // Armor
  y = DrawArmorValues(x, y, pThisSystem);

  // Accessories in each slot
  y = DrawAccessories(x, y, pThisSystem);
  
  // Interfaces
  y = DrawInterfaces(x, y, pThisSystem);
}

void DrawArmParameters(int nArmSystem, int nYPos = 0)
{
  Arm *pThisSystem = 0;

  if (nArmSystem == SYSTEM_ARM_RIGHT)
    pThisSystem = g_pTheRobot->GetRightArm();
  else
    pThisSystem = g_pTheRobot->GetLeftArm();

  int x = g_nSystemParamsX;
  int y = nYPos;

  if ((y = DrawCommonParameters(pThisSystem, y)) == 0)
    return;

  // Armor
  y = DrawArmorValues(x, y, pThisSystem);

  // Accessories in each slot
  y = DrawAccessories(x, y, pThisSystem);
  
  // Interfaces
  y = DrawInterfaces(x, y, pThisSystem);
}

void DrawLegParameters(int nLegSystem, int nYPos = 0)
{
  Leg *pThisSystem = 0;

  if (nLegSystem == SYSTEM_LEG_RIGHT)
    pThisSystem = g_pTheRobot->GetRightLeg();
  else
    pThisSystem = g_pTheRobot->GetLeftLeg();

  int x = g_nSystemParamsX;
  int y = nYPos;

  if ((y = DrawCommonParameters(pThisSystem, y)) == 0)
    return;

  // Armor
  y = DrawArmorValues(x, y, pThisSystem);

  // Accessories in each slot
  y = DrawAccessories(x, y, pThisSystem);

  // Interfaces
  y = DrawInterfaces(x, y, pThisSystem);
}

void DrawEjectionParameters(int nYPos = 0)
{
  EjectionSystem *pThisSystem = g_pTheRobot->GetEjectionSystem();

  int x = g_nSystemParamsX;
  int y = nYPos;

  if ((y = DrawCommonParameters(pThisSystem, y)) == 0)
    return;

  
  // Interfaces
  y = DrawInterfaces(x, y, pThisSystem);
}

void DrawCoolingParameters(int nYPos = 0)
{
  CoolingSystem *pThisSystem = g_pTheRobot->GetCoolingSystem();

  int x = g_nSystemParamsX;
  int y = nYPos;

  if ((y = DrawCommonParameters(pThisSystem, y)) == 0)
    return;

  char text[1024];
  
  int nModel = pThisSystem->GetSystemModel();

  sprintf(text, "Base Cooling: %d", GetCoolingSystemValue(nModel, COOL_VALUE_HEAT_REDUCE));
  y = PrintParamText(text, x, y);

  sprintf(text, "Heat Sink Cost: %d", GetCoolingSystemValue(nModel, COOL_VALUE_HEAT_SINK_COST));
  y = PrintParamText(text, x, y);

  sprintf(text, "Heat Sink Cooling: %d", GetCoolingSystemValue(nModel, COOL_VALUE_HEAT_SINK_REDUCE));
  y = PrintParamText(text, x, y);

  sprintf(text, "Heat Sink Power Need: %d", GetCoolingSystemValue(nModel, COOL_VALUE_HEAT_SINK_POWER_COST));
  y = PrintParamText(text, x, y);

  sprintf(text, "Heat Sink Weight: %d", GetCoolingSystemValue(nModel, COOL_VALUE_HEAT_SINK_WEIGHT));
  y = PrintParamText(text, x, y);
  
  // Interfaces
  y = DrawInterfaces(x, y, pThisSystem);
}

void DrawComputerParameters(int nYPos = 0)
{
  ComputerSystem *pThisSystem = g_pTheRobot->GetComputerSystem();

  int x = g_nSystemParamsX;
  int y = nYPos;

  if ((y = DrawCommonParameters(pThisSystem, y)) == 0)
    return;

  
  // Interfaces
  y = DrawInterfaces(x, y, pThisSystem);
}

void DrawHumanInterfaceParameters(int nYPos = 0)
{
  HumanInterface *pThisSystem = g_pTheRobot->GetHumanInterface();

  int x = g_nSystemParamsX;
  int y = nYPos;

  if ((y = DrawCommonParameters(pThisSystem, y)) == 0)
    return;


  // Interfaces
  y = DrawInterfaces(x, y, pThisSystem);
}

// Go through and draw the parameters of the system we have selected
void DrawSelectedSystemParameters(int y)
{
  if (g_pCurrentSystem == false)
  {
    return;
  }

  // If we don't have a model selected for this system, we draw nothing
  if (g_pCurrentSystem->GetSystemModel() <= 0)
    return;

  g_nTempPlusButtonID = BUTTON_PLUS_1;
  g_nTempSwitchButtonID = BUTTON_SWITCH_1;

  switch (g_nSystemSelected)
  {
    case SYSTEM_FRAME:
      DrawFrameParameters(y);
      break;
    case SYSTEM_HEAD:
      DrawHeadParameters(y);
      break;
    case SYSTEM_TORSO:
      DrawTorsoParameters(y);
      break;
    case SYSTEM_ARM_RIGHT:
      DrawArmParameters(SYSTEM_ARM_RIGHT, y);
      break;
    case SYSTEM_ARM_LEFT:
      DrawArmParameters(SYSTEM_ARM_LEFT, y);
      break;
    case SYSTEM_LEG_RIGHT:
      DrawLegParameters(SYSTEM_LEG_RIGHT, y);
      break;
    case SYSTEM_LEG_LEFT:
      DrawLegParameters(SYSTEM_LEG_LEFT, y);
      break;
    case SYSTEM_EJECTION:
      DrawEjectionParameters(y);
      break;
    case SYSTEM_COOLING:
      DrawCoolingParameters(y);
      break;
    case SYSTEM_COMPUTER:
      DrawComputerParameters(y);
      break;
    case SYSTEM_HUMAN_INTERFACE:
      DrawHumanInterfaceParameters(y);
      break;
  }
}

// Improve a single parameter of the selected system
void ImproveOrChangeSystemParameter(int wmId, int nType)
{
  int nIndex = 0;
  
  if (nType == 0) 
    nIndex = wmId - BUTTON_PLUS_1;
  else
    nIndex = wmId - BUTTON_SWITCH_1;

  // Create a VarFinder struct, set its data and go forth
  pVF = new VarFinder();
  
  pVF->nIndexOfVar = nIndex;
  pVF->nType = nType;
  
  // Since we set the VarFinder, this doesn't actually
  // draw anything, it simply uses the draw functions to find
  // which variable this plus button goes along with, and
  // increments it accordingly
  switch (g_nSystemSelected)
  {
    case SYSTEM_FRAME:
      DrawFrameParameters();
      break;
    case SYSTEM_HEAD:
      DrawHeadParameters();
      break;
    case SYSTEM_TORSO:
      DrawTorsoParameters();
      break;
    case SYSTEM_ARM_RIGHT:
      DrawArmParameters(SYSTEM_ARM_RIGHT);
      break;
    case SYSTEM_ARM_LEFT:
      DrawArmParameters(SYSTEM_ARM_LEFT);
      break;
    case SYSTEM_LEG_RIGHT:
      DrawLegParameters(SYSTEM_LEG_RIGHT);
      break;
    case SYSTEM_LEG_LEFT:
      DrawLegParameters(SYSTEM_LEG_LEFT);
      break;
    case SYSTEM_EJECTION:
      DrawEjectionParameters();
      break;
    case SYSTEM_COOLING:
      DrawCoolingParameters();
      break;
    case SYSTEM_COMPUTER:
      DrawComputerParameters();
      break;
    case SYSTEM_HUMAN_INTERFACE:
      DrawHumanInterfaceParameters();
      break;
  }

  // And delete it when we're done
  delete pVF;
  pVF = 0;

  // If we're switching, we should have found an
  // eq slot in the code above, so we then load up
  // the little switch screen
  if (nType == 1)
  {
    // nEqSlotToSwitch is the current slot
    ChangeScreen(SCREEN_CHANGE_SUB_SYSTEM);
  }
}


void SetPlusButtonState(int wmId)
{
  System *pSys = g_pTheRobot->GetSystemByType(g_nSystemSelected);
  
  pSys->AddPlusButtonPress(wmId - BUTTON_PLUS_1); 
  buttons[wmId]->HideButton();
}

// The system improvement buttons get passed off to here, like
// the plus buttons, etc.
void HandleSystemImprovementButtons(int wmId)
{
  // Handle pluses here
  if (wmId >= BUTTON_PLUS_1 && wmId <= MAX_PLUS_BUTTON) 
  {
    objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_6);
    ImproveOrChangeSystemParameter(wmId, 0);
    SetPlusButtonState(wmId);
    return;
  }
  
  if (wmId >= BUTTON_SWITCH_1 && wmId <= MAX_SWITCH_BUTTON)
  {
    objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_6);
    ImproveOrChangeSystemParameter(wmId, 1);
    return;
  }

  // Handle other buttons here
  /*switch (wmId)
  {
    

  }*/
}