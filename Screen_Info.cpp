
/*

  This screen shows the data you've collected so far in a chart type format that shows what each
  stakeholder wants

*/

#include "ProjectRobot.h"
#include "Screen_Stakeholders.h"
#include "System_Models.h"

int g_nInfoTop = 5;
int g_nInfoLeft = 15;

extern Stakeholder stakeholder[NUM_STAKEHOLDERS];
extern RobotParameters theCorrectRobot;

extern void DrawSystemDesignScreen();
extern void PrintPreferenceBasedOnNumAndType(char *strPref, int nStakeholder, int nPrefNum, int nPrefArrayType);

int g_nInfoScreenRightBound = 0;

void StartInfoScreen()
{
  // We disable buttons instead of hiding them since this is an
  // "overlayed" screen (I HAVE to do this a better way in the future ...)
  DisableAllButtons();

  g_nInfoScreenRightBound = g_nInfoLeft + sprites[SPRITE_INFO_PANEL_LARGE]->Wid();

  // Same background as the stakeholder screen so we can use the same parameters
  buttons[BUTTON_CANCEL]->MoveButton(g_nInfoLeft + sprites[SPRITE_INFO_PANEL_LARGE]->Wid() - 
                                      buttons[BUTTON_CANCEL]->GetWidth() - 30, 
                                     g_nInfoTop + sprites[SPRITE_INFO_PANEL_LARGE]->Hgt() - 
                                      buttons[BUTTON_CANCEL]->GetHeight()/2 - 5);
  buttons[BUTTON_CANCEL]->ShowButton();
  buttons[BUTTON_CANCEL]->EnableButton();
}

void HandleButtonInfo(int wmId)
{
  switch (wmId)
  {
    // Cancel out of the screen
    case BUTTON_CANCEL:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2); 
      ChangeScreen(SCREEN_SYSTEM_DESIGN);
      break;
    }
  }
}

int PrintInfoScreenText(char *text, int x, int y, GameFont *gf = 0)
{
  GameFont *DrawFont = gf;
  if (!gf)
  {
    DrawFont = GameFont6;
  }
  int newy = DrawFont->DrawBoundedText(wObj.getBackHDC(), text, x, g_nInfoScreenRightBound, y);
  return newy + 2;
}

int ColumnForStakeholder(int nStakeholderNum)
{
  if (nStakeholderNum == STAKEHOLDER_PM)
    return 2;
  if (nStakeholderNum == STAKEHOLDER_SENATOR)
    return 3;
  if (nStakeholderNum == STAKEHOLDER_USER)
    return 4;

  return 5;
}

int GetXForStakeholder(int nStakeholderNum)
{
  int x = g_nInfoLeft + 15;
  int nCol = ColumnForStakeholder(nStakeholderNum);

  int nCol1X = x;
  int nCol2X = nCol1X + 195;
  int nCol3X = nCol2X + 136;
  int nCol4X = nCol3X + 136;
  int nCol5X = nCol4X + 136;

  if (nCol == 1)
    return nCol1X;
  else if (nCol == 2)
    return nCol2X;
  else if (nCol == 3)
    return nCol3X;
  else if (nCol == 4)
    return nCol4X;
  else if (nCol == 5)
    return nCol5X;

  return x;
}

// Print the parameters from the actual system needs, not one of the
// stakeholders.  This is different than the stakeholders since it has 
// the ??? possibility, and doesn't base off of question state
void PrintActualSystemParam(char *strBuff, int y, int nValue)
{
  int nColX = GetXForStakeholder(-1);

  if (theGame.GetTurn() < MAX_DEVELOPMENT_TURN)
  {
    sprintf(strBuff, "???");
  }
  else if (nValue > 0)
  {
    sprintf(strBuff, "%d", nValue);
  }
  else
  {
    sprintf(strBuff, "---");
  }
  PrintInfoScreenText(strBuff, nColX, y);
}

void DrawInfoScreen()
{
  // Start by drawing the underlying screen
  DrawSystemDesignScreen();

  // Now draw this screen
  sprites[SPRITE_OVERLAY]->DrawTransFrame(wObj.getBackHDC(), 0, 0, 0);

  sprites[SPRITE_INFO_PANEL_LARGE]->DrawFrame(wObj.getBackHDC(), 0, 
                                              g_nInfoLeft, 
                                              g_nInfoTop);

  // First print the stakeholders
  RobotParameters *thePreferredBot = 0;
  RobotParameters *pCorrectPrms = &theCorrectRobot;

  // Now the prefs
  int i = 0;
  int j = 0;
  int y = g_nInfoTop + 20;
  int newY = 0;
  int x = g_nInfoLeft + 15;
  int nIndentX = x + 10;
  int nColX = 0;
  int nLineHeight = 10;
  char buff[1024];
  buff[0] = 0;

  y = DrawSpeak("AI", "Sir, here is a chart of the known stakeholder and true system needs.", 
    x, g_nInfoScreenRightBound, y);

  y += 4;
  
  sprintf(buff, "%s:", stakeholder[STAKEHOLDER_PM].GetShortName());
  PrintInfoScreenText(buff, GetXForStakeholder(STAKEHOLDER_PM) - 15, y);

  sprintf(buff, "%s:", stakeholder[STAKEHOLDER_SENATOR].GetShortName());
  PrintInfoScreenText(buff, GetXForStakeholder(STAKEHOLDER_SENATOR) - 15, y);

  sprintf(buff, "%s:", stakeholder[STAKEHOLDER_USER].GetShortName());
  PrintInfoScreenText(buff, GetXForStakeholder(STAKEHOLDER_USER) - 15, y);

  sprintf(buff, "True Needs:");
  PrintInfoScreenText(buff, GetXForStakeholder(-1) - 10, y);

  y = PrintInfoScreenText("Overall Needs:", x, y);
  for (i = SPEC_VALUE_PREF_START; i < SPEC_VALUE_PREF_END; i++)
  {
    sprintf(buff, "%s:", GET_SPEC_VALUE_TEXT(i));
    newY = PrintInfoScreenText(buff, nIndentX, y);
    for (j = 0; j < NUM_STAKEHOLDERS; j++)
    {
      if (j != STAKEHOLDER_PM && j != STAKEHOLDER_SENATOR && j != STAKEHOLDER_USER)
        continue;

      nColX = GetXForStakeholder(j);
      thePreferredBot = &stakeholder[j].RobotPreferences;
      if (thePreferredBot->nSpecValues[i])
      {
        PrintPreferenceBasedOnNumAndType(buff, j, i, PREF_ARRAY_SPEC);
      }
      else
      {
        sprintf(buff, "---");
      }
      PrintInfoScreenText(buff, nColX, y);
    }
    // Now print the actual
    PrintActualSystemParam(buff, y, pCorrectPrms->nSpecValues[i]);
    y = newY;
  }

  y += nLineHeight;
  y = PrintInfoScreenText("Long Atk Needs:", x, y);
  for (i = GUN_VALUE_PREF_START; i < GUN_VALUE_PREF_END; i++)
  {
    sprintf(buff, "%s:", GET_GUN_VALUE_TEXT(i));
    newY = PrintInfoScreenText(buff, nIndentX, y);
    for (j = 0; j < NUM_STAKEHOLDERS; j++)
    {
      if (j != STAKEHOLDER_PM && j != STAKEHOLDER_SENATOR && j != STAKEHOLDER_USER)
        continue;

      nColX = GetXForStakeholder(j);
      thePreferredBot = &stakeholder[j].RobotPreferences;
      if (thePreferredBot->nGunValues[i])
      {
        PrintPreferenceBasedOnNumAndType(buff, j, i, PREF_ARRAY_GUN);
      }
      else
      {
        sprintf(buff, "---");
      }
      PrintInfoScreenText(buff, nColX, y);
    }
    // Now print the actual
    PrintActualSystemParam(buff, y, pCorrectPrms->nGunValues[i]);
    y = newY;
  }

  y += nLineHeight;
  y = PrintInfoScreenText("Close Atk Needs:", x, y);
  for (i = MELEE_VALUE_PREF_START; i < MELEE_VALUE_PREF_END; i++)
  {
    sprintf(buff, "%s:", GET_MELEE_VALUE_TEXT(i));
    newY = PrintInfoScreenText(buff, nIndentX, y);
    for (j = 0; j < NUM_STAKEHOLDERS; j++)
    {
      if (j != STAKEHOLDER_PM && j != STAKEHOLDER_SENATOR && j != STAKEHOLDER_USER)
        continue;

      nColX = GetXForStakeholder(j);
      thePreferredBot = &stakeholder[j].RobotPreferences;
      if (thePreferredBot->nMeleeValues[i])
      {
        PrintPreferenceBasedOnNumAndType(buff, j, i, PREF_ARRAY_MELEE);
      }
      else
      {
        sprintf(buff, "---");
      }
      PrintInfoScreenText(buff, nColX, y);
    }
    // Now print the actual
    PrintActualSystemParam(buff, y, pCorrectPrms->nMeleeValues[i]);
    y = newY;
  }

  y += nLineHeight;
  y = PrintInfoScreenText("Defense Needs:", x, y);
  for (i = ARMOR_VALUE_PREF_START; i < ARMOR_VALUE_PREF_END; i++)
  {
    sprintf(buff, "%s:", GET_ARMOR_VALUE_TEXT(i));
    newY = PrintInfoScreenText(buff, nIndentX, y);
    for (j = 0; j < NUM_STAKEHOLDERS; j++)
    {
      if (j != STAKEHOLDER_PM && j != STAKEHOLDER_SENATOR && j != STAKEHOLDER_USER)
        continue;

      nColX = GetXForStakeholder(j);
      thePreferredBot = &stakeholder[j].RobotPreferences;
      if (thePreferredBot->nArmorValues[i])
      {
        PrintPreferenceBasedOnNumAndType(buff, j, i, PREF_ARRAY_ARMOR);
      }
      else
      {
        sprintf(buff, "---");
      }
      PrintInfoScreenText(buff, nColX, y);
    }
    // Now print the actual
    PrintActualSystemParam(buff, y, pCorrectPrms->nArmorValues[i]);
    y = newY;
  }
  
  y += nLineHeight;
  y = PrintInfoScreenText("Sensor Needs:", x, y);
  for (i = ACC_VALUE_PREF_START; i < ACC_VALUE_PREF_END; i++)
  {
    sprintf(buff, "%s:", GET_ACC_VALUE_TEXT(i));
    newY = PrintInfoScreenText(buff, nIndentX, y);
    for (j = 0; j < NUM_STAKEHOLDERS; j++)
    {
      if (j != STAKEHOLDER_PM && j != STAKEHOLDER_SENATOR && j != STAKEHOLDER_USER)
        continue;

      nColX = GetXForStakeholder(j);
      thePreferredBot = &stakeholder[j].RobotPreferences;
      if (thePreferredBot->nAccValues[i])
      {
        PrintPreferenceBasedOnNumAndType(buff, j, i, PREF_ARRAY_ACC);
      }
      else
      {
        sprintf(buff, "---");
      }
      PrintInfoScreenText(buff, nColX, y);
    }
    // Now print the actual
    PrintActualSystemParam(buff, y, pCorrectPrms->nAccValues[i]);
    y = newY;
  }

  // Then the buttons
  DrawEnabledButtons();
}