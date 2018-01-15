#include "datetime.hpp"

#include <ctime>
#include <cassert>
#include <cstdio>
#include <stdexcept>

/*****************************************************************************/

DateTime::DateTime()
{
	// consider start day is the first day of 2016
	m_year = 2016;
	m_day = 1;
}


/*****************************************************************************/


DateTime::DateTime(int _year, int _day)
	: m_year(_year), m_day(_day)
{
	if (!isValid())
		throw std::logic_error("InvalidDateTime");
}

/*****************************************************************************/


int
DateTime::getYear() const
{
	return m_year;
}


/*****************************************************************************/


int
DateTime::getDay() const
{
	return m_day;
}


/*****************************************************************************/


bool
DateTime::isLeapYear() const
{
	if (m_year % 4 != 0)
		return false;

	else if (m_year % 100 == 0)
		return (m_year % 400 == 0);

	return true;
}

void DateTime::nextDay()
{
	int cur_date = m_day + 1;
	if (cur_date >= 365)
	{
		m_day = cur_date - m_day;
		if (m_day < 365)
			++m_year;
		else
			m_year += m_day - 365;
	}
	else
		++m_day;
}

/*****************************************************************************/


int DateTime::operator-(DateTime const & _q) const
{
	int years = 0;
	if (_q.m_year != m_year)
	{
		years = m_year - _q.m_year;
		return years * abs(abs(m_day - _q.m_day) - 364);
	}

	return m_day - _q.m_day;
}

bool
DateTime::operator == (DateTime d) const
{
	return m_year == d.getYear()
		&& m_day == d.getDay();
}


/*****************************************************************************/


bool
DateTime::operator != (DateTime d) const
{
	return !(*this == d);
}


/*****************************************************************************/


bool
DateTime::operator < (DateTime d) const
{
	if (m_year < d.getYear())
		return true;

	else if (m_year == d.getYear())
		if (m_day < d.getDay())
			return true;

	return false;
}


/*****************************************************************************/


bool
DateTime::operator > (DateTime d) const
{
	return d < *this;
}


/*****************************************************************************/


bool
DateTime::operator <= (DateTime d) const
{
	return (*this < d) || (*this == d);
}


/*****************************************************************************/


bool
DateTime::operator >= (DateTime d) const
{
	return (d < *this) || (*this == d);
}


/*****************************************************************************/


bool
DateTime::isValid() const
{
	if (m_year == 0)
		return false;

	if (m_day < 1 || m_day > 365)
		return false;

	return true;
}


/*****************************************************************************/


std::ostream & operator << (std::ostream & o, const DateTime & d)
{
	o << d.getYear() << '/' << '/' << d.getDay();

	return o;
}
