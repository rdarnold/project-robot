
void StartStakeholderScreen1();
void StartStakeholderQuestionScreen();
void DrawStakeholderScreen(bool bInfoScreen = false);
void InitializeStakeholders();
void HandleButtonStakeholder(int wmId);
void SetupScreenPositionVars();
int DrawSpeak(char *strSpeaker, char *strText, int nXPos, int nRightBound, int nYPos);

enum
{
  STAKEHOLDERSTATE_SCREEN_1,
  STAKEHOLDERSTATE_SCREEN_2,
  STAKEHOLDERSTATE_SCREEN_3,
  STAKEHOLDERSTATE_SCREEN_4,
  STAKEHOLDERSTATE_SCREEN_5
};
