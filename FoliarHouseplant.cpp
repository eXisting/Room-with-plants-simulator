#include "FoliarHouseplant.hpp"

#include "messages.hpp"
#include "Spliter.hpp"

#include <memory>

/*-----------------------------------------------------------------*/

FoliarHouseplant::FoliarHouseplant(
		std::string const & _name
	,	int _age
	,	int _wateringPeriod
	,	int _height
	,	Spliter & _container
)
	: Houseplant(_name, _age, _wateringPeriod)
	,	height(_height)
	,	spliter(_container)
{
	if ( _height <= 0 || _height >= 250 )
		throw std::logic_error(Messages::UnexpectedHeight);
}

/*-----------------------------------------------------------------*/

void FoliarHouseplant::GiveWater()
{
	if ( getDaysPassed() == getPeriod() || isOneDayDiff() )
	{
		setWatering(CurrentDate::Instance().getCurrentDate());

		++height;

		if ( height == 250 )
		{
			height = height >> 1;

			FoliarHouseplant * splitedPlant = new FoliarHouseplant(
					getName() + "_copy"
				,	getAge()
				,	getPeriod()
				,	125
				,	spliter
			);

			spliter.addNewHousplant(splitedPlant);
		}
	}
}

/*-----------------------------------------------------------------*/

