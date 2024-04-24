#ifndef Queue_h
#define Queue_h
class Queue{
  public:
    Queue();
    void push(long val);
    float average();
    int getPeriodsArray(long*);
    long getPeriod();
    void increment(int*);
    void decrement(int*);
    bool checkSteadiness(float);
    bool nextIsThrowArm(Queue);
    long array[5];
    long periods[4];
    int start;
    int end;


  private:
    bool waitingFor2;
    int index;
    int size;
};
#endif
