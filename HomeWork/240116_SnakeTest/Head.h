#pragma once
#include "Part.h"

class Head : public Part
{
protected:
	void Update() override;
private:
	int2 PrevDir = Up;
	Part* Tail = this;

	// 충돌 처리 함수
	void CollisionWithCurBody(const int2& _MovePos);
	void CollisionWithMyBody(const int2& _MovePos, bool& _GameEnd);
	void CollisionWithWall(const int2& _MovePos, bool& _GameEnd);

	// 이동 함수
	void Move(int2& _HeadMovePos, const int2& _MoveDir);
};

