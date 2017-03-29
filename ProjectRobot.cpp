// PROJECTROBOT.cpp : Defines the entry point for the application.
//

#include "ProjectRobot.h"
#include "Screen_Title.h"
#include "Screen_Intro.h"
#include "Screen_Stakeholders.h"
#include "Screen_SystemDesign.h"
#include "Screen_End_Turn.h"
#include "System_Models.h"
#include "Screen_Change_SubSystem.h"
#include "Screen_Ask.h"
#include "Screen_Info.h"
#include "Screen_Help.h"
#include "System_Fielded.h"
#include "System_Restrictions.h"
#include "PopupWindow.h"

#define MAX_LOADSTRING 100

// Font sprite setup comes from ProjectRobot_Fonts.cpp since it's
// so huge
extern void SetupFontSprites();
extern void StartGame(); // in System_Fielded.cpp

// Global Variables:
HINSTANCE hInst;								// current instance
HWND hWnd;
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

CWinObj wObj; // Our Window object

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

bool draw = false;
int nScreen = SCREEN_TITLE;

// These are the frames for the generic buttons when clicked
// and unclicked, we set them to the correct frames when we
// load the actual sprites
int BUTTON_IMAGE_UNCLICKED = 0;
int BUTTON_IMAGE_CLICKED = 0;
int BUTTON_IMAGE_UNCLICKED_2 = 0;
int BUTTON_IMAGE_CLICKED_2 = 0;
int BUTTON_IMAGE_UNCLICKED_3 = 0;
int BUTTON_IMAGE_CLICKED_3 = 0;

// Just a generic string to print to so I don't have to declare
// them everywhere, kind of 'bad practice' but it makes it faster
// and time is what I lack right now
char buff[STRING_LENGTH];

// For these games, perhaps our objects should be linked list
Sprite *sprites[MAX_SPRITES];
GameButton *buttons[MAX_BUTTONS];

GameFont *GameFont1 = 0;
GameFont *GameFont2 = 0;
GameFont *GameFont3 = 0;
GameFont *GameFont4 = 0;
GameFont *GameFont5 = 0;
GameFont *GameFont6 = 0;
GameFont *GameFont7 = 0;
GameFont *GameFont8 = 0;
GameFont *GameFont9 = 0;
GameFont *GameFont10 = 0;
GameFont *GameFont11 = 0;
GameFont *GameFont12 = 0;
GameFont *GameFont13 = 0;
GameFont *GameFont14 = 0;
GameFont *GameFont15 = 0;
GameFont *GameFont16 = 0;

GameFont *GameFontGreen = 0;
GameFont *GameFontRed = 0;
GameFont *GameFontOrange = 0;
GameFont *GameFontDarkBlue = 0;
GameFont *GameFontYellow = 0;
GameFont *GameFontLightBlue = 0;
GameFont *GameFontDarkGray = 0;
GameFont *GameFontLightGray = 0;
GameFont *GameFontGreenNum = 0;
GameFont *GameFontOrangeNum = 0;

Sound objSound;    // The global sound object

GameData theGame;

// This is pulled into a separate function to reduce the complexity of looking through the function
void SetupGiantRobotSprites()
{
  Sprite *pSpr = sprites[SPRITE_GIANT_ROBOT];

  pSpr->SetTransColor(RGB(0, 0, 0));

  // We sit two robot pictures next to each other in the sprite, 
  // so the width of one of them is half the total sprite width
  int nOneRobotWidth = pSpr->Wid()/2;

  // Height is just the sprite height but for ease of changing I made it
  // into a variable here
  int nOneRobotHeight = pSpr->Hgt();

  // Frame 0 is the whole thing
  pSpr->CreateFrame(0, nOneRobotWidth, 0, nOneRobotHeight);

  // Head
  pSpr->CreateFrame(66, 105, 0, 87);
  pSpr->CreateFrame(66 + nOneRobotWidth, 105 + nOneRobotWidth, 0, 87);

  // Torso
  pSpr->CreateFrame(58, 131, 87, 186);
  pSpr->CreateFrame(58 + nOneRobotWidth, 131 + nOneRobotWidth, 87, 186);

  // Right arm
  pSpr->CreateFrame(132, 187, 37, 203);
  pSpr->CreateFrame(132 + nOneRobotWidth, 187 + nOneRobotWidth, 37, 203);

  // Left arm
  pSpr->CreateFrame(0, 59, 49, 185);
  pSpr->CreateFrame(0 + nOneRobotWidth, 59 + nOneRobotWidth, 49, 185);

  // Right leg
  pSpr->CreateFrame(100, nOneRobotWidth, 203, nOneRobotHeight);
  pSpr->CreateFrame(100 + nOneRobotWidth, nOneRobotWidth + nOneRobotWidth, 203, nOneRobotHeight);

  // Left leg
  pSpr->CreateFrame(0, 92, 185, 344);
  pSpr->CreateFrame(0 + nOneRobotWidth, 92 + nOneRobotWidth, 185, 344);
}

// Set up all the frames and such
void SetupAllSprites()
{
  // First set up the main sprites for the actual robot drawing
  SetupGiantRobotSprites();

  /*sprites[0]->CreateFrame(0, 150, 0, 90);
  sprites[0]->CreateFrame(0, 150, 90, 180);
  sprites[0]->CreateFrame(0, 150, 180, 270);*/

  sprites[SPRITE_TITLE_BACKGROUND]->SetTransColor(RGB(255, 255, 255));
  sprites[SPRITE_TITLE_BACKGROUND]->CreateFrame(0, sprites[SPRITE_TITLE_BACKGROUND]->Wid(), 0, sprites[SPRITE_TITLE_BACKGROUND]->Hgt());

  sprites[SPRITE_LOGO]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_LOGO]->CreateFrame(0, sprites[SPRITE_LOGO]->Wid(), 0, sprites[SPRITE_LOGO]->Hgt());
  //sprites[SPRITE_LOGO]->CreateFrame(1, sprites[SPRITE_LOGO]->Wid(), sprites[SPRITE_LOGO]->Hgt()/2, sprites[SPRITE_LOGO]->Hgt());

  sprites[SPRITE_TITLE_LOGO]->SetTransColor(RGB(255, 255, 255));
  sprites[SPRITE_TITLE_LOGO]->CreateFrame(0, sprites[SPRITE_TITLE_LOGO]->Wid(), 0, sprites[SPRITE_TITLE_LOGO]->Hgt());

  sprites[SPRITE_TITLE_COPYRIGHT]->SetTransColor(RGB(255, 255, 255));
  sprites[SPRITE_TITLE_COPYRIGHT]->CreateFrame(0, sprites[SPRITE_TITLE_COPYRIGHT]->Wid(), 0, sprites[SPRITE_TITLE_COPYRIGHT]->Hgt());

  sprites[SPRITE_GRID_BACKGROUND]->SetTransColor(RGB(255, 255, 255));
  sprites[SPRITE_GRID_BACKGROUND]->CreateFrame(0, sprites[SPRITE_GRID_BACKGROUND]->Wid(), 0, sprites[SPRITE_GRID_BACKGROUND]->Hgt());

  sprites[SPRITE_INFO_PANEL]->SetTransColor(RGB(255, 255, 255));
  sprites[SPRITE_INFO_PANEL]->CreateFrame(0, sprites[SPRITE_INFO_PANEL]->Wid(), 0, sprites[SPRITE_INFO_PANEL]->Hgt());

  sprites[SPRITE_INFO_PANEL_LARGE]->SetTransColor(RGB(255, 255, 255));
  sprites[SPRITE_INFO_PANEL_LARGE]->CreateFrame(0, sprites[SPRITE_INFO_PANEL_LARGE]->Wid(), 0, sprites[SPRITE_INFO_PANEL_LARGE]->Hgt());

  sprites[SPRITE_INFO_PANEL_2]->SetTransColor(RGB(255, 255, 255));
  sprites[SPRITE_INFO_PANEL_2]->CreateFrame(0, sprites[SPRITE_INFO_PANEL_2]->Wid(), 0, sprites[SPRITE_INFO_PANEL_2]->Hgt());

  sprites[SPRITE_RESOURCE_WINDOW]->SetTransColor(RGB(255, 255, 255));
  sprites[SPRITE_RESOURCE_WINDOW]->CreateFrame(0, sprites[SPRITE_RESOURCE_WINDOW]->Wid(), 0, sprites[SPRITE_RESOURCE_WINDOW]->Hgt());

  sprites[SPRITE_END_TURN_PANEL]->SetTransColor(RGB(255, 255, 255));
  sprites[SPRITE_END_TURN_PANEL]->CreateFrame(0, sprites[SPRITE_END_TURN_PANEL]->Wid(), 0, sprites[SPRITE_END_TURN_PANEL]->Hgt());

  sprites[SPRITE_OVERLAY]->SetTransColor(RGB(255, 255, 255));
  sprites[SPRITE_OVERLAY]->CreateFrame(0, sprites[SPRITE_OVERLAY]->Wid(), 0, sprites[SPRITE_OVERLAY]->Hgt());

  sprites[SPRITE_POPUP_WINDOW]->SetTransColor(RGB(255, 255, 255));
  sprites[SPRITE_POPUP_WINDOW]->CreateFrame(0, sprites[SPRITE_POPUP_WINDOW]->Wid(), 0, sprites[SPRITE_POPUP_WINDOW]->Hgt());


  // These sprites have black background
  sprites[SPRITE_BUTTONS_1]->SetTransColor(RGB(0, 0, 0));
  BUTTON_IMAGE_UNCLICKED = sprites[SPRITE_BUTTONS_1]->CreateFrame(0, 66, 0, 66);
  BUTTON_IMAGE_CLICKED   = sprites[SPRITE_BUTTONS_1]->CreateFrame(0, 
     sprites[SPRITE_BUTTONS_1]->GetFrameWidth(BUTTON_IMAGE_UNCLICKED), 
     sprites[SPRITE_BUTTONS_1]->GetFrameHeight(BUTTON_IMAGE_UNCLICKED), 
     sprites[SPRITE_BUTTONS_1]->GetFrameHeight(BUTTON_IMAGE_UNCLICKED)*2);

  // These sprites have black background
  sprites[SPRITE_BUTTONS_2]->SetTransColor(RGB(0, 0, 0));
  BUTTON_IMAGE_UNCLICKED_2 = sprites[SPRITE_BUTTONS_2]->CreateFrame(0, 149, 0, 37);
  BUTTON_IMAGE_CLICKED_2   = sprites[SPRITE_BUTTONS_2]->CreateFrame(0, 
     sprites[SPRITE_BUTTONS_2]->GetFrameWidth(BUTTON_IMAGE_UNCLICKED_2), 
     sprites[SPRITE_BUTTONS_2]->GetFrameHeight(BUTTON_IMAGE_UNCLICKED_2), 
     sprites[SPRITE_BUTTONS_2]->GetFrameHeight(BUTTON_IMAGE_UNCLICKED_2)*2);

  // The button with the plus/minus on it
  sprites[SPRITE_BUTTONS_PLUS]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_BUTTONS_PLUS]->CreateFrame(0,  25,  0, 25);
  sprites[SPRITE_BUTTONS_PLUS]->CreateFrame(0,  25, 25, 50);
  sprites[SPRITE_BUTTONS_PLUS]->CreateFrame(25, 50,  0, 25);
  sprites[SPRITE_BUTTONS_PLUS]->CreateFrame(25, 50, 25, 50);

  // The other plus buttons  
  sprites[SPRITE_BUTTONS_PLUS_2]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_BUTTONS_PLUS_2]->CreateFrame(0,  14,  0, 15);
  sprites[SPRITE_BUTTONS_PLUS_2]->CreateFrame(0,  14, 15, 30);

  // Switch buttons
  sprites[SPRITE_BUTTONS_SWITCH]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_BUTTONS_SWITCH]->CreateFrame(0,  24,  0, 15);
  sprites[SPRITE_BUTTONS_SWITCH]->CreateFrame(0,  24, 15, 30);

  // Overview buttons
  sprites[SPRITE_BUTTONS_OVERVIEW]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_BUTTONS_OVERVIEW]->CreateFrame(0,  180,  0, 56);
  sprites[SPRITE_BUTTONS_OVERVIEW]->CreateFrame(0,  180, 56, 112);

  sprites[SPRITE_BUTTONS_4]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_BUTTONS_4]->CreateFrame(0,  118,  0, 28);
  sprites[SPRITE_BUTTONS_4]->CreateFrame(0,  118, 28, 56);
  // This last frame is the box that shows around the selected system
  // in the System Design screen
  sprites[SPRITE_BUTTONS_4]->CreateFrame(0,  132, 56, 99);

  // Buttons for text background, like buttons that look as though
  // you're clicking actual text
  sprites[SPRITE_BUTTONS_FOR_TEXT]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_BUTTONS_FOR_TEXT]->CreateFrame(0,  434,  0, 17);
  sprites[SPRITE_BUTTONS_FOR_TEXT]->CreateFrame(0,  434, 17, 34);

  sprites[SPRITE_BUTTONS_FOR_TEXT_2]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_BUTTONS_FOR_TEXT_2]->CreateFrame(0,  299,  0, 17);
  sprites[SPRITE_BUTTONS_FOR_TEXT_2]->CreateFrame(0,  299, 17, 34);

  sprites[SPRITE_BUTTONS_FOR_TEXT_3]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_BUTTONS_FOR_TEXT_3]->CreateFrame(0,  192,  0, 17);
  sprites[SPRITE_BUTTONS_FOR_TEXT_3]->CreateFrame(0,  192, 17, 34);
  
  sprites[SPRITE_BUTTONS_FOR_TEXT_4]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_BUTTONS_FOR_TEXT_4]->CreateFrame(0,  265,  0, 17);
  sprites[SPRITE_BUTTONS_FOR_TEXT_4]->CreateFrame(0,  265, 17, 34);

  sprites[SPRITE_BUTTONS_FOR_SUBSCREEN_TEXT]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_BUTTONS_FOR_SUBSCREEN_TEXT]->CreateFrame(0,  202,  0, 17);
  sprites[SPRITE_BUTTONS_FOR_SUBSCREEN_TEXT]->CreateFrame(0,  202, 17, 34);

  sprites[SPRITE_BUTTONS_5]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_BUTTONS_5]->CreateFrame(0,  116,  0, 28);
  sprites[SPRITE_BUTTONS_5]->CreateFrame(0,  116,  28, 56);
  
  sprites[SPRITE_BUTTONS_6]->SetTransColor(RGB(0, 0, 0));
  /*sprites[SPRITE_BUTTONS_6]->CreateFrame(0,  55,  0, 28);
  sprites[SPRITE_BUTTONS_6]->CreateFrame(0,  55,  28, 56);
  sprites[SPRITE_BUTTONS_6]->CreateFrame(55, 110,  0, 28);
  sprites[SPRITE_BUTTONS_6]->CreateFrame(55, 110,  28, 56);*/
  sprites[SPRITE_BUTTONS_6]->CreateFrame(0,  33,  0, 24);
  sprites[SPRITE_BUTTONS_6]->CreateFrame(0,  33, 24, 48);
  sprites[SPRITE_BUTTONS_6]->CreateFrame(33, 66,  0, 24);
  sprites[SPRITE_BUTTONS_6]->CreateFrame(33, 66, 24, 48);

  // Now set up all the font sprites, this is done in a separate file
  // since it requires so many lines of code 
  SetupFontSprites();
}

Sprite *LoadSprite(int resource_id)
{
  Sprite *spr = 0;
  HBITMAP handle;
  handle = LoadBitmap(hInst, MAKEINTRESOURCE(resource_id));
  spr = new Sprite(wObj.getHDC(), handle);
  return spr;
}

// Load all the sprites
void LoadAllSprites()
{ 
  // Init to 0 so we can later delete
  for (int i = 0; i < MAX_SPRITES; i++) {
    sprites[i] = 0;
  }

  sprites[SPRITE_TITLE_BACKGROUND] = LoadSprite(IDB_TITLE_BACKGROUND);
  sprites[SPRITE_LOGO] = LoadSprite(IDB_LOGO);
  sprites[SPRITE_BUTTONS_1] = LoadSprite(IDB_BUTTON_SPRITE);
  sprites[SPRITE_GRID_BACKGROUND] = LoadSprite(IDB_GRID_BACKGROUND);
  sprites[SPRITE_TITLE_LOGO] = LoadSprite(IDB_TITLE_LOGO);
  sprites[SPRITE_TITLE_COPYRIGHT] = LoadSprite(IDB_TITLE_COPYRIGHT);
  sprites[SPRITE_FONT_1] = LoadSprite(IDB_FONT_1);
  sprites[SPRITE_INFO_PANEL] = LoadSprite(IDB_INFO_PANEL);
  sprites[SPRITE_FONT_2] = LoadSprite(IDB_FONT_2);
  sprites[SPRITE_BUTTONS_2] = LoadSprite(IDB_BUTTON_SPRITE_2);
  sprites[SPRITE_BUTTONS_PLUS] = LoadSprite(IDB_BUTTON_SPRITE_PLUS);
  sprites[SPRITE_FONT_3] = LoadSprite(IDB_FONT_3);
  sprites[SPRITE_BUTTONS_FOR_TEXT] = LoadSprite(IDB_BUTTON_SPRITE_FOR_TEXT);
  sprites[SPRITE_INFO_PANEL_2] = LoadSprite(IDB_INFO_PANEL_2);
  sprites[SPRITE_BUTTONS_4] = LoadSprite(IDB_BUTTON_SPRITE_4);
  sprites[SPRITE_FONT_4] = LoadSprite(IDB_FONT_4);
  sprites[SPRITE_FONT_5] = LoadSprite(IDB_FONT_5);
  sprites[SPRITE_FONT_6] = LoadSprite(IDB_FONT_6);
  sprites[SPRITE_FONT_7] = LoadSprite(IDB_FONT_7);
  sprites[SPRITE_FONT_8] = LoadSprite(IDB_FONT_8);
  sprites[SPRITE_FONT_9] = LoadSprite(IDB_FONT_9);
  sprites[SPRITE_FONT_10] = LoadSprite(IDB_FONT_10);
  sprites[SPRITE_BUTTONS_5] = LoadSprite(IDB_BUTTON_SPRITE_5);
  sprites[SPRITE_FONT_11] = LoadSprite(IDB_FONT_11);
  sprites[SPRITE_BUTTONS_6] = LoadSprite(IDB_BUTTON_SPRITE_6);
  sprites[SPRITE_RESOURCE_WINDOW] = LoadSprite(IDB_RESOURCE_WINDOW);
  sprites[SPRITE_END_TURN_PANEL] = LoadSprite(IDB_END_TURN_PANEL);
  sprites[SPRITE_BUTTONS_FOR_TEXT_2] = LoadSprite(IDB_BUTTON_SPRITE_FOR_TEXT_2);
  sprites[SPRITE_BUTTONS_FOR_TEXT_3] = LoadSprite(IDB_BUTTON_SPRITE_FOR_TEXT_3);
  sprites[SPRITE_BUTTONS_PLUS_2] = LoadSprite(IDB_BUTTON_SPRITE_PLUS_2);
  sprites[SPRITE_BUTTONS_SWITCH] = LoadSprite(IDB_BUTTON_SPRITE_SWITCH);
  sprites[SPRITE_BUTTONS_FOR_TEXT_4] = LoadSprite(IDB_BUTTON_SPRITE_FOR_TEXT_4);
  sprites[SPRITE_OVERLAY] = LoadSprite(IDB_OVERLAY);
  sprites[SPRITE_FONT_12] = LoadSprite(IDB_FONT_12);
  sprites[SPRITE_BUTTONS_OVERVIEW] = LoadSprite(IDB_BUTTON_SPRITE_OVERVIEW);
  sprites[SPRITE_FONT_13] = LoadSprite(IDB_FONT_13);
  sprites[SPRITE_FONT_14] = LoadSprite(IDB_FONT_14);
  sprites[SPRITE_FONT_15] = LoadSprite(IDB_FONT_15);
  sprites[SPRITE_FONT_16] = LoadSprite(IDB_FONT_16);
  sprites[SPRITE_GIANT_ROBOT] = LoadSprite(IDB_GIANT_ROBOT);
  sprites[SPRITE_POPUP_WINDOW] = LoadSprite(IDB_POPUP_WINDOW);
  sprites[SPRITE_INFO_PANEL_LARGE] = LoadSprite(IDB_INFO_PANEL_LARGE);
  sprites[SPRITE_BUTTONS_FOR_SUBSCREEN_TEXT] = LoadSprite(IDB_BUTTON_SPRITE_FOR_SUBSCREEN_TEXT);
}

GameButton *SetupButton(int id, Sprite *spr, DWORD style)
{
  GameButton *button = 0;
  button = new GameButton(spr, id, "", style, hWnd, hInst);
  return button;
}

void SetupAllButtons()
{
  DWORD NormStyle, OwnerStyle;
  
  NormStyle = BS_MULTILINE | WS_DLGFRAME | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;
  OwnerStyle = WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW; // | WS_VISIBLE;

  int i = 0;
  // Init to 0 so we can later delete
  for (i = 0; i < MAX_BUTTONS; i++) {
    buttons[i] = 0;
  }

  // Create the buttons 
  buttons[BUTTON_NEW] =           SetupButton(BUTTON_NEW, sprites[SPRITE_BUTTONS_1], OwnerStyle);
  buttons[BUTTON_LOAD] =          SetupButton(BUTTON_LOAD, sprites[SPRITE_BUTTONS_1], OwnerStyle);

  buttons[BUTTON_NEXT] =          SetupButton(BUTTON_NEXT, sprites[SPRITE_BUTTONS_2], OwnerStyle);

  buttons[BUTTON_OK] =            SetupButton(BUTTON_OK, sprites[SPRITE_BUTTONS_2], OwnerStyle);
  buttons[BUTTON_POPUP_OK] =      SetupButton(BUTTON_POPUP_OK, sprites[SPRITE_BUTTONS_2], OwnerStyle);
  buttons[BUTTON_CANCEL] =        SetupButton(BUTTON_CANCEL, sprites[SPRITE_BUTTONS_2], OwnerStyle);

  // Button numbers must be in order in the enum
  for (i = BUTTON_PLUS_1; i <= MAX_PLUS_BUTTON; i++)
    buttons[i] =                  SetupButton(i, sprites[SPRITE_BUTTONS_PLUS_2], OwnerStyle);

  buttons[BUTTON_INFO] =          SetupButton(BUTTON_INFO, sprites[SPRITE_BUTTONS_2], OwnerStyle);
  buttons[BUTTON_HELP] =          SetupButton(BUTTON_HELP, sprites[SPRITE_BUTTONS_2], OwnerStyle);
  buttons[BUTTON_MORE] =          SetupButton(BUTTON_MORE, sprites[SPRITE_BUTTONS_2], OwnerStyle);
  buttons[BUTTON_SAVE] =          SetupButton(BUTTON_SAVE, sprites[SPRITE_BUTTONS_2], OwnerStyle);
  
  // Button numbers must be in order in the enum
  for (i = BUTTON_TEXT_1; i <= BUTTON_TEXT_7; i++)
    buttons[i] =                  SetupButton(i, sprites[SPRITE_BUTTONS_FOR_TEXT], OwnerStyle);
  
  // Button numbers must be in order in the enum
  for (i = BUTTON_TEXT_Q_1; i <= BUTTON_TEXT_Q_7; i++)
    buttons[i] =                  SetupButton(i, sprites[SPRITE_BUTTONS_FOR_TEXT_2], OwnerStyle);

  // Button numbers must be in order in the enum
  for (i = BUTTON_SWITCH_1; i <= MAX_SWITCH_BUTTON; i++)
    buttons[i] =                  SetupButton(i, sprites[SPRITE_BUTTONS_SWITCH], OwnerStyle);

  
  // Button numbers must be in order in the enum
  for (i = BUTTON_SUBSYSTEM_1; i <= MAX_SUBSYSTEM_BUTTON; i++)
    buttons[i] =                  SetupButton(i, sprites[SPRITE_BUTTONS_FOR_SUBSCREEN_TEXT], OwnerStyle);

  buttons[BUTTON_END] =           SetupButton(BUTTON_END, sprites[SPRITE_BUTTONS_2], OwnerStyle);

  buttons[BUTTON_ASK] =           SetupButton(BUTTON_ASK, sprites[SPRITE_BUTTONS_2], OwnerStyle);
  buttons[BUTTON_RETRY] =         SetupButton(BUTTON_RETRY, sprites[SPRITE_BUTTONS_2], OwnerStyle);


  buttons[BUTTON_MODEL] =           SetupButton(BUTTON_MODEL,           sprites[SPRITE_BUTTONS_4], OwnerStyle);            
  buttons[BUTTON_HEAD] =            SetupButton(BUTTON_HEAD,            sprites[SPRITE_BUTTONS_4], OwnerStyle);             
  buttons[BUTTON_TORSO] =           SetupButton(BUTTON_TORSO,           sprites[SPRITE_BUTTONS_4], OwnerStyle);            
  buttons[BUTTON_ARM_RIGHT] =       SetupButton(BUTTON_ARM_RIGHT,       sprites[SPRITE_BUTTONS_4], OwnerStyle);        
  buttons[BUTTON_ARM_LEFT] =        SetupButton(BUTTON_ARM_LEFT,        sprites[SPRITE_BUTTONS_4], OwnerStyle);         
  buttons[BUTTON_LEG_RIGHT] =       SetupButton(BUTTON_LEG_RIGHT,       sprites[SPRITE_BUTTONS_4], OwnerStyle);        
  buttons[BUTTON_LEG_LEFT] =        SetupButton(BUTTON_LEG_LEFT,        sprites[SPRITE_BUTTONS_4], OwnerStyle);         
  buttons[BUTTON_EJECTION] =        SetupButton(BUTTON_EJECTION,        sprites[SPRITE_BUTTONS_4], OwnerStyle);         
  buttons[BUTTON_COOLING] =         SetupButton(BUTTON_COOLING,         sprites[SPRITE_BUTTONS_4], OwnerStyle);          
  buttons[BUTTON_COMPUTER] =        SetupButton(BUTTON_COMPUTER,        sprites[SPRITE_BUTTONS_4], OwnerStyle);         
  buttons[BUTTON_HUMAN_INTERFACE] = SetupButton(BUTTON_HUMAN_INTERFACE, sprites[SPRITE_BUTTONS_4], OwnerStyle);  
  
  buttons[BUTTON_ONROBOT_HEAD] =       SetupButton(BUTTON_ONROBOT_HEAD,      sprites[SPRITE_GIANT_ROBOT], OwnerStyle);             
  buttons[BUTTON_ONROBOT_TORSO] =      SetupButton(BUTTON_ONROBOT_TORSO,     sprites[SPRITE_GIANT_ROBOT], OwnerStyle);            
  buttons[BUTTON_ONROBOT_ARM_RIGHT] =  SetupButton(BUTTON_ONROBOT_ARM_RIGHT, sprites[SPRITE_GIANT_ROBOT], OwnerStyle);        
  buttons[BUTTON_ONROBOT_ARM_LEFT] =   SetupButton(BUTTON_ONROBOT_ARM_LEFT,  sprites[SPRITE_GIANT_ROBOT], OwnerStyle);         
  buttons[BUTTON_ONROBOT_LEG_RIGHT] =  SetupButton(BUTTON_ONROBOT_LEG_RIGHT, sprites[SPRITE_GIANT_ROBOT], OwnerStyle);        
  buttons[BUTTON_ONROBOT_LEG_LEFT] =   SetupButton(BUTTON_ONROBOT_LEG_LEFT,  sprites[SPRITE_GIANT_ROBOT], OwnerStyle); 
  
  buttons[BUTTON_CHANGE] =       SetupButton(BUTTON_CHANGE, sprites[SPRITE_BUTTONS_5], OwnerStyle);
  buttons[BUTTON_SELECT] =       SetupButton(BUTTON_SELECT, sprites[SPRITE_BUTTONS_5], OwnerStyle);

  buttons[BUTTON_SYSTEM_NEXT] =  SetupButton(BUTTON_SYSTEM_NEXT, sprites[SPRITE_BUTTONS_6], OwnerStyle);
  buttons[BUTTON_SYSTEM_PREV] =  SetupButton(BUTTON_SYSTEM_PREV, sprites[SPRITE_BUTTONS_6], OwnerStyle);
  
  buttons[BUTTON_MORE_INFO] =    SetupButton(BUTTON_MORE_INFO, sprites[SPRITE_BUTTONS_FOR_TEXT_3], OwnerStyle);

  buttons[BUTTON_OVERVIEW] =    SetupButton(BUTTON_OVERVIEW, sprites[SPRITE_BUTTONS_OVERVIEW], OwnerStyle);

  // Set all the background frames to the generic button background
  // And set the fonts to the right font
  for (i = 0; i < MAX_BUTTONS; i++) {
    if (buttons[i]) {
      buttons[i]->SetBackFrames(BUTTON_IMAGE_UNCLICKED, BUTTON_IMAGE_CLICKED);
      buttons[i]->SetGameFont(GameFont1);
      buttons[i]->HideButton();
    }
  }

  // These frames are all in order, except frame 0 is the full robot so it doesn't
  // go to a button
  buttons[BUTTON_ONROBOT_HEAD]->SetBackFrames(1, 2);             
  buttons[BUTTON_ONROBOT_TORSO]->SetBackFrames(3, 4);            
  buttons[BUTTON_ONROBOT_ARM_RIGHT]->SetBackFrames(5, 6);        
  buttons[BUTTON_ONROBOT_ARM_LEFT]->SetBackFrames(7, 8);         
  buttons[BUTTON_ONROBOT_LEG_RIGHT]->SetBackFrames(9, 10);        
  buttons[BUTTON_ONROBOT_LEG_LEFT]->SetBackFrames(11, 12);

  buttons[BUTTON_SYSTEM_NEXT]->SetBackFrames(2, 3);

  for (i = BUTTON_MODEL; i <= BUTTON_HUMAN_INTERFACE; i++) {
    buttons[i]->SetGameFont(GameFont4);
  }

  // Set the text buttons so that text is left-justified
  for (i = BUTTON_TEXT_1; i <= BUTTON_TEXT_7; i++)
  {
    buttons[i]->SetGameFont(GameFont7);
    buttons[i]->SetFontX(30);
  }

  // Set the text buttons so that text is left-justified
  for (i = BUTTON_TEXT_Q_1; i <= BUTTON_TEXT_Q_7; i++)
  {
    buttons[i]->SetGameFont(GameFont11);
    buttons[i]->SetFontX(30);
  }

  // Set the text buttons so that text is left-justified
  for (i = BUTTON_SUBSYSTEM_1; i <= MAX_SUBSYSTEM_BUTTON; i++)
  {
    buttons[i]->SetGameFont(GameFont6);
    buttons[i]->SetFontX(2);
    buttons[i]->SetFontY(4);
  }

  buttons[BUTTON_NEXT]->SetGameFont(GameFont2);
  buttons[BUTTON_END]->SetGameFont(GameFont2);
  buttons[BUTTON_INFO]->SetGameFont(GameFont2);
  buttons[BUTTON_HELP]->SetGameFont(GameFont2);
  buttons[BUTTON_OK]->SetGameFont(GameFont2);
  buttons[BUTTON_POPUP_OK]->SetGameFont(GameFont2);
  buttons[BUTTON_CANCEL]->SetGameFont(GameFont2);
  buttons[BUTTON_ASK]->SetGameFont(GameFont2);
  buttons[BUTTON_RETRY]->SetGameFont(GameFont2);
  buttons[BUTTON_MORE]->SetGameFont(GameFont2);
  buttons[BUTTON_SAVE]->SetGameFont(GameFont2);

  buttons[BUTTON_CHANGE]->SetGameFont(GameFont11);
  buttons[BUTTON_SELECT]->SetGameFont(GameFont11);

  buttons[BUTTON_MORE_INFO]->SetGameFont(GameFont11);

  buttons[BUTTON_NEXT]->SetFontX(82);
  buttons[BUTTON_INFO]->SetFontX(85);
  buttons[BUTTON_HELP]->SetFontX(82);
  buttons[BUTTON_END]->SetFontX(87);
  buttons[BUTTON_OK]->SetFontX(89);
  buttons[BUTTON_POPUP_OK]->SetFontX(89);
  buttons[BUTTON_CANCEL]->SetFontX(82);
  buttons[BUTTON_ASK]->SetFontX(87);
  buttons[BUTTON_RETRY]->SetFontX(82);
  buttons[BUTTON_MORE]->SetFontX(82);

  // Move the buttons to the right places  
  buttons[BUTTON_NEW]->MoveButton(
    wObj.Wid()/2 - sprites[SPRITE_BUTTONS_1]->GetFrameWidth(BUTTON_IMAGE_UNCLICKED)/2, 
    wObj.Hgt()/2 - sprites[SPRITE_BUTTONS_1]->GetFrameHeight(BUTTON_IMAGE_UNCLICKED) - 5);
  buttons[BUTTON_LOAD]->MoveButton(buttons[BUTTON_NEW]->GetX(), buttons[BUTTON_NEW]->GetY() + buttons[BUTTON_NEW]->GetHeight() + 10);
  
  buttons[BUTTON_HELP]->MoveButton(60, 40);
  buttons[BUTTON_END]->MoveButton(wObj.Wid() - buttons[BUTTON_END]->GetWidth() - buttons[BUTTON_INFO]->GetX(), wObj.Hgt() - 38);

  buttons[BUTTON_NEW]->SetFontY(29);
  buttons[BUTTON_LOAD]->SetFontY(29);

  // We have created the GameFont already so we can assign it, along with text, to the right buttons
  buttons[BUTTON_NEW]->SetButtonText("New");
  buttons[BUTTON_LOAD]->SetButtonText("Load");
  buttons[BUTTON_NEXT]->SetButtonText("Next");
  buttons[BUTTON_INFO]->SetButtonText("Info");
  buttons[BUTTON_HELP]->SetButtonText("Help");
  buttons[BUTTON_END]->SetButtonText("End");
  buttons[BUTTON_MODEL]->SetButtonText("Frame");            
  buttons[BUTTON_HEAD]->SetButtonText("Head");         
  buttons[BUTTON_TORSO]->SetButtonText("Torso");           
  buttons[BUTTON_ARM_RIGHT]->SetButtonText("R-Arm");        
  buttons[BUTTON_ARM_LEFT]->SetButtonText("L-Arm");         
  buttons[BUTTON_LEG_RIGHT]->SetButtonText("R-Leg");        
  buttons[BUTTON_LEG_LEFT]->SetButtonText("L-Leg");         
  buttons[BUTTON_EJECTION]->SetButtonText("Eject");        
  buttons[BUTTON_COOLING]->SetButtonText("Cooling");         
  buttons[BUTTON_COMPUTER]->SetButtonText("Computer");       
  buttons[BUTTON_HUMAN_INTERFACE]->SetButtonText("Pilot");
  
  buttons[BUTTON_CHANGE]->SetButtonText("Alter");
  buttons[BUTTON_SELECT]->SetButtonText("Select");
  buttons[BUTTON_MORE_INFO]->SetButtonText("Ask For More Info");

  buttons[BUTTON_OK]->SetButtonText("OK");
  buttons[BUTTON_POPUP_OK]->SetButtonText("OK");
  buttons[BUTTON_CANCEL]->SetButtonText("Back");
  buttons[BUTTON_MORE]->SetButtonText("More");
  buttons[BUTTON_SAVE]->SetButtonText("Save");

  buttons[BUTTON_ASK]->SetButtonText("Ask");
  buttons[BUTTON_RETRY]->SetButtonText("Done");
}

// Draw a single button
void DrawButton(int nButtonID)
{
  //LPDRAWITEMSTRUCT lpdis = 0;
  if (nButtonID < 0 || nButtonID > MAX_BUTTONS)
    return;

  if (buttons[nButtonID] && IsWindowVisible(buttons[nButtonID]->GetHWND())) {
    // I don't use the lpdis because it doesn't seem to set correctly
    /*lpdis = buttons[i]->GetLPDIS();

    if (!lpdis)
      return;

    if (lpdis->itemState & ODS_SELECTED) { // if selected 
      buttons[nButtonID]->DrawClicked(wObj.getBackHDC(), buttons[i]->GetX(), buttons[i]->GetY());
    } else {
      buttons[nButtonID]->DrawNormal(wObj.getBackHDC(), buttons[i]->GetX(), buttons[i]->GetY());
    }*/

    if (buttons[nButtonID]->GetSel()) { // if selected 
      buttons[nButtonID]->DrawTransClicked(wObj.getBackHDC(), buttons[nButtonID]->GetX(), buttons[nButtonID]->GetY());
    } else {
      buttons[nButtonID]->DrawTransNormal(wObj.getBackHDC(), buttons[nButtonID]->GetX(), buttons[nButtonID]->GetY());
    }
  }
}

// Our wrapper grabs the x and y when we call MoveButton so we can handle all the drawing ourselves
void DrawButtons()
{
  for (int i = 0; i < MAX_BUTTONS; i++) {
    DrawButton(i);
  }
}

// Draw only the buttons that are enabled
void DrawEnabledButtons()
{
  for (int i = 0; i < MAX_BUTTONS; i++) {
    if (buttons[i]->IsEnabled())
    {
      DrawButton(i);
    }
  }
}


// Setup our custom fonts
void SetupAllFonts()
{
  // This is all we really need to do here
  GameFont1 = new GameFont(sprites[SPRITE_FONT_1]); 
  GameFont2 = new GameFont(sprites[SPRITE_FONT_2]); 
  GameFont3 = new GameFont(sprites[SPRITE_FONT_3]);
  GameFont4 = new GameFont(sprites[SPRITE_FONT_4]);
  GameFont5 = new GameFont(sprites[SPRITE_FONT_5]);
  GameFont6 = new GameFont(sprites[SPRITE_FONT_6]);
  GameFont7 = new GameFont(sprites[SPRITE_FONT_7]);
  GameFont8 = new GameFont(sprites[SPRITE_FONT_8]);
  GameFont9 = new GameFont(sprites[SPRITE_FONT_9]);
  GameFont10 = new GameFont(sprites[SPRITE_FONT_10]);
  GameFont11 = new GameFont(sprites[SPRITE_FONT_11]);
  GameFont12 = new GameFont(sprites[SPRITE_FONT_12]);
  GameFont13 = new GameFont(sprites[SPRITE_FONT_13]);
  GameFont14 = new GameFont(sprites[SPRITE_FONT_14]);
  GameFont15 = new GameFont(sprites[SPRITE_FONT_15]);
  GameFont16 = new GameFont(sprites[SPRITE_FONT_16]);

  GameFontGreen = GameFont6;
  GameFontRed = GameFont7;
  GameFontOrange = GameFont8;
  GameFontDarkBlue = GameFont9;
  GameFontYellow = GameFont10;
  GameFontLightBlue = GameFont12;
  GameFontDarkGray = GameFont13;
  GameFontLightGray = GameFont14;
  GameFontGreenNum = GameFont15;
  GameFontOrangeNum = GameFont16;
}

// Hide and enable all buttons; since they're hidden they
// can also be enabled
void HideAndEnableAllButtons()
{
  for (int i = 0; i < MAX_BUTTONS; i++)
  {
    buttons[i]->HideButton();
    buttons[i]->EnableButton();
  }
}

// Enable all visible buttons, like if we disabled them
// on a popup or whatnot
void EnableAllVisibleButtons()
{
  for (int i = 0; i < MAX_BUTTONS; i++)
  {
    if (buttons[i]->IsVisible())
    {
      buttons[i]->EnableButton();
    }
  }
}


// Disable all buttons - this is useful for overlays and things like that
// where you'd just disable everything, then enable the couple buttons you want to use
void DisableAllButtons()
{
  for (int i = 0; i < MAX_BUTTONS; i++)
  {
    buttons[i]->DisableButton();
  }
}

// I only need this if I draw the buttons in the WndProc
GameButton *GameButtonForID(int button_id)
{
  if (button_id < 0 || button_id >= MAX_BUTTONS)
    return 0;

  if (!buttons[button_id])
    return 0;

  return buttons[button_id];
}

void ReDraw(int force)
{
  switch (nScreen)
  {
    case SCREEN_TITLE:
      DrawTitleScreen();
      break;
    case SCREEN_INTRO:
      DrawIntroScreen();
      break;
    case SCREEN_STAKEHOLDER:
      DrawStakeholderScreen();
      break;
    case SCREEN_SYSTEM_DESIGN:
      DrawSystemDesignScreen();
      break;
    case SCREEN_END_TURN:
      DrawEndTurnScreen();
      break;
    case SCREEN_CHANGE_SUB_SYSTEM:
      DrawChangeSubSystemScreen();
      break;
    case SCREEN_ASK:
      DrawAskScreen();
      break;
    case SCREEN_YOU_LOSE:
      DrawYouLoseScreen();
      break;
    case SCREEN_END_GAME:
      DrawEndOfGameScreen();
      break;
    case SCREEN_INFO:
      DrawInfoScreen();
      break;
    case SCREEN_HELP:
      DrawHelpScreen();
      break;
    case SCREEN_SCORE_RECORD:
      DrawScoreRecordScreen();
      break;
  }

  if (pEndTurnPop)
  {
    pEndTurnPop->Draw(wObj.getBackHDC());
  }

  // Draw the popup if we have one.
  if (pPop)
  {
    pPop->Draw(wObj.getBackHDC());
  }

  BitBlt(wObj.getHDC(), 0, 0, wObj.getClientWid(), wObj.getClientHgt(), wObj.getBackHDC(),0,0,SRCCOPY); 
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG mmsg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PROJECTROBOT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

  wObj.init(hWnd); // TODO - re-init this if window size changes, ala Worldmancer or better

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_PROJECTROBOT);

  init_mm(); // Initialize random number generator

  LoadAllSprites();
  SetupAllSprites();
  SetupAllFonts();
  SetupAllButtons();

  // Set up all the system restrictions
  SetupSystemRestrictions();

  // Initialize and start up the game as a whole, can use this to 'restart'
  // the game also
  StartGame();

  // Now we start our game loop
  // We only react on user input so we don't need a 'real' game loop here
  while (GetMessage(&mmsg, NULL, 0, 0)) {

    // If the message is WM_QUIT, exit the while loop
    if (mmsg.message == WM_QUIT)
       break;

    if (!TranslateAccelerator(mmsg.hwnd, hAccelTable, &mmsg)) 
    {
      TranslateMessage(&mmsg);
      DispatchMessage(&mmsg);
    } 

    // Do all game stuff


    // Draw
    ReDraw();
  }

  // And all the sprites
  int i = 0;
  for (i = 0; i < MAX_SPRITES; i++) {
    if (sprites[i]) {
      delete sprites[i];
    }
  }

  // The buttons
  for (i = 0; i < MAX_BUTTONS; i++) {
    if (buttons[i]) {
      delete buttons[i];
    }
  }

  return mmsg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_PROJECTROBOT);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0; //(LPCSTR)IDC_PROJECTROBOT;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, // WS_OVERLAPPEDWINDOW,
      WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 
      CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void ChangeScreen(int nNewScreen)
{

  nScreen = nNewScreen;

  switch (nScreen)
  {
    case SCREEN_TITLE:
      StartTitleScreen();
      break;
    case SCREEN_INTRO:
      StartIntroScreen();
      break;
    case SCREEN_STAKEHOLDER:
      StartStakeholderScreen1();
      break;
    case SCREEN_SYSTEM_DESIGN:
      StartSystemDesignScreen();
      break;
    case SCREEN_END_TURN:
      StartEndTurnScreen();
      break;
    case SCREEN_CHANGE_SUB_SYSTEM:
      StartChangeSubSystemScreen();
      break;
    case SCREEN_ASK:
      StartAskScreen();
      break;
    case SCREEN_YOU_LOSE:
      StartYouLoseScreen();
      break;
    case SCREEN_END_GAME:
      StartEndOfGameScreen();
      break;
    case SCREEN_INFO:
      StartInfoScreen();
      break;
    case SCREEN_HELP:
      StartHelpScreen();
      break;
    case SCREEN_SCORE_RECORD:
      StartScoreRecordScreen();
      break;
  }
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
  GameButton *button = 0; // Our ownerdraw button
  LPDRAWITEMSTRUCT lpDrawItem;

	switch (message) 
	{
    case WM_DRAWITEM:
      if (0 != (button = GameButtonForID(wParam)))
      {
        lpDrawItem = (LPDRAWITEMSTRUCT) lParam; 

        // Set the lpdis on the button so we can use this info later on our own terms
        //button->SetLPDIS(lpdis);

        //button->DrawNormal(lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top);

        // It does need to draw here in case we're dragging the screen wider, or even
        // just dragging it around the monitor, etc.  If it's permanently full-sized it shouldn't
        // need this, and if it draws with its own timer (does not use GetMessage) it doesn't need this
        if (lpDrawItem->itemState & ODS_SELECTED) { // if selected 
          button->SetSel(true);  // Tell it that it's selected, so that it draws correctly
          button->DrawTransClicked(lpDrawItem->hDC, lpDrawItem->rcItem.left, lpDrawItem->rcItem.top);
        } else {
          button->SetSel(false);
          button->DrawTransNormal(lpDrawItem->hDC, lpDrawItem->rcItem.left, lpDrawItem->rcItem.top);
        }
        return TRUE;
      }
      break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 

      // The popup "ok" button supercedes all others.  
      if (wmId == BUTTON_POPUP_OK)
      {
        objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2);
        ClosePopup();
        break;
      }

			// Parse the menu selections:
      if (nScreen == SCREEN_STAKEHOLDER) 
      {
        HandleButtonStakeholder(wmId);
        break;
      }
      else if (nScreen == SCREEN_SYSTEM_DESIGN) 
      {
        HandleButtonSystemDesign(wmId);
        break;
      }
      else if (nScreen == SCREEN_END_TURN) 
      {
        HandleButtonEndTurn(wmId);
        break;
      }
      else if (nScreen == SCREEN_CHANGE_SUB_SYSTEM) 
      {
        HandleButtonChangeSubSystem(wmId);
        break;
      }
      else if (nScreen == SCREEN_ASK) 
      {
        HandleButtonAsk(wmId);
        break;
      }
      else if (nScreen == SCREEN_INFO) 
      {
        HandleButtonInfo(wmId);
        break;
      }
      else if (nScreen == SCREEN_HELP) 
      {
        HandleButtonHelp(wmId);
        break;
      }
      else if (nScreen == SCREEN_YOU_LOSE) 
      {
        HandleButtonYouLose(wmId);
        break;
      }
      else if (nScreen == SCREEN_END_GAME) 
      {
        HandleButtonEndGame(wmId);
        break;
      }
      else if (nScreen == SCREEN_SCORE_RECORD) 
      {
        HandleButtonScoreRecord(wmId);
        break;
      }
			switch (wmId)
			{
        case IDM_ABOUT:
          DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
          break;
        case IDM_EXIT:
          DestroyWindow(hWnd);
          break;
        case BUTTON_NEW:
          objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_1);
          ChangeScreen(SCREEN_INTRO);
          break;
        case BUTTON_LOAD:
          objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_1);
          // TODO - load data
          break;
        case BUTTON_NEXT:
          objSound.PlaySoundFromResource(IDR_SOUND_BUTTON_2);
         
          if (nScreen == SCREEN_INTRO) 
          {
            if (!IntroScreenNext()) {
              ChangeScreen(SCREEN_STAKEHOLDER);
            }
          } 
          break;
        default:
          return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
      // I do need to paint here, otherwise when you drag the window it doesn't show up
      // although it DOES redraw in WM_MOVING and WM_SIZING but it doesn't draw fast
      // enough so it looks wonky
			hdc = BeginPaint(hWnd, &ps);
			//RECT rt;
			//GetClientRect(hWnd, &rt);
			//DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
    case WM_ERASEBKGND: 
      // I erase myself when I do the redraw, so we don't need the window to do this for us
      return 0;
    case WM_MOVING: // If someone is dragging our window around, redraw 
    case WM_SIZING: // If someone is resizing our window, redraw 
    {
      static long old_time = 0;
      if (GetTickCount() - old_time > 50) { // 20 fps when we drag
        ReDraw();
        old_time = GetTickCount();
      }
      break;
    }
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
