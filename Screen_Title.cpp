
#include "ProjectRobot.h"

void StartTitleScreen()
{
  //objSound.PlaySoundFromResource(IDR_SOUND_STARTGAME);

  // First hide them all, then show what we want
  HideAndEnableAllButtons();

  ShowWindow(buttons[BUTTON_NEW]->GetHWND(), SW_SHOW);
  ShowWindow(buttons[BUTTON_LOAD]->GetHWND(), SW_SHOW);
}

void DrawTitleScreen()
{

  sprites[SPRITE_TITLE_BACKGROUND]->DrawFrame(wObj.getBackHDC(), 0, 0, 0);

  
  DrawButtons();
  
  /*sprites[SPRITE_TITLE_LOGO]->DrawTransFrame(wObj.getBackHDC(), 0, 
    wObj.Wid()/2 - sprites[SPRITE_TITLE_LOGO]->Wid()/2, 50);

  sprites[SPRITE_TITLE_COPYRIGHT]->DrawTransFrame(wObj.getBackHDC(), 0, 
    wObj.Wid()/2 - sprites[SPRITE_TITLE_COPYRIGHT]->Wid()/2, wObj.Hgt() - 80);*/
}