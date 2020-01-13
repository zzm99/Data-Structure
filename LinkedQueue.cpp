#include <iostream>
using namespace std;

template <typename T> 
struct Node
{
	T data;
	Node<T>* next;
};


template <typename T> class LinkedQueue{
private:
	int size;
	Node<T>* QueueHead;
public:
	LinkedQueue();
	~LinkedQueue();
	int getSize()const;
	bool isEmpty()const;
	T getFront()const;
	T getBack()const;
	void push(T e);
	T pop();
};

template <typename T>
LinkedQueue<T>::LinkedQueue(){
	this->size = 0;
	this->QueueHead = new Node<T>;
	this->QueueHead->next = NULL;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue(){
	while(this->size > 0)
	{
		this->pop();
	}
	delete this->QueueHead;
}


template <typename T>
int LinkedQueue<T>::getSize()const{
	return this->size;
}

template <typename T>
bool LinkedQueue<T>::isEmpty()const{
	return (this->size == 0);
}

template <typename T>
T LinkedQueue<T>::getFront()const{
	if(this->size == 0)
	{
		cout << "isEmpty Wrong" << endl;
		return -1;
	}
	return this->QueueHead->next->data;
}

template <typename T>
T LinkedQueue<T>::getBack()const{
	if(this->size == 0)
	{
		cout << "isEmpty Wrong" << endl;
		return -1;
	}
	Node<T>* cur = this->QueueHead;
	while(cur->next != NULL)
	{
		cur = cur->next;
	}
	return cur->data;
}


template <typename T>
void LinkedQueue<T>::push(T e){
	Node<T>* cur = this->QueueHead;
	while(cur->next != NULL)
	{
		cur = cur->next;
	}
	Node<T>* ans = new Node<T>;
	ans->data = e;
	ans->next = NULL;
	cur->next = ans;
	this->size++;
}

template <typename T>
T LinkedQueue<T>::pop(){
	if(this->size == 0)
	{
		cout << "isEmpty Wrong" << endl;
		return -1;
	}
	Node<T>* delNode = this->QueueHead->next;
	this->QueueHead->next = delNode->next;
	T retdata = delNode->data;
	delete delNode;
	this->size--;
	return retdata;
}


int main(){
	LinkedQueue<int> test;
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
	cout << "Now the front: " << test.getFront() << endl;
	cout << "Now the back: " << test.getBack() << endl;
	return 0;
}
