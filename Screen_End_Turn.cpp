
#include "ProjectRobot.h"
#include "System_Models.h"
#include "Screen_SystemDesign.h"
#include "Score.h"
#include "PopupWindow.h"

extern Robot *g_pTheRobot;
extern Stakeholder stakeholder[NUM_STAKEHOLDERS];

int g_nEndTurnPanelX = 0;
int g_nEndTurnPanelY = 0;

int g_nEndTurnScreenState = 0;

int nPrevApproval = 0;
int nPrevScore = 0;

int g_nAddRes = 0;
int g_nTotalAddRes = 0;
int g_nScoreIncrease = 0;

int g_nMoreButtonY = 0;

#define TEXT_CLICK_MORE  "Click the More button below to see the details behind score and approval changes:"

extern int DrawSpeak(char *strSpeaker, char *strText, int nXPos, int nRightBound, int nYPos);
extern bool ChangeStakeholder(int nStakeholderNum);

void EndTurn();

enum
{
  END_TURN_FIRST,
  END_TURN_SUPERVISOR,
  END_TURN_PM,
  END_TURN_TRAINER,
  END_TURN_DEVELOPER,
  END_TURN_CONTRACTOR,
  END_TURN_SENATOR,
  END_TURN_USER,
  END_TURN_FIELDED_SCORE,
  END_TURN_SUMMARY,
  END_TURN_FIELDING_NOTES,
  END_TURN_CHANGE_SUPERVISOR,
  END_TURN_CHANGE_PM,
  END_TURN_CHANGE_TRAINER,
  END_TURN_CHANGE_DEVELOPER,
  END_TURN_CHANGE_CONTRACTOR,
  END_TURN_CHANGE_SENATOR,
  END_TURN_CHANGE_USER,
  NUM_END_TURN_STATES
};

#define END_TURN_CHANGE_START   END_TURN_CHANGE_SUPERVISOR

void StartEndTurnScreen()
{
  //objSound.PlaySoundFromResource(IDR_SOUND_STARTGAME);

  // Reset all the plus button presses
  g_pTheRobot->ResetAllPlusButtons();

  // Just disable them
  DisableAllButtons();

  g_nEndTurnPanelX = wObj.Wid()/2 - sprites[SPRITE_END_TURN_PANEL]->Wid()/2;
  g_nEndTurnPanelY = wObj.Hgt()/2 - sprites[SPRITE_END_TURN_PANEL]->Hgt()/2;

  buttons[BUTTON_NEXT]->ShowButton();
  buttons[BUTTON_NEXT]->EnableButton();
  buttons[BUTTON_NEXT]->MoveButton(
      wObj.Wid()/2 - buttons[BUTTON_NEXT]->GetWidth()/2,
      g_nEndTurnPanelY + sprites[SPRITE_END_TURN_PANEL]->Hgt() - buttons[BUTTON_NEXT]->GetHeight() - 18);

  // We don't show the more button yet, but put it in the right place at least
  g_nMoreButtonY = g_nEndTurnPanelY + sprites[SPRITE_END_TURN_PANEL]->Hgt() - buttons[BUTTON_MORE]->GetHeight()*2 - 28;
  buttons[BUTTON_MORE]->MoveButton(
      wObj.Wid()/2 - buttons[BUTTON_MORE]->GetWidth()/2,
      g_nMoreButtonY);

  g_nTotalAddRes = 0;

  int nOverheadRes = NUM_OVERHEAD_RESOURCES_PER_TURN;
  int nQuestions = NUM_QUESTIONS_PER_TURN;
    
  // Resources go down in the sustainment phase
  if (theGame.GetTurn() >= MAX_DEVELOPMENT_TURN)
  {
    nOverheadRes /= 4;
    nQuestions /= 2;
  }

  theGame.AddQuestions(nQuestions);

  theGame.AddResources(nOverheadRes);
  g_nTotalAddRes += nOverheadRes;

  g_nAddRes = 0;

  g_nEndTurnScreenState = END_TURN_FIRST;
}

// Is there going to be an operational test when we hit end turn?
bool IsDemoOnEndTurn(int nThisTurn)
{
  // A "demo" occurs every year after the system is fielded more or less
  if (nThisTurn >= MAX_DEVELOPMENT_TURN)
    return true;

  if (nThisTurn == 3 ||
      nThisTurn == 7 ||
      nThisTurn == 11)
  {
    return true;
  }

  return false;
}

int TurnsUntilDemo(int nThisTurn)
{
  if (nThisTurn <= 3)
    return (3 - nThisTurn);
  if (nThisTurn <= 7)
    return (7 - nThisTurn);
  if (nThisTurn <= 11)
    return (11 - nThisTurn);

  return 0;
}

void CheckNextStakeholderChange(int nStakeholder)
{
  // Set this here, not because we will necessarily display it,
  // but so that when we call EndTurn() next, it will know to actually
  // end the turn and not infinitely loop
  g_nEndTurnScreenState = END_TURN_CHANGE_START;

  if (nStakeholder >= NUM_STAKEHOLDERS)
  {
    EndTurn();
    return;
  }

  bool bStakeholderChanged = ChangeStakeholder(nStakeholder);

  // If it changed, display the appropriate screen
  if (bStakeholderChanged == true)
  {
    g_nEndTurnScreenState = nStakeholder + END_TURN_CHANGE_START;
    return;
  }

  // Otherwise just move on to check the next stakeholder
  CheckNextStakeholderChange(nStakeholder + 1);
}

void EndTurn()
{
  if (g_nEndTurnScreenState < END_TURN_CHANGE_START)
  {
    CheckNextStakeholderChange(STAKEHOLDER_SUPERVISOR);
    return;
  }

  if (IsDemoOnEndTurn(theGame.GetTurn()) == true)
  { 
    theGame.ResetSystemCostThisYear();
  }

  // Do the overall game stuff
  theGame.IncreaseTurn();

  // If we're done, end the game
  if (theGame.GetTurn() == MAX_TURN)
  {
    ChangeScreen(SCREEN_END_GAME);
    return;
  }

  // Decrease all the dev times
  g_pTheRobot->GetFrame()->DecreaseDevTimeLeft();
  g_pTheRobot->GetHead()->DecreaseDevTimeLeft();
  g_pTheRobot->GetTorso()->DecreaseDevTimeLeft();
  g_pTheRobot->GetRightArm()->DecreaseDevTimeLeft();
  g_pTheRobot->GetLeftArm()->DecreaseDevTimeLeft();
  g_pTheRobot->GetRightLeg()->DecreaseDevTimeLeft();
  g_pTheRobot->GetLeftLeg()->DecreaseDevTimeLeft();
  g_pTheRobot->GetCoolingSystem()->DecreaseDevTimeLeft();
  g_pTheRobot->GetEjectionSystem()->DecreaseDevTimeLeft();
  g_pTheRobot->GetComputerSystem()->DecreaseDevTimeLeft();
  g_pTheRobot->GetHumanInterface()->DecreaseDevTimeLeft();

  ChangeScreen(SCREEN_SYSTEM_DESIGN);
}

void SwitchEndTurnStakeholder(int nNewStakeholder)
{
  // If we didn't change, update approval and resources.
  // If we did change, don't touch anything just yet.
  //bool bStakeholderChanged = ChangeStakeholder(nNewStakeholder);
  //if (bStakeholderChanged == false)
  //{
    // If this is a regular development turn, we just
    // move on, since the stakeholder didn't change and we
    // have nothing to say
    if (IsDemoOnEndTurn(theGame.GetTurn()) == false)
    {
      // If we're to the user, we just end the turn
      if (nNewStakeholder == STAKEHOLDER_USER)
      {
        EndTurn();
        return;
      }
      // Otherwise we check the next
      g_nEndTurnScreenState++;
      SwitchEndTurnStakeholder(nNewStakeholder+1);
      return;
    }

    nPrevApproval = stakeholder[nNewStakeholder].GetApproval();
    nPrevScore = theGame.GetScore();
    UpdateStakeholderApproval(nNewStakeholder);

    if (nNewStakeholder == STAKEHOLDER_PM ||
        nNewStakeholder == STAKEHOLDER_SENATOR ||
        nNewStakeholder == STAKEHOLDER_DEVELOPER)
    {
      // Add resources based on stakeholder approval
      g_nAddRes = CalcResourcesForStakeholder(nNewStakeholder);
      theGame.AddResources(g_nAddRes);
      g_nTotalAddRes += g_nAddRes;
    }
  //}

  g_nEndTurnScreenState++;

  // If the developer didn't make any money, just switch to the next one
  // unless he changed to a different developer
  if (nNewStakeholder == STAKEHOLDER_DEVELOPER && !g_nAddRes) // && bStakeholderChanged == false)
  {
    SwitchEndTurnStakeholder(nNewStakeholder+1);
    return;
  }

  // If it's the contractor and nothing has changed, just switch to next
  // screen
  if (nNewStakeholder == STAKEHOLDER_CONTRACTOR) // && bStakeholderChanged == false)
  {
    SwitchEndTurnStakeholder(nNewStakeholder+1);
    return;
  }

  buttons[BUTTON_MORE]->ShowButton();
  buttons[BUTTON_MORE]->EnableButton();
}

// Button handler for End Turn screen
void HandleButtonEndTurn(int wmId)
{
  buttons[BUTTON_MORE]->HideButton();

  switch (wmId)
  {
    case BUTTON_MORE:
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2);
      if (g_nEndTurnScreenState == END_TURN_FIELDED_SCORE)
        ShowEndTurnPopup(sprites[SPRITE_INFO_PANEL_LARGE]);
      else
        ShowEndTurnPopup(sprites[SPRITE_INFO_PANEL]);
      break;

    // Show the info screen variation
    case BUTTON_NEXT:
    {
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2);
      
      // We only do all the approvals once per year
      // So if we're not at a test, we just display the first screen
      //if (IsDemoOnEndTurn(theGame.GetTurn()) == false)
      //{
        //EndTurn();
        //return;
      //}

      switch (g_nEndTurnScreenState)
      {
        case END_TURN_FIRST:
          SwitchEndTurnStakeholder(STAKEHOLDER_SUPERVISOR);
          break;
        case END_TURN_SUPERVISOR:
          SwitchEndTurnStakeholder(STAKEHOLDER_PM);
          break;
        case END_TURN_PM:
          SwitchEndTurnStakeholder(STAKEHOLDER_TRAINER);
          break;
        case END_TURN_TRAINER:
          SwitchEndTurnStakeholder(STAKEHOLDER_DEVELOPER);
          break;
        case END_TURN_DEVELOPER:
          SwitchEndTurnStakeholder(STAKEHOLDER_CONTRACTOR);
          break;
        case END_TURN_CONTRACTOR:
          SwitchEndTurnStakeholder(STAKEHOLDER_SENATOR);
          break;
        case END_TURN_SENATOR:
          SwitchEndTurnStakeholder(STAKEHOLDER_USER);
          break;
        case END_TURN_USER:
          theGame.strScoreDesc[0] = 0;
          if (theGame.GetTurn() >= MAX_DEVELOPMENT_TURN)
          {
            g_nScoreIncrease = UpdateScoreBasedOnSolution();
            g_nEndTurnScreenState++; // Move to Score screen 
            buttons[BUTTON_MORE]->ShowButton();
            buttons[BUTTON_MORE]->EnableButton();
          }
          else
          {
            // This is the last stakeholder state - if we don't have a
            // demo we don't want to see the summaries or anything here
            if (IsDemoOnEndTurn(theGame.GetTurn()) == false)
            {
              EndTurn();
              return;
            }
            g_nEndTurnScreenState+=2; // Move straight to summary
          }
          break;
        case END_TURN_FIELDED_SCORE:
          g_nEndTurnScreenState++;
          break;
        case END_TURN_SUMMARY:
          if (theGame.GetTurn() == MAX_DEVELOPMENT_TURN-1)
          {
            g_nEndTurnScreenState++;
          }
          else
          {
            EndTurn();
          }
          break;
        case END_TURN_FIELDING_NOTES:
          EndTurn();
          break;
        case END_TURN_CHANGE_SUPERVISOR:
          CheckNextStakeholderChange(STAKEHOLDER_PM);
          break;
        case END_TURN_CHANGE_PM:
          CheckNextStakeholderChange(STAKEHOLDER_TRAINER);
          break;
        case END_TURN_CHANGE_TRAINER:
          CheckNextStakeholderChange(STAKEHOLDER_DEVELOPER);
          break;
        case END_TURN_CHANGE_DEVELOPER:
          CheckNextStakeholderChange(STAKEHOLDER_CONTRACTOR);
          break;
        case END_TURN_CHANGE_CONTRACTOR:
          CheckNextStakeholderChange(STAKEHOLDER_SENATOR);
          break;
        case END_TURN_CHANGE_SENATOR:
          CheckNextStakeholderChange(STAKEHOLDER_USER);
          break;
        case END_TURN_CHANGE_USER:
          EndTurn();
          break;
          
      }
    }
  }
}

int DrawStakeholderChanged(Stakeholder *pSH)
{
  int x = g_nEndTurnPanelX + 20;
  int nRightBound = g_nEndTurnPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid() - 20;
  int y = g_nEndTurnPanelY + 25;

  sprintf(buff, "Sir, we have a new stakeholder on the project!  %s has been replaced by a new %s.  %s is the new %s, and has a whole new set of preferences that "
                "you will need to ask about.  Note that all questions you asked to %s are now invalid and must be re-asked "
                "of this new stakeholder for new information.", 
    pSH->GetPrevName(), Stakeholder_Types[pSH->GetType()], pSH->GetName(), Stakeholder_Types[pSH->GetType()], pSH->GetPrevName());

  //y = GameFontGreen->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);
  y = DrawSpeak("AI", buff, x, nRightBound, y);
  return y;
}

// The details for each stakeholder are relatively similar, so this draws
// the general idea
int DrawEndTurnDetails(Stakeholder *pSH)
{
  int x = g_nEndTurnPanelX + 20;
  int nRightBound = g_nEndTurnPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid() - 20;
  int y = g_nEndTurnPanelY + 25;
  int nLineSpace = 30;

  int nApprovalChange = pSH->GetApproval() - nPrevApproval; 
  int nScoreChange = theGame.GetScore() - nPrevScore;

  char buf2[2048];
  buf2[0] = 0;

  if (pSH->GetApproval() > nPrevApproval)
  {
    sprintf(buff, "%s %s approves of Project Robot's progress this quarter.", Stakeholder_Types[pSH->GetType()], pSH->GetName());
    sprintf(buf2, "+%d ", nApprovalChange);
  }
  else if (pSH->GetApproval() == nPrevApproval)
  {
    sprintf(buff, "%s %s's approval rating has not changed towards Project Robot this quarter.", Stakeholder_Types[pSH->GetType()], pSH->GetName());
    sprintf(buf2, "+0 ");
  }
  else
  {
    sprintf(buff, "%s %s does not approve of Project Robot's progress this quarter.", Stakeholder_Types[pSH->GetType()], pSH->GetName());
    sprintf(buf2, "-%d ", nApprovalChange*-1);
  }


  y = GameFontGreen->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);
  
  y = GameFontRed->DrawBoundedText(wObj.getBackHDC(), "----", x, nRightBound,  y);

  int nNewX = 0;
  if (buf2[0])
  {
    GameFontOrange->DrawBoundedText(wObj.getBackHDC(), buf2, x, nRightBound,  y);

    nNewX = x + GameFontOrange->GetTextWidth(buf2);
    GameFontRed->DrawBoundedText(wObj.getBackHDC(), "Approval", nNewX, nRightBound,  y);

    nNewX += GameFontRed->GetTextWidth("Approval");
    sprintf(buff, " (%d Total)", pSH->GetApproval());
    y = GameFontLightBlue->DrawBoundedText(wObj.getBackHDC(), buff, nNewX, nRightBound,  y);
  }

  // We don't award score by stakeholder if you're into Phase 2
  if (theGame.GetTurn() < MAX_DEVELOPMENT_TURN)
  {
    sprintf(buff, "+%d ", nScoreChange);
    GameFontOrange->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);

    nNewX = x + GameFontOrange->GetTextWidth(buff);
    GameFontRed->DrawBoundedText(wObj.getBackHDC(), "Score", nNewX, nRightBound,  y);
  
    nNewX += GameFontRed->GetTextWidth("Score");
    sprintf(buff, " (%d Total)", theGame.GetScore());
    y = GameFontLightBlue->DrawBoundedText(wObj.getBackHDC(), buff, nNewX, nRightBound,  y);
  }


  // Senator and PM both add resources, so we display that
  if (pSH->GetType() == STAKEHOLDER_PM || pSH->GetType() == STAKEHOLDER_SENATOR)
  {
    sprintf(buff, "+%d ", g_nAddRes);
    GameFontOrange->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);

    nNewX = x + GameFontOrange->GetTextWidth(buff);
    GameFontRed->DrawBoundedText(wObj.getBackHDC(), "Resources", nNewX, nRightBound,  y);
  
    nNewX += GameFontRed->GetTextWidth("Resources");
    sprintf(buff, " (%d Total)", theGame.GetResources());
    y = GameFontLightBlue->DrawBoundedText(wObj.getBackHDC(), buff, nNewX, nRightBound,  y);
  }

  y += nLineSpace;
  GameFont6->DrawBoundedText(wObj.getBackHDC(), TEXT_CLICK_MORE, x, nRightBound,  g_nMoreButtonY - 50);
  //GameFont6->DrawBoundedText(wObj.getBackHDC(), theGame.strScoreDesc, x, nRightBound + 150,  35);
  //y = GameFontGreen->DrawBoundedText(wObj.getBackHDC(), "TODO - Detailed text on the reasons behind the score and approval changes will appear here.", x, nRightBound,  y);
  return y;
}

// These don't even really need to be here since it always draws the same thing
// right now, but in case I want to doctor these up a little so that they're
// different, the functions are there
void DrawEndTurnSupervisorScreen()
{
  Stakeholder *pSH = &stakeholder[STAKEHOLDER_SUPERVISOR];
  /*if (theGame.DidStakeholderChangeThisTurn(pSH->GetType()))
  {
    DrawStakeholderChanged(pSH);
    return;
  }*/
  int y = DrawEndTurnDetails(pSH);
}

void DrawEndTurnTrainerScreen()
{
  Stakeholder *pSH = &stakeholder[STAKEHOLDER_TRAINER];
  /*if (theGame.DidStakeholderChangeThisTurn(pSH->GetType()))
  {
    DrawStakeholderChanged(pSH);
    return;
  }*/
  int y = DrawEndTurnDetails(pSH);
}

void DrawEndTurnContractorScreen()
{
  Stakeholder *pSH = &stakeholder[STAKEHOLDER_CONTRACTOR];
  /*if (theGame.DidStakeholderChangeThisTurn(pSH->GetType()))
  {
    DrawStakeholderChanged(pSH);
    return;
  }*/
}

void DrawEndTurnDeveloperScreen()
{
  Stakeholder *pSH = &stakeholder[STAKEHOLDER_DEVELOPER];
  
  /*if (theGame.DidStakeholderChangeThisTurn(pSH->GetType()))
  {
    DrawStakeholderChanged(pSH);
    return;
  }*/

  int x = g_nEndTurnPanelX + 20;
  int nRightBound = g_nEndTurnPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid() - 20;
  int y = g_nEndTurnPanelY + 25;
  int nLineSpace = 30;

  sprintf(buff, "%s %s has been able to market some of the improved armor!", Stakeholder_Types[pSH->GetType()], pSH->GetName());

  y = GameFontGreen->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);
  
  y = GameFontRed->DrawBoundedText(wObj.getBackHDC(), "----", x, nRightBound,  y);
  
  // Developer adds resources if you have done certain things
  sprintf(buff, "+%d ", g_nAddRes);
  GameFontOrange->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);

  int nNewX = x + GameFontOrange->GetTextWidth(buff);
  GameFontRed->DrawBoundedText(wObj.getBackHDC(), "Resources", nNewX, nRightBound,  y);

  nNewX += GameFontRed->GetTextWidth("Resources");
  sprintf(buff, " (%d Total)", theGame.GetResources());
  y = GameFontLightBlue->DrawBoundedText(wObj.getBackHDC(), buff, nNewX, nRightBound,  y);
}

void DrawEndTurnPMScreen()
{
  Stakeholder *pSH = &stakeholder[STAKEHOLDER_PM];
  /*if (theGame.DidStakeholderChangeThisTurn(pSH->GetType()))
  {
    DrawStakeholderChanged(pSH);
    return;
  }*/
  int y = DrawEndTurnDetails(pSH);
}

void DrawEndTurnSenatorScreen()
{
  Stakeholder *pSH = &stakeholder[STAKEHOLDER_SENATOR];
  /*if (theGame.DidStakeholderChangeThisTurn(pSH->GetType()))
  {
    DrawStakeholderChanged(pSH);
    return;
  }*/
  int y = DrawEndTurnDetails(pSH);
}

void DrawEndTurnUserScreen()
{
  Stakeholder *pSH = &stakeholder[STAKEHOLDER_USER];
  /*if (theGame.DidStakeholderChangeThisTurn(pSH->GetType()))
  {
    DrawStakeholderChanged(pSH);
    return;
  }*/
  int y = DrawEndTurnDetails(pSH);
}

void DrawEndTurnFirstScreen()
{ 
  char text[2048];
  
  int x = g_nEndTurnPanelX + 20;
  int nRightBound = g_nEndTurnPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid() - 20;
  int y = g_nEndTurnPanelY + 25;
  int nLineSpace = 15;
  
  // Three months pass, and the development of Project Robot continues.
  if (theGame.GetTurn() < MAX_DEVELOPMENT_TURN) {
    sprintf(text, "Good work this quarter, sir.  Here's the quarterly report:");
  } else {
    sprintf(text, "Good work this year, sir.  Here's the yearly report:");
  }

  y = DrawSpeak("AI", text, x, nRightBound, y);
  
  //y += nLineSpace;

  y += nLineSpace;
  sprintf(buff, "Some resources have been allocated from overhead:", theGame.GetSystemCostThisYear());  
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);

  int nOverheadRes = NUM_OVERHEAD_RESOURCES_PER_TURN;
  if (theGame.GetTurn() >= MAX_DEVELOPMENT_TURN)
    nOverheadRes /= 4;
  sprintf(buff, "+%d ", nOverheadRes);
  GameFont8->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);

  y = GameFont7->DrawBoundedText(wObj.getBackHDC(), "Resources", x + GameFont8->GetTextWidth(buff), nRightBound,  y);
  sprintf(buff, "+%d ", NUM_QUESTIONS_PER_TURN);
  GameFont8->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);
  y = GameFont7->DrawBoundedText(wObj.getBackHDC(), "Questions", x + GameFont8->GetTextWidth(buff), nRightBound,  y);

  // So we're not doing an operational test, which means we say when the next one will be
  if (IsDemoOnEndTurn(theGame.GetTurn()) == false)
  { 
    y += nLineSpace;
    int nTurnsToDemo = TurnsUntilDemo(theGame.GetTurn());
    sprintf(text, "You have %d quarter%s until the next demonstration.  Be sure the system is ready for "
                  "demo, since this demonstration will affect stakeholder approval ratings and funding for "
                  "next year!", nTurnsToDemo, (nTurnsToDemo == 1 ? "" : "s"));
    y = DrawSpeak("AI", text, x, nRightBound, y);
  }
  else if (theGame.GetTurn() < MAX_DEVELOPMENT_TURN)
  {
    sprintf(buff, "%d ", theGame.GetSystemCostThisYear());
    GameFontLightBlue->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);
    y = GameFont7->DrawBoundedText(wObj.getBackHDC(), "resources spent this year", x + GameFontLightBlue->GetTextWidth(buff), nRightBound,  y);

    if (theGame.GetTurn() != MAX_DEVELOPMENT_TURN - 1)
    {
      y += nLineSpace;
      sprintf(text, "There was a system demonstration this quarter!  The following is the report on the stakeholder approval "
                    "ratings and the funding for next year.");
      y = DrawSpeak("AI", text, x, nRightBound, y);
    }
    else 
    {
      y += nLineSpace;
      sprintf(text, "The final system demonstration occurred this quarter!");
      y = DrawSpeak("AI", text, x, nRightBound, y);

      y += nLineSpace;
      sprintf(text, "Project Robot has been deployed to the field!  The following is the report on the stakeholder approval "
                    "ratings and the funding for next year.");
      y = DrawSpeak("AI", text, x, nRightBound, y);
    }
  }
  else
  { 
    sprintf(buff, "%d ", theGame.GetSystemCostThisYear());
    GameFontLightBlue->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);
    y = GameFont7->DrawBoundedText(wObj.getBackHDC(), "resources spent this year", x + GameFontLightBlue->GetTextWidth(buff), nRightBound,  y);

    y += nLineSpace;
    int nFieldedTurns = theGame.GetTurn() - MAX_DEVELOPMENT_TURN+1;
    sprintf(text, "The system has been in the field for %d year%s now.  Let's check on its yearly performance "
                  "ratings. ", nFieldedTurns, (nFieldedTurns == 1 ? "" : "s"));
    y = DrawSpeak("AI", text, x, nRightBound, y);
  }

  if (theGame.GetTurn() == MAX_DEVELOPMENT_TURN-2)
  {
    y += nLineSpace;
    sprintf(text, "Sir, the system will be fielded next quarter!  Please make sure all the final decisions are made by then!");
    y = DrawSpeak("AI", text, x, nRightBound, y);
  }
  // Now we either do an operational test, or say when the next one will be.
  // We also display how long until system fielding, or how long it's been in
  // the field if it's already been fielded
  /*y += nLineSpace;
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), "TODO - Operational tests will appear here, including any that have recently "
                                                    "occurred and the date or quarter of the next test.  Also the final fielding date shall "
                                                    "be displayed if the game is still in Phase One.", x, nRightBound,  y);
  */
}

// So this should draw exactly where the score was gained, like each value with a score
// next to it.  Also each report should refine the information from the field a bit more,
// possibly.  Like, Heat Defense: 10 (Needed: ???) (+X Score)
//           Or, if it's too low:  7 (Needed: 10) (-30% Total Score)
// And this should show up in the "Info" section when the mech is in maintenance phase.
// That way if I add a research section later I can use the same screen.
void DrawEndTurnScoreReport()
{
  char text[2048];
  
  int x = g_nEndTurnPanelX + 20;
  int nRightBound = g_nEndTurnPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid() - 20;
  int y = g_nEndTurnPanelY + 25;
  int nLineSpace = 30;

  // So we do total score, total approval (in a little list), and total
  // resources added, plus the results of any tests, and if the resource
  // allotment this year is changing, plus increase of questions
  sprintf(text, "Field Performance Report:");

  int nDrawMid = g_nEndTurnPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid()/2 - GameFont6->GetTextWidth(text)/2;
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), text, nDrawMid, nRightBound,  y);
  
  y += nLineSpace;

  /*y = GameFont6->DrawBoundedText(wObj.getBackHDC(), "TODO - This will show the field performance report, which will consist of the most common "
                                                    "failures such as interface failures and failures to meet certain specifications, and how those "
                                                    "failures have affected the score. This "
                                                    "data is already calculated in game, it is just not displayed here yet.", x, nRightBound,  y);
  */

  y += nLineSpace;
  sprintf(buff, "+%d ", g_nScoreIncrease);
  GameFontOrange->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);

  int nNewX = x + GameFontOrange->GetTextWidth(buff);
  y = GameFontRed->DrawBoundedText(wObj.getBackHDC(), "Score", nNewX, nRightBound,  y);

  y += nLineSpace;
  GameFont6->DrawBoundedText(wObj.getBackHDC(), TEXT_CLICK_MORE, x, nRightBound,  g_nMoreButtonY - 50);
}

void DrawEndTurnSummaryScreen()
{
  char text[2048];
  
  int x = g_nEndTurnPanelX + 20;
  int nRightBound = g_nEndTurnPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid() - 20;
  int y = g_nEndTurnPanelY + 25;
  int nLineSpace = 30;

  // So we do total score, total approval (in a little list), and total
  // resources added, plus the results of any tests, and if the resource
  // allotment this year is changing, plus increase of questions
  sprintf(text, "Summary:");

  int nDrawMid = g_nEndTurnPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid()/2 - GameFont6->GetTextWidth(text)/2;
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), text, nDrawMid, nRightBound,  y);
  
  y += nLineSpace;

  sprintf(buff, "%d ", g_nTotalAddRes);
  GameFontOrange->DrawBoundedText(wObj.getBackHDC(), buff, x, nRightBound,  y);

  int nNewX = x + GameFontOrange->GetTextWidth(buff);
  y = GameFontRed->DrawBoundedText(wObj.getBackHDC(), "Total Resources Gained", nNewX, nRightBound,  y);
  
  y += nLineSpace;
  //GameFont6->DrawBoundedText(wObj.getBackHDC(), theGame.strScoreDesc, x, nRightBound + 150,  35);
  /*y = GameFont6->DrawBoundedText(wObj.getBackHDC(), "TODO - Total approval, total score, and total resources added will appear "
                                                    "here, in addition to operational tests, increase of questions to ask stakeholders, "
                                                    "and changes in yearly resource allotments.", x, nRightBound,  y);
  */
}

// The final notes that say that the score is now based upon how close your
// solution is to the actual field needs, not the wishes of the stakeholder.
// And that turns are now yearly, and no major changes can be made to the
// system at this point.  Also you may notice cost increases that reflect
// the difficulty of changing configurations after system release.
void DrawEndTurnFieldingNotesScreen()
{
  char text[2048];
  
  int x = g_nEndTurnPanelX + 20;
  int nRightBound = g_nEndTurnPanelX + sprites[SPRITE_END_TURN_PANEL]->Wid() - 20;
  int y = g_nEndTurnPanelY + 25;

  sprintf(text, "Now that your Robot has been deployed to the field, the game is "
                "entering into Phase Two, the maintenance phase. "
                "You will notice the following changes that reflect this new stage of the system life cycle: ");
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound,  y);
  y+= 15;
  sprintf(text, "Score is now based on how well your system meets the true needs of the battlefield, not the stakeholder "
                "needs.  No major changes can be made to the system, but small modifications can still be made. "
                "Costs have increased to reflect the difficulty of changing configurations "
                "after system release.");
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound,  y);
}

void DrawEndTurnScreen()
{
  // Start by drawing the underlying screen, then we draw this screen
  DrawSystemDesignScreen();

  sprites[SPRITE_END_TURN_PANEL]->DrawFrame(wObj.getBackHDC(), FRAME_ZERO, g_nEndTurnPanelX, g_nEndTurnPanelY);

  // So we do "more" and go through each stakeholder's issues
  switch (g_nEndTurnScreenState)
  {
    case END_TURN_FIRST:              DrawEndTurnFirstScreen(); break;
    case END_TURN_SUPERVISOR:         DrawEndTurnSupervisorScreen(); break;
    case END_TURN_PM:                 DrawEndTurnPMScreen(); break;
    case END_TURN_TRAINER:            DrawEndTurnTrainerScreen(); break;
    case END_TURN_DEVELOPER:          DrawEndTurnDeveloperScreen(); break;
    case END_TURN_CONTRACTOR:         DrawEndTurnContractorScreen(); break;
    case END_TURN_SENATOR:            DrawEndTurnSenatorScreen(); break;
    case END_TURN_USER:               DrawEndTurnUserScreen(); break;
    case END_TURN_FIELDED_SCORE:      DrawEndTurnScoreReport(); break;
    case END_TURN_SUMMARY:            DrawEndTurnSummaryScreen(); break;
    case END_TURN_FIELDING_NOTES:     DrawEndTurnFieldingNotesScreen(); break;
    case END_TURN_CHANGE_SUPERVISOR:  DrawStakeholderChanged(&stakeholder[STAKEHOLDER_SUPERVISOR]); break;
    case END_TURN_CHANGE_PM:          DrawStakeholderChanged(&stakeholder[STAKEHOLDER_PM]); break;
    case END_TURN_CHANGE_TRAINER:     DrawStakeholderChanged(&stakeholder[STAKEHOLDER_TRAINER]); break;
    case END_TURN_CHANGE_DEVELOPER:   DrawStakeholderChanged(&stakeholder[STAKEHOLDER_DEVELOPER]); break;
    case END_TURN_CHANGE_CONTRACTOR:  DrawStakeholderChanged(&stakeholder[STAKEHOLDER_CONTRACTOR]); break;
    case END_TURN_CHANGE_SENATOR:     DrawStakeholderChanged(&stakeholder[STAKEHOLDER_SENATOR]); break;
    case END_TURN_CHANGE_USER:        DrawStakeholderChanged(&stakeholder[STAKEHOLDER_USER]); break;
  }

  DrawEnabledButtons();

  /*
  // Your resources have increased by x
  sprintf(text, "Your stakeholders have provided additional resources for the next "
                "development period.  +%d resources.", nAddRes);
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound,  y);
  
  y += nLineSpace;
  
  // XXX stakeholder is happy/unhappy with your choice
  
  //y += nLineSpace;
  
  // A demo has taken place using your thing!  Your score for demo was:
  if (theGame.GetTurn() == 3 ||
      theGame.GetTurn() == 7 ||
      theGame.GetTurn() == 9)
  {
    
      sprintf(text, "Project Robot has been demonstrated to the stakeholders!");
      y = GameFont6->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound,  y);
  }
  
  y += nLineSpace;
  // Your system has now been fielded!  You are entering into the maintenance phase.
  // At this point each turn will last for 1 year instead of 3 months. etc.
  if (theGame.GetTurn() == 9)
  {
    sprintf(text, "Project Robot has now been fielded!  You are now entering into the maintenance phase. "
                  "At this point each turn will last for 1 year instead of 3 months. ");
      y = GameFont6->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound,  y);
  }

  DrawEnabledButtons();*/
}