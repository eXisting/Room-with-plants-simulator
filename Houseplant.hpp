#ifndef _HOUSEPLANT_HPP_
#define _HOUSEPLANT_HPP_

#include <string>

#include "CurrentDate.hpp"

/*-----------------------------------------------------------------*/

class Houseplant
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	enum TYPE { ARTIFICIAL, FLOWERING, FOLIAR, FRUIT, ABSTRACT };

	/*-----------------------------------------------------------------*/

	const std::string & getName() const;

	const int getAge() const;

	const int getPeriod() const;

	DateTime const & getLastWateringDate() const;

	virtual Houseplant::TYPE getType() const = 0;

	/*-----------------------------------------------------------------*/

	virtual ~Houseplant() = default;

	/*-----------------------------------------------------------------*/

protected:

	/*-----------------------------------------------------------------*/

	Houseplant(std::string const & _name, int _age, int _wateringPeriod);

	Houseplant(const Houseplant &) = delete;
	Houseplant & operator=(const Houseplant &) = delete;

	/*-----------------------------------------------------------------*/

	void changePeriod();

	void setWatering(DateTime const & _new);
	
	virtual void DayGone() = 0;

	virtual void GiveWater() = 0;

	/*-----------------------------------------------------------------*/

	int getDaysPassed() const;

	bool isOneDayDiff() const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	const std::string houseplantName;

	int age;

	int wateringPeriodDays;

	DateTime lastWateringDate;

	/*-----------------------------------------------------------------*/

};

/*-----------------------------------------------------------------*/

inline const std::string & 
Houseplant::getName() const
{ 
	return houseplantName;
}

/*-----------------------------------------------------------------*/

inline const int
Houseplant::getAge() const
{ 
	return age; 
}

/*-----------------------------------------------------------------*/

inline const int
Houseplant::getPeriod() const
{ 
	return wateringPeriodDays;
}

/*-----------------------------------------------------------------*/

inline DateTime const &
Houseplant::getLastWateringDate() const
{ 
	return lastWateringDate; 
}

/*-----------------------------------------------------------------*/

inline Houseplant::TYPE
Houseplant::getType() const
{ 
	return ABSTRACT; 
}

/*-----------------------------------------------------------------*/

inline void 
Houseplant::setWatering(DateTime const & _new)
{ 
	lastWateringDate = _new; 
}

/*-----------------------------------------------------------------*/

inline int 
Houseplant::getDaysPassed() const
{ 
	return CurrentDate::Instance().getCurrentDate() - getLastWateringDate(); 
}

/*-----------------------------------------------------------------*/

inline bool 
Houseplant::isOneDayDiff() const
{ 
	const int passed = getDaysPassed();
	const int period = getPeriod();

	return passed == period + 1 || passed == period - 1;
}

/*-----------------------------------------------------------------*/

#endif	//_HOUSEPLANT_HPP_