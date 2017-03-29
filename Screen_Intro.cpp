

#include "ProjectRobot.h"
#include "TextDefines.h"

enum
{
  INTROSTATE_SCREEN_1,  
  INTROSTATE_SCREEN_2,  
  NUM_INTROSTATE_SCREENS
};

int g_nIntroState = INTROSTATE_SCREEN_1;

extern int nStakeholderTop;
extern int nStakeholderLeft;

void StartIntroScreen()
{
  g_nIntroState = INTROSTATE_SCREEN_1;

  // First hide them all, then show what we want
  HideAndEnableAllButtons();
  
  nStakeholderLeft = wObj.Wid()/2 - sprites[SPRITE_INFO_PANEL]->Wid()/2;
  nStakeholderTop = wObj.Hgt()/2 - sprites[SPRITE_INFO_PANEL]->Hgt()/2;

  buttons[BUTTON_NEXT]->MoveButton(nStakeholderLeft + sprites[SPRITE_INFO_PANEL]->Wid() - 
                                      buttons[BUTTON_NEXT]->GetWidth() - 30, 
                                   nStakeholderTop + sprites[SPRITE_INFO_PANEL]->Hgt() - 
                                      buttons[BUTTON_NEXT]->GetHeight()/2 - 5);
  buttons[BUTTON_NEXT]->ShowButton();
}

int IntroScreenNext()
{
  g_nIntroState++;

  if (g_nIntroState >= 2)
    return false;

  return true;
}

void DrawIntroScreen()
{
  sprites[SPRITE_GRID_BACKGROUND]->DrawFrame(wObj.getBackHDC(), 0, 0, 0);
  
  sprites[SPRITE_LOGO]->DrawFrame(wObj.getBackHDC(), 0, wObj.Wid()/2 - sprites[SPRITE_LOGO]->Wid()/2, 4);
  
  sprites[SPRITE_INFO_PANEL]->DrawFrame(wObj.getBackHDC(), 0, 
    wObj.Wid()/2 - sprites[SPRITE_INFO_PANEL]->Wid()/2, 
    wObj.Hgt()/2 - sprites[SPRITE_INFO_PANEL]->Hgt()/2);

  int nLeftBound = wObj.Wid()/2 - sprites[SPRITE_INFO_PANEL]->Wid()/2 + 30;
  int nRightBound = wObj.Wid()/2 - sprites[SPRITE_INFO_PANEL]->Wid()/2 + sprites[SPRITE_INFO_PANEL]->Wid() - 30;
  int nTopBound = wObj.Hgt()/2 - sprites[SPRITE_INFO_PANEL]->Hgt()/2 + 60;

  switch (g_nIntroState)
  {
    case INTROSTATE_SCREEN_1:
    {
      int y = GameFont6->DrawBoundedText(wObj.getBackHDC(), IntroText, nLeftBound, nRightBound, nTopBound);
      //buttons[BUTTON_NEXT]->MoveButton(85, y + 30);
      break;
    }
    case INTROSTATE_SCREEN_2:
    {
      int y = GameFont6->DrawBoundedText(wObj.getBackHDC(), FirstTaskText, nLeftBound, nRightBound, nTopBound);
      //buttons[BUTTON_NEXT]->MoveButton(85, y + 30);
      break;
    }
  }
  
  DrawButtons();
}