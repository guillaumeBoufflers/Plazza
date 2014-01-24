#include	"common.hh"

void						init(std::map<ingredientTypes, std::string> &check)
{
  check[doe] = "doe";
  check[tomato] = "tomato";
  check[gruyere] = "gruyere";
  check[ham] = "ham";
  check[mushrooms] = "mushrooms";
  check[eggplant] = "eggplant";
  check[goatcheese] = "goatcheese";
  check[chieflove] = "chieflove";
  check[steak] = "steak";
}

std::string					IngredientToString(ingredientTypes type)
{
  std::string					ingr;
  std::map<ingredientTypes, std::string>	check;

  init(check);
  for (std::map<ingredientTypes, std::string>::iterator it = check.begin(); it != check.end(); ++it)
    {
      if (type == (*it).first)
	ingr = (*it).second;
    }
  return (ingr);
}
