#ifndef _FOLIARHOUSPLANT_HPP_
#define _FOLIARHOUSPLANT_HPP_

#include "Houseplant.hpp"

/*-----------------------------------------------------------------*/

struct Spliter;

class FoliarHouseplant
	: public Houseplant
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	FoliarHouseplant(
		std::string const & _name
		,	int _age
		,	int _wateringPeriod
		,	int _height
		,	Spliter & _container
	);

	~FoliarHouseplant() override
	{
	}

	/*-----------------------------------------------------------------*/

	const int getHeight() const;

	void GiveWater() override;

	void DayGone() override;
	
	Houseplant::TYPE getType() const override;
	
	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	int height;

	Spliter & spliter;

	/*-----------------------------------------------------------------*/

};

/*-----------------------------------------------------------------*/

inline const int 
FoliarHouseplant::getHeight() const
{
	return height;
}

inline void
FoliarHouseplant::DayGone()
{
	CurrentDate::Instance().nextDay();
}


inline Houseplant::TYPE
FoliarHouseplant::getType() const
{
	return Houseplant::FOLIAR;
}


#endif //_FOLIARHOUSPLANT_HPP_