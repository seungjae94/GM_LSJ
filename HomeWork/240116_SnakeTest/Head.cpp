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

	// ���� �̵� ��ġ ���
	bool MoveFlag = CurDir != PrevDir * (-1);
	int2 MovePos = GetPos() + CurDir;

	// �浹 ó��
	Body* CurBody = BodyManager::GetCurBody();

	if (CurBody->GetPos() == MovePos)
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
	
	// �̵� ó��
	if (MoveFlag)
	{
		// MovePos: ���� Part*�� �̵��ؾ� �� ��ġ
		// TrailingMovePos: ���� Part*�� �̵��ϱ� ���� ��ġ
		// ���� TrailingMovePos�� �׻� MovePos�� �ڵ���� �Ѵ�.
		int2 TrailingMovePos = GetPos();

		// �Ӹ� �̵�
		SetPos(MovePos);
		PrevDir = CurDir;

		// ���� �̵�
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