#ifndef		__VARCOND_HH_
#define		__VARCOND_HH__

#include	<stdio.h>
#include	<stdlib.h>
#include	<pthread.h>
#include	<unistd.h>

class		varCond
{
private:
  pthread_cond_t _cond;
  pthread_mutex_t _mutex;
public:
  varCond();
  ~varCond();
  void		setMutex(const pthread_mutex_t mutex);
  void		setCond(const pthread_cond_t cond);
  pthread_mutex_t	*getMutex();
  pthread_cond_t	*getCond();
};

#endif
