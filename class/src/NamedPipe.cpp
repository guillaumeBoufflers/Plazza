#include "../headers/NamedPipe.hh"

NamedPipe::NamedPipe(const std::string name) : _name(name), _filename("/tmp/" + name) {
  // std::ifstream file(this->_name.c_str(), std::ios::in);
  // if (!file)
    mkfifo(this->_filename.c_str(), 0644);
  // else
  //   file.close();
}

NamedPipe::~NamedPipe() {
}

bool		NamedPipe::read(std::string &msg) const {
  std::ifstream myfile(this->_filename.data(), std::ios::in);

  getline(myfile, msg);
  myfile.close();
  return (true);
}

void    NamedPipe::destroy() {
  unlink(this->_filename.c_str());
}

bool		NamedPipe::write(const std::string &msg) const {
  std::ofstream	myfile;

  myfile.open(this->_filename.data());
  myfile << msg;
  myfile << "\n";
  myfile.close();
  return (true);
}

std::string NamedPipe::getName() const {
  return (this->_name);
}
