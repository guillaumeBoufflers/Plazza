#ifndef		__NAMEDPIPE_HH__
#define		__NAMEDPIPE_HH__

#include	<fcntl.h>
#include	<sys/stat.h>
#include	<sys/types.h>
#include	<unistd.h>
#include	<strings.h>
#include	<fstream>
#include	<iostream>
#include	<string>	

class NamedPipe
{
private:
  const std::string _name;
  const std::string	_filename;
  int		_fd;
public:
  NamedPipe(std::string name);
  ~NamedPipe();
  bool		read(std::string &msg) const;
  bool		write(const std::string &msg) const;
  void		destroy();
  std::string getName() const;
};

#endif
