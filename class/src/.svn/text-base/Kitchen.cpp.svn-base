#include "../headers/Kitchen.hh"

static void *	runThread(void *a)
{
  Kitchen		*b = (Kitchen*)a;

  b->handleCookList();
  return (NULL);
}

static void *	runStock(void *a)
{
  Kitchen		*b = (Kitchen*)a;

  b->reloadStock();
  return (NULL);
}

static void *	runTimer(void *a)
{
  Kitchen		*b = (Kitchen*)a;

  b->clock();
  return (NULL);
}

Kitchen::Kitchen(const std::string &name, int nbCooks, Recipe *recipe, float cookingTimeMult, int respawn)  : _name(name), _nbCooks(nbCooks), _recipe(recipe), _cookingTimeMult(cookingTimeMult), _respawnFoodTime(respawn), _isRunnningC(true), _isRunnning(true)
{
  this->_creationP = new PizzaTaskFactory();
  this->_creationI = new IngredientFactory();
  this->_read = new NamedPipe(name + "-r");
  this->_write = new NamedPipe(name + "-w");
  this->_condRel = new varCond();
  this->initMutex();
  this->initTabRequest();
  this->initStock();
  this->createCooks();
  if (pthread_create(&(this->_handler), NULL, runThread, this) != 0)
    throw new PlazzaException("thread error\n");
  if (pthread_create(&(this->_stocker), NULL, runStock, this) != 0)
    throw new PlazzaException("thread error\n");
  if (pthread_create(&(this->_timer), NULL, runTimer, this) != 0)
    throw new PlazzaException("thread error\n");
}

void	Kitchen::clock()
{
  Timer	t;

  while (t.getElapsedTime() < 5)
    {
      if (this->_processing.size() > 0)
	t.reset();
    }
  this->_isRunnningC = false;
}

void    Kitchen::createCooks()
{
  int   i(0);
  std::string	name;

  while (i < this->_nbCooks)
    {
      name = intToString(i);
      this->_cooks.push_back(new Cook(this->_processingTask, &(this->_processing), this->_finishedTask, &(this->_finished), name, this->_cookingTimeMult, this->_isRunnningC));
      i++;
    }
}

void		Kitchen::initStock()
{
  this->_stockMutex->lock();
  this->_stock[this->_creationI->create(doe)] = 5;
  this->_stock[this->_creationI->create(tomato)] = 5;
  this->_stock[this->_creationI->create(gruyere)] = 5;
  this->_stock[this->_creationI->create(ham)] = 5;
  this->_stock[this->_creationI->create(mushrooms)] = 5;
  this->_stock[this->_creationI->create(eggplant)] = 5;
  this->_stock[this->_creationI->create(goatcheese)] = 5;
  this->_stock[this->_creationI->create(chieflove)] = 5;
  this->_stock[this->_creationI->create(steak)] = 5;
  this->_stockMutex->unlock();
}

void		Kitchen::initTabRequest()
{
  std::map<std::string, std::vector<ingredientTypes> > tmp = this->_recipe->getPizzas();
  std::string pizza;
  this->_ptrRequest["cookStatus"] = &Kitchen::requestCookStatus;
  this->_ptrRequest["nbProcessing"] = &Kitchen::requestSizeTask;
  this->_ptrRequest["nbAwaiting"] = &Kitchen::requestSizeTask;
  this->_ptrRequest["nbFinished"] = &Kitchen::requestSizeTask;
  this->_ptrRequest["awaitingList"] = &Kitchen::requestListTask;
  this->_ptrRequest["processingList"] = &Kitchen::requestListTask;
  this->_ptrRequest["finishedList"] = &Kitchen::requestListTask;
  this->_ptrRequest["nbIngredients"] = &Kitchen::requestIngredient;
  this->_ptrRequest["rquit"] = &Kitchen::requestQuit;
  this->_ptrRequest["quit"] = &Kitchen::quit;
  for (std::map<std::string, std::vector<ingredientTypes> >::const_iterator it2 = tmp.begin(); it2 != tmp.end(); ++it2)
    {
      pizza = (*it2).first;
      this->_ptrRequest[pizza] = &Kitchen::requestPossible;
    }
}

void		Kitchen::initMutex()
{
  this->_stockMutex = new Mutex();
  this->_cooksMutex = new Mutex();
  this->_processingTask = new Mutex();
  this->_awaitingTask = new Mutex();
  this->_finishedTask = new Mutex();
}

void	*Kitchen::reloadStock()
{
  struct timeval now;
  struct timespec timeout;
  struct timezone lol;
  pthread_mutex_t	*tmpM;
  pthread_cond_t	*tmpC;

  tmpM = this->_condRel->getMutex();
  tmpC = this->_condRel->getCond();
  while (1 && this->_isRunnningC)
    {
      pthread_mutex_lock(tmpM);
      gettimeofday(&now, &lol);
      timeout.tv_sec = now.tv_sec + (this->_respawnFoodTime / 1000);
      timeout.tv_nsec = now.tv_usec * 1000;
      pthread_cond_timedwait(tmpC, tmpM, &timeout);
      pthread_mutex_unlock(tmpM);
      this->_stockMutex->lock();
      for (std::map<IIngredient *, int>::iterator it = this->_stock.begin(); it != this->_stock.end(); ++it)
	{
	  (*it).second += 1;
	}

      this->_stockMutex->unlock();
    }
  return (NULL);
}

void	*Kitchen::handleCookList()
{
  IPizzaTask	*pizza;
  ICook		*cook;
  pthread_cond_t	*tmp;
  pthread_mutex_t	*tmp1;

  while (1)
    {
      this->_awaitingTask->lock();
      if (this->_awaiting.size() >= 1)
	{
	  this->_cooksMutex->lock();

	    for(std::list<ICook *>::iterator it = this->_cooks.begin(); it != this->_cooks.end(); ++it)
	    {
	    cook = (*it);
	    if (cook->getStatus())
	    {
	    tmp = cook->getCond();
	    tmp1 = cook->getMutex();
	    cook->setStatus(false);
	    pizza = this->_awaiting.back();
	    this->_awaiting.pop_back();
	    this->_processingTask->lock();
	    this->_processing.push_front(pizza);
	    this->_processingTask->unlock();
	    this->_stockMutex->lock();
	    this->removeFromStock(pizza);
	    this->_stockMutex->unlock();
	    cook->setPizzaTask(pizza);
	    pthread_mutex_lock(tmp1);
	    pthread_cond_signal(tmp);
	    pthread_mutex_unlock(tmp1);
	    break ;
	    }
	    }
	    this->_cooksMutex->unlock();
	}
      this->_awaitingTask->unlock();
    }
  return (NULL);
}

Kitchen::~Kitchen()
{

}

void		Kitchen::quit(std::string &str)
{
  str = str;
  pthread_cancel(this->_handler);
  this->_isRunnning = false;
}

void		Kitchen::requestQuit(std::string &str)
{
  str = str;
  if (this->_isRunnningC)
    this->_write->write("RUN");
  this->_write->write("QUIT");
}

void		Kitchen::requestPossible(std::string &str)
{
  str = str.substr(3);
  if (checkStock(str))
    this->_write->write(PIZZA_OK);
  else
    this->_write->write(PIZZA_NO);
}

void		Kitchen::requestIngredient(std::string &str)
{
  std::string	resultRequest, tmp;

  str = str.substr(2);
  this->_stockMutex->lock();
  for (std::map<IIngredient *, int>::iterator it = this->_stock.begin(); it != this->_stock.end(); ++it)
    {
      tmp = intToString((*it).second);
      resultRequest.append(IngredientToString((*it).first->getType()) + " " + tmp + ";");
    }
  if (resultRequest.empty())
    resultRequest.append(" ");
  this->_stockMutex->unlock();
  this->_write->write(resultRequest);
}

void		Kitchen::requestCookStatus(std::string &str)
{
  std::string	resultRequest;

  str = str;
  this->_cooksMutex->lock();
  for(std::list<ICook *>::const_iterator it = this->_cooks.begin(); it != this->_cooks.end(); ++it)
    {
      resultRequest.append((*it)->getName() + " ");
      if ((*it)->getStatus())
	resultRequest.append(AVAILABLE);
      else
	resultRequest.append(UNAVAILABLE);
      resultRequest.append(";");
    }
  if (resultRequest.empty())
    resultRequest.append(" ");
  this->_cooksMutex->unlock();
  this->_write->write(resultRequest);
}

void		Kitchen::requestSizeTask(std::string &str)
{
  int		a = 0;
  std::string	resultRequest;
  std::stringstream convert;

  this->_processingTask->lock();
  if (str == "nbProcessing")
    a = this->_processing.size();
  else if (str == "nbAwaiting")
    a = this->_awaiting.size();
  else
    a = this->_finished.size();
  this->_processingTask->unlock();
  convert << a;
  resultRequest = convert.str();
  this->_write->write(resultRequest);
}

void		Kitchen::requestListTask(std::string &str)
{
  std::string	resultRequest;

  if (str == "awaitingList")
    {
      this->_awaitingTask->lock();
       for (std::list<IPizzaTask *>::const_iterator it = this->_awaiting.begin(); it != this->_awaiting.end(); ++it)
	 {
	   resultRequest.append((*it)->getType());
	   resultRequest.append(" ");
	   resultRequest.append((*it)->getSize());
	   resultRequest.append(";");
	 }
       this->_awaitingTask->unlock();
    }
  else if (str == "processingList")
    {
      this->_processingTask->lock();
       for (std::list<IPizzaTask *>::const_iterator it = this->_processing.begin(); it != this->_processing.end(); ++it)
	 {
	   resultRequest.append((*it)->getType());
	   resultRequest.append(" ");
	   resultRequest.append((*it)->getSize());
	   resultRequest.append(";");
	 }
       this->_processingTask->unlock();
    }
  else
    {
      this->_finishedTask->lock();
      for (std::list<IPizzaTask *>::const_iterator it = this->_finished.begin(); it != this->_finished.end(); ++it)
	{
	   resultRequest.append((*it)->getType());
	   resultRequest.append(" ");
	   resultRequest.append((*it)->getSize());
	   resultRequest.append(";");
	}
      this->_finishedTask->unlock();
    }
  if (resultRequest.empty())
    resultRequest.append(" ");
  this->_write->write(resultRequest);
}

void		Kitchen::handleRequest(std::string &str)
{
  void(Kitchen::*ptr)(std::string &);
  std::string	request;

  request = str.substr(3);
  ptr = this->_ptrRequest[request];
  (this->*ptr)(request);
}

void		Kitchen::removeFromStock(IPizzaTask *pizza)
{
  std::vector<ingredientTypes> need = this->_recipe->getPizzas()[pizza->getType()];

  for (std::vector<ingredientTypes>::const_iterator it = need.begin(); it != need.end(); ++it)
    {
      for (std::map<IIngredient *, int>::iterator it2 = this->_stock.begin(); it2 != this->_stock.end(); ++it2)
	{
	  if ((it2->first)->getType() == (*it))
	    {
	      (*it2).second -= 1;
	      break ;
	    }
	}
    }
}

bool		Kitchen::checkStock(std::string &pizza)
{
  std::string	tmp;
  if (!checkNumber())
    return (false);
  this->_need[doe] = 0;
  this->_need[tomato] = 0;
  this->_need[gruyere] = 0;
  this->_need[ham] = 0;
  this->_need[mushrooms] = 0;
  this->_need[eggplant] = 0;
  this->_need[goatcheese] = 0;
  this->_need[chieflove] = 0;
  this->_need[steak] = 0;
  checkStockOne(pizza);
  for (std::list<IPizzaTask *>::const_iterator it = this->_awaiting.begin(); it != this->_awaiting.end(); ++it)
    {
      tmp = (*it)->getType();
      checkStockOne(tmp);
    }
  this->_stockMutex->lock();
  for (std::map<IIngredient *, int>::const_iterator it2 = this->_stock.begin(); it2 != this->_stock.end() ; ++it2)
    {
      if (this->_need[(*it2).first->getType()] > (*it2).second)
	{
	  this->_stockMutex->unlock();
	  return (false);
	}
    }
  this->_stockMutex->unlock();
  return (true);
}

void		Kitchen::checkStockOne(std::string &pizza)
{
  std::vector<ingredientTypes>	need;
  std::map<std::string, std::vector<ingredientTypes> > tmp = this->_recipe->getPizzas();

  need = tmp[pizza];
  for (std::vector<ingredientTypes>::const_iterator it = need.begin(); it != need.end(); ++it)
    {
      this->_need[(*it)] += 1;
    }
}

bool		Kitchen::checkError(std::string &str)
{
  std::string	tmp(str);
  std::string	tmp2("");
  int	      	n = 0;

  tmp2 = tmp.substr(0, 3);
  if (tmp2 != "c: " && tmp2 != "r: ")
    return (false);
  tmp.erase(0, 3);
  n = std::count(tmp.begin(), tmp.end(), ' ');
  if (n > 1)
    return (false);
  return (true);
}

bool		Kitchen::checkNumber()
{
  this->_awaitingTask->lock();
  this->_processingTask->lock();
  size_t	a = 0;

  a = this->_awaiting.size() + this->_processing.size();
  if ( a >= ((size_t)this->_nbCooks * 2))
    {
      this->_awaitingTask->unlock();
      this->_processingTask->unlock();
      return (false);
    }
  this->_awaitingTask->unlock();
  this->_processingTask->unlock();
  return (true);
}

void		Kitchen::handleCommand(std::string &pizza, std::string &size)
{
  int		time;

  this->_awaitingTask->lock();
  time = this->_recipe->getBakedFromName(pizza);
  this->_awaiting.push_front(this->_creationP->create(pizza, size, time));
  this->_awaitingTask->unlock();
}

void		Kitchen::getPizzaAndSize(std::string &str, std::string &pizza, std::string &size)
{
  std::string	tmp(str);
  size_t	a = 0;

  tmp.erase(0, 3);
  a = tmp.find(' ');
  pizza = tmp.substr(0, a);
  size = tmp.substr(pizza.size() + 1);
}

void		Kitchen::checkCommand(std::string &str)
{
  std::string	pizza;
  std::string	size;

  getPizzaAndSize(str, pizza, size);
  if (this->checkStock(pizza))
    {
      this->_write->write(PIZZA_OK);
      return (this->handleCommand(pizza, size));
    }
  else
    {
      this->_write->write(PIZZA_NO);
    }
}

void		Kitchen::checkMessage(std::string &str)
{
  size_t	a = std::string::npos;

  if (checkError(str) == false)
    {
      this->_write->write(ERROR);
      return ;
    }
  a = str.find("c:");
  if (a != std::string::npos)
    return (this->checkCommand(str));
  return (this->handleRequest(str));
}

void		Kitchen::run()
{
  std::string	tmp;

  tmp.clear();
  while (this->_read->read(tmp) && this->_isRunnning)
    {
      if (tmp != "")
	{
	  this->checkMessage(tmp);
	  tmp.clear();
	}
    }
  exit(0);
}
