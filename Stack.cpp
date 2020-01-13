#include <vector>
#include <iostream>
using namespace std;

#define MAX_SIZE  10

template <typename T> class Stack{
private:
	vector<T> sstack; 
	int size;
public:
	Stack();
	~Stack();
	void push(T const& e);
	T pop();
	T& top();
	bool isFull()const;
	bool isEmpty()const;
	int getsize()const;
	void clear();
}; 

template <typename T>
Stack<T>::Stack(){
	this->size = 0;
} 

template <typename T>
Stack<T>::~Stack(){

}

template <typename T>
void Stack<T>::push(T const& e){
	if(this->isFull())
		return;
	this->sstack.push_back(e);
	size++;
}

template <typename T>
T Stack<T>::pop(){
	if(this->isEmpty())
	{
		cout << "Wrong" << endl;
		return 0;
	}
	T ret = this->sstack[this->size-1];
	this->sstack.erase(this->sstack.begin()+this->size-1);
	size--;
	return ret;
}

template <typename T>
T& Stack<T>::top(){
	return this->sstack[this->size-1];
}

template <typename T>
bool Stack<T>::isFull()const{
	return (this->size == MAX_SIZE);
}

template <typename T>
bool Stack<T>::isEmpty()const{
	return (this->size == 0);
}

template <typename T>
int Stack<T>::getsize()const{
	return this->size;
}

template <typename T>
void Stack<T>::clear(){

}

int main(){
	Stack<int> test;
	cout << "The size: " << test.getsize() << endl;
	cout << "Is Empty?  " << test.isEmpty() << endl;
	for(int i=0; i<10; i++)
	{
		cout << "Push: " << i << endl;
		test.push(i);
	}	
	cout << "The size: " << test.getsize() << endl;
	for(int i=0; i<5; i++)
		cout << "Pop: " << test.pop() << endl;
	cout << "The size: " << test.getsize() << endl;
	cout << "Is Empty?  " << test.isEmpty() << endl;
	
	return 0;
}
