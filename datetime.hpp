#ifndef _DATETIME_HPP_
#define _DATETIME_HPP_

/*****************************************************************************/

#include <iostream>

/*****************************************************************************/



class DateTime
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	DateTime();
	DateTime(int _year, int _day);
	// Format: YYYY/MM/DD

	int getYear() const;
	int getDay() const;
	bool isLeapYear() const;

	void nextDay();

	void dateReset() { m_day = 1; m_year = 2016; };

	int operator-(DateTime const & _q) const;

	bool operator == (DateTime _d) const;
	bool operator != (DateTime _d) const;
	bool operator < (DateTime _d) const;
	bool operator <= (DateTime _d) const;
	bool operator > (DateTime _d) const;
	bool operator >= (DateTime _d) const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	bool isValid() const;

	/*-----------------------------------------------------------------*/

	int m_year, m_day;

	/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

std::ostream & operator << (std::ostream & o, DateTime d);



/*****************************************************************************/

#endif // _DATETIME_HPP_