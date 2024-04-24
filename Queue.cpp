#include "Queue.h"
Queue::Queue(){
  size = 5;
  waitingFor2 = true;
  start = 0;
  end = -1;
  for(int i = 0; i<size;i++){
    array[i] = -1;
  }
}
//push value, and overwrite oldest value
void Queue::push(long val){
  increment(&end);
  array[end] = val;
  if(end == start && !waitingFor2){
    increment(&start);
  }
  if(waitingFor2 && end > start){
    waitingFor2 = false;
  }
}
//get the periods of for each time value in array
int Queue::getPeriodsArray(long* pa){
  index = start;
  int prevIndex = start;
  int i = 0;
  while(index != end){
    increment(&index);
    pa[i] = array[index] - array[prevIndex];
    prevIndex = index;
    i++;
  }
  return i;
}
//get the most resent period
long Queue::getPeriod(){
 int present = end;
  int past = end;
  decrement(&past);
  return array[present] - array[past];
}
//increment, wrap around if nessesary
void Queue::increment(int* x){
  (*x)++;
  if((*x) == size){
    (*x) = 0;
  }
}
//increment, wrap around if nessesary

void Queue::decrement(int* x){
  (*x)--;
  if((*x) < 0){
    (*x) = size - 1;
  }
}
//get the average of all current periods
float Queue::average(){
  int len = getPeriodsArray(periods);
  if(len == 0){
    return -1;
  }
  long total = 0;
  for(int i = 0; i < len; i++){
    total+= periods[i];
  }
  return float(total)/float(len);
}
//check if the periods are steady
bool Queue::checkSteadiness(float tolerance){
  int len = getPeriodsArray(periods);
  if(len < 4){
    return false;
  }
  float av = average();
  for(int i = 0; i < len; i++){
    if(periods[i] > av + tolerance || periods[i] < av - tolerance){
      return false;
    }
  }
  return true;
}
//check if the next side of the arm to cross the sensor is the frisbee side
bool Queue::nextIsThrowArm(Queue falling){
  bool finish = false;
  long differences[5];
  int i = 0;
  int index = 0;
  long total = 0;
  float average;
  int len = getPeriodsArray(periods);
  if(len < 4){
    return false;
  }
  if(start == falling.start && end == falling.end)
  {
    index = start;
    while(!finish){
      differences[i] = falling.array[index] - array[index];
      total += differences[i];
      i++;
      if(index == end){
        finish = true;
      }
      increment(&index);
    }
    if(i != 5){
      return false;
    }
    average = float(total)/float(i);
    if(differences[i-1] > average){
      return true;
    }
  }
  return false;
}
  