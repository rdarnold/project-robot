
void SetupSystemRestrictions();
bool IsModelRestrictedByCurrentRobot(int nCheckThisSystemType, int nCheckThisModel, char *strRes);
bool IsAccRestrictedByCurrentRobot(int nCheckThisSystemType, int nCheckThisItem, char *strRes);
bool IsGunRestrictedByCurrentRobot(int nCheckThisSystemType, int nCheckThisItem, char *strRes);
bool IsMeleeRestrictedByCurrentRobot(int nCheckThisSystemType, int nCheckThisItem, char *strRes);
bool IsArmorRestrictedByCurrentRobot(int nCheckThisSystemType, int nCheckThisItem, char *strRes);