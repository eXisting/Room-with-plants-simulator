#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include "Spliter.hpp"

#include <vector>
#include <memory>

/*-----------------------------------------------------------------*/

class CurrentDate;

/*-----------------------------------------------------------------*/

class Room 
	: public Spliter
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	typedef std::vector< std::unique_ptr<Houseplant> > HPlants;
	typedef HPlants::const_iterator HPlantsIterator;

	/*-----------------------------------------------------------------*/

	Room() = default;
	
	/*-----------------------------------------------------------------*/

	virtual void addNewHousplant(Houseplant *) override;
	
	/*-----------------------------------------------------------------*/

	Houseplant * getPlant(int _index) const;

	HPlantsIterator getBegin() const;

	HPlantsIterator getEnd() const;

	const int getPlantsCount() const;

	bool isEmpty() const;

	/*-----------------------------------------------------------------*/

	// Iterator pattern
	// purpose: iterable for loop (for : Houseplant_object) 
	class IterableHousePlant
	{
		/*-----------------------------------------------------------------*/

	public:

		/*-----------------------------------------------------------------*/

		IterableHousePlant(HPlantsIterator _begin, HPlantsIterator _end)
			:beginPointer(_begin), endPointer(_end)
		{};

		/*-----------------------------------------------------------------*/

		HPlantsIterator begin() const { return beginPointer; };
		HPlantsIterator end() const { return endPointer; };

		/*-----------------------------------------------------------------*/

	private:

		/*-----------------------------------------------------------------*/

		HPlantsIterator beginPointer, endPointer;

		/*-----------------------------------------------------------------*/

	};

	/*-----------------------------------------------------------------*/
	
	IterableHousePlant iterable_plants() const 
	{ 
		return IterableHousePlant(getBegin(), getEnd()); 
	}

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::vector< std::unique_ptr<Houseplant> >	plants;

	/*-----------------------------------------------------------------*/

};

/*-----------------------------------------------------------------*/

inline Room::HPlantsIterator
Room::getBegin() const
{ 
	return plants.begin(); 
}

/*-----------------------------------------------------------------*/

inline Room::HPlantsIterator
Room::getEnd() const
{ 
	return plants.end(); 
}

/*-----------------------------------------------------------------*/

inline const int 
Room::getPlantsCount() const
{ 
	return plants.size(); 
}

/*-----------------------------------------------------------------*/

inline bool
Room::isEmpty() const
{ 
	return plants.empty(); 
}

/*-----------------------------------------------------------------*/

#endif // !_ROOM_HPP_
