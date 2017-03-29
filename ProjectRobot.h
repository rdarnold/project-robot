
#if !defined(AFX_MECHANIC_H__6F349B51_1E9F_4CF1_9419_C9AC7FFA50CB__INCLUDED_)
#define AFX_MECHANIC_H__6F349B51_1E9F_4CF1_9419_C9AC7FFA50CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

#include "resource.h"

#include <stdio.h>
#include <fstream.h>
#include <time.h>
#include <commdlg.h> // this is for OPENFILENAME and such
#include <math.h>

//#include <shellapi.h> // For HDROP
//#define _WIN32_WINNT 0x502 // Needed for commctrl.h
//#include <commctrl.h> // For subclassing

#include "../_GSShared/Img.h"
#include "../_GSShared/Sprite.h"  
#include "../_GSShared/GameObj.h"  
#include "../_GSShared/Utilities.h"
#include "../_GSShared/CollisionUtils.h"
#include "../_GSShared/winobj.h"
#include "../_GSShared/GameButton.h" 
#include "../_GSShared/GameScrollBar.h" 
#include "../_GSShared/GameListBox.h" 
#include "../_GSShared/GameFont.h" 
#include "../_GSShared/Sound.h"
#include "../_GSShared/LinkedList.h" 

#define CANNOT_AFFORD "Your resources are too low to afford that!"

#define NUM_STARTING_QUESTIONS  10
#define NUM_QUESTIONS_PER_TURN  5
#define NUM_OVERHEAD_RESOURCES_PER_TURN  8

#define STRING_LENGTH 2048

#define DEFAULT_NEG_ONE -1

// define the screen resolution
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 800

#define MAX_DEVELOPMENT_TURN  12
#define MAX_FIELDED_TURN      22
#define MAX_TURN              22

/// ProjectRobot.cpp
void ReDraw(int force = 0);
void HideAndEnableAllButtons();
void EnableAllVisibleButtons(); 
void DisableAllButtons();
void ChangeScreen(int nNewScreen);
///

/// Random.cpp
void init_mm();
extern int number( int from, int to );
extern int number_not(int min, int max, int not);
///

#define MAX_NUM_STAKEHOLDER_CHANGES 2

// Holds the game data like the dates, player resources, etc
class GameData
{
  public:
    GameData() {
      Clear();
    }

    int  GetQuestionsLeft() {return nQuestions;};
    void SetQuestionsLeft(int nQues) {nQuestions = nQues;};
    int  SubtractQuestion() {nQuestions--; if (nQuestions == 0) return 0; else return 1;};
    void AddQuestions(int nAdd) {nQuestions += nAdd;};

    void IncreaseTurn() { nTurn++; };
    int GetTurn() { return nTurn; };
    int GetResources() { return nResources; };
    int GetTotalSystemCost() { return nTotalSystemCost; };
    int GetTotalSystemCostPerTurn() { return (nTotalSystemCost/(nTurn+1)); };
    int GetSystemCostThisYear() { return nSystemCostThisYear; };
    void ResetSystemCostThisYear() { nSystemCostThisYear = 0; };
    void AddResources(int nAdd) { nResources += nAdd; };
    void SubResources(int nSub) 
    { 
      nResources -= nSub; 
      nTotalSystemCost += nSub;
      nSystemCostThisYear += nSub;
    };

    int GetScore() { return nScore; };
    int AddToScoreFromStakeholder(int nAdd) 
    { 
      if (nTurn < MAX_DEVELOPMENT_TURN) 
      { 
        AddToScore(nAdd); 
        return nAdd; 
      } 
      return 0; 
    };
    void AddToScoreFromField(int nAdd) { AddToScore(nAdd); };

    void IncreaseRecordTurn() {nRecordTurn++;};

    void Clear()
    { 
      strScoreDesc[0] = 0;
      nQuestions = 0;
      nTurn = 0;
      nResources = 100;
      nTotalSystemCost = 0;
      nScore = 0;
      nSystemCostThisYear = 0;

      nRecordTurn = 0;

      nNumStakeholderChanges = 0;
      nNumStakeholderChangesField = 0;

      ResetStakeholderChangeDisplayed();

      for (int i = 0; i < MAX_NUM_STAKEHOLDER_CHANGES; i++)
      {
        nStakeholderChangeTurns[i] = 0;
        nStakeholderChangeNum[i] = 0;

        nStakeholderChangeFieldTurns[i] = 0;
        nStakeholderChangeFieldNum[i] = 0;
      }
    };
  
    // Lazy but I don't feel like making accessors for these
    int nNumStakeholderChanges;
    int nStakeholderChangeTurns[MAX_NUM_STAKEHOLDER_CHANGES];
    int nStakeholderChangeNum[MAX_NUM_STAKEHOLDER_CHANGES];
    bool bStakeholderChangeAck[MAX_NUM_STAKEHOLDER_CHANGES];

    int nNumStakeholderChangesField;
    int nStakeholderChangeFieldTurns[MAX_NUM_STAKEHOLDER_CHANGES];
    int nStakeholderChangeFieldNum[MAX_NUM_STAKEHOLDER_CHANGES];
    bool bStakeholderChangeFieldAck[MAX_NUM_STAKEHOLDER_CHANGES];

    char strScoreDesc[4096];

    void ResetStakeholderChangeDisplayed()
    {
      for (int i = 0; i < MAX_NUM_STAKEHOLDER_CHANGES; i++)
      {
        bStakeholderChangeAck[i] = 0;
        bStakeholderChangeFieldAck[i] = 0;
      }
    }

    void SetStakeholderChangeDisplayed(int nStakeholderNum, bool bVal)
    {
      if (nTurn < MAX_DEVELOPMENT_TURN)
      {
        bStakeholderChangeAck[nStakeholderNum] = bVal;
      }
      else
      {
        bStakeholderChangeFieldAck[nStakeholderNum] = bVal;
      }
    }

    bool WasStakeholderChangeDisplayed(int nStakeholderNum)
    {
      if (nTurn < MAX_DEVELOPMENT_TURN)
      {
        for (int i = 0; i < nNumStakeholderChanges; i++)
        { 
          if (nStakeholderChangeTurns[i] == nTurn &&
              nStakeholderChangeNum[i] == nStakeholderNum)
              return bStakeholderChangeAck[i];
        }
      } 
      else
      {
        for (int i = 0; i < nNumStakeholderChangesField; i++)
        {
          if (nStakeholderChangeFieldTurns[i] == nTurn &&
              nStakeholderChangeFieldNum[i] == nStakeholderNum)
              return bStakeholderChangeFieldAck[i];
        }
      }

      return false;
    }

    bool DidStakeholderChangeThisTurn(int nStakeholderNum)
    {
      if (nTurn < MAX_DEVELOPMENT_TURN)
      {
        for (int i = 0; i < nNumStakeholderChanges; i++)
        { 
          if (nStakeholderChangeTurns[i] == nTurn &&
              nStakeholderChangeNum[i] == nStakeholderNum)
              return true;
        }
      } 
      else
      {
        for (int i = 0; i < nNumStakeholderChangesField; i++)
        {
          if (nStakeholderChangeFieldTurns[i] == nTurn &&
              nStakeholderChangeFieldNum[i] == nStakeholderNum)
              return true;
        }
      }

      return false;
    }

    int GetStakeholderChangeThisTurn()
    { 
      if (nTurn < MAX_DEVELOPMENT_TURN)
      {
        for (int i = 0; i < nNumStakeholderChanges; i++)
        { 
          if (nStakeholderChangeTurns[i] == nTurn)
            return nStakeholderChangeNum[i];
        }
      } 
      else
      {
        for (int i = 0; i < nNumStakeholderChangesField; i++)
        {
          if (nStakeholderChangeFieldTurns[i] == nTurn)
            return nStakeholderChangeFieldNum[i];
        }
      }

      return -1;
    }

  private:
    void AddToScore(int nAdd) { nScore += nAdd; };

    int nQuestions;
    int nTurn;
    int nResources;
    int nTotalSystemCost;
    int nSystemCostThisYear;
    int nScore;

    int nRecordTurn;
};

extern int BUTTON_IMAGE_UNCLICKED;
extern int BUTTON_IMAGE_CLICKED;
extern int BUTTON_IMAGE_UNCLICKED_2;
extern int BUTTON_IMAGE_CLICKED_2;
extern int BUTTON_IMAGE_UNCLICKED_3;
extern int BUTTON_IMAGE_CLICKED_3;

enum
{
  SCREEN_TITLE,         
  SCREEN_INTRO,          
  SCREEN_STAKEHOLDER,    
  SCREEN_SYSTEM_DESIGN,
  SCREEN_END_TURN,
  SCREEN_CHANGE_SUB_SYSTEM,
  SCREEN_ASK,
  SCREEN_YOU_LOSE,
  SCREEN_END_GAME,
  SCREEN_INFO,
  SCREEN_HELP,
  SCREEN_SCORE_RECORD,
  NUM_SCREENS
};

// Just because I keep seeing a "0" as the first argument of
// a DrawFrame and not remembering what it means - this way
// I can write FRAME_ZERO and it'll be more clear
enum
{
  FRAME_ZERO = 0,
  FRAME_ONE = 1,
  FRAME_TWO = 2,
  FRAME_THREE = 3
};

// All the game sprite defines, we load them into an array to start so that we
// only ever have one copy of each
enum 
{
  SPRITE_TITLE_BACKGROUND,   
  SPRITE_LOGO,               
  SPRITE_BUTTONS_1,          
  SPRITE_GRID_BACKGROUND,    
  SPRITE_TITLE_LOGO,         
  SPRITE_TITLE_COPYRIGHT,    
  SPRITE_FONT_1,             
  SPRITE_INFO_PANEL,         
  SPRITE_FONT_2,             
  SPRITE_BUTTONS_2,          
  SPRITE_BUTTONS_PLUS,          
  SPRITE_FONT_3,             
  SPRITE_BUTTONS_FOR_TEXT,   
  SPRITE_INFO_PANEL_2,       
  SPRITE_BUTTONS_4,    
  SPRITE_FONT_4,
  SPRITE_FONT_5,
  SPRITE_FONT_6,
  SPRITE_FONT_7,
  SPRITE_FONT_8,
  SPRITE_FONT_9,
  SPRITE_FONT_10,
  SPRITE_BUTTONS_5,
  SPRITE_FONT_11,
  SPRITE_BUTTONS_6,
  SPRITE_RESOURCE_WINDOW,
  SPRITE_END_TURN_PANEL, 
  SPRITE_BUTTONS_FOR_TEXT_2, 
  SPRITE_BUTTONS_FOR_TEXT_3,  
  SPRITE_BUTTONS_PLUS_2,
  SPRITE_BUTTONS_SWITCH,
  SPRITE_BUTTONS_FOR_TEXT_4,  
  SPRITE_OVERLAY,
  SPRITE_FONT_12,
  SPRITE_BUTTONS_OVERVIEW,
  SPRITE_FONT_13,
  SPRITE_FONT_14,
  SPRITE_FONT_15,
  SPRITE_FONT_16,
  SPRITE_GIANT_ROBOT,
  SPRITE_POPUP_WINDOW,
  SPRITE_INFO_PANEL_LARGE,
  SPRITE_BUTTONS_FOR_SUBSCREEN_TEXT,
  MAX_SPRITES 
};

// The button defines for the array of GameButton objects
enum 
{
  BUTTON_NEW,    
  BUTTON_LOAD,   
  BUTTON_NEXT,
  BUTTON_PLUS_1,    
  BUTTON_PLUS_2,         
  BUTTON_PLUS_3,          
  BUTTON_PLUS_4,          
  BUTTON_PLUS_5,          
  BUTTON_PLUS_6,          
  BUTTON_PLUS_7,          
  BUTTON_PLUS_8,         
  BUTTON_PLUS_9,         
  BUTTON_PLUS_10,         
  BUTTON_PLUS_11,         
  BUTTON_PLUS_12,         
  BUTTON_PLUS_13,         
  BUTTON_PLUS_14,         
  BUTTON_PLUS_15,         
  BUTTON_PLUS_16,         
  BUTTON_PLUS_17,         
  BUTTON_PLUS_18,         
  BUTTON_PLUS_19,         
  BUTTON_PLUS_20,        
  BUTTON_PLUS_21,         
  BUTTON_PLUS_22,         
  BUTTON_PLUS_23,         
  BUTTON_PLUS_24,         
  BUTTON_PLUS_25,         
  BUTTON_PLUS_26,         
  BUTTON_PLUS_27,         
  BUTTON_PLUS_28,         
  BUTTON_PLUS_29,         
  BUTTON_PLUS_30,          
  BUTTON_INFO, 
  BUTTON_TEXT_1,         
  BUTTON_TEXT_2,         
  BUTTON_TEXT_3,         
  BUTTON_TEXT_4,         
  BUTTON_TEXT_5,         
  BUTTON_TEXT_6,         
  BUTTON_TEXT_7,         
  BUTTON_END,            
  BUTTON_MODEL,            
  BUTTON_HEAD,             
  BUTTON_TORSO,            
  BUTTON_ARM_RIGHT,        
  BUTTON_ARM_LEFT,         
  BUTTON_LEG_RIGHT,        
  BUTTON_LEG_LEFT,         
  BUTTON_EJECTION,         
  BUTTON_COOLING,          
  BUTTON_COMPUTER,         
  BUTTON_HUMAN_INTERFACE, 
  BUTTON_CHANGE,
  BUTTON_SELECT,
  BUTTON_SYSTEM_NEXT,
  BUTTON_SYSTEM_PREV,      
  BUTTON_TEXT_Q_1,         
  BUTTON_TEXT_Q_2,         
  BUTTON_TEXT_Q_3,         
  BUTTON_TEXT_Q_4,         
  BUTTON_TEXT_Q_5,         
  BUTTON_TEXT_Q_6,         
  BUTTON_TEXT_Q_7,  
  BUTTON_MORE_INFO,
  BUTTON_SWITCH_1,
  BUTTON_SWITCH_2,
  BUTTON_SWITCH_3,
  BUTTON_SWITCH_4,
  BUTTON_SWITCH_5,
  BUTTON_SWITCH_6,
  BUTTON_SWITCH_7,
  BUTTON_SWITCH_8,
  BUTTON_SWITCH_9,
  BUTTON_SWITCH_10,
  BUTTON_OK,
  BUTTON_CANCEL,
  BUTTON_SUBSYSTEM_1,
  BUTTON_SUBSYSTEM_2,
  BUTTON_SUBSYSTEM_3,
  BUTTON_SUBSYSTEM_4,
  BUTTON_SUBSYSTEM_5,
  BUTTON_SUBSYSTEM_6,
  BUTTON_SUBSYSTEM_7,
  BUTTON_SUBSYSTEM_8,
  BUTTON_SUBSYSTEM_9,
  BUTTON_SUBSYSTEM_10,
  BUTTON_SUBSYSTEM_11,
  BUTTON_SUBSYSTEM_12,
  BUTTON_SUBSYSTEM_13,
  BUTTON_SUBSYSTEM_14,
  BUTTON_SUBSYSTEM_15,
  BUTTON_OVERVIEW,        
  BUTTON_ONROBOT_HEAD,             
  BUTTON_ONROBOT_TORSO,            
  BUTTON_ONROBOT_ARM_RIGHT,        
  BUTTON_ONROBOT_ARM_LEFT,         
  BUTTON_ONROBOT_LEG_RIGHT,        
  BUTTON_ONROBOT_LEG_LEFT,
  BUTTON_ASK,
  BUTTON_RETRY,
  BUTTON_POPUP_OK,  
  BUTTON_HELP,
  BUTTON_MORE,
  BUTTON_SAVE,
  MAX_BUTTONS           
};

#define MAX_SUBSYSTEM_BUTTON  BUTTON_SUBSYSTEM_15
#define MAX_PLUS_BUTTON       BUTTON_PLUS_30
#define MAX_SWITCH_BUTTON     BUTTON_SWITCH_10

// These are used widely so we include them here
extern void DrawButtons();
extern void DrawEnabledButtons();

extern CWinObj wObj; // Our Window object
extern Sprite *sprites[MAX_SPRITES];
extern GameButton *buttons[MAX_BUTTONS];

extern GameFont *GameFont1;
extern GameFont *GameFont2;
extern GameFont *GameFont3;
extern GameFont *GameFont4;
extern GameFont *GameFont5;
extern GameFont *GameFont6;
extern GameFont *GameFont7;
extern GameFont *GameFont8;
extern GameFont *GameFont9;
extern GameFont *GameFont10;
extern GameFont *GameFont11;
extern GameFont *GameFont12;
extern GameFont *GameFont13;
extern GameFont *GameFont14;
extern GameFont *GameFont15;
extern GameFont *GameFont16;

extern GameFont *GameFontGreen;
extern GameFont *GameFontRed;
extern GameFont *GameFontOrange;
extern GameFont *GameFontDarkBlue;
extern GameFont *GameFontYellow;
extern GameFont *GameFontLightBlue;
extern GameFont *GameFontDarkGray;
extern GameFont *GameFontLightGray;
extern GameFont *GameFontGreenNum;
extern GameFont *GameFontOrangeNum;

extern GameData theGame;
extern Sound objSound;

// buff is just for ease of printing
extern char buff[STRING_LENGTH];

#endif // !defined(AFX_MECHANIC_H__6F349B51_1E9F_4CF1_9419_C9AC7FFA50CB__INCLUDED_)
