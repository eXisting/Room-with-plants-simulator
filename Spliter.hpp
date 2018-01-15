#ifndef _SPLITER_HPP_
#define _SPLITER_HPP_

class Houseplant;

// Interface for adding plants in room
// motivation: break off file links dependences between plants and room
struct Spliter
{
	virtual void addNewHousplant(Houseplant *) = 0;
};

#endif // !_SPLITER_HPP_