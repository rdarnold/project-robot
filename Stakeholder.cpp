/*
  Stakeholder.cpp
  
  File for the Stakeholder class, written for 
  Project Robot, submission for Stevens Tech
  Experience Accelerator Contest 2010
  
  Author: 
     Ross Arnold 03/30/2010
*/

#include "ProjectRobot.h"
#include "System_Models.h"

Stakeholder stakeholder[NUM_STAKEHOLDERS];
extern Robot *g_pTheRobot;

extern RobotParameters theCorrectRobot;

extern void PrintDateToString(int nTurn, char *strDate);
extern void GetModelNameBySystem(int nSystem, int nModel, char *strName);

const char *Stakeholder_Types[] =
{
  "Supervisor",
  "Army Product Manager",
  "New Equipment Trainer",
  "Government Integrator",
  "Contractor",
  "Politician",
  "User"
};

const char *strSupervisor_Names[] =
{
  "Biff", "Weatherby", "Johnson", "Chuckles", "Wiley"
};

const char *strPM_Names[] =
{
  "General Problem", "General Dandy", "General Fatherly", "General Payne", "General Direction"
};

const char *strPM_ShortNames[] =
{
  "Gen. Problem", "Gen. Dandy", "Gen. Fatherly", "Gen. Payne", "Gen. Direction"
};

const char *strTrainer_Names[] =
{
  "Rocky", "Falcon", "Cracker", "Mopey", "Whiner"
};

const char *strDeveloper_Names[] =
{
  "Mr. Dolittle", "Mr. Doitall", "Mr. Brain", "Mr. Yesman", "Mr. Reliable"
};

const char *strContractor_Names[] =
{
  "Dimeadozen, LLC", "Moneyfornothing, INC", "Payme CO", "Cheapo CORP", "Believer, Limited"
};

const char *strSenator_Names[] =
{
  "Senator Cranky", "Senator Roberts", "Senator Golfer", "Senator Lucky", "Senator Lionheart"
};

const char *strSenator_ShortNames[] =
{
  "Sen. Cranky", "Sen. Roberts", "Sen. Golfer", "Sen. Lucky", "Sen. Lionheart"
};

const char *strUser_Names[] =
{
  "Warfighter", "Warfighter", "Warfighter", "Warfighter", "Warfighter"
};

// Supervisor
const char *strSupervisor_Questions[] = 
{
  "Project personnel",
  "Current funding",
  "~"
};

// General
const char *strPM_Questions[] = 
{
  "Attack needs",
  "Defense needs",
  "System specs",
  //"Operating environment",
  "Sustainability",
  //"Other similar military systems",
  "~"
};

// Trainer
const char *strTrainer_Questions[] = 
{
  "Training experience", // (this could show which items will decrease training costs)
  "Preferences",
  //"Familiarity",
  "~"
};

// Developer/Integrator
const char *strDeveloper_Questions[] = 
{
  //"Short-term capabilities",
  //"Long-term capabilities",
  //"Experience with integrating COTS",
  //"Experience with new development",
  //"Short-term",
  //"Long-term",
  "Resource Generation",
  "Integration Experience",
  //"Logistics",
  "~"
};

// Contractor
const char *strContractor_Questions[] = 
{
  "Efficiencies", // (what types of things are they cost-efficient at making?)
  "Deficiencies",
  "~"
};

// Senator
const char *strSenator_Questions[] = 
{
  "Public attack preferences",
  "Public defense preferences",
  "Environmental concerns",
//  "Future funding",
  "~"
};

// User
/*
const char *strUser_Questions[] = 
{
  "Alien tactics",
  "Alien weaponry",
  "Allied tactics",
  "Allied weaponry",
  "Operating environment",
  "~"
};*/

// User
const char *strUser_Questions[] = 
{
  "Attack needs",
  "Defense needs",
  "System specs",
  "Preferences",
  "Operating environment",
  "~"
};

// All the systems, then the extras in the Effs enum
const char *strEffs[] =
{
  "robot frames",
  "robot heads",
  "robot torsos",
  "robot arms",
  "robot legs",
  "ejection systems",
  "cooling systems",
  "computers",
  "human interfaces",
  "all interfaces",
  "ranged weapons",
  "close combat weapons",
  "armor",
  "sensors",
  "~"
};

const char *strTrainerExps[] =
{
  "maneuver-based systems",
  "long range attack systems",
  "close combat systems",
  "mid-weight systems",
  "lightweight systems",
  "heavyweight systems",
  "~"
};

const char *strTerrains[] =
{
  "rocky",
  "rough",
  "flat",
  "forested",
  "~"
};

const char *strTerrainReqs[] =
{
  "legs that have high jump ratings",
  "legs that have a blend of jump and maneuver ratings",
  "tracks or legs that have high speed ratings",
  "legs that have high maneuver ratings",
  "~"
};

const char *strTemperatures[] =
{
  "cold",
  "moderate",
  "varied",
  "~"
};

const char *strTemperatureReqs[] =
{
  "will operate at 120 percent of their normal effectiveness",
  "will operate at their normal rating",
  "must be expected to operate at 80 percent of their normal effectiveness",
  "~"
};

// So we can generate random #s
extern int number( int from, int to );
extern int number_not(int min, int max, int not);

// Constructor
Stakeholder::Stakeholder() 
{
  Clear();
}

const char *Stakeholder::GetNameText(int nThisPerson)
{
  switch (nType)
  {
    case STAKEHOLDER_SUPERVISOR:
      return strSupervisor_Names[nThisPerson];
    case STAKEHOLDER_PM:
      return strPM_Names[nThisPerson];
    case STAKEHOLDER_TRAINER:
      return strTrainer_Names[nThisPerson];
    case STAKEHOLDER_DEVELOPER:
      return strDeveloper_Names[nThisPerson];
    case STAKEHOLDER_CONTRACTOR:
      return strContractor_Names[nThisPerson];
    case STAKEHOLDER_SENATOR:
      return strSenator_Names[nThisPerson];
    case STAKEHOLDER_USER:
      return strUser_Names[nThisPerson];
    default:
      // Erroar!
      break;
  }

  return 0;
}

const char *Stakeholder::GetName()
{
  return GetNameText(nPerson);
}

const char *Stakeholder::GetPrevName()
{
  return GetNameText(nPrevPerson);
}

const char *Stakeholder::GetShortName()
{
  switch (nType)
  {
    case STAKEHOLDER_SUPERVISOR:
      return strSupervisor_Names[nPerson];
    case STAKEHOLDER_PM:
      return strPM_ShortNames[nPerson];
    case STAKEHOLDER_TRAINER:
      return strTrainer_Names[nPerson];
    case STAKEHOLDER_DEVELOPER:
      return strDeveloper_Names[nPerson];
    case STAKEHOLDER_CONTRACTOR:
      return strContractor_Names[nPerson];
    case STAKEHOLDER_SENATOR:
      return strSenator_ShortNames[nPerson];
    case STAKEHOLDER_USER:
      return strUser_Names[nPerson];
    default:
      // Erroar!
      break;
  }

  return 0;
}

// False means change was not made, true means change was made
bool ChangeStakeholder(int nStakeholderNum)
{
  // Check if we're supposed to change this stakeholder this turn
  // If not, we return false.
  if (theGame.GetStakeholderChangeThisTurn() != nStakeholderNum)
    return false;

  // we need to record terrain and temperature if this is the user, as these
  // shouldnt/wouldn't change based on stakeholder
  int nTerrain = stakeholder[STAKEHOLDER_USER].RobotPreferences.nTerrain;
  int nTemperature = stakeholder[STAKEHOLDER_USER].RobotPreferences.nTemperature;
  
  int nPrevPerson = stakeholder[nStakeholderNum].GetPerson();

  stakeholder[nStakeholderNum].SetupStakeholder(nStakeholderNum);
  while (stakeholder[nStakeholderNum].GetPerson() == nPrevPerson)
    stakeholder[nStakeholderNum].SetupStakeholder(nStakeholderNum);
  
  if (nStakeholderNum == STAKEHOLDER_USER)
  {
    stakeholder[STAKEHOLDER_USER].RobotPreferences.nTerrain = nTerrain;
    stakeholder[STAKEHOLDER_USER].RobotPreferences.nTemperature = nTemperature;
  }

  stakeholder[nStakeholderNum].SetPrevPerson(nPrevPerson);

  return true;
}

#define MIN_NUM_PM_PREFS        2
#define MIN_NUM_SENATOR_PREFS   4
#define MIN_NUM_USER_PREFS      2

#define MAX_NUM_PM_PREFS        3
#define MAX_NUM_SENATOR_PREFS   5
#define MAX_NUM_USER_PREFS      3

#define PREF_POS_VAR  3
#define PREF_NEG_VAR -3

// Preference types, these are based on the way the questions worked,
// like "attack" question can be melee and gun
enum
{
  PREF_TYPE_ATTACK,
  PREF_TYPE_DEFENSE,
  PREF_TYPE_SYSTEM,
  NUM_PREF_TYPES
};

// So we look through all possible number-based prefs and only
// keep the top nNum of them
void SetTopPrefs(RobotParameters *theBot, int nNum, int nPreferenceType) 
{
  int nTop = 0;
  bool bFound = false;
  for (int i = 0; i < nNum; i++)
  {
    nTop = 0;
    bFound = false;

    // First we're just finding the top thing, using nTop to store the value
    // Then we look through and match the top with one of our values
    // If it's the one we want to keep, we set it to negative for now to get it
    // out of the mix
    int j = 0;
    if (nPreferenceType == PREF_TYPE_ATTACK)
    {
      // Find nTop
      for (j = 0; j < NUM_GUN_VALUES; j++)
        ((nTop < theBot->nGunValues[j]) ? nTop = theBot->nGunValues[j] : 0);

      for (j = 0; j < NUM_MELEE_VALUES; j++)
        ((nTop < theBot->nMeleeValues[j]) ? nTop = theBot->nMeleeValues[j] : 0);

      // Look through values
      for (j = 0; j < NUM_GUN_VALUES; j++)
        if (nTop == theBot->nGunValues[j]) { 
          theBot->nGunValues[j] *= -1; 
          bFound = true; 
          break; 
        }

      if (bFound)
        continue;

      for (j = 0; j < NUM_MELEE_VALUES; j++)
        if (nTop == theBot->nMeleeValues[j]) { 
          theBot->nMeleeValues[j] *= -1; 
          bFound = true; 
          break; 
        }

      if (bFound)
        continue;
    }
    else if (nPreferenceType == PREF_TYPE_DEFENSE)
    {
      // Find nTop
      for (j = 0; j < NUM_ARMOR_VALUES; j++)
        ((nTop < theBot->nArmorValues[j]) ? nTop = theBot->nArmorValues[j] : 0);

      // Look through values
      for (j = 0; j < NUM_ARMOR_VALUES; j++)
      if (nTop == theBot->nArmorValues[j]) { 
        theBot->nArmorValues[j] *= -1; 
        bFound = true; 
        break; 
      }

      if (bFound)
        continue;

    } 
    /*else if (nPreferenceType == PREF_TYPE_ACC)
    {
      // Find nTop
      for (j = 0; j < NUM_ACC_VALUES; j++)
        ((nTop < theBot->nAccValues[j]) ? nTop = theBot->nAccValues[j] : 0);

      // Look through values
      for (j = 0; j < NUM_ACC_VALUES; j++)
      if (nTop == theBot->nAccValues[j]) { 
        theBot->nAccValues[j] *= -1; 
        bFound = true; 
        break; 
      }

      if (bFound)
        continue;

    } */
    else 
    {
      // Find nTop
      for (j = SPEC_VALUE_PREF_START; j < SPEC_VALUE_PREF_END; j++)
        ((nTop < theBot->nSpecValues[j]) ? nTop = theBot->nSpecValues[j] : 0);

      for (j = 0; j < NUM_ACC_VALUES; j++)
        ((nTop < theBot->nAccValues[j]) ? nTop = theBot->nAccValues[j] : 0);

      // Look through values
      for (j = SPEC_VALUE_PREF_START; j < SPEC_VALUE_PREF_END; j++)
      if (nTop == theBot->nSpecValues[j]) { 
        theBot->nSpecValues[j] *= -1; 
        bFound = true; 
        break; 
      }

      if (bFound)
        continue;

      // Look through values
      for (j = 0; j < NUM_ACC_VALUES; j++)
      if (nTop == theBot->nAccValues[j]) { 
        theBot->nAccValues[j] *= -1; 
        bFound = true; 
        break; 
      }

      if (bFound)
        continue;

      // Find nTop
      /*((nTop < theBot->nWeight) ? nTop = theBot->nWeight : 0);
      ((nTop < theBot->nSpeed) ? nTop = theBot->nSpeed : 0);
      ((nTop < theBot->nManeuver) ? nTop = theBot->nManeuver : 0);
      ((nTop < theBot->nCarryWeight) ? nTop = theBot->nCarryWeight : 0);
      
      // Look through values
      if (nTop == theBot->nWeight) { theBot->nWeight *= -1; continue; }
      if (nTop == theBot->nSpeed) { theBot->nSpeed *= -1; continue; }
      if (nTop == theBot->nManeuver) { theBot->nManeuver *= -1; continue; }
      if (nTop == theBot->nCarryWeight) { theBot->nCarryWeight *= -1; continue; }*/
    }
  }

  // So anything that was set to negative, we set to positive of the same number,
  // all the rest we set to 0
  if (nPreferenceType == PREF_TYPE_ATTACK)
  {
    for (i = 0; i < NUM_GUN_VALUES; i++)
      ((theBot->nGunValues[i] < 0) ? theBot->nGunValues[i] *= -1 : theBot->nGunValues[i] = 0);

    for (i = 0; i < NUM_MELEE_VALUES; i++)
      ((theBot->nMeleeValues[i] < 0) ? theBot->nMeleeValues[i] *= -1 : theBot->nMeleeValues[i] = 0);
  }
  else if (nPreferenceType == PREF_TYPE_DEFENSE)
  {
    for (i = 0; i < NUM_ARMOR_VALUES; i++)
      ((theBot->nArmorValues[i] < 0) ? theBot->nArmorValues[i] *= -1 : theBot->nArmorValues[i] = 0);
  } 
  /*else if (nPreferenceType == PREF_TYPE_ACC)
  {
    for (i = 0; i < NUM_ACC_VALUES; i++)
      ((theBot->nAccValues[i] < 0) ? theBot->nAccValues[i] *= -1 : theBot->nAccValues[i] = 0);
  } */
  else
  {
    for (i = SPEC_VALUE_PREF_START; i < SPEC_VALUE_PREF_END; i++)
      ((theBot->nSpecValues[i] < 0) ? theBot->nSpecValues[i] *= -1 : theBot->nSpecValues[i] = 0);

    for (i = 0; i < NUM_ACC_VALUES; i++)
      ((theBot->nAccValues[i] < 0) ? theBot->nAccValues[i] *= -1 : theBot->nAccValues[i] = 0);
  }

  /*char buff[256];
  sprintf(buff, "%d %d %d %d %d %d",
    theBot->nSight, theBot->nAudio, theBot->nInfrared, theBot->nRadar, theBot->nHeatSensor, theBot->nMotionSensor);
  msgs(buff);*/
}

// This operates on the int itself, just set the preference to a variation
// of the correct pref passed in
void VaryPreference(int &nPref, int nCorrectPref)
{
  nPref = nCorrectPref + number(PREF_NEG_VAR, PREF_POS_VAR);
  if (nPref < 0)
    nPref = 0;
}

// Set the prefs for a stakeholder
void SetupStakeholderPrefs(int nStakeholder)
{
  RobotParameters *theBot = &stakeholder[nStakeholder].RobotPreferences;
  RobotParameters *theCorrectBot = &theCorrectRobot; 

  switch (nStakeholder)
  {
    case STAKEHOLDER_SUPERVISOR:
    {
      theBot->nCost = number(50, 100);
      theBot->nCostMin = number(theBot->nCost-20, theBot->nCost);
      theBot->nCostMax = number(theBot->nCost, theBot->nCost + 20);

      int nNumVacs = number(1, MAX_VACATIONS);
      int nNum = 0;
      for (int i = 0; i < nNumVacs; i++)
      {
        while (ArrayContains(theBot->nVacationMonths, MAX_VACATIONS, nNum))
          nNum = number(1, 10);
        theBot->nVacationMonths[i] = nNum;
      }
      
      // Maybe supervisor goes along with one of the stakeholders depends on which
      // one is picked.  
      break;
    }
    case STAKEHOLDER_PM:
    {
      
      // The PM wants something very similar to what the User wants, which is
      // similar to the correct system with a few differences.
      // This should probably be altered more later, like the user
      // should miss certain critical aspects of the system that only
      // the research team will find

      int i = 0;
      for (i = ARMOR_VALUE_PREF_START; i < ARMOR_VALUE_PREF_END; i++)
        VaryPreference(theBot->nArmorValues[i], theCorrectBot->nArmorValues[i]);

      for (i = GUN_VALUE_PREF_START; i < GUN_VALUE_PREF_END; i++)
        VaryPreference(theBot->nGunValues[i], theCorrectBot->nGunValues[i]);

      for (i = MELEE_VALUE_PREF_START; i < MELEE_VALUE_PREF_END; i++)
        VaryPreference(theBot->nMeleeValues[i], theCorrectBot->nMeleeValues[i]);

      for (i = ACC_VALUE_PREF_START; i < ACC_VALUE_PREF_END; i++)
        VaryPreference(theBot->nAccValues[i], theCorrectBot->nAccValues[i]);

      for (i = SPEC_VALUE_PREF_START; i < SPEC_VALUE_PREF_END; i++)
        VaryPreference(theBot->nSpecValues[i], theCorrectBot->nSpecValues[i]);
      
      // So now we take the top X out of all of these, and those are what the stakeholder
      // REALLY wants.  He doesn't care about the other shit.  If he cares about every little
      // number it'll get too complicated.
      SetTopPrefs(theBot, number(MIN_NUM_PM_PREFS, MAX_NUM_PM_PREFS), PREF_TYPE_ATTACK);
      SetTopPrefs(theBot, number(MIN_NUM_PM_PREFS, MAX_NUM_PM_PREFS), PREF_TYPE_DEFENSE);
      SetTopPrefs(theBot, number(MIN_NUM_PM_PREFS, MAX_NUM_PM_PREFS), PREF_TYPE_SYSTEM);
      //SetTopPrefs(theBot, number(MIN_NUM_PM_PREFS, MAX_NUM_PM_PREFS), PREF_TYPE_ACC);

      // Set the sustainable system prefs
      for (i = 0; i < MAX_SUS_SYSTEMS; i++)
      {
        int nSystemType = number(SYSTEM_HEAD, SYSTEM_COMPUTER);
        
        // We don't want duplicates for system type, like he asks for two different types
        // of heads.
        while (ArrayContains(theBot->nSustainableSystemType, MAX_SUS_SYSTEMS, nSystemType))
          nSystemType = number(SYSTEM_HEAD, SYSTEM_COMPUTER);

        theBot->nSustainableSystemType[i] = nSystemType;

        theBot->nSustainableSystemModel[i] = number(1, MAX_SYSTEM_MODEL[theBot->nSustainableSystemType[i]]);
      }
      break;
    }
    case STAKEHOLDER_TRAINER:
    { 
      theBot->nUserInterface = number(5, MAX_DESIRED_PARAMETER);
      theBot->nUserInterfaceType = number(HUMAN_INT_FLIGHT, NUM_HUMAN_INTS-1); 

      int nNumExps = number(3, 4);
      for (int i = 0; i < nNumExps; i++)
      {
        theBot->nTrainerExp[number(0, NUM_TRAINER_EXPS-1)] = true;
      }
      break;
    }
    case STAKEHOLDER_DEVELOPER:
    {
      // Developer doesn't care about the params,
      // only has different efficiences and abilities

      int i = 0;
      int nNum = 0;

      // Armor resource generation
      for (i = 0; i < MAX_ARMOR_RES_GEN; i++)
      {
        nNum = number(ARMOR_VALUE_PREF_START, NUM_ARMOR_VALUES-1);
        while (ArrayContains(theBot->nArmorResourceGen, MAX_ARMOR_RES_GEN, nNum))
          nNum = number(ARMOR_VALUE_PREF_START, NUM_ARMOR_VALUES-1);
        theBot->nArmorResourceGen[i] = nNum;
      }

      // Integration/interface efficiencies
      for (i = 0; i < MAX_INTEGRATE_SYSTEMS; i++)
      {
        nNum = number(1, NUM_SYSTEMS-1);
        while (ArrayContains(theBot->nIntegrationExp, MAX_INTEGRATE_SYSTEMS, nNum))
          nNum = number(1, NUM_SYSTEMS-1);
        theBot->nIntegrationExp[i] = nNum;
      }
      break;
    }
    case STAKEHOLDER_CONTRACTOR:
    {
      // Contractor doesn't care about the params,
      // only has different efficiences
      int nNumEffs = number(MIN_EFFS, MAX_EFFS);
      int nNumDefs = number(MIN_EFFS, MAX_EFFS);
      for (int i = 0; i < nNumEffs; i++)
      {
        theBot->nEfficiencies[number(0, NUM_EFFS-1)] = true;
      }
      i = 0;
      while (i < nNumDefs)
      {
        for (int j = 0; j < NUM_EFFS; j++)
        {
          if (!theBot->nEfficiencies[j] && number(0, NUM_EFFS) == 0)
          {
            theBot->nDeficiencies[j] = true;
            i++;
            break;
          }
        }
      }
      break;
    }
    case STAKEHOLDER_SENATOR:
    { 
      // The senator will pick one each of gun, armor, and melee,
      // and focus on those as "newest technologies" that the public
      // would like to see
      int i = 0;
      i = number(ARMOR_VALUE_PREF_START, ARMOR_VALUE_PREF_END-1);
      theBot->nArmorValues[i] = number(1, MAX_DESIRED_PARAMETER);

      i = number(GUN_VALUE_PREF_START, GUN_VALUE_PREF_END-1);
      theBot->nGunValues[i] = number(1, MAX_DESIRED_PARAMETER);

      i = number(MELEE_VALUE_PREF_START, MELEE_VALUE_PREF_END-1);
      theBot->nMeleeValues[i] = number(1, MAX_DESIRED_PARAMETER);

      SetTopPrefs(theBot, number(MIN_NUM_SENATOR_PREFS, MAX_NUM_SENATOR_PREFS), PREF_TYPE_ATTACK);
      SetTopPrefs(theBot, number(MIN_NUM_SENATOR_PREFS, MAX_NUM_SENATOR_PREFS), PREF_TYPE_DEFENSE);

      // Now set up the environmental concerns pref
      theBot->nMaxEnvImpact = number(20, 40);
      theBot->nMaxEnvImpactBottom = theBot->nMaxEnvImpact - number(5, 15); 
      theBot->nMaxEnvImpactTop = theBot->nMaxEnvImpact + number(5, 15); 
      break;
    }
    case STAKEHOLDER_USER:
    {
      theBot->nUserInterface = number(1, MAX_DESIRED_PARAMETER);

      // Not always the same as the trainer!
      theBot->nUserInterfaceType = number(HUMAN_INT_FLIGHT, NUM_HUMAN_INTS-1); 

      // The user wants something very similar to the correct system,
      // with a few differences.
      // This should probably be altered more later, like the user
      // should miss certain critical aspects of the system that only
      // the research team will find

      int i = 0;
      for (i = ARMOR_VALUE_PREF_START; i < ARMOR_VALUE_PREF_END; i++)
        VaryPreference(theBot->nArmorValues[i], theCorrectBot->nArmorValues[i]);

      for (i = GUN_VALUE_PREF_START; i < GUN_VALUE_PREF_END; i++)
        VaryPreference(theBot->nGunValues[i], theCorrectBot->nGunValues[i]);

      for (i = MELEE_VALUE_PREF_START; i < MELEE_VALUE_PREF_END; i++)
        VaryPreference(theBot->nMeleeValues[i], theCorrectBot->nMeleeValues[i]);

      for (i = ACC_VALUE_PREF_START; i < ACC_VALUE_PREF_END; i++)
        VaryPreference(theBot->nAccValues[i], theCorrectBot->nAccValues[i]);

      for (i = SPEC_VALUE_PREF_START; i < SPEC_VALUE_PREF_END; i++)
        VaryPreference(theBot->nSpecValues[i], theCorrectBot->nSpecValues[i]);

      // Set his top stuff
      SetTopPrefs(theBot, number(MIN_NUM_USER_PREFS, MAX_NUM_USER_PREFS), PREF_TYPE_ATTACK);
      SetTopPrefs(theBot, number(MIN_NUM_USER_PREFS, MAX_NUM_USER_PREFS), PREF_TYPE_DEFENSE);
      SetTopPrefs(theBot, number(MIN_NUM_USER_PREFS, MAX_NUM_USER_PREFS), PREF_TYPE_SYSTEM);
      //SetTopPrefs(theBot, number(MIN_NUM_USER_PREFS, MAX_NUM_USER_PREFS), PREF_TYPE_ACC);

      // And the operating environment
      theBot->nTerrain = number(0, NUM_TERRAINS-1);
      theBot->nTemperature = number(0, NUM_TEMPS-1);
      break;
    }
  };
}

void Stakeholder::SetupStakeholder(int type) 
{
  int i;

  // Clear it all first
  Clear();

  nType = type;
  nPerson = number(0, 4); // Random person
  nApproval = number(40, 60); // Random approval
  switch (type)
  {
    case STAKEHOLDER_SUPERVISOR:
      //sprintf(strName, "%s", strSupervisor_Names[nPerson]);

      for (i = 0; i < MAX_QUESTIONS; i++) 
      {
        if (!strcmp(strSupervisor_Questions[i], "~"))
          break;
        sprintf(strQuestions[i], "%s", strSupervisor_Questions[i]);
      }
      break;
    case STAKEHOLDER_PM:
      //sprintf(strName, "%s", strPM_Names[nPerson]);

      for (i = 0; i < MAX_QUESTIONS; i++) 
      {
        if (!strcmp(strPM_Questions[i], "~"))
          break;
        sprintf(strQuestions[i], "%s", strPM_Questions[i]);
      }
      break;
    case STAKEHOLDER_TRAINER:
      //sprintf(strName, "%s", strTrainer_Names[nPerson]);
      
      for (i = 0; i < MAX_QUESTIONS; i++) 
      {
        if (!strcmp(strTrainer_Questions[i], "~"))
          break;
        sprintf(strQuestions[i], "%s", strTrainer_Questions[i]);
      }
      break;
    case STAKEHOLDER_DEVELOPER:
      //sprintf(strName, "%s", strDeveloper_Names[nPerson]);
      
      for (i = 0; i < MAX_QUESTIONS; i++) 
      {
        if (!strcmp(strDeveloper_Questions[i], "~"))
          break;
        sprintf(strQuestions[i], "%s", strDeveloper_Questions[i]);
      }
      break;
    case STAKEHOLDER_CONTRACTOR:
      //sprintf(strName, "%s", strContractor_Names[nPerson]);
      
      for (i = 0; i < MAX_QUESTIONS; i++) 
      {
        if (!strcmp(strContractor_Questions[i], "~"))
          break;
        sprintf(strQuestions[i], "%s", strContractor_Questions[i]);
      }
      break;
    case STAKEHOLDER_SENATOR:
      //sprintf(strName, "%s", strSenator_Names[nPerson]);
      
      for (i = 0; i < MAX_QUESTIONS; i++) 
      {
        if (!strcmp(strSenator_Questions[i], "~"))
          break;
        sprintf(strQuestions[i], "%s", strSenator_Questions[i]);
      }
      break;
    case STAKEHOLDER_USER:
      //sprintf(strName, "%s", strUser_Names[nPerson]);
      
      for (i = 0; i < MAX_QUESTIONS; i++) 
      {
        if (!strcmp(strUser_Questions[i], "~"))
          break;
        sprintf(strQuestions[i], "%s", strUser_Questions[i]);
      }
      break;
    default:
      // Erroar!
      break;
  
  }

  SetupStakeholderPrefs(type);
}

void Stakeholder::Clear()
{
  //strName[0] = 0;
  nPerson = 0;        // Which person is this stakeholder?
  nType = 0;          // Which type of stakeholder is this (military, user, etc) ?
  nApproval = 0;      // Stakeholder's approval rating of Systems Engineer's actions thus far

  nPrevPerson = 0;
 
  for (int i = 0; i < MAX_QUESTIONS; i++)
  {
    nQuestionStates[i] = 0; 
    strQuestions[i][0] = 0;
  }
}

void Stakeholder::PrintSupervisorVacs(int nQuestionNum, char *strAnswer, int nTotalCount)
{
  int nCount = 0;

  // Now print out what we want
  sprintf(strAnswer, "Some of our personnel will be out of the office around");
  int nQuestionState = GetQuestionState(nQuestionNum);
  for (int i = 0; i < MAX_VACATIONS; i++)
  {
    if (nCount >= nQuestionState)
      break;

    // If we have one, we increment count, otherwise we move on
    if (this->RobotPreferences.nVacationMonths[i])
      nCount++;
    else
      continue;

    char strDate[256];
    PrintDateToString(this->RobotPreferences.nVacationMonths[i], strDate);
    
    if (nCount != nTotalCount || nTotalCount == 1)
      sprintf(strAnswer + strlen(strAnswer), " %s,", strDate);
    else
      sprintf(strAnswer + strlen(strAnswer), " and %s", strDate);
  }
}

int Stakeholder::FindSupervisorAnswer(int nQuestionNum, char *strAnswer)
{
  switch (nQuestionNum)
  {  
    // 0 is personnel 
    case 0: 
    {
      // Count them first
      int nTotalCount = 0;
      for (int i = 0; i < MAX_VACATIONS; i++)
      {
        if (this->RobotPreferences.nVacationMonths[i])
          nTotalCount++;
      }

      PrintSupervisorVacs(nQuestionNum, strAnswer, nTotalCount);

      if (GetQuestionState(nQuestionNum) >= nTotalCount)
      {
        strcat(strAnswer, " so plan accordingly. Resource costs will double during these times.");
        return true;
      }
      
      strcat(strAnswer, " and at some other times, so plan accordingly. Resource costs will double during these times.");
      return false;
    }

    // 1 is current funding
    case 1: 
    {
      switch (GetQuestionState(nQuestionNum))
      {
        case 1:
          sprintf(strAnswer, "I'd like you to keep the yearly resource cost in the %d-%d range.", 
            this->RobotPreferences.nCostMin, this->RobotPreferences.nCostMax);
          return false;
        default:
          sprintf(strAnswer, "I'd like you to keep the yearly resource cost below %d.", this->RobotPreferences.nCost);
          return true;
      }
      break;
    }
  }

  return true;
}

void PrintPreferenceValue(char *strPref, int nPrefValue, int nPrintActualNumber)
{
  strPref[0] = 0;
  if (nPrintActualNumber > 0)
  {
    sprintf(strPref, "%d", nPrefValue);
  } else {
    sprintf(strPref, "%s", TranslateValueToText(nPrefValue));
  }
}

// Returns false if no items left to print after this one is printed
bool PrintOnePreference(int nPrefValue, char *strPrefName, char *strAnswer, 
                        int &nItemsLeft, int &nSpecific, int nQuestionState)
{
  if (nPrefValue <= 0)
    return true;

  // There are always at least 2 items, so if we're on
  // the last one, make the sentence grammatically correct,
  // of course if we're only on question state 1, we don't
  // want to say "and" because we're only printing one item
  if (nItemsLeft == 1 && nQuestionState != 1)
    strcat(strAnswer, "and ");

  if (StartsWithVowel(strPrefName))
    strcat(strAnswer, "an");
  else
    strcat(strAnswer, "a");

  char buf[256];
  PrintPreferenceValue(buf, nPrefValue, nSpecific);
  sprintf(strAnswer + strlen(strAnswer), " %s that is %s or better", strPrefName, buf);
  
  nItemsLeft--;
  nSpecific--;
  
  if (nItemsLeft <= 0)
  { 
    strcat(strAnswer, ".");
    return false;
  }
  strcat(strAnswer, ", ");

  return true;
}

int CountPrefs(int nStakeholder, int nPreferenceType)
{
  RobotParameters *theBot = &stakeholder[nStakeholder].RobotPreferences;

  int nCount = 0;
  int i = 0;
  if (nPreferenceType == PREF_TYPE_ATTACK)
  {
    for (i = 0; i < NUM_GUN_VALUES; i++)
      ((theBot->nGunValues[i] > 0) ? nCount++ : 0);

    for (i = 0; i < NUM_MELEE_VALUES; i++)
      ((theBot->nMeleeValues[i] > 0) ? nCount++ : 0);
  }
  else if (nPreferenceType == PREF_TYPE_DEFENSE)
  {
    for (i = 0; i < NUM_ARMOR_VALUES; i++)
      ((theBot->nArmorValues[i] > 0) ? nCount++ : 0);
  } 
  /*else if (nPreferenceType == PREF_TYPE_ACC)
  {
    for (i = 0; i < NUM_ACC_VALUES; i++)
      ((theBot->nAccValues[i] > 0) ? nCount++ : 0);
  } */
  else 
  {
    for (i = SPEC_VALUE_PREF_START; i < SPEC_VALUE_PREF_END; i++)
      ((theBot->nSpecValues[i] > 0) ? nCount++ : 0);

    for (i = 0; i < NUM_ACC_VALUES; i++)
      ((theBot->nAccValues[i] > 0) ? nCount++ : 0);
  }

  return nCount;
}

// Kind of reverse engineering; find the question number that this preference ties
// to so that we can check the question state and know whether to draw it as a number
// or as text.
int FindQuestionNumBasedOnPref(int nStakeholder, int nPrefArrayType)
{
  // We only use this for the stakeholders with parameter prefs
  switch (nStakeholder)
  {
    case STAKEHOLDER_PM:
    {
      if (nPrefArrayType == PREF_ARRAY_GUN || nPrefArrayType == PREF_ARRAY_MELEE)
        return 0;
      else if (nPrefArrayType == PREF_ARRAY_ARMOR)
        return 1;
      else if (nPrefArrayType == PREF_ARRAY_SPEC || nPrefArrayType == PREF_ARRAY_ACC)
        return 2;
      break;
    }
    case STAKEHOLDER_SENATOR:
    {
      if (nPrefArrayType == PREF_ARRAY_GUN || nPrefArrayType == PREF_ARRAY_MELEE)
        return 0;
      else if (nPrefArrayType == PREF_ARRAY_ARMOR)
        return 1;
      break;
    }

    case STAKEHOLDER_USER:
    {
      if (nPrefArrayType == PREF_ARRAY_GUN || nPrefArrayType == PREF_ARRAY_MELEE)
        return 0;
      else if (nPrefArrayType == PREF_ARRAY_ARMOR)
        return 1;
      else if (nPrefArrayType == PREF_ARRAY_SPEC || nPrefArrayType == PREF_ARRAY_ACC)
        return 2;
      break;
    }
  };

  return 0;
}

// So, we have a pref for Close Range Impact - which question state
// does this correspond to?  Like if we're at question state 2, does that
// mean we can display this Close Range Impact value as a number?
int FindPreferenceLocationWithinQuestion(int nStakeholder, int nPrefNum, int nPrefArrayType)
{
  RobotParameters *theBot = &stakeholder[nStakeholder].RobotPreferences;
  int i = 0;
  int nLocation = 0;

  if (nPrefArrayType == PREF_ARRAY_GUN)
  {
    for (i = GUN_VALUE_PREF_START; i < GUN_VALUE_PREF_END; i++)
    {
      if (i == nPrefNum)
        return nLocation;

      if (theBot->nGunValues[i])
        nLocation++;
    }
  }
  else if (nPrefArrayType == PREF_ARRAY_MELEE)
  {
    // Add gun values up first since melee and gun are both under "attack" prefs
    for (i = GUN_VALUE_PREF_START; i < GUN_VALUE_PREF_END; i++)
    {
      if (theBot->nGunValues[i])
        nLocation++;
    }

    for (i = MELEE_VALUE_PREF_START; i < MELEE_VALUE_PREF_END; i++)
    {
      if (i == nPrefNum)
        return nLocation;

      if (theBot->nMeleeValues[i])
        nLocation++;
    }
  } 
  else if (nPrefArrayType == PREF_ARRAY_ARMOR)
  {
    for (i = ARMOR_VALUE_PREF_START; i < ARMOR_VALUE_PREF_END; i++)
    {
      if (i == nPrefNum)
        return nLocation;

      if (theBot->nArmorValues[i])
        nLocation++;
    }
  }
  else if (nPrefArrayType == PREF_ARRAY_ACC)
  {
    // Add spec values up first since spec and acc are both under "system" prefs
    for (i = SPEC_VALUE_PREF_START; i < SPEC_VALUE_PREF_END; i++)
    {
      if (theBot->nSpecValues[i])
        nLocation++;
    }

    for (i = ACC_VALUE_PREF_START; i < ACC_VALUE_PREF_END; i++)
    {
      if (i == nPrefNum)
        return nLocation;

      if (theBot->nAccValues[i])
        nLocation++;
    }
  }
  else if (nPrefArrayType == PREF_ARRAY_SPEC)
  {
    for (i = SPEC_VALUE_PREF_START; i < SPEC_VALUE_PREF_END; i++)
    {
      if (i == nPrefNum)
        return nLocation;

      if (theBot->nSpecValues[i])
        nLocation++;
    }
  }

  return 0;
}
// If we have no information except what pref we want for which stakeholder, this will work.
// It is not as efficient as the one used in the stakeholder screen since it does all the calculations
// each time but it works just fine.
void PrintPreferenceBasedOnNumAndType(char *strPref, int nStakeholder, int nPrefNum, int nPrefArrayType)
{
  Stakeholder *pSH = &stakeholder[nStakeholder];
  RobotParameters *theBot = &pSH->RobotPreferences;

  int nQuestionNum = FindQuestionNumBasedOnPref(nStakeholder, nPrefArrayType);

  // We will figure out the question num based on what preference this is.
  int nPrefValue = 0;
  int nPreferenceType = 0;
  if (nPrefArrayType == PREF_ARRAY_GUN)
  {
    nPreferenceType = PREF_TYPE_ATTACK;
    nPrefValue = theBot->nGunValues[nPrefNum];
  }
  else if (nPrefArrayType == PREF_ARRAY_MELEE)
  {
    nPreferenceType = PREF_TYPE_ATTACK;
    nPrefValue = theBot->nMeleeValues[nPrefNum];
  } 
  else if (nPrefArrayType == PREF_ARRAY_ARMOR)
  {
    nPreferenceType = PREF_TYPE_DEFENSE;
    nPrefValue = theBot->nArmorValues[nPrefNum];
  }
  else if (nPrefArrayType == PREF_ARRAY_ACC)
  {
    nPreferenceType = PREF_TYPE_SYSTEM;
    nPrefValue = theBot->nAccValues[nPrefNum];
  }
  else if (nPrefArrayType == PREF_ARRAY_SPEC)
  {
    nPreferenceType = PREF_TYPE_SYSTEM;
    nPrefValue = theBot->nSpecValues[nPrefNum];
  }

  int nNumPrefs = CountPrefs(nStakeholder, nPreferenceType);
  int nQuestionState = pSH->GetQuestionState(nQuestionNum);
  int nLocation = FindPreferenceLocationWithinQuestion(nStakeholder, nPrefNum, nPrefArrayType);

  if (nQuestionState <= nLocation)
    sprintf(strPref, "---");
  else
    PrintPreferenceValue(strPref, nPrefValue, ((nQuestionState - nNumPrefs) > nLocation));
}

bool PrintPreferences(int nQuestionState, char *strAnswer, int nStakeholder, int nPreferenceType)
{
  RobotParameters *theBot = &stakeholder[nStakeholder].RobotPreferences;

  int nNumPrefs = CountPrefs(nStakeholder, nPreferenceType);

  int nItemsLeftToPrint = nQuestionState;

  // We only print, at max, the number of items we have
  // the extra questions are used in the NumSpecifics value
  if (nItemsLeftToPrint > nNumPrefs)
    nItemsLeftToPrint = nNumPrefs;

  // This number is the number of prefs that are the actual number, not
  // just the generic text, this counts DOWN and if it's above 0,
  // the specific is printed for that number
  int nNumSpecifics = nQuestionState - nNumPrefs;

  bool bRetv = false;
  if (nQuestionState == nNumPrefs*2)
    bRetv = true;

  int j = 0;
  if (nPreferenceType == PREF_TYPE_ATTACK)
  {
    for (j = 0; j < NUM_GUN_VALUES; j++)
      if (PrintOnePreference(theBot->nGunValues[j], GET_GUN_VALUE_FULL_TEXT(j), strAnswer, nItemsLeftToPrint, nNumSpecifics, nQuestionState) == false) 
        return bRetv;

    for (j = 0; j < NUM_MELEE_VALUES; j++)
      if (PrintOnePreference(theBot->nMeleeValues[j], GET_MELEE_VALUE_FULL_TEXT(j), strAnswer, nItemsLeftToPrint, nNumSpecifics, nQuestionState) == false) 
        return bRetv;
  } 
  else if (nPreferenceType == PREF_TYPE_DEFENSE)
  {
    for (j = 0; j < NUM_ARMOR_VALUES; j++)
      if (PrintOnePreference(theBot->nArmorValues[j], GET_ARMOR_VALUE_FULL_TEXT(j), strAnswer, nItemsLeftToPrint, nNumSpecifics, nQuestionState) == false) 
        return bRetv;
  }
  /*else if (nPreferenceType == PREF_TYPE_ACC)
  {
    for (j = 0; j < NUM_ACC_VALUES; j++)
      if (PrintOnePreference(theBot->nAccValues[j], GET_ACC_VALUE_FULL_TEXT(j), strAnswer, nItemsLeftToPrint, nNumSpecifics, nQuestionState) == false) 
        return bRetv;
  }*/
  else // Other
  {
    for (j = SPEC_VALUE_PREF_START; j < SPEC_VALUE_PREF_END; j++)
      if (PrintOnePreference(theBot->nSpecValues[j], GET_SPEC_VALUE_FULL_TEXT(j), strAnswer, nItemsLeftToPrint, nNumSpecifics, nQuestionState) == false) 
        return bRetv;

    for (j = 0; j < NUM_ACC_VALUES; j++)
      if (PrintOnePreference(theBot->nAccValues[j], GET_ACC_VALUE_FULL_TEXT(j), strAnswer, nItemsLeftToPrint, nNumSpecifics, nQuestionState) == false) 
        return bRetv;
  }

  return bRetv;
}

int Stakeholder::FindPMAnswer(int nQuestionNum, char *strAnswer)
{
  int nQuestionState = GetQuestionState(nQuestionNum);
  strAnswer[0] = 0;
  sprintf(strAnswer, "I want to see a system that has ");
  switch (nQuestionNum)
  {  
    // 0 is attacks
    case 0: return PrintPreferences(nQuestionState, strAnswer, STAKEHOLDER_PM, PREF_TYPE_ATTACK);

    // 1 is defenses
    case 1: return PrintPreferences(nQuestionState, strAnswer, STAKEHOLDER_PM, PREF_TYPE_DEFENSE);

    // 2 is system needs
    case 2: return PrintPreferences(nQuestionState, strAnswer, STAKEHOLDER_PM, PREF_TYPE_SYSTEM);

    // 3 is sustainability
    case 3: 
    {
      sprintf(strAnswer, "For sustainability, I would prefer these system models to be selected over others: ");

      char strTemp[256];
      char strModel[256];
      strTemp[0] = 0;
      strModel[0] = 0;

      System *pSys = 0;

      for (int i = 0; i < nQuestionState; i++)
      {
        int nSystemType = this->RobotPreferences.nSustainableSystemType[i];
        int nSystemModel = this->RobotPreferences.nSustainableSystemModel[i];

        pSys = g_pTheRobot->GetSystemByType(nSystemType);
   
        GetModelNameBySystem(nSystemType, nSystemModel, strModel);

        if (i == 0)
          sprintf(strTemp, "%s model for the %s", strModel, pSys->GetSystemTypeName());
        else if (i+1 == nQuestionState)
          sprintf(strTemp, ", and %s model for the %s", strModel, pSys->GetSystemTypeName());
        else 
          sprintf(strTemp, ", %s model for the %s", strModel, pSys->GetSystemTypeName());

        strcat(strAnswer, strTemp);
      }

      strcat(strAnswer, ".");

      if (nQuestionState < MAX_SUS_SYSTEMS)
        return false;

      return true;
    }
  };

  return false;
}


void Stakeholder::PrintTrainerExps(int nQuestionNum, char *strAnswer, int nTotalCount)
{
  int nCount = 0;

  // Now print out what we want
  sprintf(strAnswer, "I am comfortable training any system, but I have the most experience training ");
  int nQuestionState = GetQuestionState(nQuestionNum);
  for (int i = 0; i < NUM_EFFS; i++)
  {
    if (nCount >= nQuestionState)
      break;

    // If we have one, we increment count, otherwise we move on
    if (this->RobotPreferences.nTrainerExp[i])
      nCount++;
    else
      continue;
    
    if (nCount != nTotalCount || nTotalCount == 1)
      sprintf(strAnswer + strlen(strAnswer), " %s,", strTrainerExps[i]);
    else
      sprintf(strAnswer + strlen(strAnswer), " and %s", strTrainerExps[i]);
  }
}

int Stakeholder::FindTrainerAnswer(int nQuestionNum, char *strAnswer)
{
  int nTotalCount = 0;

  strAnswer[0] = 0;

  switch (nQuestionNum)
  {  
    // 0 is current fielded systems 
    case 0: 
    {
      // So he prefers either maneuver, firepower, defense, lightweight, or heavyweight

      // First total the number of efficiencies we have
      for (int i = 0; i < NUM_TRAINER_EXPS; i++)
      {
        if (this->RobotPreferences.nTrainerExp[i])
          nTotalCount++;
      }

      PrintTrainerExps(nQuestionNum, strAnswer, nTotalCount);

      if (GetQuestionState(nQuestionNum) >= nTotalCount)
      {
        strcat(strAnswer, ".");
        return true;
      }
      
      strcat(strAnswer, " and some other systems.");
      return false;
    }

    // 1 is preferences
    case 1: 
    {
      sprintf(strAnswer, "I would prefer we use the %s for pilot controls.",
        HumanInterfaces[this->RobotPreferences.nUserInterfaceType].strName);
      return true;
    }
  }
  return true;
}

int Stakeholder::FindDeveloperAnswer(int nQuestionNum, char *strAnswer)
{
  int nQuestionState = GetQuestionState(nQuestionNum);
  strAnswer[0] = 0;

  switch (nQuestionNum)
  {  
    // 0 is resource generation
    case 0:
    {
      sprintf(strAnswer, "If you increase the defense ratings of ");
      
      char strTemp[256];
      char strModel[256];
      strTemp[0] = 0;
      strModel[0] = 0;

      System *pSys = 0;

      for (int i = 0; i < nQuestionState; i++)
      {
        int nArmorValue = this->RobotPreferences.nArmorResourceGen[i];

        if (i == 0)
          sprintf(strTemp, "%s", GET_ARMOR_VALUE_TEXT(nArmorValue));
        else if (i+1 == nQuestionState)
          sprintf(strTemp, ", or %s", GET_ARMOR_VALUE_TEXT(nArmorValue));
        else 
          sprintf(strTemp, ", %s", GET_ARMOR_VALUE_TEXT(nArmorValue));

        strcat(strAnswer, strTemp);
      }

      if (nQuestionState == 1)
        strcat(strAnswer, " on one system by at least 4, we can market the new armor and generate additional resources for you. ");
      else
        strcat(strAnswer, " on one system by at least 4, we can market the new armor and generate additional resources for you.");

      if (nQuestionState < MAX_ARMOR_RES_GEN)
        return false;

      return true;
    }
    
    // 1 is exp
    case 1: 
    {
      sprintf(strAnswer, "We have experience integrating the interfaces of ");

      char strTemp[256];
      char strModel[256];
      strTemp[0] = 0;
      strModel[0] = 0;

      System *pSys = 0;

      for (int i = 0; i < nQuestionState; i++)
      {
        int nSystemType = this->RobotPreferences.nIntegrationExp[i];

        pSys = g_pTheRobot->GetSystemByType(nSystemType);

        if (i == 0)
          sprintf(strTemp, "%ss", pSys->GetSystemTypeName());
        else if (i+1 == nQuestionState)
          sprintf(strTemp, ", and %ss", pSys->GetSystemTypeName());
        else 
          sprintf(strTemp, ", %ss", pSys->GetSystemTypeName());

        strcat(strAnswer, strTemp);
      }

      if (nQuestionState == 1)
        strcat(strAnswer, ".  Spending money on interface development for this system will be "
                          "highly cost-effective.");
      else
        strcat(strAnswer, ".  Spending money on interface development for these systems will be "
                          "highly cost-effective.");

      if (nQuestionState < MAX_INTEGRATE_SYSTEMS)
        return false;

      return true;
    }
  }
  return true;
}

void Stakeholder::PrintEffDefs(int nQuestionNum, char *strAnswer, int nTotalCount, bool bEff)
{
  int nCount = 0;

  // Now print out what we want
  sprintf(strAnswer, "Our company is %s in", (bEff ? "efficient" : "deficient"));
  int nQuestionState = GetQuestionState(nQuestionNum);
  for (int i = 0; i < NUM_EFFS; i++)
  {
    if (nCount >= nQuestionState)
      break;

    // If we have one, we increment count, otherwise we move on
    if (bEff) {
      if (this->RobotPreferences.nEfficiencies[i])
        nCount++;
      else
        continue;
    } else {
      if (this->RobotPreferences.nDeficiencies[i])
        nCount++;
      else
        continue;
    }

    // So we know we have an efficiency, so we print it out.
    if ((nCount == 1) && (nQuestionState > 1))
      sprintf(strAnswer + strlen(strAnswer), " %s,", strEffs[i]);
    else  if (nCount == 1)
      sprintf(strAnswer + strlen(strAnswer), " %s", strEffs[i]);
    else if (nCount < nQuestionState)
      sprintf(strAnswer + strlen(strAnswer), " %s,", strEffs[i]);
    else if (nCount >= nQuestionState && nQuestionState < nTotalCount)
      sprintf(strAnswer + strlen(strAnswer), " %s,", strEffs[i]);
    else
      sprintf(strAnswer + strlen(strAnswer), " and %s", strEffs[i]);
  }
}

int Stakeholder::FindContractorAnswer(int nQuestionNum, char *strAnswer)
{
  int nTotalCount = 0;

  strAnswer[0] = 0;

  switch (nQuestionNum)
  {  
    // 0 is efficiencies 
    case 0: 
    {
      // First total the number of efficiencies we have
      for (int i = 0; i < NUM_EFFS; i++)
      {
        if (this->RobotPreferences.nEfficiencies[i])
          nTotalCount++;
      }

      PrintEffDefs(nQuestionNum, strAnswer, nTotalCount, true);

      if (GetQuestionState(nQuestionNum) >= nTotalCount)
      {
        strcat(strAnswer, ". We will be able to tackle these areas at less cost for greater gain.");
        return true;
      }
      
      strcat(strAnswer, " and some other areas. We will be able to tackle these areas at less cost for greater gain.");
      return false;
    }

    // 1 is deficiencies
    case 1: 
    {
      // First total the number of efficiencies we have
      for (int i = 0; i < NUM_EFFS; i++)
      {
        if (this->RobotPreferences.nDeficiencies[i])
          nTotalCount++;
      }

      PrintEffDefs(nQuestionNum, strAnswer, nTotalCount, false);

      if (GetQuestionState(nQuestionNum) >= nTotalCount)
      {
        strcat(strAnswer, ". These areas will induce higher than normal costs");
        return true;
      }
      
      strcat(strAnswer, " and some other areas. These areas will induce higher than normal costs.");
      return false;
    }
  }

  return true;
}

int Stakeholder::FindSenatorAnswer(int nQuestionNum, char *strAnswer)
{
  int nQuestionState = GetQuestionState(nQuestionNum);
  strAnswer[0] = 0;

  sprintf(strAnswer, "The public prefers a system that has ");
  switch (nQuestionNum)
  {  
    // 0 is attacks
    case 0: return PrintPreferences(nQuestionState, strAnswer, STAKEHOLDER_SENATOR, PREF_TYPE_ATTACK);

    // 1 is defenses
    case 1: return PrintPreferences(nQuestionState, strAnswer, STAKEHOLDER_SENATOR, PREF_TYPE_DEFENSE);
     
    // 2 is environmental impact
    case 2:
    { 
      char strTemp[256];
      strTemp[0] = 0;

      sprintf(strAnswer + strlen(strAnswer), "a maximum environmental impact rating of ");
      if (nQuestionState == 1)
      {
        sprintf(strTemp, "between %d and %d, but preferably less.", 
          this->RobotPreferences.nMaxEnvImpactBottom, this->RobotPreferences.nMaxEnvImpactTop);
        strcat(strAnswer, strTemp);
        return false;
      }

      sprintf(strTemp, "%d, preferably less.", this->RobotPreferences.nMaxEnvImpact);
      strcat(strAnswer, strTemp);
      return true;
    }
  };
  return true;
}

int Stakeholder::FindUserAnswer(int nQuestionNum, char *strAnswer)
{
  int nQuestionState = GetQuestionState(nQuestionNum);
  strAnswer[0] = 0;
  sprintf(strAnswer, "We need a system that has ");
  switch (nQuestionNum)
  {  
    // 0 is attacks
    case 0: return PrintPreferences(nQuestionState, strAnswer, STAKEHOLDER_USER, PREF_TYPE_ATTACK);

    // 1 is defenses
    case 1: return PrintPreferences(nQuestionState, strAnswer, STAKEHOLDER_USER, PREF_TYPE_DEFENSE);

    // 2 is system needs
    case 2: return PrintPreferences(nQuestionState, strAnswer, STAKEHOLDER_USER, PREF_TYPE_SYSTEM);

    // 3 is preferences
    case 3: 
    {
      sprintf(strAnswer, "I would prefer we use the %s for pilot controls.",
        HumanInterfaces[this->RobotPreferences.nUserInterfaceType].strName);
      return true;
    }
    // 4 is operating environment
    case 4:
    {
      int nTerrain = this->RobotPreferences.nTerrain;
      int nTemperature = this->RobotPreferences.nTemperature;

      sprintf(strAnswer, "The system will be operating in an environment that has %s terrain.  This means that "
                         "the Robot will need %s.  ", 
                          strTerrains[nTerrain], strTerrainReqs[nTerrain]);

      if (nQuestionState == 2)
      {
        char strTemp[256];
        strTemp[0] = 0;
        sprintf(strTemp, "Also, the temperature will be %s.  This means that "
                         "the Robot's heat sinks %s.", 
                          strTemperatures[nTemperature], strTemperatureReqs[nTemperature]);
        strcat(strAnswer, strTemp);
        this->RobotPreferences.bTemperatureRevealed = true;
        return true;
      }

      return false;
    };
  };
  return true;
}


// Find the answer to the question num of the current tier 
// Return is true if we're at the end of the tier, false if not
int Stakeholder::PrintAnswerToQuestion(int nQuestionNum, char *strAnswer)
{
  strAnswer[0] = 0;
  switch (this->nType)
  {
    case STAKEHOLDER_SUPERVISOR: 
    {
      return FindSupervisorAnswer(nQuestionNum, strAnswer);
    }
    case STAKEHOLDER_PM: 
    {
      return FindPMAnswer(nQuestionNum, strAnswer);
    }          
    case STAKEHOLDER_TRAINER: 
    {
      return FindTrainerAnswer(nQuestionNum, strAnswer);
    }     
    case STAKEHOLDER_DEVELOPER: 
    {
      return FindDeveloperAnswer(nQuestionNum, strAnswer);
    }   
    case STAKEHOLDER_CONTRACTOR: 
    {
      return FindContractorAnswer(nQuestionNum, strAnswer);
    }  
    case STAKEHOLDER_SENATOR: 
    {
      return FindSenatorAnswer(nQuestionNum, strAnswer);
    }     
    case STAKEHOLDER_USER: 
    {
      return FindUserAnswer(nQuestionNum, strAnswer);
    } 
  }

  return true;
}

// Deconstructor
Stakeholder::~Stakeholder() { /* Free memory; right now there's nothign to do here*/ }