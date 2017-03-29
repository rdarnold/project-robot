
// This is basically a file that contains things that are, or could be, common 
// to multiple different screens

#include "ProjectRobot.h"

/*
void PrintDateToString(int nTurn, char *strDate)
{
  char tempDate[2048];
  // Turns range from 0-19  
  if (nTurn < MAX_DEVELOPMENT_TURN)
  {
    // October, January, April, July
    switch (nTurn%4)
    {
      case 0:
        sprintf(tempDate, "Oct ");
        break;
      case 1:
        sprintf(tempDate, "Jan ");
        break;
      case 2:
        sprintf(tempDate, "Apr ");
        break;
      case 3:
        sprintf(tempDate, "Jul ");
        break;
    }
    
    if (nTurn < 4) {
      strcat(tempDate, "2055");
    }
    else if (nTurn < 8) {
      strcat(tempDate, "2056");
    }
    else {
      strcat(tempDate, "2057");
    }
  } 
  else 
  {
    sprintf(tempDate, "Jan %d", 2057 + nTurn - 9);
  }
  
  strcpy(strDate, tempDate);
}*/

void PrintDateToString(int nTurn, char *strDate)
{
  char tempDate[2048];
  tempDate[0] = 0;

  // Turns range from 0-21
  if (nTurn < MAX_DEVELOPMENT_TURN)
  {
    if (nTurn < 4) {
      strcat(tempDate, "Year 1");
    }
    else if (nTurn < 8) {
      strcat(tempDate, "Year 2");
    }
    else {
      strcat(tempDate, "Year 3");
    }

    sprintf(tempDate + strlen(tempDate), ", Quarter %d", (nTurn%4)+1);
  } 
  else 
  {
    sprintf(tempDate, "Year %d", nTurn - 8);
  }
  
  strcpy(strDate, tempDate);
}

void PrintNextDemoDate(int nTurn, char *strDate)
{
  if (nTurn >= MAX_DEVELOPMENT_TURN)
  {
    sprintf(strDate, "---");
    return;
  }

  int nDemoTurn = 4;
  if (nTurn < 4)
    nDemoTurn = 4;
  else if (nTurn < 8)
    nDemoTurn = 8;
  else
    nDemoTurn = MAX_DEVELOPMENT_TURN;  
  PrintDateToString(nDemoTurn, strDate);
}

// The window that shows resources, turns left, etc
void DrawResourceWindow()
{
  char text[2048];
  int x = 0, y = 0, nRightBound = 0;

  x = wObj.Wid() - sprites[SPRITE_RESOURCE_WINDOW]->Wid() - 2;
  y = 2;
  nRightBound = wObj.Wid();
  
  sprites[SPRITE_RESOURCE_WINDOW]->DrawFrame(wObj.getBackHDC(), 0, x, y);
  
  int nLineSpace = 16;
  y += nLineSpace;
  x += 12;

  GameFont *Font1 = GameFontYellow;
  GameFont *Font2 = GameFontOrange;

  Font1->DrawBoundedText(wObj.getBackHDC(), "Score: ", x, nRightBound,  y);
  sprintf(text, "%d", theGame.GetScore()); 
  Font2->DrawBoundedText(wObj.getBackHDC(), text, x + Font1->GetTextWidth("Score: "), nRightBound,  y);

  y+=nLineSpace;

  Font1->DrawBoundedText(wObj.getBackHDC(), "Resources: ", x, nRightBound,  y);
  sprintf(text, "%d", theGame.GetResources()); 
  Font2->DrawBoundedText(wObj.getBackHDC(), text, x + Font1->GetTextWidth("Resources: "), nRightBound,  y);

  y+=nLineSpace;

  Font1->DrawBoundedText(wObj.getBackHDC(), "Date: ", x, nRightBound,  y);
  PrintDateToString(theGame.GetTurn(), text);
  Font2->DrawBoundedText(wObj.getBackHDC(), text, x + Font1->GetTextWidth("Date: "), nRightBound,  y);

  y+=nLineSpace;

  Font1->DrawBoundedText(wObj.getBackHDC(), "Demo: ", x, nRightBound,  y);
  PrintNextDemoDate(theGame.GetTurn(), text);
  Font2->DrawBoundedText(wObj.getBackHDC(), text, x + Font1->GetTextWidth("Demo: "), nRightBound,  y);
    
  y+=nLineSpace;
  if (theGame.GetTurn() < MAX_DEVELOPMENT_TURN)
  {
    Font1->DrawBoundedText(wObj.getBackHDC(), "Field: ", x, nRightBound,  y);
    sprintf(text, "%d", theGame.GetResources()); 
    
    PrintDateToString(MAX_DEVELOPMENT_TURN, text);
    Font2->DrawBoundedText(wObj.getBackHDC(), text, x + Font1->GetTextWidth("Field: "), nRightBound,  y);
  }
  else
  {
    Font1->DrawBoundedText(wObj.getBackHDC(), "End of Life: ", x, nRightBound,  y);
    sprintf(text, "%d", theGame.GetResources()); 
    
    PrintDateToString(MAX_FIELDED_TURN, text);
    Font2->DrawBoundedText(wObj.getBackHDC(), text, x + Font1->GetTextWidth("End of Life: "), nRightBound,  y);
  }
}

