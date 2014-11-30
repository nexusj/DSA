#ifndef _STACKP_HEADER_

template <typename T> //Forward declaration
class StackP;

template <typename T>
std::ostream& operator<<(std::ostream&, StackP<T>&);

template <typename T>
class StackP
{
	struct ICell
	{
		T elem;
		ICell* next;
	};

	public:
		using iterator = ICell*;
		StackP();
		~StackP();
		bool IsEmpty() const;
		T& read() const;
		T& Pop();
		void Push(T);
		void Print();

	private:
		iterator head;
		int m_size;
		friend std::ostream& operator<< <>(std::ostream&,  StackP<T>&);


};

template <typename T>
StackP<T>::StackP()
{
	head = new ICell;
	head->next = head;
	m_size = 0;
}

template <typename T>
StackP<T>::~StackP()
{
	while (!this->IsEmpty())
	{
		this->Pop();
	}

	delete head;
}

template <typename T>
bool StackP<T>::IsEmpty() const
{
	return (m_size == 0);
}

template <typename T>
T& StackP<T>::read() const
{
	return head->next->elem;
}

template <typename T>
T& StackP<T>::Pop()
{
	iterator temp;
	T e;
	if (!this->IsEmpty())
	{
		temp = head->next;
		e = temp->elem;
		head->next = head->next->next;
		m_size--;
		delete temp;
	}

	return e;
}

template <typename T>
void StackP<T>::Push(T e)
{
	iterator temp = new ICell;
	
	temp->elem = e;
	temp->next = head->next;
	head->next = temp;
	m_size++;
}

template <typename T>
void StackP<T>::Print()
{
	T e;

	if(!this->IsEmpty())
	{
		
		e = this->Pop();
		
		if (m_size >= 1)
		{
			std::cout << e << ",";
		}
		else
			std::cout << e << std::endl;

		this->Print();
		this->Push(e);
		
	}
	
}

template <typename T>
std::ostream& operator<<(std::ostream& os, StackP<T>& s)
{	
	s.Print();
	return os;
}

#endif