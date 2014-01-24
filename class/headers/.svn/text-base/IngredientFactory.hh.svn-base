#ifndef			__INGREDIENTFACTORY_H__
#define			__INGREDIENTFACTORY_H__

#include		<map>
#include		<iostream>
#include		"IIngredientFactory.hh"

class IngredientFactory : public IIngredientFactory
{
public:
  IngredientFactory();
  virtual	~IngredientFactory();
  virtual	void Init();
  virtual	IIngredient *create(ingredientTypes type);
private:
  IIngredient	*createDoe();
  IIngredient	*createTomato();
  IIngredient	*createGruyer();
  IIngredient	*createHam();
  IIngredient	*createMushrooms();
  IIngredient	*createEggplant();
  IIngredient	*createGoatcheese();
  IIngredient	*createChieflove();
  IIngredient *createSteack();
  IIngredient	*(IngredientFactory::*creation[9])();
};

#endif
