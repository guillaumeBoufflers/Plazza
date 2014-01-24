#include "Ingredient.hh"

Ingredient::Ingredient(ingredientTypes type) : _type(type)
{

}

Ingredient::~Ingredient()
{

}

ingredientTypes		Ingredient::getType() const
{
  return (this->_type);
}

void			Ingredient::setType(const ingredientTypes type)
{
  this->_type = type;
}
