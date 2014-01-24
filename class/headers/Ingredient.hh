#ifndef			__INGREDIENT_HH__
#define			__INGREDIENT_HH__

#include		"IIngredient.hh"

class Ingredient : public IIngredient
{
private:
  ingredientTypes	_type;

public:
  Ingredient(ingredientTypes type);
  virtual 	~Ingredient();
  virtual	ingredientTypes getType() const;
  virtual	void		setType(const ingredientTypes type);
};

#endif
