#include 	"Mutex.hh"

Mutex::Mutex() {
  if (pthread_mutex_init(&(this->_mutex), NULL) != 0)
    throw new std::exception();
}

Mutex::~Mutex() {
  if (pthread_mutex_destroy(&(this->_mutex)) != 0)
    throw new std::exception();
}

void 		Mutex::lock() {
  pthread_mutex_lock(&(this->_mutex));
}

void 		Mutex::unlock() {
  pthread_mutex_unlock(&(this->_mutex));
}
