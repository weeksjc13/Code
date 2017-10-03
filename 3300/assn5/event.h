#ifndef EVENT_H
#define EVENT_H

struct Event
{
  int start;
  int end;
  double time;
  
  Event(int s, int e, double t)
  {
    start = s;
    end = e;
    time = t;
  }
};

#endif
