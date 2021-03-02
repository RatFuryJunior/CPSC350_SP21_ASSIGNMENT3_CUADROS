using namespace std;

class Cell{
  public:
    Cell();
    Cell(bool status);
    ~Cell();
    bool getStatus();
    void setStatus(bool update);
    bool getNextStatus();
    void setNextStatus(bool update);
    
    void setOnePast(float thatRound);
    float getOnePast();
    void setTwoPast(float onePastRound);
    float getTwoPast();
  private:
    bool mStatus;
    bool mNextStatus;
    float mOnePast;
    float mTwoPast;
};
