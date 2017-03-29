
extern void DrawSelectedSystemParameters(int y);
extern void HandleSystemImprovementButtons(int wmId);
extern void HideAllSystemImprovementButtons();
extern void DetermineResCost(int nCode, int &nRes, char *strCostText = 0, bool bPrintCostText = false);

// Almost the same as EFF_X except this adds a few
// to the end to differentiate certain things
enum
{
  COST_CODE_FRAME,
  COST_CODE_HEAD,
  COST_CODE_TORSO,
  COST_CODE_ARM,
  COST_CODE_LEG,
  COST_CODE_EJECTION,
  COST_CODE_COOLING,
  COST_CODE_COMPUTER,
  COST_CODE_HUMAN_INTERFACE,
  COST_CODE_INTERFACES,
  COST_CODE_GUNS,
  COST_CODE_MELEE,
  COST_CODE_ARMOR,
  COST_CODE_SENSORS,
  COST_CODE_ARMOR_PLUS,
  NUM_COST_CODES
};
