#include	"varCond.hh"

varCond::varCond()
{
  pthread_mutex_init(&this->_mutex, NULL);
  pthread_cond_init(&this->_cond, NULL);
}

varCond::~varCond()
{

}

pthread_cond_t	*varCond::getCond()
{
  return (&(this->_cond));
}

pthread_mutex_t	 *varCond::getMutex()
{
  return (&(this->_mutex));
}

void		varCond::setCond(const pthread_cond_t cond)
{
  this->_cond = cond;
}

void		varCond::setMutex(const pthread_mutex_t mutex)
{
  this->_mutex = mutex;
}
