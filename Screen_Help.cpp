
/*

  The help screen shows you some general information about how things are judged and what
  they mean.

*/

#include "ProjectRobot.h"
#include "Screen_Stakeholders.h"

extern int nStakeholderTop;
extern int nStakeholderLeft;

extern void DrawSystemDesignScreen();

void StartHelpScreen()
{
  // We disable buttons instead of hiding them since this is an
  // "overlayed" screen (I HAVE to do this a better way in the future ...)
  DisableAllButtons();

  // Same background as the stakeholder screen so we can use the same parameters
  buttons[BUTTON_CANCEL]->MoveButton(nStakeholderLeft + sprites[SPRITE_INFO_PANEL]->Wid() - 
                                      buttons[BUTTON_CANCEL]->GetWidth() - 30, 
                                     nStakeholderTop + sprites[SPRITE_INFO_PANEL]->Hgt() - 
                                      buttons[BUTTON_CANCEL]->GetHeight()/2 - 5);
  buttons[BUTTON_CANCEL]->ShowButton();
  buttons[BUTTON_CANCEL]->EnableButton();
}

void HandleButtonHelp(int wmId)
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


char *Help1 =
"The parameters on the overall system screen are determined in the following ways: ";

char *Help2 =
"Overall System Specs count all relevant parts of the system and add them up.  For "
"example, Weight is the total weight of all parts of the Robot combined.  Maneuver "
"is determined mostly by the legs.  Cool need is the total need, in cooling, of all "
"the parts of the system, including equipment, that need to be offset by adding heat "
"sinks to the Robot.  The Max cool need is what your current heat sinks will allow.  Add more "
"heat sinks to increase this value.";

char *Help3 =
"Long and close range attacks are additive.  That is, if you add a single rifle as an accessory to "
"one of your robot's arms, and that rifle has an impact rating of 10, the overall long range "
"attacks impact rating of your robot will be 10.";

char *Help4 = 
"Defenses are averaged over all six systems that require defenses, which are the head, torso, right and left "
"arms, and right and left legs.  For example, the heat resist defense is the average of heat resist over all "
"six aforementioned systems; if they each have a heat resist value of 5, the overall will be 5.";

char *Help5 = 
"Sensors and heat sinks depend upon other systems.  Sensors, for instance, depend upon which "
"computer system you chose.  Different computer systems allow different types of sensors, and different cooling "
"systems allow different types of heat sinks.";

void DrawHelpScreen()
{
  // Start by drawing the underlying screen
  DrawSystemDesignScreen();

  // Now draw this screen
  sprites[SPRITE_OVERLAY]->DrawTransFrame(wObj.getBackHDC(), 0, 0, 0);

  sprites[SPRITE_INFO_PANEL]->DrawFrame(wObj.getBackHDC(), 0, 
                                        nStakeholderLeft, 
                                        nStakeholderTop);

  int nRightBound = nStakeholderLeft + sprites[SPRITE_INFO_PANEL]->Wid();
  int x = nStakeholderLeft + 15;
  int y = nStakeholderTop + 15;
  int nLineHeight = 10;
  
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), Help1, x, nRightBound, y);
  y += nLineHeight;
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), Help2, x, nRightBound, y);
  y += nLineHeight;
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), Help3, x, nRightBound, y);
  y += nLineHeight;
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), Help4, x, nRightBound, y);
  y += nLineHeight;
  y = GameFont6->DrawBoundedText(wObj.getBackHDC(), Help5, x, nRightBound, y);
  y += nLineHeight;

  // Then the buttons
  DrawEnabledButtons();
}