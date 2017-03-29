

// This is just a crappy version of a popup window
// This class can be redone in a much better way if I actually use a real windows dialog for this
// and ownerdraw it - that's the way to do it in the future

#include <windows.h>
#include <stdio.h>
#include "../_GSShared/Sprite.h"
#include "../_GSShared/GameFont.h"
#include "../_GSShared/GameButton.h"
#include "../_GSShared/LinkedList.h"

#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

void ClosePopup();
void CloseEndTurnPopup();
void ShowPopup(char *text);
void ShowEndTurnPopup(Sprite *pSpr);

class PopupWindow 
{
  public:
    PopupWindow(Sprite *newSpr) { spr = newSpr; button = 0; gf = 0; strText[0] = 0; nRightOffset = 15;}; 
  
    void SetText(char *text) { sprintf(strText, "%s", text); };
    void SetSprite(Sprite *newSpr) { spr = newSpr; }; 
    void SetFont(GameFont *newGf) { gf = newGf; };
    void SetButton(GameButton *newBt) 
    { 
      button = newBt; 
      if (spr)
      {
        button->MoveButton(
          x + spr->GetFrameWidth(0)/2 - button->GetWidth()/2,
          y + spr->GetFrameHeight(0) - button->GetHeight() - 5);
      }
    };
  
    void Move(int newX, int newY) 
    { 
      x = newX; 
      y = newY; 
    
      // Align the button to the center bottom of the window
      if (spr)
      {
        button->MoveButton(
          x + spr->GetFrameWidth(0)/2 - button->GetWidth()/2,
          y + spr->GetFrameHeight(0) - button->GetHeight() - 15);
      }
    };
  
    void Draw(HDC theHDC, int x, int y) 
    {
      // First the background
      if (spr)
      {  
        spr->DrawFrame(theHDC, 0, x, y);
      }

      // Now the text
      if (gf)
      {
        gf->DrawBoundedText(theHDC, strText, x + 29, x + spr->GetFrameWidth(0) - nRightOffset, y + 25);
      }
    
      if (button && IsWindowVisible(button->GetHWND())) {
        if (button->GetSel()) { // if selected 
          button->DrawTransClicked(theHDC, button->GetX(), button->GetY());
        } else {
          button->DrawTransNormal(theHDC, button->GetX(), button->GetY());
        }
      }
    };

    void SetRightOffset(int nNewRightOffset) {nRightOffset = nNewRightOffset;};

    void Draw(HDC theHDC) { Draw(theHDC, this->x, this->y); };

    GameButton  *GetButton() { return button; };
    Sprite      *GetSprite() { return spr; };
    GameFont    *GetFont() { return gf; };
    char        *GetText() { return strText; };
 
  private:
    Sprite *spr;
    GameFont *gf;
    GameButton *button;

    char strText[10000];
    
    int x;
    int y;

    // How far from the edge of the sprite do we want the rightbound to be
    // for font drawing?
    int nRightOffset;
};


extern PopupWindow *pPop;
extern PopupWindow *pEndTurnPop;

#endif