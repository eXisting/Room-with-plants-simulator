#include "FloweringHousplant.hpp"

#include "messages.hpp"

/*-----------------------------------------------------------------*/

FloweringHouseplant::FloweringHouseplant(
		std::string const & _name
	,	int _age
	,	int _wateringPeriod
	,	int _flowDays
	,	int _needWater
)
	: Houseplant(_name, _age, _wateringPeriod)
	,	needFloweringDays(_flowDays)
	,	needRightWatering(_needWater)
{
	if ( _flowDays <= 0 || _flowDays >= 365 )
		throw std::logic_error(Messages::WrongFloweringDays);

	if ( _needWater <= 0 )
		throw std::logic_error(Messages::WrongWateringCount);
}

/*-----------------------------------------------------------------*/

void FloweringHouseplant::tryFlowering()
{
	if ( Status == NOT_ENAUGH_WATERING )
	{
		Status = FLOWERING;
		return;
	}
			
	++currentFloweringDays;

	if ( currentFloweringDays == needFloweringDays )
		makeStronger();
	
	DayGone();
}

/*-----------------------------------------------------------------*/

void FloweringHouseplant::makeStronger()
{
	floweringSuccess = true;

	changePeriod();

	resetWatering();

	std::cout << Messages::StrongerSuccess;
}

/*-----------------------------------------------------------------*/

void FloweringHouseplant::resetWatering()
{
	Status = NOT_ENAUGH_WATERING;
	currentRightWatering = 0;
	currentFloweringDays = 0;
}

/*-----------------------------------------------------------------*/

void FloweringHouseplant::GiveWater()
{
	if ( getDaysPassed() == getPeriod() )
	{
		if ( Status == NOT_ENAUGH_WATERING )
			++currentRightWatering;

		if ( isTimeToFlowering() )
			tryFlowering();

		setWatering(CurrentDate::Instance().getCurrentDate());
		return;
	}

	const bool isValidTimeToGiveWater = isOneDayDiff();

	if ( !isValidTimeToGiveWater )
	{
		if ( getStatus() == FLOWERING )
			resetWatering();
		else if ( currentRightWatering > 0 )
			--currentRightWatering;
		
		setWatering(CurrentDate::Instance().getCurrentDate());
		return;
	}
	
	if (isValidTimeToGiveWater && Status == FLOWERING && isTimeToFlowering())
	{
		tryFlowering();
		return;
	}
	
	setWatering(CurrentDate::Instance().getCurrentDate());
	resetWatering();
}

/*-----------------------------------------------------------------*/
