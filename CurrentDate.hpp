#ifndef _CURRENTDATE_HPP_
#define _CURRENTDATE_HPP_

#include "datetime.hpp"

/*-----------------------------------------------------------------*/

// Singleton pattern for managing the day cycle of a room
class CurrentDate
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	static CurrentDate & Instance()
	{
		static CurrentDate singleton;
		return singleton;
	}

	/*-----------------------------------------------------------------*/

	void nextDay() 
	{ 
		current.nextDay(); 
	}

	void resetDay() 
	{ 
		current.dateReset(); 
	}

	DateTime & getCurrentDate() 
	{ 
		return current; 
	}

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	DateTime current;

	/*-----------------------------------------------------------------*/
	
	CurrentDate() {};
	~CurrentDate() {};

	CurrentDate(const CurrentDate&) = delete;
	CurrentDate& operator=(const CurrentDate&) = delete;

	/*-----------------------------------------------------------------*/

};

/*-----------------------------------------------------------------*/

#endif // !_CURRENTDATE_HPP_
