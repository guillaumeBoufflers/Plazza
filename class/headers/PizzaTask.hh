#ifndef			__PIZZATASK_HH__
#define			__PIZZATASK_HH__

#include		"IPizzaTask.hh"

class PizzaTask : public IPizzaTask
{
public:
  PizzaTask(std::string type, std::string size, int time);
  virtual ~PizzaTask();
  virtual std::string	getType() const;
  virtual std::string	getSize() const;
  virtual int		getBakedTime() const;
  virtual void		setType(const std::string &type);
  virtual void		setSize(const std::string size);
  virtual void		setBakedTime(const int time);
  virtual bool		operator==(IPizzaTask const& pizza) const;
private:
  std::string				_type;
  std::string				_size;
  int					_bakedTime;
};

#endif
