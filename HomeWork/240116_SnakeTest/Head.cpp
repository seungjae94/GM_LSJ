#include "Head.h"
#include <conio.h>
#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"

// 
// 1. 내가 특정 방향으로 진행했다면 다음 입력때는 그 반대방향으로는 갈수가 없다.
//    내가 이동하는 방향의 반대방향으로는 가면 안된다.
// 2. 내가 이동을 해서 CurBody를 획득했다면 그 다음부터 그 바디는 나를 따라와야 한다.

void Head::Update()
{
	// 입력이 들어오지 않아도 이동
	int Select = 0;
	int InputCount = _kbhit();
	while (InputCount > 0)
	{
		Select = _getch();
		InputCount = _kbhit();
	}

	int2 MoveDir = { 0, 0 };
	switch (Select)
	{
	case 'A':
	case 'a':
		MoveDir = Left;
		break;
	case 'S':
	case 's':
		MoveDir = Down;
		break;
	case 'W':
	case 'w':
		MoveDir = Up;
		break;
	case 'D':
	case 'd':
		MoveDir = Right;
		break;
	case '1':
		GetCore()->EngineEnd();
		break;
	default:
		break;
	}

	if (nullptr == BodyManager::GetCurBody())
	{
		MsgBoxAssert("먹을수 있는 바디가 존재하지 않습니다.");
		return;
	}

	// 다음에 이동할 위치 계산
	if (MoveDir == int2{ 0, 0 } || MoveDir == PrevDir * (-1))
	{
		MoveDir = PrevDir;
	}
	int2 MovePos = GetPos() + MoveDir;

	// 충돌 처리
	Collision(MovePos);
	
	// 이동 처리
	Move(MovePos, MoveDir);
}

Part* Head::GetTail()
{
	// 꼬리 찾기
	Part* Tail = this;
	Part* TailNext = Back;
	while (TailNext != nullptr)
	{
		Tail = TailNext;
		TailNext = TailNext->GetBack();
	}

	return Tail;
}

void Head::Collision(const int2& _MovePos)
{
	Body* CurBody = BodyManager::GetCurBody();

	if (CurBody->GetPos() == _MovePos)
	{
		Part* Tail = GetTail();

		// 꼬리 위치에 추가
		Tail->SetBack(CurBody);
		CurBody->SetFront(Tail);
		CurBody->SetRenderChar('@');

		BodyManager::ResetBody();
	}
}

void Head::Move(int2& _HeadMovePos, const int2& _MoveDir)
{
	// MovePos: 현재 Part*가 이동해야 할 위치
	// TrailingMovePos: 현재 Part*가 이동하기 전의 위치 = 다음 Part*가 이동해야 할 위치
	int2& MovePos = _HeadMovePos;
	int2 TrailingMovePos = GetPos();

	// 머리 이동
	SetPos(MovePos);
	PrevDir = _MoveDir;
	MovePos = TrailingMovePos; 

	// 몸통 이동
	Part* BackBody = Back;
	while (BackBody != nullptr)
	{
		TrailingMovePos = BackBody->GetPos();
		BackBody->SetPos(MovePos);

		MovePos = TrailingMovePos;
		BackBody = BackBody->GetBack();
	}
}