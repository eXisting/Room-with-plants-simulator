#ifndef _FRUITINGHOUSPLANT_HPP_
#define _FRUITINGHOUSPLANT_HPP_

#include "FloweringHousplant.hpp"

/*-----------------------------------------------------------------*/

class FruitingHouseplant
	: public FloweringHouseplant
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	FruitingHouseplant(
			std::string const & _name
		,	int _age
		,	int _wateringPeriod
		,	int _floweringPeriod
		,	int _needWater
		,	std::string const & _fName
		,	int _fruitingDays
	);

	~FruitingHouseplant() override
	{
	}

	/*-----------------------------------------------------------------*/
	
	void GiveWater() override;

	Houseplant::TYPE getType() const override;

	const std::string & getFruitName() const;

	const int getFruitingDays() const;

	const int getCurrentFruitingDays() const;
	
	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::string fruitName;
	const int fruitingDays;

	int currentFruitingDaysCount = 0;

	void tryFruiting();

	void makeFruit();

	/*-----------------------------------------------------------------*/

};

/*-----------------------------------------------------------------*/

inline const std::string &
FruitingHouseplant::getFruitName() const
{ 
	return fruitName; 
}

/*-----------------------------------------------------------------*/

inline const int 
FruitingHouseplant::getFruitingDays() const
{ 
	return fruitingDays; 
}

/*-----------------------------------------------------------------*/

inline const int 
FruitingHouseplant::getCurrentFruitingDays() const
{ 
	return currentFruitingDaysCount; 
}

/*-----------------------------------------------------------------*/

inline Houseplant::TYPE 
FruitingHouseplant::getType() const 
{ 
	return Houseplant::FRUIT; 
}


/*-----------------------------------------------------------------*/

#endif //_FRUITINGHOUSPLANT_HPP_