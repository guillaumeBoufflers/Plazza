#include	"common.hh"

int		stringToInt(std::string val)
{
  int value;

  std::stringstream	ss(val);
  ss >> value;
  return (value);
}
