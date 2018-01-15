#include "Houseplant.hpp"

#include "messages.hpp"

/*-----------------------------------------------------------------*/

Houseplant::Houseplant(
		std::string const & _name
	,	int _age
	,	int _wateringPeriod
)
	: houseplantName(_name), age(_age), wateringPeriodDays(_wateringPeriod)
{
	if ( _name.empty() )
		throw std::logic_error(Messages::EmptyHousplantName);

	if ( _age < 0 )
		throw std::logic_error(Messages::UnexpectedAge);

	if ( _wateringPeriod < 0 || _wateringPeriod > 31 )
		throw std::logic_error(Messages::UnexpecteWateringdPeriod);

	lastWateringDate = CurrentDate::Instance().getCurrentDate();
}

/*-----------------------------------------------------------------*/

void Houseplant::changePeriod()
{
	if ( wateringPeriodDays > 31 )
		throw std::logic_error(Messages::UnexpecteWateringdPeriod);

	wateringPeriodDays += 2;
}

/*-----------------------------------------------------------------*/
