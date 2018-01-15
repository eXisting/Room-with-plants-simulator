#ifndef _ARTICIALHOUSPLANT_HPP_
#define _ARTICIALHOUSPLANT_HPP_

#include "Houseplant.hpp"

/*-----------------------------------------------------------------*/

class ArtificialHouseplant
	: public Houseplant
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	ArtificialHouseplant(std::string const & _name, int _age, int _wateringPeriod = 0);
	
	~ArtificialHouseplant() override
	{
	}

	/*-----------------------------------------------------------------*/

	void DayGone() override 
	{ 
		CurrentDate::Instance().nextDay(); 
	};

	void GiveWater() override 
	{ 
		throw std::logic_error("Sorry, it's useless!"); 
	};

	Houseplant::TYPE getType() const override 
	{ 
		return Houseplant::ARTIFICIAL; 
	};
	
	/*-----------------------------------------------------------------*/
};

/*-----------------------------------------------------------------*/

inline
ArtificialHouseplant::ArtificialHouseplant(
		std::string const & _name
	,	int _age
	,	int _wateringPeriod
)
	:Houseplant(_name, _age, _wateringPeriod)
{
}

/*-----------------------------------------------------------------*/

#endif //_ARTICIALHOUSPLANT_HPP_