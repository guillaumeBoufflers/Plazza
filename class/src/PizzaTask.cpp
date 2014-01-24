#include "../headers/PizzaTask.hh"
#include	"iostream"

PizzaTask::PizzaTask(std::string type, std::string size, int time) : _type(type), _size(size), _bakedTime(time)
{
  std::cout << "la pizza " << type << " de taille :" << size << " avec un temps de cuisson de " << time << " a bien été construite" << std::endl;
}

PizzaTask::~PizzaTask()
{

}

std::string	PizzaTask::getType() const
{
  return (this->_type);
}

std::string	PizzaTask::getSize() const
{
  return (this->_size);
}

int		PizzaTask::getBakedTime() const
{
  return (this->_bakedTime);
}

void		PizzaTask::setType(const std::string &type)
{
  this->_type = type;
}

void		PizzaTask::setSize(const std::string size)
{
  this->_size = size;
}

void		PizzaTask::setBakedTime(const int time)
{
  this->_bakedTime = time;
}

bool		PizzaTask::operator==(IPizzaTask const& pizza) const
{
  if ((this->getType() == pizza.getType()) && (this->getSize() == pizza.getSize()) && (this->getBakedTime() == pizza.getBakedTime()))
    return (true);
  return (false);
}
