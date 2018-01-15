#include "FruitingHouseplant.hpp"

#include "messages.hpp"

/*-----------------------------------------------------------------*/

FruitingHouseplant::FruitingHouseplant(
		std::string const & _name
	,	int _age
	,	int _wateringPeriod
	,	int _floweringPeriod
	,	int _needWater
	,	std::string const & _fName
	,	int _fruitingDays
)
	: FloweringHouseplant(_name, _age, _wateringPeriod, _floweringPeriod, _needWater)
	,	fruitingDays(_fruitingDays)
	,	fruitName(_fName)
{
	if ( _fName.empty() )
		throw std::logic_error(Messages::EmptyFruitName);

	if ( _fruitingDays <= 0 )
		throw std::logic_error(Messages::UnexpectedFruiting);
}

/*-----------------------------------------------------------------*/

void FruitingHouseplant::tryFruiting()
{
	++currentFruitingDaysCount;

	if ( currentFruitingDaysCount == fruitingDays )
		makeFruit();

	DayGone();
}

/*-----------------------------------------------------------------*/

void FruitingHouseplant::makeFruit()
{
	std::cout << Messages::FruitingSuccess;
	std::cout << "Housplant: " << getName() << "\n";
	std::cout << "Fruit: " << fruitName << "\n";

	floweringOver();

	currentFruitingDaysCount = 0;
	resetWatering();
}

/*-----------------------------------------------------------------*/

void FruitingHouseplant::GiveWater()
{
	if ( getDaysPassed() == getPeriod() )
	{
		if ( getStatus() == NOT_ENAUGH_WATERING )
			addRightWatering();

		if ( isSuccesFlowering() )
			tryFruiting();
		else if( isTimeToFlowering() )
			tryFlowering();
		
		setWatering(CurrentDate::Instance().getCurrentDate());
		return;
	}

	if ( !isOneDayDiff() )
	{
		if ( getCurrentRightWatering() > 0 )
			takeRightWatering();

		if ( currentFruitingDaysCount > 0 )
			resetWatering();
		

		setWatering(CurrentDate::Instance().getCurrentDate());
		return;
	}

	if ( isOneDayDiff() && getStatus() == FLOWERING && isTimeToFlowering() )
	{
		isSuccesFlowering() ?
			tryFruiting() : tryFlowering();

		return;
	}

	setWatering(CurrentDate::Instance().getCurrentDate());
	resetWatering();
}

/*-----------------------------------------------------------------*/
