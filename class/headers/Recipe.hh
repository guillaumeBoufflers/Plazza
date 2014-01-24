#ifndef		__RECIPE_HH__
#define		__RECIPE_HH__

#include	<iostream>
#include	<list>
#include	<vector>
#include	<map>
#include	<string>
#include	<fstream>
#include	<iomanip>
#include	<algorithm>
#include	<Ingredient.hh>
#include	<common.hh>

class		Recipe
{
private:
  std::map<std::string, ingredientTypes>		_check;
  std::map<std::string, std::vector<ingredientTypes> >	_pizzas;
  std::map<std::string, int>				_baked;
  int							_line;
public:
  Recipe();
  ~Recipe();
  std::map<std::string, std::vector<ingredientTypes> >	getPizzas() const;
  std::map<std::string, int>				getBaked() const;
  void							manageError(const std::list<std::string> content) const;
  void							checkIngredient(const std::vector<std::string> ingr) const;
  void							fillBaked(const std::string &name, const std::string &time);
  void							fillPizzas(const std::string &name, const std::string &ingredient, const int numbline);
  void							addPizza(std::string line, const int numbline);
  void							nameIntegrity(const std::string s, const int numbline) const;
  unsigned int						checkKoma(const std::string &s) const;
  void							isExistring(const std::string name, const int numbline) const;
  void							openIt();
  int							getBakedFromName(const std::string &name) const;
  void							checkDoubleIngr(std::vector<std::string> &ingrs, int numbline);
};

#endif
