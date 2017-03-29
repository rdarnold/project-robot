

// A base subscreen class.  This is probably not good enough to be used on another game but
// it has some good basic ideas.

#include <windows.h>
#include <stdio.h>
#include "../_GSShared/GameButton.h"
#include "../_GSShared/LinkedList.h"

#ifndef SUBSCREEN_H
#define SUBSCREEN_H

// Just a linked list for gamebutton basically
class ButtonList : public LinkedList
{
  public:
    ButtonList()
    {
      pButton = 0;

      LinkedList::SetClassPointer(this);
    };

    void SetButton(GameButton *newBT)
    { 
      pButton = newBT;
    };

    GameButton *pButton;
};

// A sub-screen is a screen that shows up as an overlay to another screen -
// so it doesn't take up the whole screen.
class SubScreen
{
  public:
    SubScreen()
    {
      pButtonList = 0;
    };

    void AddButton(GameButton *newBT)
    {
      ButtonList *NewItem = new ButtonList();

      NewItem->SetButton(newBT);
      if (!pButtonList)
      {
        pButtonList = NewItem;
      }
      else
      {
        // When we do AddToFront we need to reset our pointer to the new
        // front of the list, which is returned in the AddToFront function
        pButtonList->AddToFront(NewItem);
        pButtonList = NewItem;
      }
    };

    // Regular virtual, not pure virtual.  This
    // really should be changed to a pure virtual in the future.
    virtual void Draw(HDC theHDC) { };

    void DrawButtonList(HDC theHDC)
    {
      ButtonList *pList = pButtonList;

      GameButton *button = pList->pButton;

      if (button && button->IsVisible()) {
        if (button->GetSel()) { // if selected 
          button->DrawTransClicked(theHDC, button->GetX(), button->GetY());
        } else {
          button->DrawTransNormal(theHDC, button->GetX(), button->GetY());
        }
      }

      while (pList)
      {
        button = pList->pButton;

        if (button && button->IsVisible()) {
          if (button->GetSel()) { // if selected 
            button->DrawTransClicked(theHDC, button->GetX(), button->GetY());
          } else {
            button->DrawTransNormal(theHDC, button->GetX(), button->GetY());
          }
        }

        pList = (ButtonList*)pList->GetNext();
      }
    };

    void DrawScreen(HDC theHDC)
    {
      Draw(theHDC);

      DrawButtonList(theHDC);
    };

  private:
    ButtonList *pButtonList;
};

#endif