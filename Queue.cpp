#include <vector>
#include <iostream>

using namespace std;

template <typename T> class Queue{
private:
	vector<T> qqueue;
	int size;
public:
	Queue();
	~Queue();
	void push(T e);
	T pop();
	int getSize()const;
	int isEmpty()const;
	T getFront();
	T getBack();
};

template <typename T>
Queue<T>::Queue(){
	this->size = 0;
}

template <typename T>
Queue<T>::~Queue(){

}

template <typename T>
void Queue<T>::push(T e){
	this->qqueue.push_back(e);
	this->size++;
}

template <typename T>
T Queue<T>::pop(){
	if(this->size == 0)
	{
		cout << "isEmpty Wrong" << endl;
		return -1;
	}
	T ret = this->qqueue[0];
	for(int i=0; i<this->size-1; i++)
		this->qqueue[i] = this->qqueue[i+1];
	this->qqueue.erase(this->qqueue.begin() + this->size - 1);
	this->size --;
	return ret;
}

template <typename T>
int Queue<T>::getSize()const{
	return this->size;
}

template <typename T>
int Queue<T>::isEmpty()const{
	return (this->size == 0);
}

template <typename T>
T Queue<T>::getFront(){
	if(this->size == 0)
	{
		cout << "isEmpty Wrong" << endl;
		return -1;
	}
	return this->qqueue[0];
}

template <typename T>
T Queue<T>::getBack(){
	if(this->size == 0)
	{
		cout << "isEmpty Wrong" << endl;
		return -1;
	}
	return this->qqueue[this->size-1];
}


int main(){
	Queue<int> test;
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
