#include <time.h>
#include <chrono>

#ifndef CLASEELAPSEDTIME
#define CLASEELAPSEDTIME

using namespace std::chrono;

class E_time{
 protected:
  microseconds ms1;
  microseconds ms2;
    
 public:
  E_time(void);
  virtual ~E_time(void);
  virtual void start(void);
  virtual void stop(void);
  virtual microseconds elapsed(void);
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
  ms1 = duration_cast< microseconds >(
    system_clock::now().time_since_epoch()
);
}

void E_time::stop(void)
{
  ms2 = duration_cast< microseconds >(
    system_clock::now().time_since_epoch()
);
}

microseconds E_time::elapsed(void)
{
  return ms2 - ms1;
}

#endif
