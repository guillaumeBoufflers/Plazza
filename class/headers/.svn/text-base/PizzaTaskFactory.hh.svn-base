#ifndef			__PIZZATASKFACTORY_H__
#define			__PIZZATASKFACTORY_H__

#include		<map>
#include		<iostream>
#include		"PizzaTask.hh"
#include		"IPizzaTaskFactory.hh"

class PizzaTaskFactory : public IPizzaTaskFactory
{
public:
  PizzaTaskFactory();
  virtual	~PizzaTaskFactory();
  virtual	IPizzaTask *create(const std::string name, const std::string size, const int time);
private:
};

#endif
