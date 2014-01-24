#ifndef			__KITCHEN_HH__
#define			__KITCHEN_HH__

#include		<list>
#include		<map>
#include		<vector>
#include		<algorithm>
#include		<sstream>
#include		<sys/time.h>
#include		"NamedPipe.hh"
#include		"Ingredient.hh"
#include		"IngredientFactory.hh"
#include		"ICook.hh"
#include		"Cook.hh"
#include		"PizzaTask.hh"
#include		"common.hh"
#include		"Mutex.hh"
#include		"Recipe.hh"
#include		"PizzaTaskFactory.hh"
#include		"common.hh"
#include		"Timer.hh"

class	varCond;
class	IIngredientFactory;

class Kitchen
{
public:
  Kitchen(const std::string &name, int, Recipe *, float cookingTimeMult, int respawn);
  ~Kitchen();

  void		run();
  void		initTabRequest();
  void		initStock();
  void		initMutex();
  void		checkMessage(std::string &);
  void		checkCommand(std::string &);
  void		checkStockOne(std::string &);
  bool		checkStock(std::string &);
  bool		checkNumber();
  bool		checkError(std::string &);
  void		handleCommand(std::string &, std::string &);
  void		handleRequest(std::string &);
  void		removeFromStock(IPizzaTask *);

  void		requestCookStatus(std::string &);
  void		requestSizeTask(std::string &);
  void		requestListTask(std::string &);
  void		requestIngredient(std::string &);
  void		requestPossible(std::string &);
  void		requestQuit(std::string &);
  void		quit(std::string &);

  void		getPizzaAndSize(std::string &, std::string &, std::string &);

  void		createCooks();
  void		*handleCookList();
  void		*reloadStock();
  void		clock();

private:
  std::string		_name;
  int			_nbCooks;
  Recipe		*_recipe;
  float			_cookingTimeMult;
  int                   _respawnFoodTime;
  std::list<ICook *>	_cooks;
  std::list<IPizzaTask *> _awaiting;
  std::list<IPizzaTask *> _processing;
  std::list<IPizzaTask *> _finished;
  std::map<IIngredient *, int>	_stock;
  std::map<std::string , void(Kitchen::*)(std::string &)>  _ptrRequest;
  Mutex			*_stockMutex;
  Mutex			*_cooksMutex;
  Mutex			*_processingTask;
  Mutex			*_awaitingTask;
  Mutex			*_finishedTask;
  NamedPipe		*_read;
  NamedPipe		*_write;
  IPizzaTaskFactory	*_creationP;
  IIngredientFactory	*_creationI;

  pthread_t		_handler;
  pthread_t		_stocker;
  pthread_t		_timer;
  varCond		*_condRel;

  bool			_isRunnningC;
  bool			_isRunnning;
  std::map<ingredientTypes, int> _need;
};

#endif
