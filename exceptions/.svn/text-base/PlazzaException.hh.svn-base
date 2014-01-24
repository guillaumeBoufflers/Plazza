#ifndef 				__PLAZZA_EXCEPTION_HH__
#define 				__PLAZZA_EXCEPTION_HH__

#include 				<exception>
#include 				<string>

class 					PlazzaException : public std::exception
{
private:
	const std::string 	_message;

public:
	virtual ~PlazzaException() throw() {};
	
	PlazzaException(const std::string &message) throw() : _message(message) {};

	virtual const char* what() const throw() {
		return this->_message.c_str();
	}

};

#endif
