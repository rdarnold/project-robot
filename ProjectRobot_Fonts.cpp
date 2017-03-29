/*

  Project Robot has so many fonts that I moved their
  creation into a separate file - it was taking up too
  much space in the main file

*/
#include "ProjectRobot.h"

extern Sprite *sprites[MAX_SPRITES];

void SetupFontSprites()
{
  // Normally the sprite should look like this:
  //    abc
  //    ABC
  //    123
  // Although the font class creates the capital letters first so they
  // need to come first, I proabbly should change the sprite file structure though
  // in that case...
  // 
  // In Font 1, all letters are capitalized
  
  // First set up the #s we'l use to establish our fonts  
  int nFontNumber             = 0;  
  int nFontCapLetterHeight    = 0;
  int nFontSmallLetterHeight  = 0; 
  int nFontLetterHeight       = 0; 
  int nFontNumberStartHeight  = 0;
  int nFontNumberHeight       = 0;

  
  // Now begin font setup
  nFontNumber = SPRITE_FONT_1; 
  nFontCapLetterHeight = 10;  
  sprites[nFontNumber]->SetTransColor(RGB(0, 0, 0));

  // Big letters
  sprites[nFontNumber]->CreateFrame(0,   9,   0, nFontCapLetterHeight); // A
  sprites[nFontNumber]->CreateFrame(9,   18,  0, nFontCapLetterHeight); // B
  sprites[nFontNumber]->CreateFrame(18,  27,  0, nFontCapLetterHeight); // C
  sprites[nFontNumber]->CreateFrame(27,  37,  0, nFontCapLetterHeight); // D
  sprites[nFontNumber]->CreateFrame(37,  45,  0, nFontCapLetterHeight); // E
  sprites[nFontNumber]->CreateFrame(45,  53,  0, nFontCapLetterHeight); // F
  sprites[nFontNumber]->CreateFrame(53,  63,  0, nFontCapLetterHeight); // G
  sprites[nFontNumber]->CreateFrame(63,  71,  0, nFontCapLetterHeight); // H
  sprites[nFontNumber]->CreateFrame(71,  74,  0, nFontCapLetterHeight); // I
  sprites[nFontNumber]->CreateFrame(74,  80,  0, nFontCapLetterHeight); // J
  sprites[nFontNumber]->CreateFrame(80,  89,  0, nFontCapLetterHeight); // K
  sprites[nFontNumber]->CreateFrame(89,  97,  0, nFontCapLetterHeight); // L
  sprites[nFontNumber]->CreateFrame(97,  107, 0, nFontCapLetterHeight); // M
  sprites[nFontNumber]->CreateFrame(107, 115, 0, nFontCapLetterHeight); // N
  sprites[nFontNumber]->CreateFrame(115, 125, 0, nFontCapLetterHeight); // O
  sprites[nFontNumber]->CreateFrame(125, 133, 0, nFontCapLetterHeight); // P
  sprites[nFontNumber]->CreateFrame(133, 145, 0, nFontCapLetterHeight); // Q
  sprites[nFontNumber]->CreateFrame(145, 154, 0, nFontCapLetterHeight); // R
  sprites[nFontNumber]->CreateFrame(154, 163, 0, nFontCapLetterHeight); // S
  sprites[nFontNumber]->CreateFrame(163, 172, 0, nFontCapLetterHeight); // T
  sprites[nFontNumber]->CreateFrame(172, 180, 0, nFontCapLetterHeight); // U
  sprites[nFontNumber]->CreateFrame(180, 189, 0, nFontCapLetterHeight); // V
  sprites[nFontNumber]->CreateFrame(189, 202, 0, nFontCapLetterHeight); // W
  sprites[nFontNumber]->CreateFrame(202, 209, 0, nFontCapLetterHeight); // X
  sprites[nFontNumber]->CreateFrame(209, 216, 0, nFontCapLetterHeight); // Y
  sprites[nFontNumber]->CreateFrame(216, 223, 0, nFontCapLetterHeight); // Z

  // Small letters
  nFontSmallLetterHeight = 10; 
  sprites[nFontNumber]->CreateFrame(0,   9,   0, nFontSmallLetterHeight); // a
  sprites[nFontNumber]->CreateFrame(9,   18,  0, nFontSmallLetterHeight); // b
  sprites[nFontNumber]->CreateFrame(18,  27,  0, nFontSmallLetterHeight); // c
  sprites[nFontNumber]->CreateFrame(27,  37,  0, nFontSmallLetterHeight); // d
  sprites[nFontNumber]->CreateFrame(37,  45,  0, nFontSmallLetterHeight); // e
  sprites[nFontNumber]->CreateFrame(45,  53,  0, nFontSmallLetterHeight); // f
  sprites[nFontNumber]->CreateFrame(53,  63,  0, nFontSmallLetterHeight); // g
  sprites[nFontNumber]->CreateFrame(63,  71,  0, nFontSmallLetterHeight); // h
  sprites[nFontNumber]->CreateFrame(71,  74,  0, nFontSmallLetterHeight); // i
  sprites[nFontNumber]->CreateFrame(74,  80,  0, nFontSmallLetterHeight); // j
  sprites[nFontNumber]->CreateFrame(80,  89,  0, nFontSmallLetterHeight); // k
  sprites[nFontNumber]->CreateFrame(89,  97,  0, nFontSmallLetterHeight); // l
  sprites[nFontNumber]->CreateFrame(97,  107, 0, nFontSmallLetterHeight); // m
  sprites[nFontNumber]->CreateFrame(107, 115, 0, nFontSmallLetterHeight); // n
  sprites[nFontNumber]->CreateFrame(115, 125, 0, nFontSmallLetterHeight); // o
  sprites[nFontNumber]->CreateFrame(125, 133, 0, nFontSmallLetterHeight); // p
  sprites[nFontNumber]->CreateFrame(133, 145, 0, nFontSmallLetterHeight); // q
  sprites[nFontNumber]->CreateFrame(145, 154, 0, nFontSmallLetterHeight); // r
  sprites[nFontNumber]->CreateFrame(154, 163, 0, nFontSmallLetterHeight); // s
  sprites[nFontNumber]->CreateFrame(163, 172, 0, nFontSmallLetterHeight); // t
  sprites[nFontNumber]->CreateFrame(172, 180, 0, nFontSmallLetterHeight); // u
  sprites[nFontNumber]->CreateFrame(180, 189, 0, nFontSmallLetterHeight); // v
  sprites[nFontNumber]->CreateFrame(189, 202, 0, nFontSmallLetterHeight); // w
  sprites[nFontNumber]->CreateFrame(202, 209, 0, nFontSmallLetterHeight); // x
  sprites[nFontNumber]->CreateFrame(209, 216, 0, nFontSmallLetterHeight); // y
  sprites[nFontNumber]->CreateFrame(216, 223, 0, nFontSmallLetterHeight); // z

  // Numbers and special characters
  nFontNumberHeight = 23;  
  nFontNumberStartHeight = nFontCapLetterHeight+2;
  sprites[nFontNumber]->CreateFrame(0,   10,  nFontNumberStartHeight, nFontNumberHeight);   // 0
  sprites[nFontNumber]->CreateFrame(10,  15,  nFontNumberStartHeight, nFontNumberHeight);   // 1
  sprites[nFontNumber]->CreateFrame(15,  25,  nFontNumberStartHeight, nFontNumberHeight);   // 2
  sprites[nFontNumber]->CreateFrame(25,  34,  nFontNumberStartHeight, nFontNumberHeight);   // 3
  sprites[nFontNumber]->CreateFrame(34,  43,  nFontNumberStartHeight, nFontNumberHeight);   // 4
  sprites[nFontNumber]->CreateFrame(43,  53,  nFontNumberStartHeight, nFontNumberHeight);   // 5
  sprites[nFontNumber]->CreateFrame(53,  63,  nFontNumberStartHeight, nFontNumberHeight);   // 6
  sprites[nFontNumber]->CreateFrame(63,  71,  nFontNumberStartHeight, nFontNumberHeight);   // 7
  sprites[nFontNumber]->CreateFrame(71,  81,  nFontNumberStartHeight, nFontNumberHeight);   // 8
  sprites[nFontNumber]->CreateFrame(81,  90,  nFontNumberStartHeight, nFontNumberHeight);   // 9
  sprites[nFontNumber]->CreateFrame(90,  93,  nFontNumberStartHeight, nFontNumberHeight);   // !
  sprites[nFontNumber]->CreateFrame(93,  96,  nFontNumberStartHeight, nFontNumberHeight);   // '
  sprites[nFontNumber]->CreateFrame(96,  99,  nFontNumberStartHeight, nFontNumberHeight);   // :
  sprites[nFontNumber]->CreateFrame(99,  104, nFontNumberStartHeight, nFontNumberHeight);   // "
  sprites[nFontNumber]->CreateFrame(104, 107, nFontNumberStartHeight, nFontNumberHeight);   // .
  sprites[nFontNumber]->CreateFrame(107, 110, nFontNumberStartHeight, nFontNumberHeight+1); // ;
  sprites[nFontNumber]->CreateFrame(110, 118, nFontNumberStartHeight, nFontNumberHeight);   // ?
  sprites[nFontNumber]->CreateFrame(118, 127, nFontNumberStartHeight-1, nFontNumberHeight); // $
  sprites[nFontNumber]->CreateFrame(127, 135, nFontNumberStartHeight, nFontNumberHeight);   // -
  sprites[nFontNumber]->CreateFrame(135, 144, nFontNumberStartHeight, nFontNumberHeight);   // +
  sprites[nFontNumber]->CreateFrame(144, 151, nFontNumberStartHeight, nFontNumberHeight);   // =
  sprites[nFontNumber]->CreateFrame(151, 154, nFontNumberStartHeight, nFontNumberHeight+1); // ,

  // Font 3 is the same as font 1 but diff color
  sprites[SPRITE_FONT_3]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_FONT_3]->CopyFrameDimensions(sprites[SPRITE_FONT_1]);
  
  sprites[SPRITE_FONT_11]->SetTransColor(RGB(255, 0, 0));
  sprites[SPRITE_FONT_11]->CopyFrameDimensions(sprites[SPRITE_FONT_1]);

  nFontNumber = SPRITE_FONT_2; 
  sprites[nFontNumber]->SetTransColor(RGB(0, 0, 0));
  nFontCapLetterHeight = 6;  

  // Big letters
  sprites[nFontNumber]->CreateFrame(0,   11,  0, nFontCapLetterHeight); // A
  sprites[nFontNumber]->CreateFrame(11,  21,  0, nFontCapLetterHeight); // B
  sprites[nFontNumber]->CreateFrame(21,  30,  0, nFontCapLetterHeight); // C
  sprites[nFontNumber]->CreateFrame(30,  40,  0, nFontCapLetterHeight); // D
  sprites[nFontNumber]->CreateFrame(40,  49,  0, nFontCapLetterHeight); // E
  sprites[nFontNumber]->CreateFrame(49,  58,  0, nFontCapLetterHeight); // F
  sprites[nFontNumber]->CreateFrame(58,  68,  0, nFontCapLetterHeight); // G
  sprites[nFontNumber]->CreateFrame(68,  78,  0, nFontCapLetterHeight); // H
  sprites[nFontNumber]->CreateFrame(78,  81,  0, nFontCapLetterHeight); // I
  sprites[nFontNumber]->CreateFrame(81,  87,  0, nFontCapLetterHeight); // J
  sprites[nFontNumber]->CreateFrame(87,  96,  0, nFontCapLetterHeight); // K
  sprites[nFontNumber]->CreateFrame(96,  105, 0, nFontCapLetterHeight); // L
  sprites[nFontNumber]->CreateFrame(105, 118, 0, nFontCapLetterHeight); // M
  sprites[nFontNumber]->CreateFrame(118, 127, 0, nFontCapLetterHeight); // N
  sprites[nFontNumber]->CreateFrame(127, 136, 0, nFontCapLetterHeight); // O
  sprites[nFontNumber]->CreateFrame(137, 146, 0, nFontCapLetterHeight); // P
  sprites[nFontNumber]->CreateFrame(146, 155, 0, nFontCapLetterHeight); // Q
  sprites[nFontNumber]->CreateFrame(156, 166, 0, nFontCapLetterHeight); // R
  sprites[nFontNumber]->CreateFrame(166, 174, 0, nFontCapLetterHeight); // S
  sprites[nFontNumber]->CreateFrame(174, 183, 0, nFontCapLetterHeight); // T
  sprites[nFontNumber]->CreateFrame(183, 192, 0, nFontCapLetterHeight); // U
  sprites[nFontNumber]->CreateFrame(192, 202, 0, nFontCapLetterHeight); // V
  sprites[nFontNumber]->CreateFrame(202, 216, 0, nFontCapLetterHeight); // W
  sprites[nFontNumber]->CreateFrame(216, 226, 0, nFontCapLetterHeight); // X
  sprites[nFontNumber]->CreateFrame(226, 235, 0, nFontCapLetterHeight); // Y
  sprites[nFontNumber]->CreateFrame(235, 243, 0, nFontCapLetterHeight); // Z
  
  // Small letters
  nFontSmallLetterHeight = 6; 
  sprites[nFontNumber]->CreateFrame(0,   11,  0, nFontSmallLetterHeight); // a
  sprites[nFontNumber]->CreateFrame(11,  21,  0, nFontSmallLetterHeight); // b
  sprites[nFontNumber]->CreateFrame(21,  30,  0, nFontSmallLetterHeight); // c
  sprites[nFontNumber]->CreateFrame(30,  40,  0, nFontSmallLetterHeight); // d
  sprites[nFontNumber]->CreateFrame(40,  49,  0, nFontSmallLetterHeight); // e
  sprites[nFontNumber]->CreateFrame(49,  58,  0, nFontSmallLetterHeight); // f
  sprites[nFontNumber]->CreateFrame(58,  68,  0, nFontSmallLetterHeight); // g
  sprites[nFontNumber]->CreateFrame(68,  78,  0, nFontSmallLetterHeight); // h
  sprites[nFontNumber]->CreateFrame(78,  81,  0, nFontSmallLetterHeight); // i
  sprites[nFontNumber]->CreateFrame(81,  87,  0, nFontSmallLetterHeight); // j
  sprites[nFontNumber]->CreateFrame(87,  96,  0, nFontSmallLetterHeight); // k
  sprites[nFontNumber]->CreateFrame(96,  105, 0, nFontSmallLetterHeight); // l
  sprites[nFontNumber]->CreateFrame(105, 118, 0, nFontSmallLetterHeight); // m
  sprites[nFontNumber]->CreateFrame(118, 127, 0, nFontSmallLetterHeight); // n
  sprites[nFontNumber]->CreateFrame(127, 136, 0, nFontSmallLetterHeight); // o
  sprites[nFontNumber]->CreateFrame(137, 146, 0, nFontSmallLetterHeight); // p
  sprites[nFontNumber]->CreateFrame(146, 155, 0, nFontSmallLetterHeight); // q
  sprites[nFontNumber]->CreateFrame(156, 166, 0, nFontSmallLetterHeight); // r
  sprites[nFontNumber]->CreateFrame(166, 174, 0, nFontSmallLetterHeight); // s
  sprites[nFontNumber]->CreateFrame(174, 183, 0, nFontSmallLetterHeight); // t
  sprites[nFontNumber]->CreateFrame(183, 192, 0, nFontSmallLetterHeight); // u
  sprites[nFontNumber]->CreateFrame(192, 202, 0, nFontSmallLetterHeight); // v
  sprites[nFontNumber]->CreateFrame(202, 216, 0, nFontSmallLetterHeight); // w
  sprites[nFontNumber]->CreateFrame(216, 226, 0, nFontSmallLetterHeight); // x
  sprites[nFontNumber]->CreateFrame(226, 235, 0, nFontSmallLetterHeight); // y
  sprites[nFontNumber]->CreateFrame(235, 243, 0, nFontSmallLetterHeight); // z

  // Big letters
  nFontNumber = SPRITE_FONT_4;
  sprites[nFontNumber]->SetTransColor(RGB(177, 203, 233));
  nFontCapLetterHeight = 11;

  sprites[nFontNumber]->CreateFrame(0,   11,  0, nFontCapLetterHeight); // A
  sprites[nFontNumber]->CreateFrame(11,  21,  0, nFontCapLetterHeight); // B
  sprites[nFontNumber]->CreateFrame(21,  33,  0, nFontCapLetterHeight); // C
  sprites[nFontNumber]->CreateFrame(33,  45,  0, nFontCapLetterHeight); // D
  sprites[nFontNumber]->CreateFrame(45,  55,  0, nFontCapLetterHeight); // E
  sprites[nFontNumber]->CreateFrame(55,  65,  0, nFontCapLetterHeight); // F
  sprites[nFontNumber]->CreateFrame(65,  77,  0, nFontCapLetterHeight); // G
  sprites[nFontNumber]->CreateFrame(77,  87,  0, nFontCapLetterHeight); // H
  sprites[nFontNumber]->CreateFrame(87,  91,  0, nFontCapLetterHeight); // I
  sprites[nFontNumber]->CreateFrame(91,  99,  0, nFontCapLetterHeight); // J
  sprites[nFontNumber]->CreateFrame(99,  110, 0, nFontCapLetterHeight); // K
  sprites[nFontNumber]->CreateFrame(110, 120, 0, nFontCapLetterHeight); // L
  sprites[nFontNumber]->CreateFrame(120, 132, 0, nFontCapLetterHeight); // M
  sprites[nFontNumber]->CreateFrame(132, 142, 0, nFontCapLetterHeight); // N
  sprites[nFontNumber]->CreateFrame(142, 154, 0, nFontCapLetterHeight); // O
  sprites[nFontNumber]->CreateFrame(154, 164, 0, nFontCapLetterHeight); // P
  sprites[nFontNumber]->CreateFrame(164, 178, 0, nFontCapLetterHeight); // Q
  sprites[nFontNumber]->CreateFrame(178, 189, 0, nFontCapLetterHeight); // R
  sprites[nFontNumber]->CreateFrame(189, 199, 0, nFontCapLetterHeight); // S
  sprites[nFontNumber]->CreateFrame(199, 211, 0, nFontCapLetterHeight); // T
  sprites[nFontNumber]->CreateFrame(211, 221, 0, nFontCapLetterHeight); // U
  sprites[nFontNumber]->CreateFrame(221, 233, 0, nFontCapLetterHeight); // V
  sprites[nFontNumber]->CreateFrame(233, 247, 0, nFontCapLetterHeight); // W
  sprites[nFontNumber]->CreateFrame(247, 256, 0, nFontCapLetterHeight); // X
  sprites[nFontNumber]->CreateFrame(256, 265, 0, nFontCapLetterHeight); // Y
  sprites[nFontNumber]->CreateFrame(265, 274, 0, nFontCapLetterHeight); // Z

  nFontSmallLetterHeight = nFontCapLetterHeight;
  sprites[nFontNumber]->CreateFrame(0,   11,  0, nFontSmallLetterHeight); // a
  sprites[nFontNumber]->CreateFrame(11,  21,  0, nFontSmallLetterHeight); // b
  sprites[nFontNumber]->CreateFrame(21,  33,  0, nFontSmallLetterHeight); // c
  sprites[nFontNumber]->CreateFrame(33,  45,  0, nFontSmallLetterHeight); // d
  sprites[nFontNumber]->CreateFrame(45,  55,  0, nFontSmallLetterHeight); // e
  sprites[nFontNumber]->CreateFrame(55,  65,  0, nFontSmallLetterHeight); // f
  sprites[nFontNumber]->CreateFrame(65,  77,  0, nFontSmallLetterHeight); // g
  sprites[nFontNumber]->CreateFrame(77,  87,  0, nFontSmallLetterHeight); // h
  sprites[nFontNumber]->CreateFrame(87,  91,  0, nFontSmallLetterHeight); // i
  sprites[nFontNumber]->CreateFrame(91,  99,  0, nFontSmallLetterHeight); // j
  sprites[nFontNumber]->CreateFrame(99,  110, 0, nFontSmallLetterHeight); // k
  sprites[nFontNumber]->CreateFrame(110, 120, 0, nFontSmallLetterHeight); // l
  sprites[nFontNumber]->CreateFrame(120, 132, 0, nFontSmallLetterHeight); // m
  sprites[nFontNumber]->CreateFrame(132, 142, 0, nFontSmallLetterHeight); // n
  sprites[nFontNumber]->CreateFrame(142, 154, 0, nFontSmallLetterHeight); // o
  sprites[nFontNumber]->CreateFrame(154, 164, 0, nFontSmallLetterHeight); // p
  sprites[nFontNumber]->CreateFrame(164, 178, 0, nFontSmallLetterHeight); // q
  sprites[nFontNumber]->CreateFrame(178, 189, 0, nFontSmallLetterHeight); // r
  sprites[nFontNumber]->CreateFrame(189, 199, 0, nFontSmallLetterHeight); // s
  sprites[nFontNumber]->CreateFrame(199, 211, 0, nFontSmallLetterHeight); // t
  sprites[nFontNumber]->CreateFrame(211, 221, 0, nFontSmallLetterHeight); // u
  sprites[nFontNumber]->CreateFrame(221, 233, 0, nFontSmallLetterHeight); // v
  sprites[nFontNumber]->CreateFrame(233, 247, 0, nFontSmallLetterHeight); // w
  sprites[nFontNumber]->CreateFrame(247, 256, 0, nFontSmallLetterHeight); // x
  sprites[nFontNumber]->CreateFrame(256, 265, 0, nFontSmallLetterHeight); // y
  sprites[nFontNumber]->CreateFrame(265, 274, 0, nFontSmallLetterHeight); // z

  // Numbers and special characters
  nFontNumberStartHeight = nFontCapLetterHeight+1;
  nFontNumberHeight = 26;
  sprites[nFontNumber]->CreateFrame(0,   12,  nFontNumberStartHeight, nFontNumberHeight);   // 0
  sprites[nFontNumber]->CreateFrame(12,  19,  nFontNumberStartHeight, nFontNumberHeight);   // 1
  sprites[nFontNumber]->CreateFrame(19,  31,  nFontNumberStartHeight, nFontNumberHeight);   // 2
  sprites[nFontNumber]->CreateFrame(31,  43,  nFontNumberStartHeight, nFontNumberHeight);   // 3
  sprites[nFontNumber]->CreateFrame(43,  54,  nFontNumberStartHeight, nFontNumberHeight);   // 4
  sprites[nFontNumber]->CreateFrame(54,  66,  nFontNumberStartHeight, nFontNumberHeight);   // 5
  sprites[nFontNumber]->CreateFrame(66,  78,  nFontNumberStartHeight, nFontNumberHeight);   // 6
  sprites[nFontNumber]->CreateFrame(78,  89,  nFontNumberStartHeight, nFontNumberHeight);   // 7
  sprites[nFontNumber]->CreateFrame(89,  101, nFontNumberStartHeight, nFontNumberHeight);   // 8
  sprites[nFontNumber]->CreateFrame(101, 113, nFontNumberStartHeight, nFontNumberHeight);   // 9
  sprites[nFontNumber]->CreateFrame(113, 118, nFontNumberStartHeight, nFontNumberHeight);   // !
  sprites[nFontNumber]->CreateFrame(118, 123, nFontNumberStartHeight, nFontNumberHeight);   // '
  sprites[nFontNumber]->CreateFrame(123, 128, nFontNumberStartHeight, nFontNumberHeight);   // :
  sprites[nFontNumber]->CreateFrame(128, 136, nFontNumberStartHeight, nFontNumberHeight);   // "
  sprites[nFontNumber]->CreateFrame(136, 141, nFontNumberStartHeight, nFontNumberHeight);   // .
  sprites[nFontNumber]->CreateFrame(141, 146, nFontNumberStartHeight, nFontNumberHeight+1); // ;
  sprites[nFontNumber]->CreateFrame(146, 157, nFontNumberStartHeight, nFontNumberHeight);   // ?
  sprites[nFontNumber]->CreateFrame(157, 169, nFontNumberStartHeight-1, nFontNumberHeight); // $
  sprites[nFontNumber]->CreateFrame(169, 179, nFontNumberStartHeight, nFontNumberHeight);   // -
  sprites[nFontNumber]->CreateFrame(179, 191, nFontNumberStartHeight, nFontNumberHeight);   // +
  sprites[nFontNumber]->CreateFrame(191, 201, nFontNumberStartHeight, nFontNumberHeight);   // =
  sprites[nFontNumber]->CreateFrame(201, 205, nFontNumberStartHeight, nFontNumberHeight+1); // ,

  sprites[SPRITE_FONT_5]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_FONT_5]->CopyFrameDimensions(sprites[SPRITE_FONT_4]);

  nFontNumber = SPRITE_FONT_15;
  sprites[nFontNumber]->SetTransColor(RGB(0, 0, 0));
  nFontNumberStartHeight = 0;
  nFontNumberHeight = 10;

  // This font has no letters, it is a number-only font
  for (int i = 0; i < 52; i++)
    sprites[nFontNumber]->CreateFrame(0, 0, 0, 0);
  
  sprites[nFontNumber]->CreateFrame(0,   10,  nFontNumberStartHeight, nFontNumberHeight);   // 0
  sprites[nFontNumber]->CreateFrame(11,  19,  nFontNumberStartHeight, nFontNumberHeight);   // 1
  sprites[nFontNumber]->CreateFrame(20,  30,  nFontNumberStartHeight, nFontNumberHeight);   // 2
  sprites[nFontNumber]->CreateFrame(31,  40,  nFontNumberStartHeight, nFontNumberHeight);   // 3
  sprites[nFontNumber]->CreateFrame(41,  50,  nFontNumberStartHeight, nFontNumberHeight);   // 4
  sprites[nFontNumber]->CreateFrame(51,  60,  nFontNumberStartHeight, nFontNumberHeight);   // 5
  sprites[nFontNumber]->CreateFrame(61,  70,  nFontNumberStartHeight, nFontNumberHeight);   // 6
  sprites[nFontNumber]->CreateFrame(71,  80,  nFontNumberStartHeight, nFontNumberHeight);   // 7
  sprites[nFontNumber]->CreateFrame(81,  90,  nFontNumberStartHeight, nFontNumberHeight);   // 8
  sprites[nFontNumber]->CreateFrame(91,  100, nFontNumberStartHeight, nFontNumberHeight);   // 9

  sprites[SPRITE_FONT_16]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_FONT_16]->CopyFrameDimensions(sprites[SPRITE_FONT_15]);

  nFontNumber = SPRITE_FONT_6;
  sprites[nFontNumber]->SetTransColor(RGB(0, 0, 0));
  nFontLetterHeight = 10;

  sprites[nFontNumber]->CreateFrame(0,   10,  0, nFontLetterHeight); // A
  sprites[nFontNumber]->CreateFrame(10,  19,  0, nFontLetterHeight); // B
  sprites[nFontNumber]->CreateFrame(19,  30,  0, nFontLetterHeight); // C
  sprites[nFontNumber]->CreateFrame(30,  41,  0, nFontLetterHeight); // D
  sprites[nFontNumber]->CreateFrame(41,  50,  0, nFontLetterHeight); // E
  sprites[nFontNumber]->CreateFrame(50,  59,  0, nFontLetterHeight); // F
  sprites[nFontNumber]->CreateFrame(59,  70,  0, nFontLetterHeight); // G
  sprites[nFontNumber]->CreateFrame(70,  79,  0, nFontLetterHeight); // H
  sprites[nFontNumber]->CreateFrame(79,  83,  0, nFontLetterHeight); // I
  sprites[nFontNumber]->CreateFrame(83,  91,  0, nFontLetterHeight); // J
  sprites[nFontNumber]->CreateFrame(90,  100, 0, nFontLetterHeight); // K
  sprites[nFontNumber]->CreateFrame(100, 109, 0, nFontLetterHeight); // L
  sprites[nFontNumber]->CreateFrame(109, 120, 0, nFontLetterHeight); // M
  sprites[nFontNumber]->CreateFrame(120, 129, 0, nFontLetterHeight); // N
  sprites[nFontNumber]->CreateFrame(129, 140, 0, nFontLetterHeight); // O
  sprites[nFontNumber]->CreateFrame(140, 149, 0, nFontLetterHeight); // P
  sprites[nFontNumber]->CreateFrame(149, 162, 0, nFontLetterHeight); // Q
  sprites[nFontNumber]->CreateFrame(162, 172, 0, nFontLetterHeight); // R
  sprites[nFontNumber]->CreateFrame(172, 182, 0, nFontLetterHeight); // S
  sprites[nFontNumber]->CreateFrame(181, 192, 0, nFontLetterHeight); // T
  sprites[nFontNumber]->CreateFrame(192, 201, 0, nFontLetterHeight); // U
  sprites[nFontNumber]->CreateFrame(201, 211, 0, nFontLetterHeight); // V
  sprites[nFontNumber]->CreateFrame(211, 225, 0, nFontLetterHeight); // W
  sprites[nFontNumber]->CreateFrame(225, 233, 0, nFontLetterHeight); // X
  sprites[nFontNumber]->CreateFrame(233, 241, 0, nFontLetterHeight); // Y
  sprites[nFontNumber]->CreateFrame(241, 249, 0, nFontLetterHeight); // Z

  sprites[nFontNumber]->CreateFrame(0,   10,  0, nFontLetterHeight); // a
  sprites[nFontNumber]->CreateFrame(10,  19,  0, nFontLetterHeight); // b
  sprites[nFontNumber]->CreateFrame(19,  30,  0, nFontLetterHeight); // c
  sprites[nFontNumber]->CreateFrame(30,  41,  0, nFontLetterHeight); // d
  sprites[nFontNumber]->CreateFrame(41,  50,  0, nFontLetterHeight); // e
  sprites[nFontNumber]->CreateFrame(50,  59,  0, nFontLetterHeight); // f
  sprites[nFontNumber]->CreateFrame(59,  70,  0, nFontLetterHeight); // g
  sprites[nFontNumber]->CreateFrame(70,  79,  0, nFontLetterHeight); // h
  sprites[nFontNumber]->CreateFrame(79,  83,  0, nFontLetterHeight); // i
  sprites[nFontNumber]->CreateFrame(83,  91,  0, nFontLetterHeight); // j
  sprites[nFontNumber]->CreateFrame(90,  100, 0, nFontLetterHeight); // k
  sprites[nFontNumber]->CreateFrame(100, 109, 0, nFontLetterHeight); // l
  sprites[nFontNumber]->CreateFrame(109, 120, 0, nFontLetterHeight); // m
  sprites[nFontNumber]->CreateFrame(120, 129, 0, nFontLetterHeight); // n
  sprites[nFontNumber]->CreateFrame(129, 140, 0, nFontLetterHeight); // o
  sprites[nFontNumber]->CreateFrame(140, 149, 0, nFontLetterHeight); // p
  sprites[nFontNumber]->CreateFrame(149, 162, 0, nFontLetterHeight); // q
  sprites[nFontNumber]->CreateFrame(162, 172, 0, nFontLetterHeight); // r
  sprites[nFontNumber]->CreateFrame(172, 182, 0, nFontLetterHeight); // s
  sprites[nFontNumber]->CreateFrame(181, 192, 0, nFontLetterHeight); // t
  sprites[nFontNumber]->CreateFrame(192, 201, 0, nFontLetterHeight); // u
  sprites[nFontNumber]->CreateFrame(201, 211, 0, nFontLetterHeight); // v
  sprites[nFontNumber]->CreateFrame(211, 225, 0, nFontLetterHeight); // w
  sprites[nFontNumber]->CreateFrame(225, 233, 0, nFontLetterHeight); // x
  sprites[nFontNumber]->CreateFrame(233, 241, 0, nFontLetterHeight); // y
  sprites[nFontNumber]->CreateFrame(241, 249, 0, nFontLetterHeight); // z


  // Numbers and special characters
  nFontNumberStartHeight = nFontLetterHeight+1;
  nFontNumberHeight = 20;
  sprites[nFontNumber]->CreateFrame(0,   9,   nFontNumberStartHeight, nFontNumberHeight);   // 0
  sprites[nFontNumber]->CreateFrame(9,   14,  nFontNumberStartHeight, nFontNumberHeight);   // 1
  sprites[nFontNumber]->CreateFrame(14,  23,  nFontNumberStartHeight, nFontNumberHeight);   // 2
  sprites[nFontNumber]->CreateFrame(23,  32,  nFontNumberStartHeight, nFontNumberHeight);   // 3
  sprites[nFontNumber]->CreateFrame(32,  40,  nFontNumberStartHeight, nFontNumberHeight);   // 4
  sprites[nFontNumber]->CreateFrame(40,  49,  nFontNumberStartHeight, nFontNumberHeight);   // 5
  sprites[nFontNumber]->CreateFrame(49,  58,  nFontNumberStartHeight, nFontNumberHeight);   // 6
  sprites[nFontNumber]->CreateFrame(58,  66,  nFontNumberStartHeight, nFontNumberHeight);   // 7
  sprites[nFontNumber]->CreateFrame(66,  75,  nFontNumberStartHeight, nFontNumberHeight);   // 8
  sprites[nFontNumber]->CreateFrame(75,  84,  nFontNumberStartHeight, nFontNumberHeight);   // 9
  sprites[nFontNumber]->CreateFrame(84,  88,  nFontNumberStartHeight, nFontNumberHeight);   // !
  sprites[nFontNumber]->CreateFrame(88,  92,  nFontNumberStartHeight, nFontNumberHeight);   // '
  sprites[nFontNumber]->CreateFrame(92,  96,  nFontNumberStartHeight, nFontNumberHeight);   // :
  sprites[nFontNumber]->CreateFrame(96,  102, nFontNumberStartHeight, nFontNumberHeight);   // "
  sprites[nFontNumber]->CreateFrame(102, 106, nFontNumberStartHeight, nFontNumberHeight);   // .
  sprites[nFontNumber]->CreateFrame(106, 110, nFontNumberStartHeight, nFontNumberHeight+1); // ;
  sprites[nFontNumber]->CreateFrame(110, 118, nFontNumberStartHeight, nFontNumberHeight);   // ?
  sprites[nFontNumber]->CreateFrame(118, 127, nFontNumberStartHeight-1, nFontNumberHeight); // $
  sprites[nFontNumber]->CreateFrame(127, 135, nFontNumberStartHeight, nFontNumberHeight);   // -
  sprites[nFontNumber]->CreateFrame(134, 143, nFontNumberStartHeight, nFontNumberHeight);   // +
  sprites[nFontNumber]->CreateFrame(143, 150, nFontNumberStartHeight, nFontNumberHeight);   // =
  sprites[nFontNumber]->CreateFrame(150, 153, nFontNumberStartHeight, nFontNumberHeight+1); // ,
  sprites[nFontNumber]->CreateFrame(153, 159, nFontNumberStartHeight-1, nFontNumberHeight); // (
  sprites[nFontNumber]->CreateFrame(158, 164, nFontNumberStartHeight-1, nFontNumberHeight); // )

  sprites[SPRITE_FONT_7]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_FONT_7]->CopyFrameDimensions(sprites[SPRITE_FONT_6]);

  sprites[SPRITE_FONT_8]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_FONT_8]->CopyFrameDimensions(sprites[SPRITE_FONT_6]);

  sprites[SPRITE_FONT_9]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_FONT_9]->CopyFrameDimensions(sprites[SPRITE_FONT_6]);

  sprites[SPRITE_FONT_10]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_FONT_10]->CopyFrameDimensions(sprites[SPRITE_FONT_6]);

  sprites[SPRITE_FONT_12]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_FONT_12]->CopyFrameDimensions(sprites[SPRITE_FONT_6]);

  sprites[SPRITE_FONT_13]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_FONT_13]->CopyFrameDimensions(sprites[SPRITE_FONT_6]);

  sprites[SPRITE_FONT_14]->SetTransColor(RGB(0, 0, 0));
  sprites[SPRITE_FONT_14]->CopyFrameDimensions(sprites[SPRITE_FONT_6]);
}