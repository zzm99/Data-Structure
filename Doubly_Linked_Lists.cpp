#include <iostream>
using namespace std;

template<typename T>
struct Node
{
	T entry;
	Node<T> *back, *next;
	Node(){
		entry = 0;
		back = NULL;
		next = NULL;
	}
	Node(T x, Node<T>* link_back = NULL, Node<T>* link_next = NULL){
		entry = x;
		back = link_back;
		next = link_next;
	}
};

template<typename T>
class List
{
private:
	int count;
	mutable int current_position;
	mutable Node<T> *current;
public:
	List();
	~List();
	void set_position(int position)const;
	bool insert(int position, const T& x);
};

template<typename T>
void List<T>::set_position(int position)const{
	if(current_position <= position)
		for(; current_position != position; current_position++)
			current = current->next;
	else
		for(; current_position != position; current_position--)
			current = current->back;
}


template<typename T>
bool List<T>::insert(int position, const T& x){
	Node<T>* new_node, *following, *preceding;
	if(position < 0 || position > count) return false;
	if(position == 0){
		preceding = NULL;
		if(count = 0) following = NULL;
		else{
			set_position(0);
			following = current;
		}
	}
	else{
		set_position(position-1);
		preceding = current;
		following = preceding->next;
	}
	new_node = new Node<T>(x, preceding, following);
	if(new_node == NULL) return false;
	if(preceding != NULL) preceding->next = new_node;
	if(following != NULL) following->back = new_node;
	current = new_node;
	current_position = position;
	count++;
	return true;
}

