#ifndef _QUEUEP_HEADER_

template <typename T>
class QueueP
{
	struct ICell
	{
		T elem;
		ICell* next;
	};

	public:
		using iterator = ICell*;
		QueueP();
		~QueueP();
		bool IsEmpty() const;
		T& Head() const;
		T& Tail() const;
		T& Pop();
		void Push(T);
		void Print();

	private:
		iterator head, tail;
		int m_size;
};

template <typename T>
QueueP<T>::QueueP()
{
	head = new ICell;
	tail = new ICell;

	head->next = head;
	tail->next = head;

	m_size = 0;
}

template <typename T>
QueueP<T>::~QueueP()
{
	while (!this->IsEmpty())
	{
		this->Pop();
	}

	delete tail;
	delete head;
}

template <typename T>
bool QueueP<T>::IsEmpty() const
{
	return(m_size == 0);
}

template <typename T>
T& QueueP<T>::Head() const
{
	return head->next->elem;
}

template <typename T>
T& QueueP<T>::Tail() const
{
	return tail->next->elem;
}

template <typename T>
T& QueueP<T>::Pop()
{
	iterator temp;
	T e;

	if (!this->IsEmpty())
	{
		temp = head->next;
		e = temp->elem;
		head->next = temp->next;
		m_size--;
		m_size == 0 ? tail->next = head : tail->next = tail->next;
		delete temp;
	}

	return e;
}

template <typename T>
void QueueP<T>::Push(T e)
{
	iterator temp = new ICell;
	iterator next = tail->next;

	temp->elem = e;
	temp->next = head;
	tail->next = temp;
	next->next = temp;
	m_size++;
}

template <typename T>
void QueueP<T>::Print()
{
	QueueP<T> q;
	
	while(!this->IsEmpty())
	{
		if (m_size > 1)
		{
			std::cout << this->Head() << ",";
		}
		else
			std::cout << this->Head() << std::endl;

		q.Push(this->Pop());
	}

	while (!q.IsEmpty())
	{
		this->Push(q.Pop());
	}
}

#endif