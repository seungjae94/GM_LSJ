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
	bool GameEnd = false;
	CollisionWithCurBody(MovePos);
	CollisionWithMyBody(MovePos, GameEnd);
	CollisionWithWall(MovePos, GameEnd);

	// 게임 종료 처리
	if (GameEnd)
	{
		GetCore()->EngineEnd();
		return;
	}

	// 이동 처리
	Move(MovePos, MoveDir);
}

void Head::CollisionWithCurBody(const int2& _MovePos)
{
	Body* CurBody = BodyManager::GetCurBody();

	if (CurBody->GetPos() == _MovePos)
	{
		// 꼬리 뒤에 CurBody 추가
		Tail->SetBack(CurBody);
		CurBody->SetFront(Tail);
		CurBody->SetRenderChar('@');

		// CurBody를 꼬리로 설정
		Tail = CurBody;

		BodyManager::ResetBody();
	}
}

void Head::CollisionWithMyBody(const int2& _MovePos, bool& _GameEnd)
{
	// 길이 1인 경우 MyBody와 충돌하지 않는다.
	if (Back == nullptr)
	{
		return;
	}

	Part* MyBody = Back;
	while (MyBody != Tail)
	{
		// MyBody와 충돌하는 경우
		if (MyBody->GetPos() == _MovePos)
		{
			_GameEnd = true;
			return;
		}

		MyBody = MyBody->GetBack();
	}
}

void Head::CollisionWithWall(const int2& _MovePos, bool& _GameEnd)
{
	int2 OriginalPos = GetPos();
	SetPos(_MovePos);
	ConsoleObject* Object = Collision(1);
	SetPos(OriginalPos);

	if (Object != nullptr)
	{
		_GameEnd = true;
		return;
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