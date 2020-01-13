#include <iostream>
using namespace std;
#define MAXQUEUE 10

void Visit(int index, int key){
    cout << index << ":" << key << " ";
}

class CQueue{
public:
    CQueue(){Front = 0; Rear = -1;}
    bool Append(int key);
    bool Serve(int &key);
    void Display(void visit(int, int));
    int GetCount(){ return (Rear-Front+1+MAXQUEUE)%MAXQUEUE; }
private:
    int Front, Rear;
    int Data[MAXQUEUE];
};


bool CQueue::Append(int key){
    if(GetCount() == MAXQUEUE) return false;
    Rear = (Rear+1) % MAXQUEUE;
    Data[Rear] = key;
    return true;
}

bool CQueue::Serve(int &key){
    if(GetCount() == 0) return false;
    key = Data[Front];
    Front = (Front+1) % MAXQUEUE;
    return true;
}

void CQueue::Display(void Visit(int, int)){
    for(int i=0; i<GetCount(); i++){
        Visit((Front+i)%MAXQUEUE, Data[(Front+i)%MAXQUEUE]);
    }
    cout << endl;
}

int main(){
    CQueue test;
    for(int i=0; i<7; i++) test.Append(i);
    test.Display(Visit);
    for(int i=0; i<3; i++){
        int cur = 0;
        if(test.Serve(cur)) cout << cur << " ";
    }
    cout <<endl;
    test.Display(Visit);
    for(int i=0; i<4; i++) test.Append(i*i);
    test.Display(Visit);
    return 0;
}

