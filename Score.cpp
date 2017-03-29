/*

  Score.cpp/h

  Author: Ross Arnold
  Date  : 04/24/2010

  These files are used to determine the scores awarded by each stakeholder each month,
  how many resources each stakeholder gives, and any other aspect of the game
  relating to score, in-game rewards, and score calculation, such as new questions
  awarded, new resources, etc.

*/

#include "ProjectRobot.h"
#include "System_Models.h"
#include "Screen_Change_SubSystem.h"
#include "Records.h"

extern Stakeholder stakeholder[NUM_STAKEHOLDERS];
extern Robot *g_pTheRobot;
extern RobotParameters theCorrectRobot;

// This is a list of the score records for each turn
// Doesn't really need to be MAX_TURN 
ScoreRecordList recordlist[MAX_TURN];

void ResetRecords()
{
  ScoreRecord *pRec;
  for (int i = 0; i < MAX_TURN; i++)
  {
    for (int j = 0; j < MAX_SCORE_RECORD; j++)
    {
      pRec = recordlist[i].GetRecord(j);
      pRec->Clear();
    }
  }
}

ScoreRecord *GetThisTurnRecordForStakeholder(int nStakeholder)
{
  int nTurn = theGame.GetTurn();

  if (nTurn == 3)
    nTurn = 0;
  else if (nTurn == 7)
    nTurn = 1;
  else if (nTurn == 11)
    nTurn = 2;
  else
    nTurn -= 9;

  return recordlist[nTurn].GetRecord(nStakeholder);
}

void RecordScore(int nID, int nApprove, int nScore)
{
  ScoreRecord *pRec = GetThisTurnRecordForStakeholder(nID);
  pRec->RecordScoreInfo(nID, nApprove, nScore);
}

void AddToScoreRecord(int nID, int nApprove, int nScore)
{
  ScoreRecord *pRec = GetThisTurnRecordForStakeholder(nID);
  pRec->AddScoreInfo(nID, nApprove, nScore);
}


// Special accessories give special defense bonuses
int GetArmorParamBasedOnAccessories(SystemWithArmor *pSwa, int nArmorValueIndex)
{
  Accessory *pEq = 0;
  for (int i = 0; i < MAX_EQ_SLOTS; i++)
  {
    if (pSwa->GetEq(i))
    {
      pEq = pSwa->GetEq(i);

      if (pEq->GetType() != ACC_TYPE_ACC)
        continue;

      if ((pEq->GetModel() == ACC_SER_DEFENSE) &&
          (nArmorValueIndex == ARMOR_VALUE_SONIC || 
           nArmorValueIndex == ARMOR_VALUE_EMP || 
           nArmorValueIndex == ARMOR_VALUE_RADIATION))
        return 3;

      if ((pEq->GetModel() == ACC_MAGNETIC_DEFLECTOR) &&
          (nArmorValueIndex == ARMOR_VALUE_IMPACT || 
           nArmorValueIndex == ARMOR_VALUE_STEALTH || 
           nArmorValueIndex == ARMOR_VALUE_MANEUVER))
        return 3;
    }
  }

  return 0;
}

void AddArmorParams(SystemWithArmor *pSwa)
{
  for (int i = 0; i < NUM_ARMOR_VALUES; i++)
  {
    if (pSwa->GetArmorValue(i) > 0)
    {
      g_pTheRobot->TotalSystemParams.nArmorValues[i] += pSwa->GetArmorValue(i);
    }
    g_pTheRobot->TotalSystemParams.nArmorValues[i] += GetArmorParamBasedOnAccessories(pSwa, i);
  }
}

void AddSpecParams(System *pSys)
{
  for (int i = 0; i < NUM_SPEC_VALUES; i++)
  {
    g_pTheRobot->TotalSystemParams.nSpecValues[i] += pSys->GetSpecValue(i);
  }
}

void AddAccessoryParams(System *pSys)
{
  for (int i = 0; i < MAX_EQ_SLOTS; i++)
  {
    Accessory *pEq = pSys->GetEq(i);
    if (pEq)
    {
      // Check the type to see what to do
      switch (pEq->GetType())
      {
        
        // Add the accessory params
        case ACC_TYPE_ACC:
        {
          for (int j = 0; j < NUM_ACC_VALUES; j++)
          {
            if (pEq->IsSensor())
            {
              g_pTheRobot->TotalSystemParams.nAccValues[j] += GetSensorValueForTheRobot(pEq->GetModel(), j);
            }
            else
            {
              g_pTheRobot->TotalSystemParams.nAccValues[j] += GetDefaultAccValue(pEq->GetModel(), j);
            }
          }
          break;
        }

        // Gun has the gun params
        case ACC_TYPE_GUN:
        {
          for (int j = 0; j < NUM_GUN_VALUES; j++)
          {
            g_pTheRobot->TotalSystemParams.nGunValues[j] += GetDefaultGunValue(pEq->GetModel(), j);
          }
          break;
        }

       // Melee, do melee params
        case ACC_TYPE_MELEE:
        {
          for (int j = 0; j < NUM_MELEE_VALUES; j++)
          {
            g_pTheRobot->TotalSystemParams.nMeleeValues[j] += GetDefaultMeleeValue(pEq->GetModel(), j);
          }
          break;
        }
      }
    }
  }
}

void CalcParams_Frame()
{
  Frame *pFrame = g_pTheRobot->GetFrame();
  AddSpecParams(pFrame);
}

void CalcParams_Head()
{
  Head *pHead = g_pTheRobot->GetHead();
  AddArmorParams(pHead);
  AddAccessoryParams(pHead);
  AddSpecParams(pHead);
}

void CalcParams_Torso()
{
  Torso *pTorso = g_pTheRobot->GetTorso();
  AddArmorParams(pTorso);
  AddAccessoryParams(pTorso);
  AddSpecParams(pTorso);
}

void CalcParams_Arm(bool bIsLeft)
{
  Arm *pArm = 0;
  if (bIsLeft) {
    pArm = g_pTheRobot->GetLeftArm();
  } else {
    pArm = g_pTheRobot->GetRightArm();
  }
  AddArmorParams(pArm);
  AddAccessoryParams(pArm);
  AddSpecParams(pArm);
}

void CalcParams_Leg(bool bIsLeft)
{

  Leg *pLeg = 0;
  if (bIsLeft) {
    pLeg = g_pTheRobot->GetLeftLeg();
  } else {
    pLeg = g_pTheRobot->GetRightLeg();
  }
  AddArmorParams(pLeg);
  AddAccessoryParams(pLeg);
  AddSpecParams(pLeg);
}

void ClearParams()
{
  for (int i = 0; i < NUM_ARMOR_VALUES; i++)
  {
    g_pTheRobot->TotalSystemParams.nArmorValues[i] = 0;
  }

  for (i = 0; i < NUM_ACC_VALUES; i++)
  {
    g_pTheRobot->TotalSystemParams.nAccValues[i] = 0;
  }

  for (i = 0; i < NUM_GUN_VALUES; i++)
  {
    g_pTheRobot->TotalSystemParams.nGunValues[i] = 0;
  }

  for (i = 0; i < NUM_MELEE_VALUES; i++)
  {
    g_pTheRobot->TotalSystemParams.nMeleeValues[i] = 0;
  }

  for (i = 0; i < NUM_SPEC_VALUES; i++)
  {
    g_pTheRobot->TotalSystemParams.nSpecValues[i] = 0;
  }
}

// This function figures out what our total system parameters
// are based on sub-systems, so like what is the total speed,
// or the total heat defense
void RecalculateTotalSystemParams()
{
  // First we clear what we had already
  ClearParams();

  // Now we calc all the new stuff
  CalcParams_Frame();
  CalcParams_Head();
  CalcParams_Torso();
  CalcParams_Arm(false);
  CalcParams_Arm(true);
  CalcParams_Leg(false);
  CalcParams_Leg(true);

  // Now we have to average the defense values over the whole system,
  // 6 systems are armored so that's what we divide by
  for (int i = 0; i < NUM_ARMOR_VALUES; i++)
  {
    g_pTheRobot->TotalSystemParams.nArmorValues[i] /= 6;
  }

  g_pTheRobot->TotalSystemParams.nSpecValues[SPEC_VALUE_MANEUVER] =
    g_pTheRobot->GetTotalManeuver();

  g_pTheRobot->TotalSystemParams.nSpecValues[SPEC_VALUE_SPEED] =
    g_pTheRobot->GetTotalSpeed();
}

// if bHigherIsBetter is true, then a higher weight gives a better
// rating, like in the case of weight capacity
int TranslateWeightToRating(int nWeight, bool bHigherIsBetter)
{
  float fBase = 40;
  float fMax = 100;
  float fDiv = (fMax-fBase)/MAX_DESIRED_PARAMETER;
  float fWeight = (float)nWeight;

  // A rating of 15 is the 'best' i.e. the lowest weight
  if (fWeight < fBase)
  {
    if (bHigherIsBetter)
      return 0;
    else
      return MAX_DESIRED_PARAMETER;
  }
  if (fWeight > fMax)
  {
    if (bHigherIsBetter)
      return MAX_DESIRED_PARAMETER;
    else
      return 0;
  }

  // So the rating is based on how far below the max
  // weight you are.  You get more score if you're further
  // below.
  float fRating = ((fMax - fWeight)/fDiv);

  if (bHigherIsBetter)
  {
    fRating = MAX_DESIRED_PARAMETER - fRating;
  }

  return (int)fRating;
}

int CalcSystemHas(int nSystemHas, int nDesired, char *strValueName)
{
  int nRetv = 0;
  
  if (nSystemHas >= nDesired)
  {
    nRetv += nDesired;
    sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
      "Gained Approval: %s meets or exceeds the required value\n", strValueName);
  }
  else
  {
    nRetv += nSystemHas;

    // Do the division to see if we're at the right level for where we are
    double fDesired = (double)nDesired;
    fDesired /= MAX_DEVELOPMENT_TURN;
    fDesired *= theGame.GetTurn();

    double fSystemHas = (double)nSystemHas;

    if (fSystemHas >= fDesired)
      sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
        "Gained Approval: %s meets or exceeds the desired value\n", strValueName);
    else
      sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
        "Lost Approval: %s is lower than desired value\n", strValueName);
  }

  return nRetv;
}

void UpdateApproval(Stakeholder *pSH)
{
  RobotParameters *pDesiredPrms = 0;
  RobotParameters *pTotalSystemPrms = 0;
  int nTotalDesired = 0;
  int nTotalSystemHas = 0;
  int i = 0;

  pDesiredPrms = &pSH->RobotPreferences;
  pTotalSystemPrms = &g_pTheRobot->TotalSystemParams;

  // What we actually do here is take every measure together and
  // average it to see if we're on track based on the current turn.
  // So he doesn't really care about the individual things, rather he cares
  // if everything overall is 'where it should be' depending on how far
  // along we are in the process.

  for (i = SPEC_VALUE_PREF_START; i < SPEC_VALUE_PREF_END; i++)
  {
    if (pDesiredPrms->nSpecValues[i] > 0)
    {
      // Weights are handled differently because they're given a rating
      if (i == SPEC_VALUE_CARRY_WEIGHT)
      {
        nTotalDesired += pDesiredPrms->nSpecValues[i];
        int nTotalWeight = TranslateWeightToRating(g_pTheRobot->GetTotalWeight(), 
          (i == SPEC_VALUE_WEIGHT ? false : true));
        
        nTotalSystemHas += 
          CalcSystemHas(nTotalWeight, pDesiredPrms->nSpecValues[i], GET_SPEC_VALUE_FULL_TEXT(i));
      }
      else
      {
        nTotalDesired += pDesiredPrms->nSpecValues[i];

        nTotalSystemHas += 
          CalcSystemHas(pTotalSystemPrms->nSpecValues[i], pDesiredPrms->nSpecValues[i], GET_SPEC_VALUE_FULL_TEXT(i));
      }
    }
  }
  for (i = 0; i < NUM_ARMOR_VALUES; i++)
  {
    if (pDesiredPrms->nArmorValues[i] > 0)
    {
      nTotalDesired += pDesiredPrms->nArmorValues[i];
      
      nTotalSystemHas += 
        CalcSystemHas(pTotalSystemPrms->nArmorValues[i], pDesiredPrms->nArmorValues[i], GET_ARMOR_VALUE_FULL_TEXT(i));
    }
  }
  for (i = 0; i < NUM_GUN_VALUES; i++)
  {
    if (pDesiredPrms->nGunValues[i] > 0)
    {
      nTotalDesired += pDesiredPrms->nGunValues[i];

      nTotalSystemHas += 
        CalcSystemHas(pTotalSystemPrms->nGunValues[i], pDesiredPrms->nGunValues[i], GET_GUN_VALUE_FULL_TEXT(i));
    }
  }
  for (i = 0; i < NUM_MELEE_VALUES; i++)
  {
    if (pDesiredPrms->nMeleeValues[i] > 0)
    {
      nTotalDesired += pDesiredPrms->nMeleeValues[i];

      nTotalSystemHas += 
        CalcSystemHas(pTotalSystemPrms->nMeleeValues[i], pDesiredPrms->nMeleeValues[i], GET_MELEE_VALUE_FULL_TEXT(i));
    }
  }
  for (i = 0; i < NUM_ACC_VALUES; i++)
  {
    if (pDesiredPrms->nAccValues[i] > 0)
    {
      nTotalDesired += pDesiredPrms->nAccValues[i];

      nTotalSystemHas += 
        CalcSystemHas(pTotalSystemPrms->nAccValues[i], pDesiredPrms->nAccValues[i], GET_ACC_VALUE_FULL_TEXT(i));
    }
  }

  // Now we have the total desired, and total of what the system currently has.
  // So we divide the desired by the turn to find out what we need per turn.
  nTotalDesired /= MAX_DEVELOPMENT_TURN;
  nTotalDesired *= theGame.GetTurn();

  int nDiff = nTotalSystemHas - nTotalDesired;

  // And the score is changed depending on how far off we are in points

  // We can be below what we really want and still gain score
  int nScore = nDiff+5;
  if (nScore > 0)
  {
    theGame.AddToScoreFromStakeholder(nScore);
    AddToScoreRecord(pSH->GetType(), 0, nScore);
  }

  // Approval is purely the difference
  pSH->AddApproval(nDiff);  
  AddToScoreRecord(pSH->GetType(), nDiff, 0);
}

void UpdateSupervisorApproval()
{
  //////////////////////////
  //// BEGIN SUPERVISOR ////
  //////////////////////////
  theGame.strScoreDesc[0] = 0;
  Stakeholder *pSH = 0;
  int nPointsGained = 0;

  pSH = &stakeholder[STAKEHOLDER_SUPERVISOR];

  // Supervisor is concerned with cost
  int nTotalCostPerTurn = theGame.GetTotalSystemCostPerTurn();

  // So we get how much we should have spent by now, which is
  // the total cost divided by the total number of turns, times
  // the number of turns that have passed
  int nTotalCostPerTurnShouldBe = (pSH->RobotPreferences.nCost/10)*theGame.GetTurn();

  nPointsGained = nTotalCostPerTurnShouldBe - nTotalCostPerTurn;

  // One point for each resource below, you still get score for being 5 higher
  int nScore = nPointsGained+5;
  if (nScore > 0)
  {
    theGame.AddToScoreFromStakeholder((nScore/2));
    AddToScoreRecord(pSH->GetType(), 0, (nScore/2));
  }

  int nApproval = nPointsGained/2;
  pSH->AddApproval(nApproval);
  AddToScoreRecord(pSH->GetType(), nApproval, 0);
  
  if (nApproval > 0)
  {
    sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
      "Gained Approval: Cost is within budget\n");
  }
}

void UpdatePMApproval()
{
  //////////////////
  //// BEGIN PM ////
  //////////////////
  theGame.strScoreDesc[0] = 0;
  Stakeholder *pSH = &stakeholder[STAKEHOLDER_PM];
  UpdateApproval(pSH);

  if (theGame.GetTurn() < MAX_DEVELOPMENT_TURN)
    return;

  // Now update based on whether or not we've picked any of the sustainable systems
  for (int i = 0; i < MAX_SUS_SYSTEMS; i++)
  {
    System *pSys = g_pTheRobot->GetSystemByType(pSH->RobotPreferences.nSustainableSystemType[i]);
    if (pSys->GetSystemModel() == pSH->RobotPreferences.nSustainableSystemModel[i])
    {  
      int nAdd = 3;
      pSH->AddApproval(nAdd);
      theGame.AddToScoreFromStakeholder(nAdd);
      AddToScoreRecord(pSH->GetType(), nAdd, nAdd);

      sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
        "Gained Approval: Sustainable %s chosen\n", pSys->GetSystemTypeName());
    }
  }
}

void UpdateTrainerApproval()
{
  ///////////////////////
  //// BEGIN TRAINER ////
  ///////////////////////
  theGame.strScoreDesc[0] = 0;
  int nPointsGained = 0;
  Stakeholder *pSH = &stakeholder[STAKEHOLDER_TRAINER];

  // If we've chosen a pilot interface and it isn't the one he
  // wants, he doesn't approve.  But he cares a lot MORE after
  // it's fielded.
  if (theGame.GetTurn() < MAX_DEVELOPMENT_TURN)
    nPointsGained = 3;
  else
    nPointsGained = 6;

  if (g_pTheRobot->GetHumanInterface()->GetSystemModel() != SYSTEM_MODEL_NONE)
  {
    if (g_pTheRobot->GetHumanInterface()->GetSystemModel() == pSH->RobotPreferences.nUserInterfaceType)
    {
      theGame.AddToScoreFromStakeholder(nPointsGained);
      pSH->AddApproval(nPointsGained);
      AddToScoreRecord(pSH->GetType(), nPointsGained, nPointsGained);

      sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
        "Gained Approval: Preferred pilot interface chosen\n");
    }
    else 
    {
      pSH->SubApproval(nPointsGained);

      sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
        "Lost Approval: Non-preferred pilot interface chosen\n");
    }
  }

  // Now check based on the trainer exps
  if (theGame.GetTurn() < MAX_DEVELOPMENT_TURN)
    return;

  bool bAddPoints = false;
  nPointsGained = 5;

  if (pSH->RobotPreferences.nTrainerExp[TRAINER_EXP_MANEUVER])
  {
    if (g_pTheRobot->GetTotalManeuver() >= 7)
      bAddPoints = true;
  }
  if (pSH->RobotPreferences.nTrainerExp[TRAINER_EXP_FIREPOWER])
  {
    if (g_pTheRobot->CountTotalGuns() >= g_pTheRobot->CountTotalMelees())
      bAddPoints = true;
  }
  if (pSH->RobotPreferences.nTrainerExp[TRAINER_EXP_CLOSE_COMBAT])
  {
    if (g_pTheRobot->CountTotalMelees() >= g_pTheRobot->CountTotalGuns())
      bAddPoints = true;
  }
  if (pSH->RobotPreferences.nTrainerExp[TRAINER_EXP_MID_WEIGHT])
  {
    if (g_pTheRobot->GetTotalWeight() > 70 &&
        g_pTheRobot->GetTotalWeight() < 120)
      bAddPoints = true;
  }
  if (pSH->RobotPreferences.nTrainerExp[TRAINER_EXP_LIGHT])
  {
    if (g_pTheRobot->GetTotalWeight() <= 70)
      bAddPoints = true;
  }
  if (pSH->RobotPreferences.nTrainerExp[TRAINER_EXP_HEAVY])
  {
    if (g_pTheRobot->GetTotalWeight() >= 120)
      bAddPoints = true;
  }

  if (bAddPoints)
  {
    theGame.AddToScoreFromStakeholder(nPointsGained);
    pSH->AddApproval(nPointsGained);
    AddToScoreRecord(pSH->GetType(), nPointsGained, nPointsGained);

    sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
      "Gained Approval: Robot parameters are in line with trainer experience\n");
  }
  else
  {
    pSH->SubApproval(nPointsGained);
    AddToScoreRecord(pSH->GetType(), (nPointsGained * -1), 0);

    sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
      "Lost Approval: Robot parameters are not in line with trainer experience\n");
  }
}

void UpdateDeveloperApproval()
{ 
  /////////////////////////
  //// BEGIN DEVELOPER ////
  /////////////////////////
  theGame.strScoreDesc[0] = 0;
}

void UpdateContractorApproval()
{
  //////////////////////////
  //// BEGIN CONTRACTOR ////
  //////////////////////////
  theGame.strScoreDesc[0] = 0;
}

void UpdateSenatorApproval()
{
  ///////////////////////
  //// BEGIN SENATOR ////
  ///////////////////////
  theGame.strScoreDesc[0] = 0;
  Stakeholder *pSH = &stakeholder[STAKEHOLDER_SENATOR];

  UpdateApproval(pSH);

  if (theGame.GetTurn() < MAX_DEVELOPMENT_TURN)
    return;

  // If we're in the fielded phase, update based on environmental concerns
  int nTotalEnvMax = pSH->RobotPreferences.nMaxEnvImpact;
    
  int nTotalEnv = g_pTheRobot->GetTotalEnvImpact();
   
  if (nTotalEnv < nTotalEnvMax)
  {
    // Good, points and approval for this
    theGame.AddToScoreFromStakeholder(5);
    pSH->AddApproval(3);
    AddToScoreRecord(pSH->GetType(), 3, 5);

    sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
      "Gained Approval: Environmental impact within preference range\n");
  }
  else
  {
    int nDiff = nTotalEnv - nTotalEnvMax;
    pSH->SubApproval(nDiff/2);
    AddToScoreRecord(pSH->GetType(), (nDiff/2), 0);

    sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
      "Gained Approval: Environmental impact higher than preferred\n");
  }
}

void UpdateUserApproval()
{
  ////////////////////
  //// BEGIN USER ////
  ////////////////////
  theGame.strScoreDesc[0] = 0;
  int nPointsGained = 0;
  Stakeholder *pSH = &stakeholder[STAKEHOLDER_USER];

  UpdateApproval(pSH);
  
  // If we've chosen a pilot interface and it isn't the one he
  // wants, he doesn't approve.  But he cares a lot MORE after
  // it's fielded.
  if (theGame.GetTurn() < MAX_DEVELOPMENT_TURN)
    nPointsGained = 3;
  else
    nPointsGained = 6;

  if (g_pTheRobot->GetHumanInterface()->GetSystemModel() != SYSTEM_MODEL_NONE)
  {
    if (g_pTheRobot->GetHumanInterface()->GetSystemModel() == pSH->RobotPreferences.nUserInterfaceType)
    {
      theGame.AddToScoreFromStakeholder(nPointsGained);
      pSH->AddApproval(nPointsGained);
      AddToScoreRecord(pSH->GetType(), nPointsGained, nPointsGained);

      sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
        "Gained Approval: Preferred pilot interface chosen\n");
    }
    else 
    {
      pSH->SubApproval(nPointsGained);
      AddToScoreRecord(pSH->GetType(), (nPointsGained * -1), 0);

      sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
        "Lost Approval: Non-Preferred pilot interface chosen\n");
    }
  }

  // Now check operating environment
  if (theGame.GetTurn() < MAX_DEVELOPMENT_TURN)
    return;

  nPointsGained = 5;
  
  int nManeuver = g_pTheRobot->GetTotalManeuver();

  int nJump = g_pTheRobot->GetTotalJump();

  int nSpeed = g_pTheRobot->GetTotalSpeed();

  bool nHasTracks = false;
  if (g_pTheRobot->GetRightLeg()->GetSystemModel() == LEG_TRACK &&
      g_pTheRobot->GetLeftLeg()->GetSystemModel() == LEG_TRACK)
      nHasTracks = true;

  int nTerrain = pSH->RobotPreferences.nTerrain;

  // Gain the most if we are up to snuff, but we still gain a few points if we're
  // not bad, like if we don't quite meet the standard but we're close
  if ((nTerrain == TERRAIN_ROCKY && nJump >= 7) ||
      (nTerrain == TERRAIN_ROUGH && nJump >= 5 && nManeuver >= 5) ||
      (nTerrain == TERRAIN_FLAT && (nSpeed >= 7 || nHasTracks)) ||
      (nTerrain == TERRAIN_FORESTED && nManeuver >= 7))
  {
    theGame.AddToScoreFromStakeholder(nPointsGained);
    pSH->AddApproval(nPointsGained);
    AddToScoreRecord(pSH->GetType(), nPointsGained, nPointsGained);

    sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
      "Gained Approval: Robot is designed correctly for operating environment\n");
  }
  else if ((nTerrain == TERRAIN_ROCKY && nJump >= 5) ||
           (nTerrain == TERRAIN_ROUGH && nJump >= 4 && nManeuver >= 4) ||
           (nTerrain == TERRAIN_FLAT && nSpeed >= 5) ||
           (nTerrain == TERRAIN_FORESTED && nManeuver >= 5))
  {
    theGame.AddToScoreFromStakeholder(nPointsGained/2);
    pSH->AddApproval(nPointsGained/2);
    AddToScoreRecord(pSH->GetType(), nPointsGained/2, nPointsGained/2);

    sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
      "Gained Some Approval: Robot is designed adequately for operating environment\n");
  }
  else
  {
    pSH->SubApproval(nPointsGained);
    AddToScoreRecord(pSH->GetType(), (nPointsGained * -1), 0);

    sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
      "Lost Approval: Robot is not designed for operating environment\n");
  }
}

// This should be moved to the stakeholder file once it's finished.
// This function is called every turn.
void UpdateStakeholderApproval(int nStakeholderIndex)
{
  // So we have to take each stakeholder, figure out what he wants,
  // and make sure we're following what he wants.  Then we adjust
  // based on that.

  // First let's make sure our overall parameters are up to date.
  RecalculateTotalSystemParams();

  theGame.strScoreDesc[0] = 0;

  // Now update the approval of whichever one we chose
  switch (nStakeholderIndex)
  {
    case STAKEHOLDER_SUPERVISOR:  UpdateSupervisorApproval(); break;
    case STAKEHOLDER_TRAINER:     UpdateTrainerApproval(); break;
    case STAKEHOLDER_PM:          UpdatePMApproval(); break;
    case STAKEHOLDER_DEVELOPER:   UpdateDeveloperApproval(); break;
    case STAKEHOLDER_CONTRACTOR:  UpdateContractorApproval(); break;
    case STAKEHOLDER_SENATOR:     UpdateSenatorApproval(); break;
    case STAKEHOLDER_USER:        UpdateUserApproval(); break;
  }
}

int CalcResourcesForDeveloperAndSystem(SystemWithArmor *pSys, int nArmorValue)
{
  int nArmorType = pSys->GetArmorType();

  if (nArmorType == ARMOR_NONE)
    return 0;

  if (pSys->GetArmorValue(nArmorValue) >= (GetDefaultArmorValue(nArmorType, nArmorValue) + 4))
    return number(5, 10);

  return 0;
}

// So it figures out how many resources this stakeholder will
// give you based on approval
int CalcResourcesForStakeholder(int nStakeholder)
{
  double fResources = 0;

  // Developer gives you resources if you have done certain things with armor
  if (nStakeholder == STAKEHOLDER_DEVELOPER)
  {
    int nNum = 0;
    for (int i = 0; i < MAX_ARMOR_RES_GEN; i++)
    {
      int nArmorValue = stakeholder[STAKEHOLDER_DEVELOPER].RobotPreferences.nArmorResourceGen[i];
      if (0 != (nNum = CalcResourcesForDeveloperAndSystem(g_pTheRobot->GetHead(), nArmorValue)))
      {
        fResources += (double)nNum;
        continue;
      }
      if (0 != (nNum = CalcResourcesForDeveloperAndSystem(g_pTheRobot->GetTorso(), nArmorValue)))
      {
        fResources += (double)nNum;
        continue;
      }
      if (0 != (nNum = CalcResourcesForDeveloperAndSystem(g_pTheRobot->GetRightArm(), nArmorValue)))
      {
        fResources += (double)nNum;
        continue;
      }
      if (0 != (nNum = CalcResourcesForDeveloperAndSystem(g_pTheRobot->GetLeftArm(), nArmorValue)))
      {
        fResources += (double)nNum;
        continue;
      }
      if (0 != (nNum = CalcResourcesForDeveloperAndSystem(g_pTheRobot->GetRightLeg(), nArmorValue)))
      {
        fResources += (double)nNum;
        continue;
      }
      if (0 != (nNum = CalcResourcesForDeveloperAndSystem(g_pTheRobot->GetLeftLeg(), nArmorValue)))
      {
        fResources += (double)nNum;
        continue;
      }
    }
    return (int)fResources;
  }

  // Base of 5 
  fResources = 5;

  // Give them 2/3 of approval as resources, basically
  int fResAdd = ((stakeholder[nStakeholder].GetApproval()*2)/3);

  fResources += fResAdd;

  // And the senator gives only 2/3 of that
  if (nStakeholder == STAKEHOLDER_SENATOR)
    fResources *= 0.67;

  // If we're in the sustainment phase, give less money
  if (theGame.GetTurn() >= MAX_DEVELOPMENT_TURN)
    fResources /= 4;

  return (fResources < 0 ? 0 : (int)fResources);
}

/*

  SCORE FORMULA:

    - Score is awarded at 10 points if the amount is correct, plus 1 point for every point above
      the correct amount.
      Ex. Heat Def needs to be 15.  We have 17.  Thus we get 10 + (17 - 15) points (12 total).

    - Score is awarded at 0 points if the amount is 1 lower than the correct amount.

    - For any item that is 2 or more below, TOTAL score is reduced by a 10*amount percentage.
      Ex. Heat Def needs to be 15.  It is 12.  Thus total score of the ENTIRE SYSTEM is reduced by 30%.

*/

// A negative return is a divider
// A positive return is the actual score
int CalcScoreForValue(int nValue, int nRequiredValue)
{
  int nScore = 0;

  if (nValue >= nRequiredValue)
  {
    nScore = 10;
    nScore += nValue - nRequiredValue;
    return nScore;
  }

  if (nValue == nRequiredValue - 1)
    return 0;

  // Cant go less than losing 100 percent
  if ((nRequiredValue - nValue) >= 20)
    return -20;

  return ((nRequiredValue - nValue) * -1);
}

void CalcScoreChange(int nValue, int nRequiredValue, int &nTotalScore, double &fPercent, char *strValueName)
{
  int nScoreChange = CalcScoreForValue(nValue, nRequiredValue);

  if (nScoreChange < 0)
  {
    double fScoreChange = (double)nScoreChange;

    // Flip it back to a positive number
    fScoreChange *= -1;  

    // So now fScoreChange represents the number of points we were off.  Like if
    // we were 20 lower than our target value, fScoreChange would now be 20.

    // Translate fScoreChange to the actual percentage.  We want to calc at around
    // 2.5 percent per point.  So simply do the math.

    fScoreChange *= 0.025;

    // So if fScoreChange were 20, now it would be 20 * 0.025, or 0.5.  If it
    // were 10, it would now be 0.25.  This is actually the percent LOST, i.e. the amount 
    // we want to subtract from 1 to find the real percent.

    // And just for kicks, make sure it's bounded in case I screwed up somewhere.  This
    // will at least prevent total disaster.
    if (fScoreChange < 0)
      fScoreChange = 0;
    if (fScoreChange > 1.0)
      fScoreChange = 1.0;

    fPercent *= (1.0 - fScoreChange);
    sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc), 
      "%s: -%0.0f Percent\n", strValueName, fScoreChange*100);
  } 
  else
  {
    nTotalScore += nScoreChange;
    sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc), 
      "%s: %s%d\n", strValueName, (nScoreChange > 0 ? "+" : ""), nScoreChange);
  }
}

int CalcScoreForOneSystemInterfaces(System *pSys)
{
  int nScore = 0;

  if (!pSys)
    return 0;

  for (int i = 0; i < NUM_INTERFACES; i++) 
  {
    if (!pSys->HasInterface(i))
      continue;

    if (number(0, INTERFACE_LEVELS-1) <= pSys->GetInterfaceValue(i))
      nScore += 1;
    else
      nScore -= 1;
  }

  sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc), 
    "%s Interfaces: %s%d\n", GET_INTERFACE_TEXT(pSys->GetSystemType()), 
    (nScore > 0 ? "+" : ""), nScore);

  return nScore;
}

int UpdateScoreBasedOnInterfaces()
{
  int nAddToTotalScore = 0;

  // For each interface, do a random roll based on the interface confidence.  If it fails,
  // report the failure for display and if it succeeds, add to the score.  Just a flat #
  // for each one - like X points for each interface that succeeds, -X for each that fails,
  // but you can't LOSE score

  nAddToTotalScore += CalcScoreForOneSystemInterfaces(g_pTheRobot->GetHead());
  nAddToTotalScore += CalcScoreForOneSystemInterfaces(g_pTheRobot->GetTorso());
  nAddToTotalScore += CalcScoreForOneSystemInterfaces(g_pTheRobot->GetRightArm());
  nAddToTotalScore += CalcScoreForOneSystemInterfaces(g_pTheRobot->GetLeftArm());
  nAddToTotalScore += CalcScoreForOneSystemInterfaces(g_pTheRobot->GetRightLeg());
  nAddToTotalScore += CalcScoreForOneSystemInterfaces(g_pTheRobot->GetLeftLeg());
  nAddToTotalScore += CalcScoreForOneSystemInterfaces(g_pTheRobot->GetCoolingSystem());
  nAddToTotalScore += CalcScoreForOneSystemInterfaces(g_pTheRobot->GetComputerSystem());
  nAddToTotalScore += CalcScoreForOneSystemInterfaces(g_pTheRobot->GetEjectionSystem());
  nAddToTotalScore += CalcScoreForOneSystemInterfaces(g_pTheRobot->GetHumanInterface());

  if (nAddToTotalScore < 0)
    nAddToTotalScore = 0;

  return nAddToTotalScore;
}

int UpdateScoreBasedOnParams()
{
  RobotParameters *pCorrectPrms = 0;
  RobotParameters *pTotalSystemPrms = 0;
  int nCorrectAmount = 0;
  int nAddToTotalScore = 0;
  double fScorePercent = 1.0;
  int i = 0;

  pCorrectPrms = &theCorrectRobot;
  pTotalSystemPrms = &g_pTheRobot->TotalSystemParams;

  // What we actually do here is take every measure together and
  // average it to see if we're on track based on the current turn.
  // So he doesn't really care about the individual things, rather he cares
  // if everything overall is 'where it should be' depending on how far
  // along we are in the process.

  // Weight is not used as a preferred parameter anymore since it is taken
  // into account in the Problems section
  for (i = SPEC_VALUE_PREF_START; i < SPEC_VALUE_PREF_END; i++)
  {
    if (pCorrectPrms->nSpecValues[i] > 0)
    {
      // Weights are handled differently because they're given a rating
      if (i == SPEC_VALUE_CARRY_WEIGHT)
      {
        nCorrectAmount = pCorrectPrms->nSpecValues[i];
        int nTotalWeight = TranslateWeightToRating(g_pTheRobot->GetTotalWeight(), 
          (i == SPEC_VALUE_WEIGHT ? false : true));

        CalcScoreChange(nTotalWeight, pCorrectPrms->nSpecValues[i], 
          nAddToTotalScore, fScorePercent, GET_SPEC_VALUE_FULL_TEXT(i));
      }
      else
      {
        CalcScoreChange(pTotalSystemPrms->nSpecValues[i], pCorrectPrms->nSpecValues[i], 
          nAddToTotalScore, fScorePercent, GET_SPEC_VALUE_FULL_TEXT(i));
      }
    }
  }
  for (i = 0; i < NUM_ARMOR_VALUES; i++)
  {
    if (pCorrectPrms->nArmorValues[i] > 0)
    {
      CalcScoreChange(pTotalSystemPrms->nArmorValues[i], pCorrectPrms->nArmorValues[i], 
        nAddToTotalScore, fScorePercent, GET_ARMOR_VALUE_FULL_TEXT(i));
    }
  }
  for (i = 0; i < NUM_GUN_VALUES; i++)
  {
    if (pCorrectPrms->nGunValues[i] > 0)
    {
      CalcScoreChange(pTotalSystemPrms->nGunValues[i], pCorrectPrms->nGunValues[i], 
        nAddToTotalScore, fScorePercent, GET_GUN_VALUE_FULL_TEXT(i));
    }
  }
  for (i = 0; i < NUM_MELEE_VALUES; i++)
  {
    if (pCorrectPrms->nMeleeValues[i] > 0)
    {
      CalcScoreChange(pTotalSystemPrms->nMeleeValues[i], pCorrectPrms->nMeleeValues[i], 
        nAddToTotalScore, fScorePercent, GET_MELEE_VALUE_FULL_TEXT(i));
    }
  }
  for (i = 0; i < NUM_ACC_VALUES; i++)
  {
    if (pCorrectPrms->nAccValues[i] > 0)
    {
      CalcScoreChange(pTotalSystemPrms->nAccValues[i], pCorrectPrms->nAccValues[i], 
        nAddToTotalScore, fScorePercent, GET_ACC_VALUE_FULL_TEXT(i));
    }
  }

  // So we have the score total, just multiply it by the percentage of score we're giving
  // to get the real total, since we reduce by percentiles of things aren't up to snuff
  double fAddToTotalScoreDecimal = (double)nAddToTotalScore * fScorePercent;
  nAddToTotalScore = (int)fAddToTotalScoreDecimal;
 
  // We can actually get a Score Percent reduction HIGHER than 1, like if things are WAY off,
  // but we don't want to REDUCE score so we just move along and give the player nothing.
  if (nAddToTotalScore < 0)
    nAddToTotalScore = 0;

  // Add the score
  theGame.AddToScoreFromField(nAddToTotalScore);

  // And return the score we added
  return nAddToTotalScore;
}

int VaryMaxHeatCostBasedOnOpEnv(int nMaxHeatCost, bool bForce = true)
{
  // If we're not forcing it to calculate, we check to see if the temperature
  // has been revealed through questioning 
  if (bForce == false && theGame.GetTurn() < MAX_DEVELOPMENT_TURN && 
      stakeholder[STAKEHOLDER_USER].RobotPreferences.bTemperatureRevealed == false)
  {
    return nMaxHeatCost;
  }

  double fNewMaxHeatCost = (double)nMaxHeatCost;

  int nTemp = stakeholder[STAKEHOLDER_USER].RobotPreferences.nTemperature;
  if (nTemp == TEMP_COLD)
    fNewMaxHeatCost *= 1.2;
  else if (nTemp == TEMP_VARIED)
    fNewMaxHeatCost *= 0.8;

  return ((int)fNewMaxHeatCost);
}

// Update score based on whether or not certain values are too high, like weight etc.
double UpdateScoreBasedOnProblems()
{
  double fNewScorePercent = 100.0;
  double fPercentReduce = 0.0;

  // Weight, 1.0% for each point over
  if (g_pTheRobot->GetTotalWeight() > g_pTheRobot->GetMaxWeight())
  {
    fPercentReduce = 1.0 * (g_pTheRobot->GetTotalWeight() - g_pTheRobot->GetMaxWeight());
    fNewScorePercent *= (1.0 - (fPercentReduce/100));
    sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
      "Max Weight Exceeded by %d!  Score -%d percent\n", g_pTheRobot->GetTotalWeight() - g_pTheRobot->GetMaxWeight(),
      (int)fPercentReduce);
  }

  // Power, 2% for each point over
  if (g_pTheRobot->GetTotalPowerCost() > g_pTheRobot->GetMaxPowerCost())
  {
    fPercentReduce = 2.0 * (g_pTheRobot->GetTotalPowerCost() - g_pTheRobot->GetMaxPowerCost());
    fNewScorePercent *= (1.0 - (fPercentReduce/100));
    sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
      "Max Power Exceeded by %d!  Score -%d percen\nt", g_pTheRobot->GetTotalPowerCost() - g_pTheRobot->GetMaxPowerCost(),
      (int)fPercentReduce);
  }

  // Heat, 2% for each point over
  int nMaxHeatCost = VaryMaxHeatCostBasedOnOpEnv(g_pTheRobot->GetMaxHeatCost());
    
  if (g_pTheRobot->GetTotalHeatCost() > nMaxHeatCost)
  {
    fPercentReduce = 2.0 * (g_pTheRobot->GetTotalHeatCost() - nMaxHeatCost);
    fNewScorePercent *= (1.0 - (fPercentReduce/100));
    sprintf(theGame.strScoreDesc + strlen(theGame.strScoreDesc),
      "Max Heat Exceeded by %d!  Score -%d percent\n", g_pTheRobot->GetTotalHeatCost() - nMaxHeatCost,
      (int)fPercentReduce);
  }

  if (fNewScorePercent < 0.0)
    fNewScorePercent = 0.0;

  return (fNewScorePercent/100.0);
}


int UpdateScoreBasedOnSolution()
{
  double nTotalScore = 0;

  theGame.strScoreDesc[0] = 0;

  nTotalScore += (double)UpdateScoreBasedOnParams();
  nTotalScore += (double)UpdateScoreBasedOnInterfaces();

  nTotalScore *= UpdateScoreBasedOnProblems();

  // Record the info
  RecordScore(SCORE_ID_FIELDED, 0, (int)nTotalScore);

  return (int)nTotalScore;
}
