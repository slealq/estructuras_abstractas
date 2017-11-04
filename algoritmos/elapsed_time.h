#include <time.h>

#ifndef CLASEELAPSEDTIME
#define CLASEELAPSEDTIME

class E_time{
 protected:
  time_t start_value;
  time_t stop_value;

 public:
  E_time(void);
  virtual ~E_time(void);
  virtual void start(void);
  virtual void stop(void);
  virtual time_t elapsed(void);
};

// IMPLEMENTACION
E_time::E_time(void)
{
  
}

E_time::~E_time(void)
{

}

void E_time::start(void)
{
  start_value = time(0);
}

void E_time::stop(void)
{
  stop_value = time(0);
}

time_t E_time::elapsed(void)
{
  return start_value - stop_value;
}

#endif
