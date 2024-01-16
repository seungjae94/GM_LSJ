#pragma once
#include <ConsoleEngine/ConsoleObject.h>

class Part : public ConsoleObject
{
public:
	inline Part* GetBack()
	{
		return Back;
	}

	inline void SetFront(Part* _Front)
	{
		Front = _Front;
	}

protected:
	Part* Front = nullptr;
	Part* Back = nullptr;
};

