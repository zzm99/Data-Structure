#include <iostream>
using namespace std;
#define max_list 10

template <typename T> class List{
private:
	int count;
	T entry[max_list];
public:
	List();
	int size()const;
	bool full()const;
	bool empty()const;
	void clear();
	void traverse(void (*visit)(T&));
	bool retrieve(int position, T& x)const;
	bool replace(int position, const T& x);
	bool remove(int position, T& x);
	bool insert(int position, const T& x);
};

template<typename T>
List<T>::List(){
	count = 0;
}

template<typename T>
int List<T>::size()const{
	return count;
}

template<typename T>
bool List<T>::full()const{
	return count >= max_list;
}

template<typename T>
bool List<T>::empty()const{
	return count == 0;
}

template<typename T>
void List<T>::clear(){
	for(int i=0; i<count; i++)
		entry = 0;
	count = 0;
}

template<typename T>
bool List<T>::replace(int position, const T& x){
	if(position < 0 || position > count) return false;
	entry[position] = x;
	return true;
}

template<typename T>
bool List<T>::insert(int position, const T& x){
	if(full()) return false;
	if(position < 0 || position > count) return false;
	for(int i=count-1; i>=position; i--) entry[i+1] = entry[i];
	entry[position] = x;
	count++;
	return true;
}

template<typename T>
void List<T>::traverse(void (*visit)(T&)){ //function pointer
	for(int i=0; i<count; i++)
		visit(entry[i]);
}


template<typename T>
bool List<T>::remove(int position, T& x){
	if(position < 0 || position >= count) return false;
	x = entry[position];
	for(int i=position; i<count-1; i++)
		entry[i] = entry[i+1];
	count--;
	return true;
}

template<typename T>
bool List<T>::retrieve(int position, T& x)const{
	if(position < 0 || position >= count) return false;
	x = entry[position];
	return true;
}
