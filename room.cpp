#include "room.hpp"

#include "Houseplant.hpp"
#include "messages.hpp"

#include <cassert>

/*-----------------------------------------------------------------*/

void Room::addNewHousplant(Houseplant * _hs)
{
	assert(_hs);

	plants.push_back(std::unique_ptr<Houseplant>(_hs));
}

/*-----------------------------------------------------------------*/

Houseplant *
Room::getPlant(int _index) const
{
	if ( _index < 0 || _index > static_cast<int>( plants.size() ) )
		throw std::out_of_range(Messages::IndexOutOfRange);

	return plants[_index].get();
}

/*-----------------------------------------------------------------*/
