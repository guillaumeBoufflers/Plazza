#ifndef			__IINGREDIENT_HH__
#define			__IINGREDIENT_HH__

enum ingredientTypes
  {
    doe = 0,
    tomato = 1,
    gruyere = 2,
    ham = 3,
    mushrooms = 4,
    eggplant = 5,
    goatcheese = 6,
    chieflove = 7,
    steak = 8,
  };

class IIngredient
{
public:
  virtual 	~IIngredient(){};
  virtual	ingredientTypes getType() const = 0;
  virtual	void		setType(ingredientTypes type) = 0;
};

#endif
