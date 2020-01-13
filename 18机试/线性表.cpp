#include <iostream>
using namespace std;
#define MAXLIST 10

void Visit(int key, int count)
{
    cout << key << ":" << count << " ";
}

struct Node {
    int Key;
    int Count;
};

class MyList {
public:
    MyList() { Rear = -1; };
    bool Append(int key);
    bool Delete(int key);
    void Traversal(void visit(int, int));
private:
    int Rear;
    Node Data[MAXLIST];
};

bool MyList::Append(int key){
    for(int i=0; i<=Rear; i++){
        if(Data[i].Key == key){
            Data[i].Count++;
            return true;
        }
    }
    if(Rear == MAXLIST-1) return false;
    Rear++;
    Data[Rear].Key = key;
    Data[Rear].Count = 1;
    return true;
}

bool MyList::Delete(int key){
    for(int i=0; i<=Rear; i++){
        if(Data[i].Key == key){
            Data[i].Count--;
            if(Data[i].Count > 0) return true;
            for(int j=i; j<Rear; j++){
                Data[j] = Data[j+1];
            }
            Rear--;
            return true;
        }
    }
    return false;
}

void MyList::Traversal(void visit(int, int)){
    for(int i=0; i<=Rear; i++){
        visit(Data[i].Key, Data[i].Count);
    }
    cout << endl;
}

int main(){
    MyList test;
    for(int i=0; i<5; i++){
        test.Append(i);
        test.Append(i);
    }
    test.Traversal(Visit);
    for(int i=0; i<5; i++){
        test.Delete(i);
    }
    test.Traversal(Visit);
    test.Delete(0);
    test.Traversal(Visit);
    return 0;
}
