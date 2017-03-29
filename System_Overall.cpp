
#include "ProjectRobot.h"
#include "System_Models.h"

extern Stakeholder stakeholder[NUM_STAKEHOLDERS];

// From Screen_SystemDesign.cpp
extern Robot *g_pTheRobot;
extern int g_nSystemSelected;
extern int g_nModelShownOnScreen;

extern int g_nSystemParamsX;
extern int g_nSystemParamsY;
extern int g_nSystemParamsRightBound;

extern int g_nSystemDesignRightBound;

extern int VaryMaxHeatCostBasedOnOpEnv(int nMaxHeatCost, bool bForce);

int g_nRobotX = 0;
int g_nRobotY = 0;

int PrintOverallParamText(char *text, int x, int y, GameFont *gf = 0)
{
  GameFont *DrawFont = gf;
  if (!gf)
  {
    DrawFont = GameFont6;
  }
  int newy = DrawFont->DrawBoundedText(wObj.getBackHDC(), text, x, g_nSystemParamsRightBound, y);
  return newy + 2;
}

/*
int PrintStakeholderApprovalText(char *text, int x, int y, GameFont *gf = 0)
{
  GameFont *DrawFont = gf;
  if (!gf)
  {
    DrawFont = GameFont7;
  }
  int newy = DrawFont->DrawBoundedText(wObj.getBackHDC(), text, x, g_nSystemParamsRightBound, y);
  return newy + 2;
}*/

int DrawOverallSystemArmor(int nXPos, int nRightBound, int nYPos)
{ 

  RobotParameters *pTotalSystemPrms = &g_pTheRobot->TotalSystemParams;

  int y = nYPos;
  int x = nXPos;

  // There should be like a little ? help button so you can see that defenses
  // are averaged over all sub-systems
  y = PrintOverallParamText("Defenses:", x + 105, y, GameFontLightBlue);

  int nVal = 0;
  for (int i = ARMOR_VALUE_PREF_START; i < NUM_ARMOR_VALUES; i++)
  {
    sprintf(buff, "%s: ", GET_ARMOR_VALUE_TEXT(i));
    PrintOverallParamText(buff, x, y);

    nVal = pTotalSystemPrms->nArmorValues[i];
    sprintf(buff, "%d : %s", nVal, TranslateValueToText(nVal)); 
    y = PrintOverallParamText(buff, x + 175, y);   
  }
  return y;
}

int DrawOverallSystemRangeAttacks(int nXPos, int nRightBound, int nYPos)
{ 
  RobotParameters *pTotalSystemPrms = &g_pTheRobot->TotalSystemParams;

  int y = nYPos;
  int x = nXPos;
  int nValSpace = 110;

  y = PrintOverallParamText("Long Range Attacks:", x + 40, y, GameFontLightBlue);

  int nVal = 0;
  for (int i = GUN_VALUE_HEAT; i < GUN_VALUE_POWER_COST; i++)
  {
    sprintf(buff, "%s: ", GET_GUN_VALUE_TEXT(i));
    PrintOverallParamText(buff, x, y);

    nVal = pTotalSystemPrms->nGunValues[i];
    sprintf(buff, "%d : %s", nVal, TranslateValueToText(nVal)); 
    y = PrintOverallParamText(buff, x + nValSpace, y);   
  }
  return y;
}

int DrawOverallSystemCloseAttacks(int nXPos, int nRightBound, int nYPos)
{ 
  RobotParameters *pTotalSystemPrms = &g_pTheRobot->TotalSystemParams;

  int y = nYPos;
  int x = nXPos;
  int nValSpace = 110;

  y = PrintOverallParamText("Close Range Attacks:", x + 40, y, GameFontLightBlue);

  int nVal = 0;
  for (int i = MELEE_VALUE_IMPACT; i < MELEE_VALUE_POWER_COST; i++)
  {
    sprintf(buff, "%s: ", GET_MELEE_VALUE_TEXT(i));
    PrintOverallParamText(buff, x, y);

    nVal = pTotalSystemPrms->nMeleeValues[i];
    sprintf(buff, "%d : %s", nVal, TranslateValueToText(nVal)); 
    y = PrintOverallParamText(buff, x + nValSpace, y);   
  }
  return y;
}

int DrawOverallSystemSpecs(int nXPos, int nRightBound, int nYPos)
{ 

  RobotParameters *pTotalSystemPrms = &g_pTheRobot->TotalSystemParams;

  int y = nYPos;
  int x = nXPos;
  int nValSpace = 110;

  y = PrintOverallParamText("Overall System Specs:", x + 40, y, GameFontLightBlue);

  // Weight first, since we don't want to do a "Superb" or whatever
  // for weight as it's just the total system weight
  sprintf(buff, "%s: ", GET_SPEC_VALUE_TEXT(SPEC_VALUE_WEIGHT));
  PrintOverallParamText(buff, x, y);
  //sprintf(buff, "%d (Max %d)", pTotalSystemPrms->nSpecValues[SPEC_VALUE_WEIGHT], g_pTheRobot->GetMaxWeight()); 
  sprintf(buff, "%d (Max %d)", g_pTheRobot->GetTotalWeight(), g_pTheRobot->GetMaxWeight());
  y = PrintOverallParamText(buff, x + nValSpace, y); 

  int nVal = 0;
  for (int i = SPEC_VALUE_PREF_START; i < SPEC_VALUE_PREF_END; i++)
  {
    sprintf(buff, "%s: ", GET_SPEC_VALUE_TEXT(i));
    PrintOverallParamText(buff, x, y);

    nVal = pTotalSystemPrms->nSpecValues[i];
    sprintf(buff, "%d : %s", nVal, TranslateValueToText(nVal)); 
    y = PrintOverallParamText(buff, x + nValSpace, y);   
  }

  // Now draw heat and power costs
  sprintf(buff, "Cool Need: ");
  PrintOverallParamText(buff, x, y);
 
  int nMaxHeatCost = VaryMaxHeatCostBasedOnOpEnv(g_pTheRobot->GetMaxHeatCost(), false);
  sprintf(buff, "%d (Max %d)", g_pTheRobot->GetTotalHeatCost(), nMaxHeatCost); 
  y = PrintOverallParamText(buff, x + nValSpace, y); 

  sprintf(buff, "Pwr Need: ");
  PrintOverallParamText(buff, x, y);
 
  sprintf(buff, "%d (Max %d)", g_pTheRobot->GetTotalPowerCost(), g_pTheRobot->GetMaxPowerCost()); 
  y = PrintOverallParamText(buff, x + nValSpace, y);

  sprintf(buff, "Env Impact: ");
  PrintOverallParamText(buff, x, y);
 
  sprintf(buff, "%d", g_pTheRobot->GetTotalEnvImpact()); 
  y = PrintOverallParamText(buff, x + nValSpace, y);

  return y;
}

void DrawOverallSystemSensors(int nXPos, int nRightBound, int nYPos)
{
  RobotParameters *pTotalSystemPrms = &g_pTheRobot->TotalSystemParams;

  int y = nYPos + 10;
  int x = nXPos + 20;
  int nValSpace = 130;

  y = PrintOverallParamText("Sensors:", x + 40, y, GameFontLightBlue);

  int nVal = 0;
  for (int i = ACC_VALUE_SIGHT; i <= ACC_VALUE_MOTION_SENSOR; i++)
  {
    sprintf(buff, "%s: ", GET_ACC_VALUE_TEXT(i));
    PrintOverallParamText(buff, x, y);

    nVal = pTotalSystemPrms->nAccValues[i];
    sprintf(buff, "%d : %s", nVal, TranslateValueToText(nVal)); 
    y = PrintOverallParamText(buff, x + nValSpace, y);   
  }
}

// This is not used anymore
/*void DrawStakeholderApproval(int nXPos, int nRightBound, int nYPos)
{
  int y = nYPos;
  int x = nXPos;

  y = PrintStakeholderApprovalText("Stakeholder Approval:", x + 10, y);

  int nVal = 0;
  for (int i = 0; i < NUM_STAKEHOLDERS; i++)
  {
    sprintf(buff, "%s: ", stakeholder[i].GetName());
    PrintStakeholderApprovalText(buff, x, y);

    nVal = stakeholder[i].GetApproval();
    sprintf(buff, "%d : %s", nVal, TranslateApprovalToText(nVal)); 
    y = PrintStakeholderApprovalText(buff, x + 185, y, GameFont8);   
  }
}*/

void DrawOverallSystem()
{
  int nXPos = buttons[BUTTON_MODEL]->GetX() + 400;
  int nYPos = buttons[BUTTON_MODEL]->GetY() - 24;
  int nRightBound = g_nSystemDesignRightBound;
 
  int nYLineSpace = 14;
  nYPos = DrawOverallSystemSpecs(nXPos, nRightBound, nYPos);
  nYPos += nYLineSpace;
  nYPos = DrawOverallSystemRangeAttacks(nXPos, nRightBound, nYPos);
  nYPos += nYLineSpace;
  nYPos = DrawOverallSystemCloseAttacks(nXPos, nRightBound, nYPos);
  nYPos += nYLineSpace;
  nYPos = DrawOverallSystemArmor(nXPos - 65, nRightBound, nYPos);

  //DrawStakeholderApproval(buttons[BUTTON_HUMAN_INTERFACE]->GetX(), nRightBound,
    //buttons[BUTTON_HUMAN_INTERFACE]->GetY() + buttons[BUTTON_HUMAN_INTERFACE]->GetHeight() + 15);

  DrawOverallSystemSensors(buttons[BUTTON_HUMAN_INTERFACE]->GetX(), nRightBound,
    buttons[BUTTON_HUMAN_INTERFACE]->GetY() + buttons[BUTTON_HUMAN_INTERFACE]->GetHeight() + 15);

  sprites[SPRITE_GIANT_ROBOT]->DrawTransFrame(wObj.getBackHDC(), FRAME_ZERO, g_nRobotX, g_nRobotY);
}

void ShowGiantRobotButtons()
{
  for (int i = BUTTON_ONROBOT_HEAD; i <= BUTTON_ONROBOT_LEG_LEFT; i++)
    buttons[i]->ShowButton(); 
  
  buttons[BUTTON_ASK]->ShowButton();
  buttons[BUTTON_INFO]->ShowButton();
  buttons[BUTTON_HELP]->ShowButton();
}

void HideGiantRobotButtons()
{
  for (int i = BUTTON_ONROBOT_HEAD; i <= BUTTON_ONROBOT_LEG_LEFT; i++)
    buttons[i]->HideButton();  

  buttons[BUTTON_ASK]->HideButton();
}

void StartOverallSystemSubScreen()
{
  g_nRobotX = buttons[BUTTON_MODEL]->GetX() + buttons[BUTTON_MODEL]->GetWidth() + 45;
  g_nRobotY = buttons[BUTTON_MODEL]->GetY() + 5;

  Sprite *pSpr = sprites[SPRITE_GIANT_ROBOT];

  // Move the buttons to the right spots
  buttons[BUTTON_ONROBOT_HEAD]->MoveButton(
    g_nRobotX + pSpr->GetFrameLeft(buttons[BUTTON_ONROBOT_HEAD]->GetBackFrameNormal()),
    g_nRobotY + pSpr->GetFrameTop(buttons[BUTTON_ONROBOT_HEAD]->GetBackFrameNormal()));

  buttons[BUTTON_ONROBOT_TORSO]->MoveButton(
    g_nRobotX + pSpr->GetFrameLeft(buttons[BUTTON_ONROBOT_TORSO]->GetBackFrameNormal()),
    g_nRobotY + pSpr->GetFrameTop(buttons[BUTTON_ONROBOT_TORSO]->GetBackFrameNormal()));

  buttons[BUTTON_ONROBOT_ARM_RIGHT]->MoveButton(
    g_nRobotX + pSpr->GetFrameLeft(buttons[BUTTON_ONROBOT_ARM_RIGHT]->GetBackFrameNormal()),
    g_nRobotY + pSpr->GetFrameTop(buttons[BUTTON_ONROBOT_ARM_RIGHT]->GetBackFrameNormal()));

  buttons[BUTTON_ONROBOT_ARM_LEFT]->MoveButton(
    g_nRobotX + pSpr->GetFrameLeft(buttons[BUTTON_ONROBOT_ARM_LEFT]->GetBackFrameNormal()),
    g_nRobotY + pSpr->GetFrameTop(buttons[BUTTON_ONROBOT_ARM_LEFT]->GetBackFrameNormal()));

  buttons[BUTTON_ONROBOT_LEG_RIGHT]->MoveButton(
    g_nRobotX + pSpr->GetFrameLeft(buttons[BUTTON_ONROBOT_LEG_RIGHT]->GetBackFrameNormal()),
    g_nRobotY + pSpr->GetFrameTop(buttons[BUTTON_ONROBOT_LEG_RIGHT]->GetBackFrameNormal()));

  buttons[BUTTON_ONROBOT_LEG_LEFT]->MoveButton(
    g_nRobotX + pSpr->GetFrameLeft(buttons[BUTTON_ONROBOT_LEG_LEFT]->GetBackFrameNormal()),
    g_nRobotY + pSpr->GetFrameTop(buttons[BUTTON_ONROBOT_LEG_LEFT]->GetBackFrameNormal()));

  buttons[BUTTON_ASK]->MoveButton(buttons[BUTTON_HELP]->GetX(), buttons[BUTTON_END]->GetY());
  buttons[BUTTON_INFO]->MoveButton(buttons[BUTTON_ASK]->GetX() + buttons[BUTTON_ASK]->GetWidth() + 10, buttons[BUTTON_ASK]->GetY());

  ShowGiantRobotButtons();
}