
/*

The System Design screen, this is sort of like the "main" screen -
the user will spend most of his time here.

*/

#include "ProjectRobot.h"
#include "System_Models.h"
#include "ScreenExtras.h"
#include "System_Development.h"
#include "System_Overall.h"
#include "System_Fielded.h"
#include "System_Restrictions.h"
#include "PopupWindow.h"
#include "Screen_Change_SubSystem.h"

extern struct SystemModel *AllSystemModels[NUM_SYSTEMS][MAX_MODELS];
extern void RecalculateTotalSystemParams();

Robot *g_pTheRobot = 0;

System *g_pCurrentSystem = 0; 

// Local
void ChangeSelectedSystem(int nNewSystem);

extern Stakeholder stakeholder[NUM_STAKEHOLDERS];

int g_nSystemSelected = DEFAULT_NEG_ONE;
int g_nModelShownOnScreen = 0;

int g_nSystemDesignX = 0;
int g_nSystemDesignY = 0;
int g_nSystemDesignRightBound = 0;

int g_nSystemParamsX = 0;
int g_nSystemParamsY = 0;
int g_nSystemParamsRightBound = 0;

void InitializeSystemDesignScreen()
{
  g_nSystemSelected = DEFAULT_NEG_ONE;
  g_nModelShownOnScreen = 0;
  g_pCurrentSystem = 0;
}

void StartSystemDesignScreen()
{
  // First hide them all, then show what we want
  HideAndEnableAllButtons();

  buttons[BUTTON_INFO]->ShowButton();
  buttons[BUTTON_HELP]->ShowButton();
  buttons[BUTTON_END]->ShowButton();

  buttons[BUTTON_MODEL]->ShowButton();
  buttons[BUTTON_HEAD]->ShowButton();
  buttons[BUTTON_TORSO]->ShowButton();
  buttons[BUTTON_ARM_RIGHT]->ShowButton();
  buttons[BUTTON_ARM_LEFT]->ShowButton();
  buttons[BUTTON_LEG_RIGHT]->ShowButton();
  buttons[BUTTON_LEG_LEFT]->ShowButton();
  buttons[BUTTON_EJECTION]->ShowButton();
  buttons[BUTTON_COOLING]->ShowButton();
  buttons[BUTTON_COMPUTER]->ShowButton();
  buttons[BUTTON_HUMAN_INTERFACE]->ShowButton();

  buttons[BUTTON_OVERVIEW]->ShowButton();

  int nLeft = wObj.Wid()/2 - sprites[SPRITE_INFO_PANEL_2]->Wid()/2 + 20;
  int nTop = wObj.Hgt()/2 - sprites[SPRITE_INFO_PANEL_2]->Hgt()/2 + 36; 

  buttons[BUTTON_OVERVIEW]->ShowButton();
  buttons[BUTTON_OVERVIEW]->MoveButton(wObj.Wid()/2 - buttons[BUTTON_OVERVIEW]->GetWidth()/2, nTop-5);

  nTop += buttons[BUTTON_OVERVIEW]->GetHeight() + 15;

  int nButtonSpacing = 40;
  buttons[BUTTON_MODEL]->MoveButton(nLeft, nTop);
  nTop += nButtonSpacing;
  buttons[BUTTON_HEAD]->MoveButton(nLeft, nTop);
  nTop += nButtonSpacing;
  buttons[BUTTON_TORSO]->MoveButton(nLeft, nTop);
  nTop += nButtonSpacing;
  buttons[BUTTON_ARM_RIGHT]->MoveButton(nLeft, nTop);
  nTop += nButtonSpacing;
  buttons[BUTTON_ARM_LEFT]->MoveButton(nLeft, nTop);
  nTop += nButtonSpacing;
  buttons[BUTTON_LEG_RIGHT]->MoveButton(nLeft, nTop);
  nTop += nButtonSpacing;
  buttons[BUTTON_LEG_LEFT]->MoveButton(nLeft, nTop);
  nTop += nButtonSpacing;
  buttons[BUTTON_EJECTION]->MoveButton(nLeft, nTop);
  nTop += nButtonSpacing;
  buttons[BUTTON_COOLING]->MoveButton(nLeft, nTop);
  nTop += nButtonSpacing;
  buttons[BUTTON_COMPUTER]->MoveButton(nLeft, nTop);
  nTop += nButtonSpacing;
  buttons[BUTTON_HUMAN_INTERFACE]->MoveButton(nLeft, nTop);

  ChangeSelectedSystem(g_nSystemSelected);

  g_nSystemDesignX = buttons[BUTTON_MODEL]->GetX() + 150;
  g_nSystemDesignY = buttons[BUTTON_MODEL]->GetY();
  g_nSystemDesignRightBound = 
    wObj.Wid()/2 - sprites[SPRITE_INFO_PANEL_2]->Wid()/2 + sprites[SPRITE_INFO_PANEL_2]->Wid() - 20;

  g_nSystemParamsX = g_nSystemDesignX;
  g_nSystemParamsY = g_nSystemDesignY + 160;
  g_nSystemParamsRightBound = g_nSystemDesignRightBound;
}


// Some systems can't be chosen until other systems have been chosen first.
// This is what checks that on the broadest level.
int RequiredSystemsChosen(int nSystem, char *text)
{
  if (text) {
    text[0] = 0;
  }

  switch (nSystem)
  {
    case SYSTEM_FRAME:
      break;
    case SYSTEM_HEAD:
    case SYSTEM_TORSO:
    case SYSTEM_ARM_RIGHT:
    case SYSTEM_ARM_LEFT:
    case SYSTEM_LEG_RIGHT:
    case SYSTEM_LEG_LEFT:
      if (g_pTheRobot->GetFrame()->GetSystemModel() == 0) 
      {
        if (text) 
          sprintf(text, "Requires: Frame");
        return 0;
      }
      break;
    case SYSTEM_EJECTION:
    case SYSTEM_COOLING:
    case SYSTEM_COMPUTER:
      if ((g_pTheRobot->GetFrame()->GetSystemModel() == 0) ||  
          (g_pTheRobot->GetTorso()->GetSystemModel() == 0))
      {
        if (text) 
          sprintf(text, "Requires: Frame, Torso");
        return 0;
      }
      break;
    case SYSTEM_HUMAN_INTERFACE:
      if ((g_pTheRobot->GetFrame()->GetSystemModel() == 0) ||  
          (g_pTheRobot->GetHead()->GetSystemModel() == 0) ||  
          (g_pTheRobot->GetTorso()->GetSystemModel() == 0))
      {
        if (text) 
          sprintf(text, "Requires: Frame, Head, Torso");
        return 0;
      }
      break;
    default:
      return 0;
  }

  return true;  
}

void GetModelNameBySystem(int nSystem, int nModel, char *strName)
{
  strName[0] = 0;

  if (nModel < 0)
    return;

  switch (nSystem)
  {
    case SYSTEM_FRAME:
      sprintf(strName, "%s", Frames[nModel].strName);
      break;
    case SYSTEM_HEAD:
      sprintf(strName, "%s", Heads[nModel].strName);
      break;
    case SYSTEM_TORSO:
      sprintf(strName, "%s", Torsos[nModel].strName);
      break;
    case SYSTEM_ARM_RIGHT:
      sprintf(strName, "%s", Arms[nModel].strName);
      break;
    case SYSTEM_ARM_LEFT:
      sprintf(strName, "%s", Arms[nModel].strName);
      break;
    case SYSTEM_LEG_RIGHT:
      sprintf(strName, "%s", Legs[nModel].strName);
      break;
    case SYSTEM_LEG_LEFT:
      sprintf(strName, "%s", Legs[nModel].strName);
      break;
    case SYSTEM_EJECTION:
      sprintf(strName, "%s", Ejections[nModel].strName);
      break;
    case SYSTEM_COOLING:
      sprintf(strName, "%s", Coolings[nModel].strName);
      break;
    case SYSTEM_COMPUTER:
      sprintf(strName, "%s", Computers[nModel].strName);
      break;
    case SYSTEM_HUMAN_INTERFACE:
      sprintf(strName, "%s", HumanInterfaces[nModel].strName);
      break;
  }
}

void ChangeSelectedSystem(int nNewSystem)
{
  // Update the total system params
  RecalculateTotalSystemParams();

  g_nSystemSelected = nNewSystem; 

  buttons[BUTTON_CHANGE]->HideButton();
  buttons[BUTTON_SELECT]->HideButton();
  buttons[BUTTON_SYSTEM_NEXT]->HideButton();
  buttons[BUTTON_SYSTEM_PREV]->HideButton();

  g_nModelShownOnScreen = 0;

  HideAllSystemImprovementButtons();
  HideGiantRobotButtons();

  g_pCurrentSystem = g_pTheRobot->GetSystemByType(g_nSystemSelected);

  if (RequiredSystemsChosen(g_nSystemSelected, 0) && theGame.GetTurn() < MAX_DEVELOPMENT_TURN)
  {
    buttons[BUTTON_CHANGE]->ShowButton();
  }

  if (nNewSystem == SYSTEM_OVERALL)
  { 
    StartOverallSystemSubScreen();
  }
}

void SetNewFrameParams(System *pSys, int nNewModel)
{
  struct FrameType *tempStruct = &Frames[nNewModel];

  pSys->SetSpecValue(SPEC_VALUE_WEIGHT, tempStruct->nWeight);
}

void SetNewHeadParams(System *pSys, int nNewModel)
{
  struct HeadType *tempStruct = &Heads[nNewModel];

  pSys->SetDevTimeLeft(tempStruct->nDevTime);

  pSys->SetBaseValue(BASE_VALUE_EQ_SLOTS, tempStruct->nEqSlots);
  pSys->SetBaseValue(BASE_VALUE_MAX_POWER, tempStruct->nMaxPower);

  pSys->SetSpecValue(SPEC_VALUE_WEIGHT, tempStruct->nWeight);
}

void SetNewTorsoParams(System *pSys, int nNewModel)
{
  struct TorsoType *tempStruct = &Torsos[nNewModel];

  pSys->SetDevTimeLeft(tempStruct->nDevTime);

  pSys->SetBaseValue(BASE_VALUE_EQ_SLOTS, tempStruct->nEqSlots);
  pSys->SetBaseValue(BASE_VALUE_STORAGE, tempStruct->nStorage);

  pSys->SetSpecValue(SPEC_VALUE_WEIGHT, tempStruct->nWeight);
}

void SetNewLegParams(System *pSys, int nNewModel)
{
  struct LegType *tempStruct = &Legs[nNewModel];

  pSys->SetDevTimeLeft(tempStruct->nDevTime);

  pSys->SetBaseValue(BASE_VALUE_EQ_SLOTS, tempStruct->nEqSlots);
  pSys->SetBaseValue(BASE_VALUE_MAX_WEIGHT, tempStruct->nMaxWeight);

  pSys->SetSpecValue(SPEC_VALUE_WEIGHT, tempStruct->nWeight);
  pSys->SetSpecValue(SPEC_VALUE_SPEED, tempStruct->nSpeed);
  pSys->SetSpecValue(SPEC_VALUE_MANEUVER, tempStruct->nManeuver);
}

void SetNewArmParams(System *pSys, int nNewModel)
{
  struct ArmType *tempStruct = &Arms[nNewModel];

  pSys->SetDevTimeLeft(tempStruct->nDevTime);

  pSys->SetBaseValue(BASE_VALUE_EQ_SLOTS, tempStruct->nEqSlots);

  pSys->SetSpecValue(SPEC_VALUE_WEIGHT, tempStruct->nWeight);
  pSys->SetSpecValue(SPEC_VALUE_CARRY_WEIGHT, tempStruct->nCarryWeight);
}

void SetNewEjectionParams(System *pSys, int nNewModel)
{
  struct EjectionType *tempStruct = &Ejections[nNewModel];

  pSys->SetDevTimeLeft(tempStruct->nDevTime);

  pSys->SetSpecValue(SPEC_VALUE_WEIGHT, tempStruct->nWeight);
}

void SetNewCoolingParams(System *pSys, int nNewModel)
{
  struct CoolingType *tempStruct = &Coolings[nNewModel];

  pSys->SetDevTimeLeft(tempStruct->nDevTime);

  pSys->SetSpecValue(SPEC_VALUE_WEIGHT, tempStruct->nWeight);
}

void SetNewComputerParams(System *pSys, int nNewModel)
{
  struct ComputerType *tempStruct = &Computers[nNewModel];

  pSys->SetDevTimeLeft(tempStruct->nDevTime);

  pSys->SetSpecValue(SPEC_VALUE_WEIGHT, tempStruct->nWeight);
}

void SetNewHumanInterfaceParams(System *pSys, int nNewModel)
{
  struct HumanInterfaceType *tempStruct = &HumanInterfaces[nNewModel];

  pSys->SetDevTimeLeft(tempStruct->nDevTime);

  pSys->SetSpecValue(SPEC_VALUE_WEIGHT, tempStruct->nWeight);
}

void ChangeModel(int nSystem, int nNewModel)
{
  int nCost = 0;

  int nResources = theGame.GetResources();

  if (IsModelRestrictedByCurrentRobot(nSystem, nNewModel, buff))
  {
    // TODO - message box here?  Or play a "beep" noise to say you can't do it?
    ShowPopup("This model is restricted by other components of your Robot.");
    return;
  }

  switch (nSystem)
  {
    case SYSTEM_FRAME:
      if (g_pTheRobot->GetFrame()->GetSystemModel() == nNewModel)
        return;
      nCost = Frames[nNewModel].nCost;
      DetermineResCost(COST_CODE_FRAME, nCost);
      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      // If we chose a new model, we need to reset the system
      // so that it doesn't have all the bonuses
      g_pTheRobot->ResetSystem(nSystem);
      SetNewFrameParams(g_pTheRobot->GetFrame(), nNewModel);
      break;
    case SYSTEM_HEAD:
      if (g_pTheRobot->GetHead()->GetSystemModel() == nNewModel)
        return;
      nCost = Heads[nNewModel].nCost;
      DetermineResCost(COST_CODE_HEAD, nCost);
      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      g_pTheRobot->ResetSystem(nSystem);
      SetNewHeadParams(g_pTheRobot->GetHead(), nNewModel);
      break;
    case SYSTEM_TORSO:
      if (g_pTheRobot->GetTorso()->GetSystemModel() == nNewModel)
        return;
      nCost = Torsos[nNewModel].nCost;
      DetermineResCost(COST_CODE_TORSO, nCost);
      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      g_pTheRobot->ResetSystem(nSystem);
      SetNewTorsoParams(g_pTheRobot->GetTorso(), nNewModel);
      break;
    case SYSTEM_ARM_RIGHT:
      if (g_pTheRobot->GetRightArm()->GetSystemModel() == nNewModel)
        return;
      nCost = Arms[nNewModel].nCost;
      DetermineResCost(COST_CODE_ARM, nCost);
      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      g_pTheRobot->ResetSystem(nSystem);
      SetNewArmParams(g_pTheRobot->GetRightArm(), nNewModel);
      break;
    case SYSTEM_ARM_LEFT:
      if (g_pTheRobot->GetLeftArm()->GetSystemModel() == nNewModel)
        return;
      nCost = Arms[nNewModel].nCost;
      DetermineResCost(COST_CODE_ARM, nCost);
      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      g_pTheRobot->ResetSystem(nSystem);
      SetNewArmParams(g_pTheRobot->GetLeftArm(), nNewModel);
      break;
    case SYSTEM_LEG_RIGHT:
      if (g_pTheRobot->GetRightLeg()->GetSystemModel() == nNewModel)
        return;
      nCost = Legs[nNewModel].nCost;
      DetermineResCost(COST_CODE_LEG, nCost);
      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      g_pTheRobot->ResetSystem(nSystem);
      SetNewLegParams(g_pTheRobot->GetRightLeg(), nNewModel);
      break;
    case SYSTEM_LEG_LEFT:
      if (g_pTheRobot->GetLeftLeg()->GetSystemModel() == nNewModel)
        return;
      nCost = Legs[nNewModel].nCost;
      DetermineResCost(COST_CODE_LEG, nCost);
      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      g_pTheRobot->ResetSystem(nSystem);
      SetNewLegParams(g_pTheRobot->GetLeftLeg(), nNewModel);
      break;
    case SYSTEM_EJECTION:
      if (g_pTheRobot->GetEjectionSystem()->GetSystemModel() == nNewModel)
        return;
      nCost = Ejections[nNewModel].nCost;
      DetermineResCost(COST_CODE_EJECTION, nCost);
      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      g_pTheRobot->ResetSystem(nSystem);
      SetNewEjectionParams(g_pTheRobot->GetEjectionSystem(), nNewModel);
      break;
    case SYSTEM_COOLING:
    {
      if (g_pTheRobot->GetCoolingSystem()->GetSystemModel() == nNewModel)
        return;
      nCost = Coolings[nNewModel].nCost;
      DetermineResCost(COST_CODE_COOLING, nCost);
      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      g_pTheRobot->ResetSystem(nSystem);
      SetNewCoolingParams(g_pTheRobot->GetCoolingSystem(), nNewModel);

      // Now remove all heat sinks and give a message box that says this
      int nNumHeatSinks = g_pTheRobot->RemoveAllHeatSinks();

      if (nNumHeatSinks > 0)
      {
        char text[256];
        sprintf(text, "Heat sinks depend on cooling system.  All %d heat sinks removed.", nNumHeatSinks);
        ShowPopup(text);
      }
      break;
    }
    case SYSTEM_COMPUTER:
    {
      if (g_pTheRobot->GetComputerSystem()->GetSystemModel() == nNewModel)
        return;
      nCost = Computers[nNewModel].nCost;
      DetermineResCost(COST_CODE_COMPUTER, nCost);
      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      g_pTheRobot->ResetSystem(nSystem);
      SetNewComputerParams(g_pTheRobot->GetComputerSystem(), nNewModel);

      // Now remove all sensors and give a message box that says this
      int nNum = g_pTheRobot->RemoveAllSensors();

      if (nNum > 0)
      {
        char text[256];
        sprintf(text, "Sensors depend on the computer system.  All %d sensors removed.", nNum);
        ShowPopup(text);
      }
      break;
    }
    case SYSTEM_HUMAN_INTERFACE:
      if (g_pTheRobot->GetHumanInterface()->GetSystemModel() == nNewModel)
        return;
      nCost = HumanInterfaces[nNewModel].nCost;
      DetermineResCost(COST_CODE_HUMAN_INTERFACE, nCost);
      if (nCost > nResources)
      {
        ShowPopup(CANNOT_AFFORD);
        return;
      }
      g_pTheRobot->ResetSystem(nSystem);
      SetNewHumanInterfaceParams(g_pTheRobot->GetHumanInterface(), nNewModel);
      break;
  }

  // We do have a generic pointer we can use too
  g_pCurrentSystem->SetTotalCost(nCost);
  g_pCurrentSystem->SetSystemModel(nNewModel);

  theGame.SubResources(nCost);
}

void OnEndTurnButton()
{ 
  // So on the last turn of development, we have to check whether we can field or not
  if (theGame.GetTurn() == MAX_DEVELOPMENT_TURN-1)
  {
    char text[2048];
    if (!CanField(text))
    {
      ChangeScreen(SCREEN_YOU_LOSE);
      return;
    }
  }

  ChangeScreen(SCREEN_END_TURN);
}

void ShowSystemModel(int nModel)
{
  g_nModelShownOnScreen = nModel;

  if (g_nModelShownOnScreen > MAX_SYSTEM_MODEL[g_pCurrentSystem->GetSystemType()])
  {
    g_nModelShownOnScreen = 1;
  }

  if (g_nModelShownOnScreen <= 0)
  {
    g_nModelShownOnScreen = MAX_SYSTEM_MODEL[g_pCurrentSystem->GetSystemType()];
  }

  if (IsModelRestrictedByCurrentRobot(g_nSystemSelected, g_nModelShownOnScreen, buff)) 
  {
    buttons[BUTTON_SELECT]->HideButton();
  } 
  else 
  {
    buttons[BUTTON_SELECT]->ShowButton();
  }
}

// Button handler for stakeholder screen
void HandleButtonSystemDesign(int wmId)
{
  // Handle plus button presses by passing them to
  // the System_Development file.  These buttons are 
  // in order in the enum so this works fine.
  if ((wmId >= BUTTON_PLUS_1 && wmId <= MAX_PLUS_BUTTON) ||
      (wmId >= BUTTON_SWITCH_1 && wmId <= MAX_SWITCH_BUTTON))
  {
    HandleSystemImprovementButtons(wmId);
    return;
  }

  // Now do the large switch statement for all the other buttons
  switch (wmId)
  {
    // Show the stakeholder ask screen variation
    case BUTTON_ASK:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2); 
      ChangeScreen(SCREEN_ASK);
      break;
    }

    // Show the stakeholder ask screen variation
    case BUTTON_INFO:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2); 
      ChangeScreen(SCREEN_INFO);
      break;
    }
    
    // Show the stakeholder ask screen variation
    case BUTTON_HELP:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2); 
      ChangeScreen(SCREEN_HELP);
      break;
    }

    // End the turn and go to next turn
    case BUTTON_END:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2);
      OnEndTurnButton();
      break;  
    }

    // Select a different system
    case BUTTON_MODEL:
    case BUTTON_HEAD:
    case BUTTON_TORSO:
    case BUTTON_ARM_RIGHT:
    case BUTTON_ARM_LEFT:
    case BUTTON_LEG_RIGHT:
    case BUTTON_LEG_LEFT:
    case BUTTON_EJECTION:
    case BUTTON_COOLING:
    case BUTTON_COMPUTER:
    case BUTTON_HUMAN_INTERFACE:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_7);
      ChangeSelectedSystem(wmId - BUTTON_MODEL);
      break;
    }

    case BUTTON_ONROBOT_HEAD:
    case BUTTON_ONROBOT_TORSO:
    case BUTTON_ONROBOT_ARM_RIGHT:
    case BUTTON_ONROBOT_ARM_LEFT:
    case BUTTON_ONROBOT_LEG_RIGHT:
    case BUTTON_ONROBOT_LEG_LEFT:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_7);
      // +1 since we don't have an overall "model" button
      ChangeSelectedSystem(wmId - BUTTON_ONROBOT_HEAD + 1);
      break;
    }

    case BUTTON_OVERVIEW:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_7);
      ChangeSelectedSystem(SYSTEM_OVERALL);
      break;
    }

    // Hitting this button means we want to change some
    // aspect of the system, like its model or attributes
    case BUTTON_CHANGE:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_1);

      ShowSystemModel(1);
      HideAllSystemImprovementButtons();

      buttons[BUTTON_SYSTEM_NEXT]->ShowButton();
      buttons[BUTTON_SYSTEM_PREV]->ShowButton();
      break;
    }

    // Hitting this button means we want to select the
    // model we currently are viewing on the design screen
    case BUTTON_SELECT:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_5);

      ChangeModel(g_nSystemSelected, g_nModelShownOnScreen);

      // Now we sort of do a "reset" by re-selecting this
      // system, which will show the buttons and text
      // correctly and stuff
      ChangeSelectedSystem(g_nSystemSelected);
      break;
    }

    // This takes you to the next model in the list if you're
    // selecting models
    case BUTTON_SYSTEM_NEXT:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_6);

      ShowSystemModel(g_nModelShownOnScreen+1);
      break;
    }

    // This button is for going to the previous model
    case BUTTON_SYSTEM_PREV:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_6);

      ShowSystemModel(g_nModelShownOnScreen-1);
      break;
    } 
  }
}

void AlignSystemDesignButtons()
{
  buttons[BUTTON_SELECT]->MoveButton(buttons[BUTTON_CHANGE]->GetX(), 
    buttons[BUTTON_CHANGE]->GetY() + buttons[BUTTON_CHANGE]->GetHeight() + 5);
  buttons[BUTTON_SYSTEM_PREV]->MoveButton(
    buttons[BUTTON_CHANGE]->GetX() - buttons[BUTTON_SYSTEM_PREV]->GetWidth() - 5, 
    buttons[BUTTON_SELECT]->GetY());
  buttons[BUTTON_SYSTEM_NEXT]->MoveButton(
    buttons[BUTTON_CHANGE]->GetX() + buttons[BUTTON_SELECT]->GetWidth() + 5, 
    buttons[BUTTON_SELECT]->GetY());
}

int SetupSystemSelectButtons(int nYPos, int nXPos)
{
  int y = nYPos;

  if (buttons[BUTTON_CHANGE]->GetY() != y)
  {
    buttons[BUTTON_CHANGE]->MoveButton(nXPos, y);
    AlignSystemDesignButtons();
  }
  
  if (buttons[BUTTON_SELECT]->IsVisible())
  {
    y = buttons[BUTTON_SELECT]->GetY() + buttons[BUTTON_SELECT]->GetHeight() + 10;
  }
  else
  {
    y = buttons[BUTTON_CHANGE]->GetY() + buttons[BUTTON_CHANGE]->GetHeight() + 10;
  }

  return y;
}

// Draws the top part of the system and returns the y position of where
// the next part should start drawing
int DrawTopOfSystem(int nLeftBound, int nRightBound, int nTopBound,
                     int nSystemType, char *strSystemName, char *strSystemDesc, char *strSystemTypeName)
{
  int y = buttons[BUTTON_MODEL]->GetY();
  char text[2048];

  // Torso goes too far down if we draw the top of the system when we have
  // one selected, g_nModelShownOnScreen is 0 when we are showing the actual selected system
  if (nSystemType == SYSTEM_TORSO && g_pTheRobot->GetTorso()->GetSystemModel() != TORSO_NONE &&
      g_nModelShownOnScreen <= 0)
  { 
    sprintf(text, "%s", strSystemName);
    int nXPos = nLeftBound - GameFont5->GetTextWidth(text)/2;
    y = GameFont5->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    y = SetupSystemSelectButtons(y, nXPos - buttons[BUTTON_CHANGE]->GetWidth()/2 + GameFont5->GetTextWidth(text)/2);
    return y;
  }

  y = GameFont5->DrawBoundedText(wObj.getBackHDC(), 
    strSystemTypeName,
    nLeftBound - GameFont5->GetTextWidth(strSystemTypeName)/2, nRightBound, y);
  
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), 
    strSystemDesc,
    g_nSystemDesignX, nRightBound, y);

  if (!RequiredSystemsChosen(nSystemType, text))
  {
    y += 15;
    GameFont6->DrawBoundedText(wObj.getBackHDC(), 
      text, nLeftBound - GameFont5->GetTextWidth(text)/2, nRightBound, y);
    return 0;
  }

  y += 15;

  sprintf(text, "%s", strSystemName);
  int nXPos = nLeftBound - GameFont5->GetTextWidth(text)/2;

  y = GameFont5->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

  y += 10;

  y = SetupSystemSelectButtons(y, nXPos - buttons[BUTTON_CHANGE]->GetWidth()/2 + GameFont5->GetTextWidth(text)/2);
  return y;
}

// Print a generic cost string for each system
void PrintCostString(int nCode, int nBaseCost, char *text)
{
  char strCostText[256];
  strCostText[0] = 0;
  // Can't just pass in base cost because this actually changes
  // the cost variable 
  int nCost = nBaseCost;
  DetermineResCost(nCode, nCost, strCostText, true);

  sprintf(text, "Cost: %d%s", nCost, strCostText);
}

int DrawRobotFrame(int nLeftBound, int nRightBound, int nTopBound)
{
  Frame *pFrame = g_pTheRobot->GetFrame();

  int y = 0;
  if ((y = DrawTopOfSystem(nLeftBound, nRightBound, nTopBound, 
                           SYSTEM_FRAME, Frames[pFrame->GetSystemModel()].strName, 
                           pFrame->GetDesc(), pFrame->GetSystemTypeName())) == 0)
    return y;

  int nXPos = g_nSystemDesignX;
  int nLineSpace = 18;
  GameFont *pFont = GameFont5;
  if (g_nModelShownOnScreen > 0) 
  {
    char text[2048];
    int nCurrentModel = g_nModelShownOnScreen;

    // So we're displaying the model selection data here
    y = pFont->DrawBoundedText(wObj.getBackHDC(), 
                               Frames[g_nModelShownOnScreen].strName, 
                               nXPos, nRightBound, y);
    y+=nLineSpace + 5;

    PrintCostString(COST_CODE_FRAME, Frames[nCurrentModel].nCost, text);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Weight: %d tons", Frames[nCurrentModel].nWeight);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    y = pFont->DrawBoundedText(wObj.getBackHDC(), Frames[nCurrentModel].strDesc, nXPos, nRightBound, y);
  }
  return y;
}

int DrawHead(int nLeftBound, int nRightBound, int nTopBound)
{
  Head *pHead = g_pTheRobot->GetHead();

  int y = 0;
  if ((y = DrawTopOfSystem(nLeftBound, nRightBound, nTopBound, 
                           SYSTEM_HEAD, Heads[pHead->GetSystemModel()].strName, 
                           pHead->GetDesc(), pHead->GetSystemTypeName())) == 0)
    return y;

  int nXPos = g_nSystemDesignX;
  int nLineSpace = 18;
  GameFont *pFont = GameFont5;
  if (g_nModelShownOnScreen > 0) 
  {
    char text[2048];
    int nCurrentModel = g_nModelShownOnScreen;

    // So we're displaying the model selection data here
    y = pFont->DrawBoundedText(wObj.getBackHDC(), 
                               Heads[nCurrentModel].strName, 
                               nXPos, nRightBound, y);
    y+=nLineSpace+5;
    
    PrintCostString(COST_CODE_HEAD, Heads[nCurrentModel].nCost, text);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Weight: %d tons", Heads[nCurrentModel].nWeight);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);
 
    sprintf(text, "Equipment Slots: %d", Heads[nCurrentModel].nEqSlots); 
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Max Power: %d", Heads[nCurrentModel].nMaxPower);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Development Time: %s", GET_DEV_TIME_TEXT(Heads[nCurrentModel].nDevTime));
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);
  }
  return y;
}

int DrawTorso(int nLeftBound, int nRightBound, int nTopBound)
{
  Torso *pTorso = g_pTheRobot->GetTorso();

  int y = 0;

  if ((y = DrawTopOfSystem(nLeftBound, nRightBound, nTopBound, 
                           SYSTEM_TORSO, Torsos[pTorso->GetSystemModel()].strName, 
                           pTorso->GetDesc(), pTorso->GetSystemTypeName())) == 0)
    return y;

  int nXPos = g_nSystemDesignX;
  int nLineSpace = 18;
  GameFont *pFont = GameFont5;
  if (g_nModelShownOnScreen > 0) 
  {
    char text[2048];
    int nCurrentModel = g_nModelShownOnScreen;

    // So we're displaying the model selection data here
    y = pFont->DrawBoundedText(wObj.getBackHDC(), 
                               Torsos[nCurrentModel].strName, 
                               nXPos, nRightBound, y);
    y+=nLineSpace+5;

    PrintCostString(COST_CODE_TORSO, Torsos[nCurrentModel].nCost, text);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Weight: %d tons", Torsos[nCurrentModel].nWeight);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);
 
    sprintf(text, "Equipment Slots: %d", Torsos[nCurrentModel].nEqSlots); 
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Storage Space: %d tons", Torsos[nCurrentModel].nStorage);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Development Time: %s", GET_DEV_TIME_TEXT(Torsos[nCurrentModel].nDevTime));
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    if (nCurrentModel == TORSO_WORKER)
    {
      sprintf(text, "Special: The worker torso cannot equip any weapons, and cannot use heavy armor or flak armor.");
      y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);
    }
  }

  return y;
}


int DrawArmModelOptions(int nXPos, int nYPos, int nRightBound)
{
  int x = nXPos;
  int y = nYPos;

  int nLineSpace = 18;
  GameFont *pFont = GameFont5;
  if (g_nModelShownOnScreen > 0) 
  {
    char text[2048];
    int nCurrentModel = g_nModelShownOnScreen;

    // So we're displaying the model selection data here
    y = pFont->DrawBoundedText(wObj.getBackHDC(), 
                               Arms[nCurrentModel].strName, 
                               nXPos, nRightBound, y);
    y+=nLineSpace+5;

    PrintCostString(COST_CODE_ARM, Arms[nCurrentModel].nCost, text);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Weight: %d tons", Arms[nCurrentModel].nWeight);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Carry Weight: %d tons", Arms[nCurrentModel].nCarryWeight);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound, y);
 
    sprintf(text, "Equipment Slots: %d", Arms[nCurrentModel].nEqSlots); 
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound, y);

    sprintf(text, "Development Time: %s", GET_DEV_TIME_TEXT(Arms[nCurrentModel].nDevTime));
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound, y);
  }
  return y;
}

int DrawRightArm(int nLeftBound, int nRightBound, int nTopBound)
{
  Arm *pRightArm = g_pTheRobot->GetRightArm();

  int y = 0;
  if ((y = DrawTopOfSystem(nLeftBound, nRightBound, nTopBound, 
                           SYSTEM_ARM_RIGHT, Arms[pRightArm->GetSystemModel()].strName, 
                           pRightArm->GetDesc(), pRightArm->GetSystemTypeName())) == 0)
    return y;

  int nXPos = buttons[BUTTON_MODEL]->GetX() + 150;
  y = DrawArmModelOptions(nXPos, y, nRightBound);
  return y;
}

int DrawLeftArm(int nLeftBound, int nRightBound, int nTopBound)
{
  Arm *pLeftArm = g_pTheRobot->GetLeftArm();

  int y = 0;
  if ((y = DrawTopOfSystem(nLeftBound, nRightBound, nTopBound, 
                           SYSTEM_ARM_LEFT, Arms[pLeftArm->GetSystemModel()].strName, 
                           pLeftArm->GetDesc(), pLeftArm->GetSystemTypeName())) == 0)
    return y;

  int nXPos = g_nSystemDesignX;
  y = DrawArmModelOptions(nXPos, y, nRightBound);
  return y;
}

int DrawLegModelOptions(int nXPos, int nYPos, int nRightBound)
{
  int x = nXPos;
  int y = nYPos;

  char text[2048];

  int nLineSpace = 18;
  GameFont *pFont = GameFont5;
  if (g_nModelShownOnScreen > 0) 
  {
    int nCurrentModel = g_nModelShownOnScreen;

    // So we're displaying the model selection data here
    y = GameFont6->DrawBoundedText(wObj.getBackHDC(), 
                               Legs[nCurrentModel].strName, 
                               x, nRightBound, y);
    y+=nLineSpace+5;

    PrintCostString(COST_CODE_LEG, Legs[nCurrentModel].nCost, text);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound, y);

    sprintf(text, "Weight: %d tons", Legs[nCurrentModel].nWeight);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound, y);

    sprintf(text, "Max Weight: %d tons", Legs[nCurrentModel].nMaxWeight);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound, y);

    sprintf(text, "Speed Rating: %d", Legs[nCurrentModel].nSpeed);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound, y);

    sprintf(text, "Maneuver Rating: %d", Legs[nCurrentModel].nManeuver);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound, y);

    sprintf(text, "Jump Rating: %d", Legs[nCurrentModel].nJump);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound, y);
 
    sprintf(text, "Equipment Slots: %d", Legs[nCurrentModel].nEqSlots); 
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound, y);

    sprintf(text, "Development Time: %s", GET_DEV_TIME_TEXT(Legs[nCurrentModel].nDevTime));
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound, y);
  }

  return y;
}

int DrawRightLeg(int nLeftBound, int nRightBound, int nTopBound)
{
  Leg *objRightLeg = g_pTheRobot->GetRightLeg();

  int y = 0;
  if ((y = DrawTopOfSystem(nLeftBound, nRightBound, nTopBound, 
                           SYSTEM_LEG_RIGHT, Legs[objRightLeg->GetSystemModel()].strName, 
                           objRightLeg->GetDesc(), objRightLeg->GetSystemTypeName())) == 0)
    return y;

  int nXPos = g_nSystemDesignX;
  y = DrawLegModelOptions(nXPos, y, nRightBound);
  return y;
}

int DrawLeftLeg(int nLeftBound, int nRightBound, int nTopBound)
{
  Leg *objLeftLeg = g_pTheRobot->GetLeftLeg();

  int y = 0;
  if ((y = DrawTopOfSystem(nLeftBound, nRightBound, nTopBound, 
                           SYSTEM_LEG_LEFT, Legs[objLeftLeg->GetSystemModel()].strName, 
                           objLeftLeg->GetDesc(), objLeftLeg->GetSystemTypeName())) == 0)
    return y;
    
  int nXPos = g_nSystemDesignX;
  y = DrawLegModelOptions(nXPos, y, nRightBound);
  return y;
}

int DrawEjectionSystem(int nLeftBound, int nRightBound, int nTopBound)
{
  EjectionSystem *pEjectionSystem = g_pTheRobot->GetEjectionSystem();

  int y = 0;
  if ((y = DrawTopOfSystem(nLeftBound, nRightBound, nTopBound, 
                           SYSTEM_EJECTION, Ejections[pEjectionSystem->GetSystemModel()].strName, 
                           pEjectionSystem->GetDesc(), pEjectionSystem->GetSystemTypeName())) == 0)
    return y;
  
  int nXPos = buttons[BUTTON_MODEL]->GetX() + 150;
  int nLineSpace = 18;
  GameFont *pFont = GameFont5;
  if (g_nModelShownOnScreen > 0) 
  {
    char text[2048];
    int nCurrentModel = g_nModelShownOnScreen;

    // So we're displaying the model selection data here
    y = pFont->DrawBoundedText(wObj.getBackHDC(), 
                               Ejections[nCurrentModel].strName, 
                               nXPos, nRightBound, y);
    y+=nLineSpace+5;

    PrintCostString(COST_CODE_EJECTION, Ejections[nCurrentModel].nCost, text);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Weight: %d tons", Ejections[nCurrentModel].nWeight);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Development Time: %s", GET_DEV_TIME_TEXT(Ejections[nCurrentModel].nDevTime));
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);
  }
  return y;
}

int DrawCoolingSystem(int nLeftBound, int nRightBound, int nTopBound)
{ 
  CoolingSystem *pCoolingSystem = g_pTheRobot->GetCoolingSystem();

  int y = 0;
  if ((y = DrawTopOfSystem(nLeftBound, nRightBound, nTopBound, 
                           SYSTEM_COOLING, Coolings[pCoolingSystem->GetSystemModel()].strName, 
                           pCoolingSystem->GetDesc(), pCoolingSystem->GetSystemTypeName())) == 0)
    return y;

  int nXPos = g_nSystemDesignX;
  int nLineSpace = 18;
  GameFont *pFont = GameFont5;
  if (g_nModelShownOnScreen > 0) 
  {
    char text[2048];
    int nCurrentModel = g_nModelShownOnScreen;

    // So we're displaying the model selection data here
    y = pFont->DrawBoundedText(wObj.getBackHDC(), 
                               Coolings[nCurrentModel].strName, 
                               nXPos, nRightBound, y);
    y+=nLineSpace+5;

    PrintCostString(COST_CODE_COOLING, GetCoolingSystemValue(nCurrentModel, COOL_VALUE_COST), text);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Weight: %d", GetCoolingSystemValue(nCurrentModel, COOL_VALUE_WEIGHT));
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);
    
    sprintf(text, "Base Cooling: %d", GetCoolingSystemValue(nCurrentModel, COOL_VALUE_HEAT_REDUCE));
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    char strTemp[256];
    PrintCostString(COST_CODE_COOLING, GetCoolingSystemValue(nCurrentModel, COOL_VALUE_HEAT_SINK_COST), strTemp);
    sprintf(text, "Heat Sink %s", strTemp);
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Heat Sink Cooling: %d", GetCoolingSystemValue(nCurrentModel, COOL_VALUE_HEAT_SINK_REDUCE));
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Heat Sink Power Need: %d", GetCoolingSystemValue(nCurrentModel, COOL_VALUE_HEAT_SINK_POWER_COST));
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Heat Sink Weight: %d", GetCoolingSystemValue(nCurrentModel, COOL_VALUE_HEAT_SINK_WEIGHT));
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    sprintf(text, "Development Time: %s", GET_DEV_TIME_TEXT(Coolings[nCurrentModel].nDevTime));
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);
  }
  return y;
}

int DrawComputerSystem(int nLeftBound, int nRightBound, int nTopBound)
{
  ComputerSystem *pComputerSystem = g_pTheRobot->GetComputerSystem();

  int y = 0;
  if ((y = DrawTopOfSystem(nLeftBound, nRightBound, nTopBound, 
                           SYSTEM_COMPUTER, Computers[pComputerSystem->GetSystemModel()].strName, 
                           pComputerSystem->GetDesc(), pComputerSystem->GetSystemTypeName())) == 0)
    return y;
    
  int nXPos = g_nSystemDesignX;
  int nLineSpace = 18;
  GameFont *pFont = GameFont5;
  if (g_nModelShownOnScreen > 0) 
  {
    char text[2048];
    int nCurrentModel = g_nModelShownOnScreen;

    // So we're displaying the model selection data here
    y = pFont->DrawBoundedText(wObj.getBackHDC(), 
                               Computers[nCurrentModel].strName, 
                               nXPos, nRightBound, y);
    y+=nLineSpace+5;

    PrintCostString(COST_CODE_COMPUTER, Computers[nCurrentModel].nCost, text);
    pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);
    y+=nLineSpace;

    sprintf(text, "Weight: %d tons", Computers[nCurrentModel].nWeight);
    pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);
    y+=nLineSpace;

    sprintf(text, "Development Time: %s", GET_DEV_TIME_TEXT(Computers[nCurrentModel].nDevTime));
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

    GameFont *pChartFont = GameFont6;
    
    y+=nLineSpace;
    y = pChartFont->DrawBoundedText(wObj.getBackHDC(), "Sensor Specifications:", nXPos, nRightBound, y);
    y+=nLineSpace;
    // Now the chart of all the values:
    //                Cost  Wgt  PwrNeed CoolNeed  Sight Sound Infra Radar Heat Motion   
    // Camera:      
    // Audio Sensor:

    int nStartX = nXPos + 150;
    int i = 0;

    sprintf(text, "Cost   Weight  Pwr Need  Cool Need");
    y = pChartFont->DrawBoundedText(wObj.getBackHDC(), text, nStartX - 15, nRightBound, y);

    for (i = ACC_SENSOR_CAMERA; i <= ACC_SENSOR_OMNI; i++)
    {
      int nXVar = 90;

      // The name
      sprintf(text, "%s", GET_ACC_TYPE_TEXT(i));
      pChartFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

      sprintf(text, "%d", GetSensorCost(i, nCurrentModel));
      pChartFont->DrawBoundedText(wObj.getBackHDC(), text, nStartX, nRightBound, y);

      sprintf(text, "%d", GetSensorWeight(i, nCurrentModel));
      pChartFont->DrawBoundedText(wObj.getBackHDC(), text, nStartX + nXVar, nRightBound, y);

      sprintf(text, "%d", GetSensorPowerCost(i, nCurrentModel));
      pChartFont->DrawBoundedText(wObj.getBackHDC(), text, nStartX + nXVar*2, nRightBound, y);

      sprintf(text, "%d", GetSensorHeatCost(i, nCurrentModel));
      y = pChartFont->DrawBoundedText(wObj.getBackHDC(), text, nStartX + nXVar*3, nRightBound, y);
    }
    y+=nLineSpace;

    sprintf(text, "Sight  Sound Infra Radar  Heat Motion");
    y = pChartFont->DrawBoundedText(wObj.getBackHDC(), text, nStartX - 15, nRightBound, y);

    for (i = ACC_SENSOR_CAMERA; i <= ACC_SENSOR_OMNI; i++)
    {
      // The name
      sprintf(text, "%s", GET_ACC_TYPE_TEXT(i));
      pChartFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);

      int nXVar = 0;
      int nYVar = y;
      for (int j = ACC_VALUE_SIGHT; j <= ACC_VALUE_MOTION_SENSOR; j++)
      {
        sprintf(text, "%d", GetSensorValue(i, j, nCurrentModel));
        y = pChartFont->DrawBoundedText(wObj.getBackHDC(), text, nStartX + nXVar, nRightBound, nYVar);

        nXVar += 60;
      }
    }

  }
  return y;
}

int DrawHumanInterface(int nLeftBound, int nRightBound, int nTopBound)
{
  HumanInterface *pHumanInterface = g_pTheRobot->GetHumanInterface();

  int y = 0;
  if ((y = DrawTopOfSystem(nLeftBound, nRightBound, nTopBound, 
                           SYSTEM_HUMAN_INTERFACE, HumanInterfaces[pHumanInterface->GetSystemModel()].strName, 
                           pHumanInterface->GetDesc(), pHumanInterface->GetSystemTypeName())) == 0)
    return y;
    
  int nXPos = g_nSystemDesignX;
  int nLineSpace = 18;
  GameFont *pFont = GameFont5;
  if (g_nModelShownOnScreen > 0) 
  {
    char text[2048];
    int nCurrentModel = g_nModelShownOnScreen;

    // So we're displaying the model selection data here
    y = pFont->DrawBoundedText(wObj.getBackHDC(), 
                               HumanInterfaces[nCurrentModel].strName, 
                               nXPos, nRightBound, y);
    y+=nLineSpace+5;

    PrintCostString(COST_CODE_HUMAN_INTERFACE, HumanInterfaces[nCurrentModel].nCost, text);
    pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);
    y+=nLineSpace;

    sprintf(text, "Weight: %d tons", HumanInterfaces[nCurrentModel].nWeight);
    pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);
    y+=nLineSpace;

    sprintf(text, "Development Time: %s", GET_DEV_TIME_TEXT(HumanInterfaces[nCurrentModel].nDevTime));
    y = pFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, y);
  }
  return y;
}

void DrawSystemDesignScreen()
{
  sprites[SPRITE_GRID_BACKGROUND]->DrawFrame(wObj.getBackHDC(), 0, 0, 0);

  sprites[SPRITE_LOGO]->DrawFrame(wObj.getBackHDC(), 0, wObj.Wid()/2 - sprites[SPRITE_LOGO]->Wid()/2, 4);
  
  sprites[SPRITE_INFO_PANEL_2]->DrawFrame(wObj.getBackHDC(), 0, 
    wObj.Wid()/2 - sprites[SPRITE_INFO_PANEL_2]->Wid()/2, 
    wObj.Hgt()/2 - sprites[SPRITE_INFO_PANEL_2]->Hgt()/2 + 20);

  // If no selection, we just draw the window
  if (g_nSystemSelected < 0)
  {
    DrawResourceWindow();
    DrawButtons();
    return;
  }

  int nLeftBound = wObj.Wid()/2 - sprites[SPRITE_INFO_PANEL_2]->Wid()/2 + 20;
  int nRightBound = g_nSystemDesignRightBound;
  int nTopBound = g_nSystemDesignY + 100;

  int nSelectionBoxY = buttons[g_nSystemSelected + BUTTON_MODEL]->GetY() - 7;
  int nSelectionBoxX = nLeftBound - 7;

  if (g_pCurrentSystem != false)
  {
    sprites[SPRITE_BUTTONS_4]->DrawTransFrame(wObj.getBackHDC(), 2, nSelectionBoxX, nSelectionBoxY); 
  }

  nLeftBound = wObj.Wid()/2 + 50;

  // Now draw the system info
  switch (g_nSystemSelected)
  {
    case SYSTEM_FRAME:
      nTopBound = DrawRobotFrame(nLeftBound, nRightBound, nTopBound);
      break;
    case SYSTEM_HEAD:
      nTopBound = DrawHead(nLeftBound, nRightBound, nTopBound);
      break;
    case SYSTEM_TORSO:
      nTopBound = DrawTorso(nLeftBound, nRightBound, nTopBound);
      break;
    case SYSTEM_ARM_RIGHT:
      nTopBound = DrawRightArm(nLeftBound, nRightBound, nTopBound);
      break;
    case SYSTEM_ARM_LEFT:
      nTopBound = DrawLeftArm(nLeftBound, nRightBound, nTopBound);
      break;
    case SYSTEM_LEG_RIGHT:
      nTopBound = DrawRightLeg(nLeftBound, nRightBound, nTopBound);
      break;
    case SYSTEM_LEG_LEFT:
      nTopBound = DrawLeftLeg(nLeftBound, nRightBound, nTopBound);
      break;
    case SYSTEM_EJECTION:
      nTopBound = DrawEjectionSystem(nLeftBound, nRightBound, nTopBound);
      break;
    case SYSTEM_COOLING:
      nTopBound = DrawCoolingSystem(nLeftBound, nRightBound, nTopBound);
      break;
    case SYSTEM_COMPUTER:
      nTopBound = DrawComputerSystem(nLeftBound, nRightBound, nTopBound);
      break;
    case SYSTEM_HUMAN_INTERFACE:
      nTopBound = DrawHumanInterface(nLeftBound, nRightBound, nTopBound);
      break;
    case SYSTEM_OVERALL:
      // This is in the System_Overall file
      DrawOverallSystem();
      break;
  }

  if (g_nModelShownOnScreen <= 0)
  {
    DrawSelectedSystemParameters(nTopBound);
  }

  DrawResourceWindow();

  DrawButtons();
}
