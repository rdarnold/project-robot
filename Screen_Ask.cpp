
/*

  Basically the same as the stakeholder screen,
  but this is accessed from the Ask button during the game

  Should probably change this filename since now it's the ask screen

*/

#include "ProjectRobot.h"
#include "Screen_Stakeholders.h"

extern int nStakeholderTop;
extern int nStakeholderLeft;

extern int g_nStakeholderState;

extern void DrawSystemDesignScreen();


void StartAskScreen()
{
  // We disable buttons instead of hiding them since this is an
  // "overlayed" screen (I HAVE to do this a better way in the future ...)
  DisableAllButtons();

  // We use the stakeholder screen
  StartStakeholderQuestionScreen();

  buttons[BUTTON_CANCEL]->MoveButton(nStakeholderLeft + sprites[SPRITE_INFO_PANEL]->Wid() - 
                                      buttons[BUTTON_CANCEL]->GetWidth() - 30, 
                                     nStakeholderTop + sprites[SPRITE_INFO_PANEL]->Hgt() - 
                                      buttons[BUTTON_CANCEL]->GetHeight()/2 - 5);
  buttons[BUTTON_CANCEL]->ShowButton();
  buttons[BUTTON_CANCEL]->EnableButton();

  g_nStakeholderState = STAKEHOLDERSTATE_SCREEN_3;
}

void HandleButtonAsk(int wmId)
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
    default:
    {
      HandleButtonStakeholder(wmId);
      break;
    }
  }
}

void DrawAskScreen()
{
  // Start by drawing the underlying screen
  DrawSystemDesignScreen();

  // Now draw the stakeholder screen
  DrawStakeholderScreen(true);

  // Then the buttons
  DrawEnabledButtons();
}