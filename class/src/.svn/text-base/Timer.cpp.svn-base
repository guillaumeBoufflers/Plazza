#include	"Timer.hh"

Timer::Timer()
{
  gettimeofday(&this->_t1, NULL);
  gettimeofday(&this->_t2, NULL);
}

Timer::~Timer()
{

}

void	Timer::reset()
{
  gettimeofday(&this->_t1, NULL);
}

double	Timer::getElapsedTime()
{
  gettimeofday(&this->_t2, NULL);
  return ((this->_t2.tv_sec - this->_t1.tv_sec));
}
