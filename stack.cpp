#include "stack.h"

using namespace std;

template<class Type>
Stack<Type>::Stack()
{
	head = nullptr;
}

template <class Type>
Stack<Type>::~Stack()
{
	this->head = nullptr;
}

template <class Type>
void Stack<Type>::push(Type input)
{
	input->next = head;
	head = input;
}

template <class Type>
void Stack<Type>::pop()
{
	head = head->next;
}

template <class Type>
Type Stack<Type>::top()
{
	return head;
}

template <class Type>
bool Stack<Type>::isEmpty()
{
	return head == nullptr;
}
