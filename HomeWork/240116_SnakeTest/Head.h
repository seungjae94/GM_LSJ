#pragma once
#include "Part.h"

class Head : public Part
{
protected:
	void Update() override;
private:
	int2 PrevDir = Up;
	Part* Tail = this;

	// �浹 ó�� �Լ�
	void CollisionWithCurBody(const int2& _MovePos);
	void CollisionWithMyBody(const int2& _MovePos, bool& _GameEnd);
	void CollisionWithWall(const int2& _MovePos, bool& _GameEnd);

	// �̵� �Լ�
	void Move(int2& _HeadMovePos, const int2& _MoveDir);
};

