#include "Head.h"
#include <conio.h>
#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"

// 
// 1. ���� Ư�� �������� �����ߴٸ� ���� �Է¶��� �� �ݴ�������δ� ������ ����.
//    ���� �̵��ϴ� ������ �ݴ�������δ� ���� �ȵȴ�.
// 2. ���� �̵��� �ؼ� CurBody�� ȹ���ߴٸ� �� �������� �� �ٵ�� ���� ����;� �Ѵ�.

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
		MsgBoxAssert("������ �ִ� �ٵ� �������� �ʽ��ϴ�.");
		return;
	}

	// �Ӹ� �̵� ó��
	bool MoveFlag = CurDir != PrevDir * (-1);
	int2 BeforeMovePos = GetPos();
	if (MoveFlag)
	{
		AddPos(CurDir);
		PrevDir = CurDir;
	}

	// �浹 ó��
	Body* CurBody = BodyManager::GetCurBody();

	if (CurBody->GetPos() == GetPos())
	{
		// ���� ã��
		Part* Tail = this;
		Part* TailNext = Back;
		while (TailNext != nullptr)
		{
			Tail = TailNext;
			TailNext = TailNext->GetBack();
		}
		
		// ���� ��ġ�� �߰�
		Tail->SetBack(CurBody);
		CurBody->SetFront(Tail);

		BodyManager::ResetBody();
	}
	
	// ���� �̵� ó��
	if (MoveFlag)
	{
		int2 TargetPos = BeforeMovePos;
		Part* BackBody = Back;
		while (BackBody != nullptr)
		{
			int2 NextTargetPos = BackBody->GetPos();
			BackBody->SetPos(TargetPos);
			BackBody = BackBody->GetBack();
			TargetPos = NextTargetPos;
		}
	}
}