

// All the class implementation features are in the header.  this is just some basic 
// data manipulation.


#include "PopupWindow.h"
#include "ProjectRobot.h"

PopupWindow *pPop = 0;
PopupWindow *pEndTurnPop = 0;

bool ButtonsEnabled[MAX_BUTTONS];
bool ButtonsVisible[MAX_BUTTONS];

// Take a snapshot of what the buttons look like at a certain time
void CaptureButtonStates()
{
  for (int i = 0; i < MAX_BUTTONS; i++)
  {
    if (buttons[i]->IsEnabled())
      ButtonsEnabled[i] = true;
    else
      ButtonsEnabled[i] = false;
    
    if (buttons[i]->IsVisible())
      ButtonsVisible[i] = true;
    else
      ButtonsVisible[i] = false;
  }
}

void ClosePopup()
{
  if (pPop)
  {
    // Use the captured states to reset the buttons
    for (int i = 0; i < MAX_BUTTONS; i++)
    {
      if (ButtonsEnabled[i] == true)
        buttons[i]->EnableButton();
      else
        buttons[i]->DisableButton();
    
      if (ButtonsVisible[i] == true)
        buttons[i]->ShowButton();
      else
        buttons[i]->HideButton();
    }

    pPop->GetButton()->HideButton();
    
    delete pPop;
    pPop = 0;
  } 
  else if (pEndTurnPop)
  {
    // Use the captured states to reset the buttons
    for (int i = 0; i < MAX_BUTTONS; i++)
    {
      if (ButtonsEnabled[i] == true)
        buttons[i]->EnableButton();
      else
        buttons[i]->DisableButton();
    
      if (ButtonsVisible[i] == true)
        buttons[i]->ShowButton();
      else
        buttons[i]->HideButton();
    }

    pEndTurnPop->GetButton()->HideButton();
    
    delete pEndTurnPop;
    pEndTurnPop = 0;
  }
}

void ShowPopup(char *text)
{
  // Delete one if we have it
  if (pPop)
  {
    delete pPop;
    pPop = 0;
  }

  pPop = new PopupWindow(sprites[SPRITE_POPUP_WINDOW]);

  pPop->SetButton(buttons[BUTTON_POPUP_OK]);
  pPop->SetFont(GameFont2);
  pPop->SetText(text);

  pPop->Move(SCREEN_WIDTH/2 - sprites[SPRITE_POPUP_WINDOW]->GetFrameWidth(0)/2, SCREEN_HEIGHT/2 - sprites[SPRITE_POPUP_WINDOW]->GetFrameHeight(0)/2);

  // Capture all the states of the buttons
  CaptureButtonStates();

  // Disable them all
  DisableAllButtons();

  // And just enable the one on the popup
  pPop->GetButton()->EnableButton();
  pPop->GetButton()->ShowButton();
}

void ShowEndTurnPopup(Sprite *pSpr)
{
  // Delete one if we have it
  if (pEndTurnPop)
  {
    delete pEndTurnPop;
    pEndTurnPop = 0;
  }

  pEndTurnPop = new PopupWindow(pSpr);

  pEndTurnPop->SetButton(buttons[BUTTON_POPUP_OK]);
  pEndTurnPop->SetFont(GameFont6);

  if (theGame.strScoreDesc[0])
    pEndTurnPop->SetText(theGame.strScoreDesc);
  else
    pEndTurnPop->SetText("Nothing to report");

  pEndTurnPop->Move(SCREEN_WIDTH/2 - pSpr->GetFrameWidth(0)/2, SCREEN_HEIGHT/2 - pSpr->GetFrameHeight(0)/2);

  // Add a little more space to this popup, it doesn't seem to draw right,
  // this is probably not the best fix but whatever
  pEndTurnPop->SetRightOffset(25);

  // Capture all the states of the buttons
  CaptureButtonStates();

  // Disable them all
  DisableAllButtons();

  // And just enable the one on the popup
  pEndTurnPop->GetButton()->EnableButton();
  pEndTurnPop->GetButton()->ShowButton();
}
