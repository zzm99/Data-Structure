#include <iostream>
using namespace std;

template <typename K>
struct Node
{
	K data;
	Node<K>* next;
};

template <typename T> class LinkedStack{
private:
	int size;
	Node<T>* StackHead;
public:
	LinkedStack();
	~LinkedStack();
	void push(T e);
	T pop();
	bool isEmpty()const;
	int getSize()const;
};


template <typename T>
LinkedStack<T>::LinkedStack(){
	this->size = 0;
	StackHead = new Node<T>; 
	StackHead->next = NULL; 
}

template <typename T>
LinkedStack<T>::~LinkedStack(){
	while(this->size > 0)
	{
		this->pop();
	}
	delete this->StackHead;
}


template <typename T>
void LinkedStack<T>::push(T e){
	Node<T>* tmpCell = new Node<T>;
	tmpCell->data = e;
	tmpCell->next = this->StackHead->next;
	this->StackHead->next = tmpCell;
	this->size++;
}

template <typename T>
T LinkedStack<T>::pop(){
	if(isEmpty())
	{
		cout << "Empty Wrong" << endl;
		return -1;
	}
	Node<T>* FirstCell;
	T TopElem;
	FirstCell = this->StackHead->next;
	TopElem = FirstCell->data;
	this->StackHead->next = FirstCell->next;
	delete FirstCell;
	this->size--;
	return TopElem;
}

template <typename T>
bool LinkedStack<T>::isEmpty()const{
	return (this->size == 0);
}

template <typename T>
int LinkedStack<T>::getSize()const{
	return this->size;
}


int main(){
	LinkedStack<int> test;
	cout << "The size: " << test.getSize() << endl;
	cout << "Is Empty?  " << test.isEmpty() << endl;
	for(int i=0; i<10; i++)
	{
		cout << "Push: " << i << endl;
		test.push(i);
	}	
	cout << "The size: " << test.getSize() << endl;
	for(int i=0; i<5; i++)
		cout << "Pop: " << test.pop() << endl;
	cout << "The size: " << test.getSize() << endl;
	cout << "Is Empty?  " << test.isEmpty() << endl;
	
	return 0;
}
