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
	// �Է��� ������ �ʾƵ� �̵�
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
		MsgBoxAssert("������ �ִ� �ٵ� �������� �ʽ��ϴ�.");
		return;
	}

	// ������ �̵��� ��ġ ���
	if (MoveDir == int2{ 0, 0 } || MoveDir == PrevDir * (-1))
	{
		MoveDir = PrevDir;
	}
	int2 MovePos = GetPos() + MoveDir;

	// �浹 ó��
	Collision(MovePos);
	
	// �̵� ó��
	Move(MovePos, MoveDir);
}

Part* Head::GetTail()
{
	// ���� ã��
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

		// ���� ��ġ�� �߰�
		Tail->SetBack(CurBody);
		CurBody->SetFront(Tail);
		CurBody->SetRenderChar('@');

		BodyManager::ResetBody();
	}
}

void Head::Move(int2& _HeadMovePos, const int2& _MoveDir)
{
	// MovePos: ���� Part*�� �̵��ؾ� �� ��ġ
	// TrailingMovePos: ���� Part*�� �̵��ϱ� ���� ��ġ = ���� Part*�� �̵��ؾ� �� ��ġ
	int2& MovePos = _HeadMovePos;
	int2 TrailingMovePos = GetPos();

	// �Ӹ� �̵�
	SetPos(MovePos);
	PrevDir = _MoveDir;
	MovePos = TrailingMovePos; 

	// ���� �̵�
	Part* BackBody = Back;
	while (BackBody != nullptr)
	{
		TrailingMovePos = BackBody->GetPos();
		BackBody->SetPos(MovePos);

		MovePos = TrailingMovePos;
		BackBody = BackBody->GetBack();
	}
}