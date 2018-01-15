#ifndef _FLOWERINGHOUSPLANT_HPP_
#define _FLOWERINGHOUSPLANT_HPP_

#include "Houseplant.hpp"

/*-----------------------------------------------------------------*/

class FloweringHouseplant
	: public Houseplant
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	enum STATUS { FLOWERING, NOT_ENAUGH_WATERING };

	/*-----------------------------------------------------------------*/

	FloweringHouseplant(
			std::string const &_name
		,	int _age
		,	int _wateringPeriod
		,	int _flowDays
		,	int _needWater
	);

	/*-----------------------------------------------------------------*/
	
	virtual void DayGone() override 
	{ 
		CurrentDate::Instance().nextDay(); 
	}

	virtual void GiveWater() override;

	virtual Houseplant::TYPE getType() const override 
	{ 
		return Houseplant::FLOWERING; 
	}

	virtual ~FloweringHouseplant() override 
	{
	}
	
	/*-----------------------------------------------------------------*/

	const int getCurrentFloweringDays() const;

	const int getNeedRightWatering() const;

	const int getFlowering() const;

	const int getCurrentRightWatering() const;

	const STATUS getStatus() const;

	const bool isSuccesFlowering() const;

	const bool isTimeToFlowering() const;

	/*-----------------------------------------------------------------*/

protected:

	/*-----------------------------------------------------------------*/

	void tryFlowering();

	void makeStronger();

	void resetWatering();
	
	void floweringOver();

	void addRightWatering();

	void takeRightWatering();

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	const int needFloweringDays;
	const int needRightWatering;
	
	int currentFloweringDays = 0;
	int currentRightWatering = 0;

	bool floweringSuccess = false;

	STATUS Status = NOT_ENAUGH_WATERING;

	/*-----------------------------------------------------------------*/

};

/*-----------------------------------------------------------------*/

inline const int 
FloweringHouseplant::getCurrentFloweringDays() const
{
	return currentFloweringDays;
}

/*-----------------------------------------------------------------*/

inline const int
FloweringHouseplant::getNeedRightWatering() const
{
	return needRightWatering;
}

/*-----------------------------------------------------------------*/

inline const int
FloweringHouseplant::getFlowering() const
{
	return needFloweringDays;
}

/*-----------------------------------------------------------------*/

inline const int
FloweringHouseplant::getCurrentRightWatering() const
{
	return currentRightWatering;
}

/*-----------------------------------------------------------------*/

inline const FloweringHouseplant::STATUS
FloweringHouseplant::getStatus() const
{
	return Status;
}

/*-----------------------------------------------------------------*/

inline void 
FloweringHouseplant::floweringOver()
{
	floweringSuccess = false;
}

/*-----------------------------------------------------------------*/

inline void 
FloweringHouseplant::addRightWatering()
{
	++currentRightWatering;
}

/*-----------------------------------------------------------------*/

inline void 
FloweringHouseplant::takeRightWatering()
{
	--currentRightWatering;
}

/*-----------------------------------------------------------------*/

inline const bool 
FloweringHouseplant::isSuccesFlowering() const
{
	return floweringSuccess;
}

/*-----------------------------------------------------------------*/

inline const bool 
FloweringHouseplant::isTimeToFlowering() const
{
	return getCurrentRightWatering() == getNeedRightWatering();
}

/*-----------------------------------------------------------------*/


#endif //_FLOWERINGHOUSPLANT_HPP_