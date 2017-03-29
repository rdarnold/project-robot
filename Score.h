
/*

  Score.cpp/h

  Author: Ross Arnold
  Date  : 04/24/2010

  These files are used to determine the scores awarded by each stakeholder each month,
  how many resources each stakeholder gives, and any other aspect of the game
  relating to score, in-game rewards, and score calculation, such as new questions
  awarded, new resources, etc.

*/

void UpdateStakeholderApproval(int nStakeholderIndex);
int CalcResourcesForStakeholder(int nStakeholder);
int UpdateScoreBasedOnSolution();
void DrawEndTurnScoreReport();
void ResetRecords();