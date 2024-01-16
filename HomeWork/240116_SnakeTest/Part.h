#pragma once
#include <ConsoleEngine/ConsoleObject.h>

class Part : public ConsoleObject
{
public:
	inline Part* GetFront()
	{
		return Front;
	}

	inline Part* GetBack()
	{
		return Back;
	}

	inline void SetFront(Part* _Front)
	{
		Front = _Front;
	}

	inline void SetBack(Part* _Back)
	{
		Back = _Back;
	}

protected:
	Part* Front = nullptr;
	Part* Back = nullptr;
};

