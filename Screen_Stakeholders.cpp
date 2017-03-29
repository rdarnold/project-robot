
#include "ProjectRobot.h"
#include "System_Models.h"
#include "Screen_SystemDesign.h"
#include "Screen_Stakeholders.h"

extern Stakeholder stakeholder[NUM_STAKEHOLDERS];
extern void ChangeSelectedSystem(int nNewSystem);

int g_nStakeholderSelected = DEFAULT_NEG_ONE;
int g_nQuestionNum = DEFAULT_NEG_ONE;

int g_nStakeholderState = STAKEHOLDERSTATE_SCREEN_1;

int nStakeholderTop = 0;
int nStakeholderLeft = 0;
int nSHLeftBound = 0;
int nSHRightBound = 0;
int nSHTopBound = 0;

// Init the stakeholders
void InitializeStakeholders()
{
  for (int i = 0; i < NUM_STAKEHOLDERS; i++)
  {
    stakeholder[i].SetupStakeholder(i);
  }
}

// Setup the position vars for where things display on screen - we need
// to do this each time we call a StartXScreen in case we didn't go through
// previous screens to get there, like we loaded a saved game or something
void SetupScreenPositionVars()
{
  nStakeholderLeft = wObj.Wid()/2 - sprites[SPRITE_INFO_PANEL]->Wid()/2;
  nStakeholderTop = wObj.Hgt()/2 - sprites[SPRITE_INFO_PANEL]->Hgt()/2;

  nSHLeftBound = nStakeholderLeft + 30;
  nSHRightBound = nStakeholderLeft + sprites[SPRITE_INFO_PANEL]->Wid() - 30;
  nSHTopBound = nStakeholderTop + 30;
}

void SelectStakeholder(int nIndex)
{
  // Dynamically show and hide the buttons
  buttons[BUTTON_TEXT_Q_1]->HideButton();
  buttons[BUTTON_TEXT_Q_2]->HideButton();
  buttons[BUTTON_TEXT_Q_3]->HideButton();
  buttons[BUTTON_TEXT_Q_4]->HideButton();
  buttons[BUTTON_TEXT_Q_5]->HideButton();
  buttons[BUTTON_TEXT_Q_6]->HideButton();
  buttons[BUTTON_TEXT_Q_7]->HideButton();

  if (g_nStakeholderSelected == nIndex)
  {
    g_nStakeholderSelected = DEFAULT_NEG_ONE;
  } else {
    g_nStakeholderSelected = nIndex;

    char text[2048];
    for (int j = 0; j < MAX_QUESTIONS; j++) {
      if (stakeholder[g_nStakeholderSelected].GetQuestion(j)[0] == 0)
        break;
      sprintf(text, "%s", stakeholder[g_nStakeholderSelected].GetQuestion(j));
      buttons[BUTTON_TEXT_Q_1 + j]->SetButtonText(text);

      buttons[BUTTON_TEXT_Q_1 + j]->EnableButton();
      buttons[BUTTON_TEXT_Q_1 + j]->ShowButton();
    }
  }
}

void UntoggleAllStakeholderButtons()
{
  for (int i = 0; i < NUM_STAKEHOLDERS; i++)
  {
    buttons[i + BUTTON_TEXT_1]->SetBackFrames(0, 1);
  }
}

// When we switch to another stakeholder we want to reset all the button images
void UntoggleAllQuestionButtons()
{
  g_nQuestionNum = DEFAULT_NEG_ONE;
  buttons[BUTTON_MORE_INFO]->HideButton();
  for (int i = 0; i < MAX_QUESTIONS; i++)
  {
    buttons[i + BUTTON_TEXT_Q_1]->SetBackFrames(0, 1);
  }
}

void ToggleSelectedButtonImage(int nButtonID)
{
  if (buttons[nButtonID]->GetBackFrameNormal() == 0) 
  {
    buttons[nButtonID]->SetBackFrames(1, 0);
  } else {
    buttons[nButtonID]->SetBackFrames(0, 1);
  }
}

void SelectStakeholderFromButton(int wmId)
{
  ToggleSelectedButtonImage(wmId);

  int nButtonNumber = wmId - BUTTON_TEXT_1;

  // If we're clicking a new one, make sure we toggle the previous
  // one's button
  if ((nButtonNumber != g_nStakeholderSelected) && (g_nStakeholderSelected != DEFAULT_NEG_ONE))
  { 
    ToggleSelectedButtonImage(g_nStakeholderSelected + BUTTON_TEXT_1);
  }

  UntoggleAllQuestionButtons();
  SelectStakeholder(nButtonNumber);
}

void StartStakeholderScreen1()
{
  // Initialize everything in case we restarted
  g_nStakeholderSelected = DEFAULT_NEG_ONE;
  g_nQuestionNum = DEFAULT_NEG_ONE;
  g_nStakeholderState = STAKEHOLDERSTATE_SCREEN_1;

  // First hide them all, then show what we want
  HideAndEnableAllButtons();

  SetupScreenPositionVars();

  theGame.SetQuestionsLeft(NUM_STARTING_QUESTIONS);

  buttons[BUTTON_NEXT]->ShowButton();
}

void StartStakeholderScreen2()
{
  // First hide them all, then show what we want
  HideAndEnableAllButtons();

  SetupScreenPositionVars();

  ShowWindow(buttons[BUTTON_NEXT]->GetHWND(), SW_SHOW);
}

void StartStakeholderQuestionScreen()
{  
  SetupScreenPositionVars();

  g_nStakeholderSelected = DEFAULT_NEG_ONE;
  g_nQuestionNum = DEFAULT_NEG_ONE;

  UntoggleAllStakeholderButtons();
  UntoggleAllQuestionButtons();

  int nXPos = nSHLeftBound;
  int nYPos = nSHTopBound + 100;
  int nLineHeight = 20;

  char text[2048];
  for (int i = 0; i < NUM_STAKEHOLDERS; i++)
  { 
    sprintf(text, "%s: %s", Stakeholder_Types[i], stakeholder[i].GetName());
    buttons[BUTTON_TEXT_1 + i]->SetButtonText(text); 
    buttons[BUTTON_TEXT_1 + i]->MoveButton(nXPos, nYPos); 
    buttons[BUTTON_TEXT_1 + i]->ShowButton();
    buttons[BUTTON_TEXT_1 + i]->EnableButton();
    nYPos += nLineHeight;
  }

  nYPos += nLineHeight;
  nXPos += 15;
  for (i = 0; i < NUM_STAKEHOLDERS; i++)
  { 
    // Also move the Q buttons to the right spots
    buttons[BUTTON_TEXT_Q_1 + i]->MoveButton(nXPos, nYPos); 
    nYPos += nLineHeight;
  }

  buttons[BUTTON_MORE_INFO]->EnableButton();

  // This is so that if we come in here after we already had
  // selected a stakeholder, we essentially "re-select" so that
  // we show the text buttons.  If we haven't come in here
  // before, we do nothing since we're just setting nStakeholderSelected
  // to what it was originally.
  int nOldStakeholder = g_nStakeholderSelected;
  g_nStakeholderSelected = DEFAULT_NEG_ONE;
  SelectStakeholder(nOldStakeholder);
}

void StartStakeholderScreen3()
{
  // First hide them all, then show what we want
  HideAndEnableAllButtons();

  StartStakeholderQuestionScreen();
}

void StartStakeholderScreen4()
{
  // First hide them all, then show what we want
  HideAndEnableAllButtons();

  ShowWindow(buttons[BUTTON_NEXT]->GetHWND(), SW_SHOW);
}

void StakeholderScreenNext()
{
  g_nStakeholderState++;

  switch (g_nStakeholderState)
  {
    case STAKEHOLDERSTATE_SCREEN_2:
      StartStakeholderScreen2();
      break;
    case STAKEHOLDERSTATE_SCREEN_3:
      StartStakeholderScreen3();
      break;
    case STAKEHOLDERSTATE_SCREEN_4:
      StartStakeholderScreen4();
      break;
    default:
      ChangeScreen(SCREEN_SYSTEM_DESIGN); 
      ChangeSelectedSystem(SYSTEM_OVERALL);
      break;
  };
}

// Draw a speaker with speech afterwards, like AI: <speech>
int DrawSpeak(char *strSpeaker, char *strText, int nXPos, int nRightBound, int nYPos)
{
  int x = nXPos;
  int y = nYPos;

  char text[2048];
  sprintf(text, "%s:", strSpeaker);
  GameFont10->DrawBoundedText(wObj.getBackHDC(), text, x, nRightBound,  y);

  int nSpace = GameFont10->GetTextWidth(strSpeaker) + 10;
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), strText, x + nSpace, nRightBound,  y);

  return y;
}

// Display the current text answer based on
// how deep into the question we've gotten

// Most things are simply text, but some, like
// attacks and defenses, are actually parameters.
void DrawQuestionAnswer()
{
  if (g_nStakeholderSelected == DEFAULT_NEG_ONE || g_nQuestionNum == DEFAULT_NEG_ONE)
  {
    return;
  }

  int nXPos = 0;
  int nYPos = 0;
  int nRightBound = nSHRightBound;

  nXPos = buttons[BUTTON_TEXT_Q_1]->GetX() + buttons[BUTTON_TEXT_Q_1]->GetWidth() + 30;
  nYPos = buttons[BUTTON_TEXT_Q_1]->GetY();

  Stakeholder *pSH = &stakeholder[g_nStakeholderSelected];
  GameFont *theFont = GameFont6;
  // But for now we're just going to do the text.
  
  int nTierEnd = false;
  if (pSH->GetQuestionState(g_nQuestionNum) <= 0)
  {  
    // Question has not been asked 
    // Display ( No Information ) or just nothing
    int y = theFont->DrawBoundedText(wObj.getBackHDC(), " ", nXPos, nRightBound, nYPos);
    nYPos = y + 5;
  }
  else
  {
    // Question has been asked
    // Display ( Current information state )
    char text[2048];
    nTierEnd = pSH->PrintAnswerToQuestion(g_nQuestionNum, text);
    int y = theFont->DrawBoundedText(wObj.getBackHDC(), text, nXPos, nRightBound, nYPos);
    nYPos = y + 5;
  }
  
  if (theGame.GetQuestionsLeft() > 0)
  {
    buttons[BUTTON_MORE_INFO]->MoveButton(nXPos, nYPos);
    buttons[BUTTON_MORE_INFO]->ShowButton();
  }

  if (nTierEnd && buttons[BUTTON_MORE_INFO]->IsVisible())
  {
    buttons[BUTTON_MORE_INFO]->HideButton();
  }
}

void ClickMoreInfo()
{
  if (theGame.GetQuestionsLeft() <= 0)
  {
    // AI should say you're out of time, but you can review this
    // answers later by accessing the Info Panel
    return;
  }

  stakeholder[g_nStakeholderSelected].IncreaseQuestionState(g_nQuestionNum);
  theGame.SubtractQuestion();

  if (theGame.GetQuestionsLeft() <= 0)
  {
    buttons[BUTTON_MORE_INFO]->HideButton();
    buttons[BUTTON_NEXT]->ShowButton();
  }
}

void ClickQuestionTopic(int wmId)
{

  ToggleSelectedButtonImage(wmId);

  int nNewQuestionNumber = wmId - BUTTON_TEXT_Q_1;

  // If we're clicking a new one, make sure we toggle the previous
  // one's button
  if ((nNewQuestionNumber != g_nQuestionNum) && (g_nQuestionNum != DEFAULT_NEG_ONE))
  { 
    ToggleSelectedButtonImage(g_nQuestionNum + BUTTON_TEXT_Q_1);
  }
  // If we clicked the same one, remove the text from screen
  else if ((nNewQuestionNumber == g_nQuestionNum) && (g_nQuestionNum != DEFAULT_NEG_ONE))
  {
    buttons[BUTTON_MORE_INFO]->HideButton();
    g_nQuestionNum = DEFAULT_NEG_ONE;
    return;
  } 

  g_nQuestionNum = nNewQuestionNumber;

  if (theGame.GetQuestionsLeft() > 0)
  {
    buttons[BUTTON_MORE_INFO]->ShowButton();
  }
}

// Button handler for stakeholder screen
void HandleButtonStakeholder(int wmId)
{
  switch (wmId)
  {
    case BUTTON_NEXT:
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2);
      StakeholderScreenNext();
      break;
    case BUTTON_TEXT_1:
    case BUTTON_TEXT_2:
    case BUTTON_TEXT_3:
    case BUTTON_TEXT_4:
    case BUTTON_TEXT_5:
    case BUTTON_TEXT_6:
    case BUTTON_TEXT_7:
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_4);
      SelectStakeholderFromButton(wmId);
      break;
    case BUTTON_TEXT_Q_1:
    case BUTTON_TEXT_Q_2:
    case BUTTON_TEXT_Q_3:
    case BUTTON_TEXT_Q_4:
    case BUTTON_TEXT_Q_5:
    case BUTTON_TEXT_Q_6:
    case BUTTON_TEXT_Q_7:
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_5);
      ClickQuestionTopic(wmId);
      break;
    case BUTTON_MORE_INFO:
      objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_5);
      ClickMoreInfo();
      break;
  }
}

int PrintStakeholderApprovalText(char *text, int x, int y, GameFont *gf = 0)
{
  GameFont *DrawFont = gf;
  if (!gf)
  {
    DrawFont = GameFontLightBlue;
  }
  int newy = DrawFont->DrawBoundedText(wObj.getBackHDC(), text, x, nSHRightBound + 20, y);
  return newy + 2;
}

void DrawStakeholderApproval()
{
  int y = buttons[BUTTON_TEXT_1]->GetY() - 17;
  int x = nSHLeftBound + 490;

  y = PrintStakeholderApprovalText("Approval Ratings:", x - 25, y);

  int nVal = 0;
  y += 3;
  for (int i = 0; i < NUM_STAKEHOLDERS; i++)
  {
    nVal = stakeholder[i].GetApproval();
    sprintf(buff, "%d : %s", nVal, TranslateApprovalToText(nVal)); 
    y = PrintStakeholderApprovalText(buff, x, y, GameFont8); 
    y += 3;
  }
}


void DrawStakeholderScreen1(int nLeftBound, int nRightBound, int nTopBound)
{
  GameFont6->DrawBoundedText(wObj.getBackHDC(), 
    "Project Robot Kickoff Meeting:", nLeftBound, nRightBound,  nTopBound);

  char text[4096];
  nTopBound += 25;
  
  //GameFont10->DrawBoundedText(wObj.getBackHDC(), "AI:", nLeftBound, nRightBound,  nTopBound);

  sprintf(text, "Welcome to the Project Robot Kickoff Meeting, Chief Systems Engineer!  I am the advanced "
                "artificial intelligence support system, AAISS, or AI for short.  I will be chairing the meeting "
                "today.  Let's get "
                "started.  First off, I will go ahead and introduce the meeting attendees.  Present, "
                "we have your %s, %s, whom you, of course, are already familiar with.  Also in attendance "
                "are %s the %s, %s the %s, the %s, %s, and %s, the %s.  Lastly, we have the pleasure of "
                "%s's presence as well.  Oh, and let us not forget the %s Representative, our %s.  Thank you "
                "all for coming. ", 
                  Stakeholder_Types[0], stakeholder[0].GetName(),
                  stakeholder[1].GetName(), Stakeholder_Types[1], 
                  stakeholder[2].GetName(), Stakeholder_Types[2], 
                  Stakeholder_Types[3], stakeholder[3].GetName(), 
                  stakeholder[4].GetName(), Stakeholder_Types[4], 
                  stakeholder[5].GetName(),
                  Stakeholder_Types[6], stakeholder[6].GetName());
  //int y = GameFont6->DrawBoundedText(wObj.getBackHDC(), text, nLeftBound + 25, nRightBound,  nTopBound);

  DrawSpeak("AI", text, nLeftBound, nRightBound, nTopBound);
  //buttons[BUTTON_NEXT]->MoveButton(85, y + 30);
}

void DrawStakeholderScreen2(int nLeftBound, int nRightBound, int nTopBound)
{
  GameFont6->DrawBoundedText(wObj.getBackHDC(), 
    "Project Robot Kickoff Meeting:", nLeftBound, nRightBound,  nTopBound);

  char text[4096];

  nTopBound += 25;
  //GameFont10->DrawBoundedText(wObj.getBackHDC(), "AI:", nLeftBound, nRightBound,  nTopBound);
  sprintf(text, "So, as you all know, we are gathered here today to discuss Project Robot, the Allied "
                "Army's latest response to our friendly neighborhood Aliens.  All of you, as representatives "
                "of the major stakeholders in the effort, will dictate the direction of the program, which "
                "itself will be executed by our very own Systems Engineer.  Without any further questions, "
                "I will move to the heart of the matter.  Please attend to any questions our Systems "
                "Engineer has, as your answers will surely provide the direction that this program needs. ");

  //int y = GameFont6->DrawBoundedText(wObj.getBackHDC(), text, nLeftBound + 25, nRightBound,  nTopBound);

  DrawSpeak("AI", text, nLeftBound, nRightBound, nTopBound);
  //buttons[BUTTON_NEXT]->MoveButton(85, y + 30);
}

void DrawStakeholderScreen3(int nLeftBound, int nRightBound, int nTopBound, bool bInfoScreen = false)
{
  char text[2048];
  int y = nTopBound;

  // If it's not on the info screen, draw normally
  if (!bInfoScreen)
  {
    GameFont6->DrawBoundedText(wObj.getBackHDC(), 
      "Project Robot Kickoff Meeting:", nLeftBound, nRightBound,  y);

    y += 25;
  
    sprintf(text, "You are now free to ask the stakeholders about their needs and preferences."); 
    GameFont6->DrawBoundedText(wObj.getBackHDC(), text, nLeftBound, nRightBound,  y);

    y += 45;
  } 
  else 
  {
    //GameFont10->DrawBoundedText(wObj.getBackHDC(), "AI:", nLeftBound, nRightBound,  y);

    sprintf(text, "Feel free to ask the stakeholders additional questions.");
    //y = GameFont6->DrawBoundedText(wObj.getBackHDC(), text, nLeftBound + 25, nRightBound,  y);

    
    y = DrawSpeak("AI", text, nLeftBound, nRightBound, nTopBound);

    y += 25;
  }


  sprintf(text, "Question%s remaining: ", (theGame.GetQuestionsLeft() == 1) ? "" : "s"); 
  GameFont6->DrawBoundedText(wObj.getBackHDC(), text, nLeftBound, nRightBound,  y);
  int nQuestionXPos = nLeftBound + GameFont6->GetTextWidth(text);
  sprintf(text, "%d", theGame.GetQuestionsLeft());
  GameFont8->DrawBoundedText(wObj.getBackHDC(), text, nQuestionXPos, nRightBound,  y);

  // If a question has been asked, draw the answer
  DrawQuestionAnswer();

  DrawStakeholderApproval();
}

void DrawStakeholderScreen4(int nLeftBound, int nRightBound, int nTopBound)
{
  GameFont6->DrawBoundedText(wObj.getBackHDC(), 
    "Project Robot Kickoff Meeting Closure:", nLeftBound, nRightBound,  nTopBound);

  char text[4096];

  nTopBound += 25;
  //GameFont10->DrawBoundedText(wObj.getBackHDC(), "AI:", nLeftBound, nRightBound,  nTopBound);
  sprintf(text, "Alas, we are out of time.  This has certainly been a productive meeting.  Thank you all "
                "for attending, and I hope our Systems Engineer has gathered enough information to begin "
                "the development of this extremely important system.  May the Allies be Victorious!");

  //int y = GameFont6->DrawBoundedText(wObj.getBackHDC(), text, nLeftBound + 25, nRightBound,  nTopBound);

  int y = DrawSpeak("AI", text, nLeftBound, nRightBound, nTopBound);
  //buttons[BUTTON_NEXT]->MoveButton(85, y + 30);

  y += 30;
  sprintf(text, "You will now have 3 years to conduct system development, divided into 4 quarters each year, "
    "which will be followed by 10 years of sustainment.  The current quarter or year can be seen in the top right corner of "
    "the main screen, as well as other pertinent time information.");
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), text, nLeftBound, nRightBound,  y);
}


void DrawStakeholderScreen(bool bInfoScreen)
{
  if (bInfoScreen == false)
  {
    sprites[SPRITE_GRID_BACKGROUND]->DrawFrame(wObj.getBackHDC(), 0, 0, 0);
  }
  
  sprites[SPRITE_LOGO]->DrawFrame(wObj.getBackHDC(), 0, wObj.Wid()/2 - sprites[SPRITE_LOGO]->Wid()/2, 4);
  
  if (bInfoScreen == true)
  {
    sprites[SPRITE_OVERLAY]->DrawTransFrame(wObj.getBackHDC(), 0, 0, 0);
  }

  sprites[SPRITE_INFO_PANEL]->DrawFrame(wObj.getBackHDC(), 0, 
                                        nStakeholderLeft, 
                                        nStakeholderTop);

  int nLeftBound = nSHLeftBound;
  int nRightBound = nSHRightBound;
  int nTopBound = nSHTopBound;

  switch (g_nStakeholderState)
  {
    case STAKEHOLDERSTATE_SCREEN_1:
      DrawStakeholderScreen1(nLeftBound, nRightBound, nTopBound);
      break;
    case STAKEHOLDERSTATE_SCREEN_2:
      DrawStakeholderScreen2(nLeftBound, nRightBound, nTopBound);
      break;
    case STAKEHOLDERSTATE_SCREEN_3:
      DrawStakeholderScreen3(nLeftBound, nRightBound, nTopBound, bInfoScreen);
      break;
    case STAKEHOLDERSTATE_SCREEN_4:
      DrawStakeholderScreen4(nLeftBound, nRightBound, nTopBound);
      break;
  };
  
  if (bInfoScreen == false)
  {
    DrawButtons();
  }
}