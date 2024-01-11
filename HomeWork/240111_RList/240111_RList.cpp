#include <iostream>
#include <list>
#include <ConsoleEngine/EngineDebug.h>

typedef int DataType;

class MyList
{
private:
	class ListNode
	{
	public:
		DataType Data = DataType();
		ListNode* Next = nullptr;
		ListNode* Prev = nullptr;
	};

	class common_iterator
	{
		friend MyList;

	public:
		common_iterator()
		{
		}

		common_iterator(ListNode* _CurNode)
			: CurNode(_CurNode)
		{
		}

		bool operator!=(const common_iterator& _Other)
		{
			return CurNode != _Other.CurNode;
		}

		DataType& operator*()
		{
			return CurNode->Data;
		}

		// 연산자 겹지정 중에 
		virtual void operator++()
		{
		}
	private:
		ListNode* CurNode = nullptr;
	};

public:

	class iterator : public common_iterator
	{
	public:
		iterator()
		{
		}

		iterator(ListNode* _CurNode) : common_iterator(_CurNode)
		{
		}

		void operator++()
		{
			CurNode = CurNode->Next;
		}
	};

	class reverse_iterator : public common_iterator
	{
	public:
		reverse_iterator()
		{
		}

		reverse_iterator(ListNode* _CurNode)
			: common_iterator(_CurNode)
		{
		}

		// 연산자 겹지정 중에 
		void operator++()
		{
			CurNode = CurNode->Prev;
		}
	};

	MyList()
	{
		Start->Next = End;
		End->Prev = Start;
	}

	~MyList()
	{
		ListNode* CurNode = Start;
		while (CurNode)
		{
			ListNode* Next = CurNode->Next;
			if (nullptr != CurNode)
			{
				delete CurNode;
				CurNode = Next;
			}
		}
	}


	iterator begin()
	{
		return iterator(Start->Next);
	}

	iterator end()
	{
		return iterator(End);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(End->Prev);
	}

	reverse_iterator rend()
	{
		return reverse_iterator(Start);
	}

	// End의 Prev에 새로운 데이터를 넣겠다.
	void push_back(const DataType& _Data)
	{
		ListNode* NewNode = new ListNode();
		NewNode->Data = _Data;

		NewNode->Next = End;
		NewNode->Prev = End->Prev;

		ListNode* PrevNode = NewNode->Prev;
		ListNode* NextNode = NewNode->Next;

		PrevNode->Next = NewNode;
		NextNode->Prev = NewNode;
	}

	// Start의 Next에 새로운 데이터를 넣겠다.
	void push_front(const DataType& _Data)
	{
		// 역함수
		ListNode* NewNode = new ListNode();
		NewNode->Data = _Data;

		NewNode->Prev = Start;
		NewNode->Next = Start->Next;

		ListNode* PrevNode = NewNode->Prev;
		ListNode* NextNode = NewNode->Next;

		PrevNode->Next = NewNode;
		NextNode->Prev = NewNode;

	}

	iterator erase(iterator& _Iter)
	{
		if (_Iter.CurNode == Start)
		{
			MsgBoxAssert("Start를 삭제하려고 했습니다.");
		}

		if (_Iter.CurNode == End)
		{
			MsgBoxAssert("End를 삭제하려고 했습니다.");
		}

		iterator ReturnIter;

		if (nullptr != _Iter.CurNode)
		{
			ReturnIter = iterator(_Iter.CurNode->Next);

			ListNode* PrevNode = _Iter.CurNode->Prev;
			ListNode* NextNode = _Iter.CurNode->Next;

			PrevNode->Next = NextNode;
			NextNode->Prev = PrevNode;

			if (nullptr != _Iter.CurNode)
			{
				delete _Iter.CurNode;
				_Iter.CurNode = nullptr;
			}
		}

		return ReturnIter;
	}


protected:

private:

	ListNode* Start = new ListNode();
	ListNode* End = new ListNode();
};

int main()
{
	LeakCheck;

	{
		std::cout << "내 리스트 (iterator)" << std::endl;
		MyList NewList = MyList();
		// 0, 1, 2, 3, 4
		for (int i = 0; i < 5; i++)
		{
			NewList.push_back(i);
			// NewList.push_front();
		}

		MyList::iterator rStartIter = NewList.begin();
		MyList::iterator rEndIter = NewList.end();

		for (/*std::list<int>::iterator StartIter = NewList.begin()*/
			; rStartIter != rEndIter
			; ++rStartIter)
		{
			std::cout << *rStartIter << std::endl;
		}
	}

	{
		std::cout << "내 리스트 (reverse_iterator)" << std::endl;
		MyList NewList = MyList();
		// 0, 1, 2, 3, 4
		for (int i = 0; i < 5; i++)
		{
			NewList.push_back(i);
			// NewList.push_front();
		}

		MyList::iterator NewStartIter = NewList.begin();
		MyList::reverse_iterator rStartIter = NewList.rbegin();
		MyList::reverse_iterator rEndIter = NewList.rend();

		for (/*std::list<int>::iterator StartIter = NewList.begin()*/
			; rStartIter != rEndIter
			; ++rStartIter)
		{
			std::cout << *rStartIter << std::endl;
		}
	}
}
