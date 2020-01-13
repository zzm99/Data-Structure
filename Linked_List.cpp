#include <iostream>
using namespace std;
#define max_size 10
//simply linked implementation

template<typename T>
struct Node{
	T entry;
	Node<T> *next;
	Node(){
		entry = 0;
		next = NULL;
	}
	Node(T x, Node<T>* link = NULL){
		entry = x;
		next = link;
	}
};

template<typename T>
class List{
private:
	int count;
	Node<T> *head;
public:
	List();
	List(const List<T>& copy);
	~List(){ clear(); }
	bool empty(){ return count; }
	bool full() { return count >= max_size; }
	int size(){ return count; }
	void clear(){
		Node<T>* q = head;
		while(q){
			Node<T>* cur = q->next;
			delete q;
			q = cur;
		}
		count = 0;
	}
	List<T> operator=(const List<T>& copy);
	Node<T>* set_position(int position)const;
	bool insert(int position, const T& x);
	bool replace(int position, const T& x);
	bool remove(int position, T& x);
}

template<typename T>
Node<T>* List<T>::set_position(int position)const{
	Node<T>* q = head;
	for(int i=0; i<position; i++) q = q->next;
	return q;
}

template<typename T>
bool List<T>::insert(int position, const T& x){
	if(position < 0 || position > count) return false;
	Node<T>* new_node, *previous, *following;
	if(position == 0) following = head;
	else{
		previous = set_position(position-1);
		following = previous->next;
	}
	new_node = new Node<T>(x, following);
	if(new_node == NULL) return false;
	if(position == 0) head = new_node;
	else previous->next = new_node;
	count++;
	return true;
}

template<typename T>
List<T> List<T>::operator=(const List<T>& copy){
	clear();
	this->count = copy.count;
	this->head = new Node<T>(copy.head->entry, copy.head->next);
	return &this;
}


template<typename T>
bool List<T>::replace(int position, const T& x){
	if(position < 0 || position >= count) return false;
	Node<T>* tmp;
	tmp = set_position(position);
	if(tmp != NULL){
		tmp->entry = x;
	}
	else
		return false;
	return true;
}

template<typename T>
bool List<T>::remove(int position, T& x){
	if(position < 0 || position >= count) return false;
	Node<T>* tmp;
	tmp = set_position(position);
	if(!tmp)
		return false;
	else{
		Node<T>* pre = set_position(position-1);
		pre->next = tmp->next;
		delete tmp;
		count--;
	}
	return true;
}
