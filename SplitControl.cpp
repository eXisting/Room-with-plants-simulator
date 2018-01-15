#include "SplitControl.hpp"

#include "room.hpp"

#include "messages.hpp"

/*-----------------------------------------------------------------*/

void SpliterHelper::addNewHousplant(Houseplant * _half)
{
	direct->addNewHousplant(_half);
}

/*-----------------------------------------------------------------*/

SpliterHelper::SpliterHelper(Room * _source)
	:direct(_source)
{
	if ( !_source )
		throw std::logic_error(Messages::WrongPointerToRoom);
}

/*-----------------------------------------------------------------*/

void SpliterHelper::connectToRoom(Room * _r) 
{
	if ( !_r )
		throw std::logic_error(Messages::WrongPointerToRoom); 
	
	direct = _r;
}

/*-----------------------------------------------------------------*/
