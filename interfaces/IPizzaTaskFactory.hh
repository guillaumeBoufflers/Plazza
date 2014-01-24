#ifndef			__IPIZZATASKFACTORY_HH__
#define			__IPIZZATASKFACTORY_HH__

#include		<string>
#include		"PizzaTask.hh"

class IPizzaTaskFactory
{
public:
  virtual	~IPizzaTaskFactory(){};
  virtual	IPizzaTask *create(const std::string name, const std::string size, const int time) = 0;
};

#endif
