

// This file is used to record the different scores awarded at various times, and
// to keep track of the questions asked and when

#define SCORE_ID_FIELDED  NUM_STAKEHOLDERS

#define MAX_SCORE_RECORD  SCORE_ID_FIELDED+1

class ScoreRecord
{
  public:
  
    ScoreRecord()
    {
      Clear();
    };
    
    // ID is the stakeholder num or SCORE_ID_FIELDED
    void RecordScoreInfo(int nStakeholder, int nApprove, int nScore)
    {
      SetID(nStakeholder);
      SetApprovalGiven(nApprove);
      SetScoreAwarded(nScore);
    };
    
    void AddScoreInfo(int nStakeholder, int nApprove, int nScore)
    {
      SetID(nStakeholder);
      nApprovalGiven += nApprove;
      nScoreAwarded += nScore;
    };
    
    void SetID(int nNum) {nID = nNum;};
    void SetApprovalGiven(int nNum) {nApprovalGiven = nNum;};
    void SetScoreAwarded(int nNum) {nScoreAwarded = nNum;};
    
    int GetID() {return nID;};
    int GetApprovalGiven() {return nApprovalGiven;};
    int GetScoreAwarded() {return nScoreAwarded;};
    
    void Clear()
    {
      nID = -1;
      nApprovalGiven = 0;
      nScoreAwarded = 0;
    }
    
  private:
    int nID;
    
    int nApprovalGiven;
    int nScoreAwarded;
};

class ScoreRecordList
{
  public:
    
    ScoreRecordList() {};
    
    ScoreRecord *GetRecord(int nStakeholder) { return &records[nStakeholder]; };
    
  private:
    ScoreRecord records[MAX_SCORE_RECORD];
};