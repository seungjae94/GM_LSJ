#pragma once
#include "Part.h"

class Head : public Part
{
protected:
	void Update() override;
private:
	int2 PrevDir = Up;

	void Collision(const int2& _MovePos);
	void Move(int2& _HeadMovePos, const int2& _MoveDir);
	Part* GetTail();
};

