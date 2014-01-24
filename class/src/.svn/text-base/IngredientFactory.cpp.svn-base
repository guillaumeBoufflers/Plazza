#include	"IngredientFactory.hh"

IngredientFactory::IngredientFactory()
{
  Init();
}

IngredientFactory::~IngredientFactory()
{

}

void		IngredientFactory::Init()
{
  this->creation[0] = &IngredientFactory::createDoe;
  this->creation[1] = &IngredientFactory::createTomato;
  this->creation[2] = &IngredientFactory::createGruyer;
  this->creation[3] = &IngredientFactory::createHam;
  this->creation[4] = &IngredientFactory::createMushrooms;
  this->creation[5] = &IngredientFactory::createEggplant;
  this->creation[6] = &IngredientFactory::createGoatcheese;
  this->creation[7] = &IngredientFactory::createChieflove;
  this->creation[8] = &IngredientFactory::createSteack;
}

IIngredient	*IngredientFactory::createDoe()
{
  return (new Ingredient(doe));
}

IIngredient	*IngredientFactory::createTomato()
{
  return (new Ingredient(tomato));
}

IIngredient	*IngredientFactory::createGruyer()
{
  return (new Ingredient(gruyere));
}

IIngredient	*IngredientFactory::createHam()
{
  return (new Ingredient(ham));
}

IIngredient	*IngredientFactory::createMushrooms()
{
  return (new Ingredient(mushrooms));
}

IIngredient	*IngredientFactory::createEggplant()
{
  return (new Ingredient(eggplant));
}

IIngredient	*IngredientFactory::createGoatcheese()
{
  return (new Ingredient(goatcheese));
}

IIngredient	*IngredientFactory::createChieflove()
{
  return (new Ingredient(chieflove));
}

IIngredient	*IngredientFactory::createSteack()
{
  return (new Ingredient(steak));
}

IIngredient	*IngredientFactory::create(ingredientTypes type)
{
  if (type >= 0 && type <= 8)
    return ((this->*creation[type])());
  return NULL;
}
