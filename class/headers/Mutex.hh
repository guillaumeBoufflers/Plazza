#ifndef			__MUTEX_HH__
#define			__MUTEX_HH__

#include 		<pthread.h>
#include 		<exception>

class Mutex
{
private:
  pthread_mutex_t _mutex;

public:
  Mutex();
  ~Mutex();

  void 		lock();
  void		unlock();

};

#endif
