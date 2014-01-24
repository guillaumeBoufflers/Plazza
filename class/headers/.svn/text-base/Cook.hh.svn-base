#ifndef				__COOK_HH__
#define				__COOK_HH__

#include			<pthread.h>
#include 			<iostream>
#include			<string>
#include			<list>
#include			"Mutex.hh"
#include			"ICook.hh"
#include			"varCond.hh"

class 				Cook : public ICook
{
public:
  Cook(Mutex *, std::list<IPizzaTask *>*, Mutex *, std::list<IPizzaTask *> *, std::string &, float timeCookMult, bool &);
  virtual ~Cook();
  virtual void		setStatus(bool val);
  virtual bool		getStatus() const;
  virtual std::string	getName() const;
  virtual void		*handleMe();
  virtual void		setPizzaTask(IPizzaTask *);
  virtual pthread_cond_t	*getCond();
  virtual pthread_mutex_t	*getMutex();
private:

  Mutex				*_processing;
  std::list<IPizzaTask *>	*_processingTask;
  Mutex				*_finished;
  std::list<IPizzaTask *>	*_finishedTask;

  std::string			_name;
  pthread_t 			_thread;
  varCond			*_cond;
  bool				_isAvailable;
  IPizzaTask			*_task;
  float				_timeCookMult;
  bool				&_isRunnning;
};
#endif
