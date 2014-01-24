#ifndef			__ICOOK_HH__
#define			__ICOOK_HH__

#include		"IPizzaTask.hh"

class ICook
{
public:
  virtual	~ICook() {};

  virtual	void	setStatus(bool val) = 0;
  virtual	bool	getStatus() const = 0;
  virtual	std::string	getName() const = 0;
  virtual	void	*handleMe()  = 0;
  virtual	void	setPizzaTask(IPizzaTask *) = 0;
  virtual pthread_cond_t	*getCond() = 0;
  virtual pthread_mutex_t	*getMutex() = 0;
private:

};

#endif
