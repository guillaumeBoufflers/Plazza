#include	"Recipe.hh"

Recipe::Recipe()
{
  this->_check["doe"] = doe;
  this->_check["tomato"] = tomato;
  this->_check["gruyere"] = gruyere;
  this->_check["ham"] = ham;
  this->_check["mushrooms"] = mushrooms;
  this->_check["eggplant"] = goatcheese;
  this->_check["goatcheese"] = goatcheese;
  this->_check["chieflove"] = chieflove;
  this->_check["steak"] = steak;
}

Recipe::~Recipe()
{

}

std::map<std::string, std::vector<ingredientTypes> >	Recipe::getPizzas() const
{
  return (this->_pizzas);
}

std::map<std::string, int>				Recipe::getBaked() const
{
  return (this->_baked);
}

int							Recipe::getBakedFromName(const std::string &name) const
{
  int		time;

  time = 0;
  for (std::map<std::string, int>::const_iterator it = this->_baked.begin(); it != this->_baked.end(); ++it)
    {
      if ((*it).first == name)
	time = (*it).second;
    }
  return (time);
}

void							Recipe::fillBaked(const std::string &name, const std::string &time)
{
  this->_baked[name] = stringToInt(time);
}

void							Recipe::checkIngredient(const std::vector<std::string> ingr) const
{
  bool		ishere;

  for (std::vector<std::string>::const_iterator it = ingr.begin(); it != ingr.end(); ++it)
    {
      ishere = false;
      for (std::map<std::string, ingredientTypes>::const_iterator it2 = this->_check.begin(); it2 != this->_check.end(); ++it2)
	{
	  if ((*it) == (*it2).first)
	    ishere = true;
	}
      if (ishere == false)
	{
      throw new PlazzaException("Ingredient ain't valid");
	}
    }
}

unsigned int						Recipe::checkKoma(const std::string &s) const
{
  unsigned int		j;

  j = 0;
  for(unsigned int i = 0; i < s.length(); i++)
    {
      if (s[i] == ',')
	j++;
    }
  return (j);
}

void							Recipe::checkDoubleIngr(std::vector<std::string> &ingrs, int numbline)
{
  int		i;

  (void)numbline;
  for (std::map<std::string, ingredientTypes>::const_iterator it2 = this->_check.begin(); it2 != this->_check.end(); ++it2)
    {
      i = 0;
      for (std::vector<std::string>::const_iterator it = ingrs.begin(); it != ingrs.end(); ++it)
	{
	  if ((*it2).first == (*it))
	    i++;
	}
      if (i > 1)
	{
      throw new PlazzaException("Impossible to put an ingredient more than one time on line");
	}
    }
}

void							Recipe::fillPizzas(const std::string &name, const std::string &ingredient, const int numbline)
{
  unsigned int			nbkoma;
  std::vector<ingredientTypes>	ingrt;
  std::vector<std::string>	ingrs;

  nbkoma = checkKoma(ingredient);
  ingrs = split(',', ingredient);
  checkDoubleIngr(ingrs, numbline);
  if (nbkoma != (ingrs.size() -1))
    {
      std::cout << "[Fatal-Error] : Syntax error on line  " << numbline << std::endl;
      throw new PlazzaException("Syntax error in configuration file.");
    }
  checkIngredient(ingrs);
  for (std::vector<std::string>::const_iterator it = ingrs.begin(); it != ingrs.end(); ++it)
    {
      for (std::map<std::string, ingredientTypes>::const_iterator it2 = this->_check.begin(); it2 != this->_check.end(); ++it2)
	{
	  if ((*it) == (*it2).first)
	    ingrt.push_back((*it2).second);
	}
    }
  this->_pizzas[name] = ingrt;
  std::cout << "[Info] : Adding pizza \"" << name << "\" ..." << std::endl;
}

void							Recipe::nameIntegrity(const std::string s, const int numbline) const
{
  (void) numbline;
  for(unsigned int i = 0; i < s.length(); i++)
    {
      if(s[i] < 'A' || (s[i] > 'Z' && s[i] < 'a') || s[i] > 'z')
	{
	  std::cout << "[Fatal-Error] : Pizza's name is incorrect on line  " << numbline << std::endl;
      throw new PlazzaException("Syntax error in configuration file.");
	}
    }
}

void							Recipe::isExistring(const std::string name, const int numbline) const
{
  for (std::map<std::string, std::vector<ingredientTypes> >::const_iterator it = this->_pizzas.begin(); it != this->_pizzas.end(); ++it)
    {
      if (name == (*it).first)
	{
	  std::cout << "[Fatal-Error] : Redefinition of pizza " << name << " on line " << numbline << std::endl;
      throw new PlazzaException("Syntax error in configuration file.");
	}
    }
}

void							Recipe::addPizza(std::string line, const int numbline)
{
  int				i;
  std::string			name;
  std::vector<std::string>	flds;

  i = 0;
  line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
  flds = split(':', line);
  for (std::vector<std::string>::iterator it = flds.begin(); it != flds.end(); ++it)
    {
      if (i == 0)
	{
	  if ((*it).size() == 0)
	    {
	      std::cout << "[Fatal-Error] : Pizza has no name on line " << numbline << std::endl;
          throw new PlazzaException("Syntax error in configuration file.");
	    }
	  nameIntegrity((*it), numbline);
	  isExistring((*it), numbline);
	  name = (*it);
	}
      else if (i == 1)
	{
	  if (isNumber((*it)) == false)
	    {
	      std::cout << "[Fatal-Error] : Time to bake a pizza should be a number on line " << numbline << std::endl;
          throw new PlazzaException("Syntax error in configuration file.");
	    }
	  fillBaked(name, (*it));
	}
      else
	fillPizzas(name, (*it), numbline);
      i++;
    }
}

void							Recipe::manageError(const std::list<std::string> content) const
{
  std::vector<std::string>	flds;
  int				i;

  i = 1;
  if (content.size() == 0)
    {
      throw new PlazzaException("File is empty.");
    }
  for (std::list<std::string>::const_iterator it = content.begin(); it != content.end(); ++it)
    {
      flds = split(':', (*it));
      if (count((*it), ':') != 2 || flds.size() != 3)
	{
	  std::cout << "[Fatal-Error] : Error on line " << i << std::endl;
      throw new PlazzaException("Syntax error in configuration file.");
	}
      i++;
    }
}

void							Recipe::openIt()
{
  std::list<std::string>	content;
  std::ifstream myfile("recipe", std::ios::in);
  std::string	line;
  int		i;

  i = 1;
  if (!myfile)
    {
      throw new PlazzaException("File ain't valid");
    }
  while(getline(myfile, line))
    content.push_back(line);
  manageError(content);
  for (std::list<std::string>::const_iterator it = content.begin(); it != content.end(); ++it)
    {
      this->addPizza((*it), i);
      i++;
    }
  myfile.close();
}
