/*

  When the system is fielded, what happens?  And how do we check whether it's
  doing well in the field?  This file takes care of that

*/

#include "ProjectRobot.h"
#include "System_Models.h"
#include "Score.h"
#include "Records.h"

extern Stakeholder stakeholder[NUM_STAKEHOLDERS];


extern void SetupFinalSolution();
extern void StartTitleScreen();
extern void InitializeStakeholders();
extern void RecalculateTotalSystemParams();
extern void InitializeSystemDesignScreen();
extern int DrawSpeak(char *strSpeaker, char *strText, int nXPos, int nRightBound, int nYPos);
extern System *g_pCurrentSystem;

extern int g_nEndTurnPanelX;
extern int g_nEndTurnPanelY;

extern int g_nInfoLeft;
extern int g_nInfoTop;

extern ScoreRecordList recordlist[MAX_TURN];

int g_nPrevScreen = 0;

// From Screen_SystemDesign.cpp
extern Robot *g_pTheRobot;

bool PrintMissing(System *pSys, char *strMissing)
{
  if (pSys->GetSystemModel() == SYSTEM_MODEL_NONE)
  {
    sprintf(strMissing + strlen(strMissing), "System missing %s!\n", pSys->GetSystemTypeName());
    return false;
  }
  return true;
}

// Can we actually field the system?  It must have all components to be fielded
bool CanField(char *strMissingParts)
{
  bool bCanField = true;
  strMissingParts[0] = 0;

  bCanField &= PrintMissing(g_pTheRobot->GetFrame(), strMissingParts);
  bCanField &= PrintMissing(g_pTheRobot->GetHead(), strMissingParts);
  bCanField &= PrintMissing(g_pTheRobot->GetTorso(), strMissingParts);
  bCanField &= PrintMissing(g_pTheRobot->GetRightArm(), strMissingParts);
  bCanField &= PrintMissing(g_pTheRobot->GetLeftArm(), strMissingParts);
  bCanField &= PrintMissing(g_pTheRobot->GetRightLeg(), strMissingParts);
  bCanField &= PrintMissing(g_pTheRobot->GetLeftLeg(), strMissingParts);
  // Don't actually NEED an ejection system
  //PrintMissing(g_pTheRobot->GetEjectionSystem(), strMissing);
  bCanField &= PrintMissing(g_pTheRobot->GetCoolingSystem(), strMissingParts);
  bCanField &= PrintMissing(g_pTheRobot->GetComputerSystem(), strMissingParts);
  bCanField &= PrintMissing(g_pTheRobot->GetHumanInterface(), strMissingParts);

  return bCanField;
}

void SetupStakeholderChanges()
{
  int i = 0;

  theGame.nNumStakeholderChanges = number(1, MAX_NUM_STAKEHOLDER_CHANGES);

  for (i = 0; i < theGame.nNumStakeholderChanges; i++)
  {
    theGame.nStakeholderChangeTurns[i] = number(2, MAX_DEVELOPMENT_TURN-2);
    theGame.nStakeholderChangeNum[i] = number(0, STAKEHOLDER_USER-1);
  }

  theGame.nNumStakeholderChangesField = number(1, MAX_NUM_STAKEHOLDER_CHANGES);

  for (i = 0; i < theGame.nNumStakeholderChanges; i++)
  {
    theGame.nStakeholderChangeFieldTurns[i] = number(MAX_DEVELOPMENT_TURN, MAX_TURN-2);
    theGame.nStakeholderChangeFieldNum[i] = number(0, STAKEHOLDER_USER-1);
  }
}

// Starts OR restarts the game
void StartGame()
{
  theGame.Clear();

  if (g_pTheRobot)
  {
    delete g_pTheRobot;
    g_pTheRobot = 0;
  }
  g_pTheRobot = new Robot();

  g_pCurrentSystem = 0;

  // Reset any records we had
  ResetRecords();

  // Set up the correct robot parameters randomly for this game
  // This should be done before we init stakeholders so that we can
  // base some stakeholder data off of this
  SetupFinalSolution();

  // Now initialize the stakeholders and other game-related data
  InitializeStakeholders();

  RecalculateTotalSystemParams();

  // Zero out some of our parameters in here 
  InitializeSystemDesignScreen();

  // Redo the turns when stakeholders will change
  SetupStakeholderChanges();

  // Start up on the main screen
  ChangeScreen(SCREEN_TITLE);
}


// Path is not necessary.  0 means it has no path so
// we find it, 1 means the path is included in the 
// filename
bool SaveFile(char *filename, char *text, bool path = false) 
{
  char ExePath[MAX_PATH];
  char *new_name = 0;

  if (!path) {
    FindPath(ExePath);
    new_name = new char[strlen(filename) + strlen(ExePath)+5];
    sprintf(new_name, "%s/%s", ExePath, filename); 
    ofstream textfile(new_name);
    if (textfile.is_open())
    {
      textfile << text;
      textfile.close();
	    if (new_name)
	     delete new_name;
	    return 1;
    }
    if (new_name)
     delete new_name;
  } else {
    ofstream textfile(filename);
    if (textfile.is_open())
    {
      textfile << text;
      textfile.close();
	  return 1;
    }
  }
  
  return 0;
}

bool ScoredStakeholder(int nNum)
{
  if (nNum != STAKEHOLDER_SUPERVISOR && 
      nNum != STAKEHOLDER_PM && 
      nNum != STAKEHOLDER_TRAINER && 
      nNum != STAKEHOLDER_SENATOR && 
      nNum != STAKEHOLDER_USER && 
      nNum != SCORE_ID_FIELDED)
    return false;

  return true;
}

void SaveFinalScoreToFile()
{
  char buff[50000];

  buff[0] = 0;
  sprintf(buff + strlen(buff), "#######################################\n");
  sprintf(buff + strlen(buff), "###### Overall Game Score Report ######\n");
  sprintf(buff + strlen(buff), "#######################################\n\n");
  sprintf(buff + strlen(buff), "       Supervisor:    PM:            Trainer:       Senator:       User:          Field:\n");
  sprintf(buff + strlen(buff), "Year:\n");

  ScoreRecord *pRec = 0;
  int nStakeholder = 0;
  int i = 0;
  for (i = 0; i < 13; i++)
  {
    sprintf(buff + strlen(buff), "%2d     ", i+1);

    // So we go down the line for each stakeholder
    for (nStakeholder = 0; nStakeholder < MAX_SCORE_RECORD; nStakeholder++)
    {
      if (!ScoredStakeholder(nStakeholder))
        continue;
      pRec = recordlist[i].GetRecord(nStakeholder);

      //if (pRec->GetID() == -1)
        //continue;

      // Score: X
      // Approval: X
      if (nStakeholder == SCORE_ID_FIELDED && i < 3)
      {
        sprintf(buff + strlen(buff), "Score: ---    ");
      }
      else
      {
        sprintf(buff + strlen(buff), "Score: %s%-4d%s   ", (pRec->GetScoreAwarded() > 0 ? "+" : (pRec->GetScoreAwarded() == 0 ? " " : "")), pRec->GetScoreAwarded(),
          (pRec->GetScoreAwarded() < 0 ? " " : ""));
      }
    }
    strcat(buff, "\n       ");
    for (nStakeholder = 0; nStakeholder < MAX_SCORE_RECORD; nStakeholder++)
    {
      if (!ScoredStakeholder(nStakeholder))
        continue;

      pRec = recordlist[i].GetRecord(nStakeholder);

      //if (pRec->GetID() == -1)
        //continue;

      if (nStakeholder != SCORE_ID_FIELDED)
      {
        sprintf(buff + strlen(buff), "Apprv: %s%-4d%s   ", (pRec->GetApprovalGiven() > 0 ? "+" : (pRec->GetApprovalGiven() == 0 ? " " : "")), pRec->GetApprovalGiven(),
        (pRec->GetApprovalGiven() < 0 ? " " : ""));
      }
    }
    strcat(buff, "\n\n");
  }

  
  sprintf(buff + strlen(buff), "Total Score: ");
  // Now do the totals
  for (nStakeholder = 0; nStakeholder < MAX_SCORE_RECORD; nStakeholder++)
  {
    if (!ScoredStakeholder(nStakeholder))
      continue;
    int nTotal = 0;
    for (i = 0; i < 13; i++)
    {
      pRec = recordlist[i].GetRecord(nStakeholder);
      nTotal += pRec->GetScoreAwarded();
    }
    sprintf(buff + strlen(buff), "%s%-5d%s         ", (nTotal > 0 ? "+" : (nTotal == 0 ? " " : "")), nTotal,
    (nTotal < 0 ? " " : ""));
  }
  strcat(buff, "\n");
  sprintf(buff + strlen(buff), "Total Apprv: ");
  for (nStakeholder = 0; nStakeholder < MAX_SCORE_RECORD; nStakeholder++)
  {
    if (!ScoredStakeholder(nStakeholder))
      continue;
    int nTotal = 0;
    for (i = 0; i < 13; i++)
    {
      pRec = recordlist[i].GetRecord(nStakeholder);
      nTotal += pRec->GetApprovalGiven();
    }
    sprintf(buff + strlen(buff), "%s%-5d%s         ", (nTotal > 0 ? "+" : (nTotal == 0 ? " " : "")), nTotal,
    (nTotal < 0 ? " " : ""));
  }

  SaveFile("FinalScore.txt", buff);
}

void HandleButtonScoreRecord(int wmId)
{
  switch (wmId)
  {
    // Cancel out of the screen
    case BUTTON_CANCEL:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2);
      if (g_nPrevScreen)
        ChangeScreen(g_nPrevScreen);
      else
        ChangeScreen(SCREEN_END_GAME);
      break;
    }
    case BUTTON_SAVE:
      // TODO - save out to a file
      break;
  }
}

void HandleButtonYouLose(int wmId)
{
  switch (wmId)
  {
    // Cancel out of the screen
    case BUTTON_RETRY:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2);
      StartGame();
      break;
    }
    case BUTTON_MORE:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2);
      g_nPrevScreen = SCREEN_YOU_LOSE;
      ChangeScreen(SCREEN_SCORE_RECORD);
      break;
    }
  }
}

void HandleButtonEndGame(int wmId)
{
  switch (wmId)
  {
    // Cancel out of the screen
    case BUTTON_RETRY:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2);
      StartGame();
      break;
    }
    case BUTTON_MORE:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2);
      g_nPrevScreen = SCREEN_END_GAME;
      ChangeScreen(SCREEN_SCORE_RECORD);
      break;
    }
  }
}

void StartScoreRecordScreen()
{
  HideAndEnableAllButtons();

  /*buttons[BUTTON_SAVE]->ShowButton();
  buttons[BUTTON_SAVE]->MoveButton(
      wObj.Wid()/2 - buttons[BUTTON_SAVE]->GetWidth() - 5,
      g_nInfoTop + sprites[SPRITE_INFO_PANEL_LARGE]->Hgt() + buttons[BUTTON_SAVE]->GetHeight()/2);*/

  buttons[BUTTON_CANCEL]->ShowButton();
  buttons[BUTTON_CANCEL]->MoveButton(
      wObj.Wid()/2  - buttons[BUTTON_CANCEL]->GetWidth()/2,
      g_nInfoTop + sprites[SPRITE_INFO_PANEL_LARGE]->Hgt() - buttons[BUTTON_CANCEL]->GetHeight() + 10);
}

void SetupEndGameScreen()
{
  HideAndEnableAllButtons();

  buttons[BUTTON_MORE]->ShowButton();
  buttons[BUTTON_MORE]->MoveButton(
      wObj.Wid()/2 - buttons[BUTTON_MORE]->GetWidth()/2,
      g_nEndTurnPanelY + sprites[SPRITE_END_TURN_PANEL]->Hgt() - buttons[BUTTON_MORE]->GetHeight()*2 - 25);

  buttons[BUTTON_RETRY]->ShowButton();
  buttons[BUTTON_RETRY]->MoveButton(
      wObj.Wid()/2 - buttons[BUTTON_RETRY]->GetWidth()/2,
      g_nEndTurnPanelY + sprites[SPRITE_END_TURN_PANEL]->Hgt() - buttons[BUTTON_RETRY]->GetHeight() - 20);
  
  // And we also auto-save the score record data here
  SaveFinalScoreToFile();
}

void StartYouLoseScreen()
{
  SetupEndGameScreen();
}

void StartEndOfGameScreen()
{
  SetupEndGameScreen();
}

// Do this!  Oiyah!
void DrawScoreRecordScreen()
{
  sprites[SPRITE_GRID_BACKGROUND]->DrawFrame(wObj.getBackHDC(), 0, 0, 0);

  sprites[SPRITE_LOGO]->DrawFrame(wObj.getBackHDC(), 0, wObj.Wid()/2 - sprites[SPRITE_LOGO]->Wid()/2, 4);

  sprites[SPRITE_INFO_PANEL_LARGE]->DrawFrame(wObj.getBackHDC(), 0, 
                                              g_nInfoLeft, 
                                              g_nInfoTop);

  int x = g_nInfoLeft + 15;
  int y = g_nInfoTop + 15;
  int nRightBound = g_nInfoLeft + sprites[SPRITE_INFO_PANEL_LARGE]->Wid();
  int nLineHeight = 15;

  // Now go through the record list

  // It should look like this:

  /*
          
          Supervisor:   Product Manager:    True System:
  Year:
  1       Score: X      Score: X            Score: X
          Approval: X   Approval: X

  2


  3


  4

  ...

      
          Total App:
          Total Score:
  */

  sprintf(buff, "Overall Game Score Report");
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), buff, 
    ((g_nInfoLeft + sprites[SPRITE_INFO_PANEL_LARGE]->Wid())/2) - (GameFont6->GetTextWidth(buff)/2), 
    nRightBound,  y+5);
  y+= nLineHeight;

  sprintf(buff, "      Supervisor:  PM:         Trainer:     Senator:    User:       Field:");
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);
  sprintf(buff, "Year:");
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);

  int nRowY = y;
  int nStartX = x;

  ScoreRecord *pRec = 0;
  for (int i = 0; i < 13; i++)
  {
    nRowY = y;
    x = nStartX;

    sprintf(buff, "%d", i+1);
    GameFont6->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  nRowY);
    x += 60;

    // So we go down the line for each stakeholder
    for (int nStakeholder = 0; nStakeholder < MAX_SCORE_RECORD; nStakeholder++)
    {
      pRec = recordlist[i].GetRecord(nStakeholder);

      if (pRec->GetID() == -1)
        continue;

      // Score: X
      // Approval: X
      sprintf(buff, "Score: %s%d", (pRec->GetScoreAwarded() > 0 ? "+" : ""), pRec->GetScoreAwarded());
      GameFont6->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  nRowY);

      if (nStakeholder != SCORE_ID_FIELDED)
      {
        sprintf(buff, "Apprv: %s%d", (pRec->GetApprovalGiven() > 0 ? "+" : ""), pRec->GetApprovalGiven());
        GameFont6->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  nRowY + nLineHeight);
      }
      x += 115;
    }
    y+=nLineHeight*3;
  }

  DrawButtons();
}

void DrawYouLoseScreen()
{
  
  //  You suck!/Lose!

  sprites[SPRITE_GRID_BACKGROUND]->DrawFrame(wObj.getBackHDC(), 0, 0, 0);

  sprites[SPRITE_LOGO]->DrawFrame(wObj.getBackHDC(), 0, wObj.Wid()/2 - sprites[SPRITE_LOGO]->Wid()/2, 4);

  sprites[SPRITE_END_TURN_PANEL]->DrawFrame(wObj.getBackHDC(), FRAME_ZERO, g_nEndTurnPanelX, g_nEndTurnPanelY);

  char text[2048];
  
  int x = g_nEndTurnPanelX + 20;
  int nRightBound = g_nEndTurnPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid() - 10;
  int y = g_nEndTurnPanelY + 25;
  int nLineSpace = 20;
  
  // Three months pass, and the development of Project Robot continues.
  sprintf(text, "Sir, it's time to field but your system has not been completed!  All is lost!");
  y = DrawSpeak("AI", text, x, nRightBound, y);
  
  y += nLineSpace;

  CanField(buff);
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);

  y += nLineSpace;
  sprintf(buff, "Final Score: ");
  GameFont6->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);
  sprintf(text, "%d", theGame.GetScore());
  y = GameFontLightBlue->DrawBoundedText(wObj.getBackHDC(), 
    text, x + GameFontLightBlue->GetTextWidth(buff), nRightBound,  y);

  y += nLineSpace;
  sprintf(buff, "Game Over!  Please Try Again!");
  int nXPos = g_nEndTurnPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid()/2 - GameFont6->GetTextWidth(buff)/2;
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), buff, nXPos, nRightBound,  y);

  DrawButtons();
}

void DrawEndOfGameScreen()
{
  //  You maybe don't suck/maybe win!

  sprites[SPRITE_GRID_BACKGROUND]->DrawFrame(wObj.getBackHDC(), 0, 0, 0);

  sprites[SPRITE_LOGO]->DrawFrame(wObj.getBackHDC(), 0, wObj.Wid()/2 - sprites[SPRITE_LOGO]->Wid()/2, 4);

  sprites[SPRITE_END_TURN_PANEL]->DrawFrame(wObj.getBackHDC(), FRAME_ZERO, g_nEndTurnPanelX, g_nEndTurnPanelY);

  char text[2048];
  
  int x = g_nEndTurnPanelX + 20;
  int nRightBound = g_nEndTurnPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid() - 10;
  int y = g_nEndTurnPanelY + 25;
  int nLineSpace = 20;
  
  // Three months pass, and the development of Project Robot continues.
  sprintf(text, "It seems that Project Robot has reached the end of its life cycle.  Good work, sir.  The people "
                "of Earth thank you for your efforts.");
  y = DrawSpeak("AI", text, x, nRightBound, y);

  y += nLineSpace;
  sprintf(buff, "Final Score: ");
  GameFont6->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);
  sprintf(text, "%d", theGame.GetScore());
  y = GameFontLightBlue->DrawBoundedText(wObj.getBackHDC(), 
    text, x + GameFontLightBlue->GetTextWidth(buff), nRightBound,  y);

  y += nLineSpace;
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), "Please click the More button for detailed information on your final score.", x, nRightBound,  y);

  y += nLineSpace;
  sprintf(buff, "The End");
  int nXPos = g_nEndTurnPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid()/2 - GameFont6->GetTextWidth(buff)/2;
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), buff, nXPos, nRightBound,  y);

  y += nLineSpace;
  sprintf(buff, "Thanks for playing!");
  nXPos = g_nEndTurnPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid()/2 - GameFont6->GetTextWidth(buff)/2;
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), buff, nXPos, nRightBound,  y);

  DrawButtons();
}