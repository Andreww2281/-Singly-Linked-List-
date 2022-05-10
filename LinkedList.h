#pragma once
#include <iostream>

#define Procedur_func
//#define Recurs_func
 
//////////////////// Перечень функций //////////////////////////////////////

// OutPut -  вывод массива
// pop_front - удаление первого элемента
// push_front - добавление элемента в конец списка
// size - получение количества элементов в списке 
// clear - очистка списка (полное удаление элементов)
// pop - удаление элемента списка по индексу
// insert - вставка элемента по индексу
// push_back - добавить элемент в конец списка
// pop_back - удалить последний элемент списка
//
//
// Библиотека имеет два варианта набора функций:
//	1) Рекурсивные(pop, insert, push_back, pop_back, getElemR) - реализованы рекурсиным методом, они быстрее, но памяти требуют больше 
//	2) Процедурные(pop, insert, push_back, pop_back) - реализованы процедурным методом, медленее чем рекусивные, занимаю меньше памяти 
//	Чтобы включить один из вариантов функций - #define (Procedur_func, Recurs_func)
// 
// 
// Реализованы такие прегрузки:
//	 1) Квадратные скобки в двух экземлярах. При разных наборах функций принцып работы отличается 
//	 2) Вывод на экран
//	 3) Оператор присваивания
//
///////////////////////////////////////////////////////////////////////////


template<typename type>
class LinkedList
{
private:
	class Node
	{
	public:
		Node* pNext;
		type data;

		Node(type elem = type(), Node* pNext = nullptr)
		{
			this->data = elem;
			this->pNext = pNext;
		}

		~Node()
		{
		}

	};

	Node* head;
	unsigned int len;

public:

/////////////////// Объявления для процедурных функций //////////////////////////////////////////////////////////////////////

#ifdef Procedur_func

#ifndef Recurs_func

	type pop(int ind);

	// Вставить элемент по индексу
	void insert(const type&, int ind);


	// Добавление элемента в конец списка 
	void push_back(const type&);

	// Удаление последнего элемента списка через цикл
	type pop_back();

	// Получение элемета по индексу
	type& operator[](int n);

#define pop         pop
#define insert      insert
#define push_back   push_back
#define pop_back    pop_back

#endif

#endif 

//////////////////// Объявления для рекурсивных функций /////////////////////////////////////////////////////////////////////

#ifdef Recurs_func

	type& getElemR(int ind, int pos = 0, Node* elem = nullptr);

	type popR(int ind, Node* elem = nullptr, int pos = 0);

	void insertR(const type&, int ind, Node* elem = nullptr, int pos = 0);

	void push_backR(const type& elem, int pos = 0, Node* tmp = nullptr);

	type pop_backR(Node* elem = nullptr, int pos = 0);

	type& operator[](int ind);



#define pop popR
#define insert insertR
#define push_back push_backR
#define pop_back pop_backR

#endif 

////////////////////// Объявления для общих функций /////////////////////////////////////////////////////////////////

#pragma region Объявления для общих функций

	LinkedList() { len = 0; head = nullptr; }
	~LinkedList() { clear(); }

	template<typename type>
	LinkedList(const std::initializer_list<type> _arr)
	{
		for (size_t i = 0; i < _arr.size(); i++)
		{
			push_front(*(_arr.end() - i - 1));
		}
	}


	LinkedList<type>& operator=(const LinkedList<type>& _arr)
	{
		Node* tmp = _arr.head;
		len = 0;
		for (size_t i = 0; i < _arr.size(); i++)
		{
			push_back(tmp->data);
			tmp = tmp->pNext;
		}
		return *this;
	}

	LinkedList(const LinkedList<type>& _arr)
	{
		head = nullptr;
		Node* tmp = _arr.head;
		len = 0;
		for (size_t i = 0; i < _arr.size(); i++)
		{
			push_back(tmp->data);
			tmp = tmp->pNext;
		}
	}

	void OutPut();

	//Перегрузка оператора вывода 
	template<typename type>
	friend std::ostream& operator<<(std::ostream&, const LinkedList<type>&);


	// Удалить первый элемент
	type pop_front();

	// Добавить элемент в начало
	void push_front(const type&);

	// Получить размер списка
	unsigned int size() const;

	// Очистить массив
	void clear();
#pragma endregion Объявления для общих функций
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};



////////////////////// Описание общих функций для двух наборов  ////////////////////////////////////////////////

#pragma region Описание общих функций для двух наборов

template<typename type>
void LinkedList<type>::OutPut()
{
	Node* tmp = head;
	for (size_t i = 0; i < len; i++)
	{
		std::cout << tmp->data << " ";
		tmp = tmp->pNext;
	}
	std::cout << std::endl;
}

template<typename type>
std::ostream& operator<< (std::ostream& out, const LinkedList<type>& d)
{
	
	typename LinkedList<type>::Node* tmp = d.head;

	for (size_t i = 0; i < d.len; i++)
	{
		out << tmp->data << " ";
		tmp = tmp->pNext;
	}
	out << std::endl;
	return out;
}

template<typename type>
type LinkedList<type>::pop_front()
{
	Node* tmp = head;
	type data = tmp->data;
	head = tmp->pNext;
	delete tmp;
	len--;
	return data;
}

template<typename type>
void LinkedList<type>::push_front(const type& elem)
{
	Node* tmp = head;
	head = new Node(elem, tmp);
	len++;
}

template<typename type>
unsigned int LinkedList<type>::size() const { return len; }
	
template<typename type>
void LinkedList<type>::clear()
{
	while (len != 0)
	{
		pop_front();
	}
}


#pragma endregion Описание общих функций для двух наборов

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef Recurs_func

template<typename type>
inline type& LinkedList<type>::getElemR(int ind, int pos, Node* elem)
{
	if (ind == 0)
	{
		elem = head;
		return elem->data;
	}
	else if (ind == pos) return elem->data;

	if (elem == nullptr) elem = head;

	if (ind != pos)
	{
		elem = elem->pNext;
		pos++;
		getElemR(ind, pos, elem);
	}
	else return elem->data;
}

template<typename type>
type& LinkedList<type>::operator[](int ind){ return getElemR(ind);}

template<typename type>
void LinkedList<type>::push_backR(const type& elem, int pos, Node* tmp)
{

	if (len == 0) return push_front(elem);
	if (tmp == nullptr) tmp = head;

	if (pos == len-1)
	{
		Node* NewElem = new Node(elem, tmp->pNext);
		tmp->pNext = NewElem;

		len++;
		return;
	}
	else
	{
		tmp = tmp->pNext;
		pos++;
		return push_backR(elem, pos, tmp);
	}
}

template<typename type>
type LinkedList<type>::pop_backR(Node* elem, int pos)
{
	if (pos == 0) elem = head;

	// Если текущая позиция указателя равна последнему элементу
	if (pos == len-1)
	{
		Node* tmp = elem;
		type data = tmp->data;
		tmp->pNext = nullptr;

		delete tmp;
		len--;
		return data;
	}
	else  // Переприсваиваем другой указатель и увеличиваем текущую позицию
	{
		elem = elem->pNext;
		pos++;
		return pop_backR(elem, pos);
	}
}

template<typename type>
void LinkedList<type>::insertR(const type& elem, int ind, Node* tmp, int pos)
{
	if (ind < 0 || ind > len - 1) return;


	if (ind == 0) return push_front(elem);
	if (tmp == nullptr) tmp = head;


	if (pos+1 == ind)
	{
		Node* NewElem = new Node(elem, tmp->pNext);
		tmp->pNext = NewElem;

		len++;
		return;
		
	}
	else
	{
		tmp = tmp->pNext;
		pos++;
		return insertR(elem, ind, tmp, pos);
	}
}

template<typename type>
type LinkedList<type>::popR(int ind, Node* elem, int pos)
{
	/*if (ind < 0 || ind > len - 1) return;*/

	if (ind == 0) return pop_front();
	else if (pos == 0) elem = head;


	if (ind == pos - 1 || ind == 1)
	{
		type data = elem->pNext->data;
		Node* tmp = elem->pNext;

		elem->pNext = elem->pNext->pNext;
		len--;
		delete tmp;
		return data;
	}
	else
	{
		elem = elem->pNext;
		pos++;
		return popR(ind, elem, pos);
	}
}


#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef Procedur_func

template<typename type>
type& LinkedList<type>::operator[](int n)
{
	int number = 0;

	Node* cur = head;
	while (cur != nullptr)
	{
		if (number == n)
		{
			return cur->data;
		}
		cur = cur->pNext;
		number++;
	}
}


template<typename type>
void LinkedList<type>::push_back(const type& elem)
{
	if (len == 0) return push_front(elem);

	if (head == nullptr)
	{
		head = new Node(elem);
	}
	else
	{
		Node* current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node(elem);

	}
	len++;
}

template<typename type>
inline type LinkedList<type>::pop_back()
{
	Node* tmp = head;

	for (size_t i = 0; i < len-2; i++)
	{
		tmp = tmp->pNext;
	}
	Node* del = tmp->pNext;
	type data = del->data;
	
	delete del;
	len--;
	return data;
}

template<typename type>
void LinkedList<type>::insert(const type& elem, int ind)
{

	if (ind == 0) push_front(elem);
	else
	{
		Node* tmp = head;

		for (size_t i = 0; i < ind - 1; i++)
		{
			tmp = tmp->pNext;
		}

		Node* NewNode = new Node(elem, tmp->pNext);
		tmp->pNext = NewNode;

		len++;
	}
}


template<typename type>
type LinkedList<type>::pop(int ind)
{
	if (ind == 0) return pop_front();

	Node* interator = head;

	for (size_t i = 0; i < ind - 1; i++)
	{
		interator = interator->pNext;
	}

	type data = interator->pNext->data;
	Node* tmp = interator->pNext;

	interator->pNext = interator->pNext->pNext;
	len--;
	delete tmp;
	return data;
}




#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////