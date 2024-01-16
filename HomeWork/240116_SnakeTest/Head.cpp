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
	int InputCount = _kbhit();
	if (0 == InputCount)
	{
		return;
	}

	int Select = _getch();

	// InputCount = _kbhit();

	// X Y
	// 1 0

	int2 CurDir = { 0, 0 };

	switch (Select)
	{
	case 'A':
	case 'a':
		CurDir = Left;
		break;
	case 'S':
	case 's':
		CurDir = Down;
		break;
	case 'W':
	case 'w':
		CurDir = Up;
		break;
	case 'D':
	case 'd':
		CurDir = Right;
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

	// 다음 이동 위치 계산
	bool MoveFlag = CurDir != PrevDir * (-1);
	int2 MovePos = GetPos() + CurDir;

	// 충돌 처리
	Body* CurBody = BodyManager::GetCurBody();

	if (CurBody->GetPos() == MovePos)
	{
		// 꼬리 찾기
		Part* Tail = this;
		Part* TailNext = Back;
		while (TailNext != nullptr)
		{
			Tail = TailNext;
			TailNext = TailNext->GetBack();
		}
		
		// 꼬리 위치에 추가
		Tail->SetBack(CurBody);
		CurBody->SetFront(Tail);

		BodyManager::ResetBody();
	}
	
	// 이동 처리
	if (MoveFlag)
	{
		// MovePos: 현재 Part*가 이동해야 할 위치
		// TrailingMovePos: 현재 Part*가 이동하기 전의 위치
		// 따라서 TrailingMovePos는 항상 MovePos를 뒤따라야 한다.
		int2 TrailingMovePos = GetPos();

		// 머리 이동
		SetPos(MovePos);
		PrevDir = CurDir;

		// 몸통 이동
		MovePos = TrailingMovePos;
		Part* BackBody = Back;
		while (BackBody != nullptr)
		{
			TrailingMovePos = BackBody->GetPos();
			BackBody->SetPos(MovePos);

			MovePos = TrailingMovePos;
			BackBody = BackBody->GetBack();
		}
	}
}