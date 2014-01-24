#ifndef			__IPIZZATASK_HH__
#define			__IPIZZATASK_HH__

#include		<string>

enum pizzaTypes
  {
    Regina = 1,
    Margarita = 2,
    Americaine = 4,
    Fantasia = 8
  };

enum pizzaSizes
  {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
  };

class IPizzaTask
{
public:
  virtual		~IPizzaTask(){};
  virtual std::string	getType() const = 0;
  virtual std::string	getSize() const = 0;
  virtual int		getBakedTime() const = 0;
  virtual void		setType(const std::string &type) = 0;
  virtual void		setSize(const std::string size) = 0;
  virtual void		setBakedTime(const int time) = 0;
  virtual bool		operator==(IPizzaTask const& pizza) const = 0;
private:

};

#endif
