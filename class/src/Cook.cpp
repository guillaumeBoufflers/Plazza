#include "../headers/Cook.hh"

static void *	runThread(void *a)
{
  ICook		*b = (ICook*)a;

  b->handleMe();
  return (NULL);
}

Cook::Cook(Mutex *processing, std::list<IPizzaTask *> *processingTask, Mutex*finished, std::list<IPizzaTask *> *finishedTask, std::string &name, float timeCookMult, bool &lol) : _processing(processing), _processingTask(processingTask), _finished(finished), _finishedTask(finishedTask), _name(name), _isAvailable(true), _timeCookMult(timeCookMult), _isRunnning(lol)
{
  std::cout << "[Debug] : Cook constructor ..." << std::endl;
  this->_cond = new varCond();
  pthread_create(&(this->_thread), NULL, runThread, this);
}

Cook::~Cook() {

}

void	Cook::setStatus(bool val)
{
  this->_isAvailable = val;
}

bool	Cook::getStatus() const
{
  return (this->_isAvailable);
}

std::string	Cook::getName() const
{
  return (this->_name);
}

void	*Cook::handleMe()
{
  pthread_mutex_t	*tmpMutex;
  pthread_cond_t	*tmpCond;

  tmpMutex = this->_cond->getMutex();
  tmpCond = this->_cond->getCond();
  while (1)
    {
      pthread_mutex_lock(tmpMutex);
      std::cout << "le cuisiniier est en état de repose" << std::endl;
      pthread_cond_wait(tmpCond, tmpMutex);
      std::cout << "le cuisiniier commence sa pizza" << std::endl;
      sleep(this->_task->getBakedTime() * this->_timeCookMult);
      this->_processing->lock();
      for(std::list<IPizzaTask *>::iterator it = this->_processingTask->begin(); it != this->_processingTask->end(); ++it)
      	{
      	  if (*it == this->_task)
	    {
	      this->_finished->lock();
	      this->_finishedTask->push_back((*it));
	      this->_finished->unlock();
	      this->_processingTask->erase(it);
	      break;
	    }
      	}
      std::cout << "taille restante de processing " << this->_processingTask->size() << std::endl;
      this->_processing->unlock();
      std::cout << "le cuisinier a fini sa pizza" << std::endl;
      this->_isAvailable = true;
      pthread_mutex_unlock(tmpMutex);
    }
  return (NULL);
}

void	Cook::setPizzaTask(IPizzaTask *val)
{
  this->_task = val;
}

pthread_cond_t *Cook::getCond()
{
  return (this->_cond->getCond());
}

pthread_mutex_t *Cook::getMutex()
{
  return (this->_cond->getMutex());
}
