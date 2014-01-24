#include "../headers/PizzaTaskFactory.hh"

PizzaTaskFactory::PizzaTaskFactory()
{

}

PizzaTaskFactory::~PizzaTaskFactory()
{

}

IPizzaTask *PizzaTaskFactory::create(const std::string name, const std::string size, const int time)
{
  return (new PizzaTask(name, size, time));
}
