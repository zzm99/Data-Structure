#include <iostream>
using namespace std;
#define MAXTABLE 11

struct HNode {
    int Key;
    HNode *next;
    HNode() { next = NULL; };
    HNode(int key) { Key = key; next = NULL; };
};

class HashList {
public:
    ~HashList();
    int Hash(int key) { return (3*key+7) % MAXTABLE; };
    bool Insert(int key);
    bool Search(int key);
    void Display();
private:
    HNode Table[MAXTABLE];
};

bool HashList::Insert(int key){
    int hashkey = Hash(key);
    if(Table[hashkey].next == NULL){
        Table[hashkey].next = new HNode(key);
        return true;
    }
    HNode* cur = Table[hashkey].next;
    while(cur->next){
        cur = cur->next;
    }
    cur->next = new HNode(key);
    return true;
}

bool HashList::Search(int key){
    int hashkey = Hash(key);
    if(Table[hashkey].next == NULL) return false;
    HNode* cur = Table[hashkey].next;
    while(cur != NULL){
        if(cur->Key == key) return true;
        cur = cur->next;
    }
    return false;
}

void HashList::Display()
{
    HNode *Pt;
    for (int i = 0; i < MAXTABLE; i++) {
        cout << i << ":";
        for (Pt = Table[i].next; Pt != NULL; Pt = Pt->next) cout << " " << Pt->Key;
        cout << endl;
    }
}

HashList::~HashList()
{
    HNode *Pt1, *Pt2;
    for (int i = 0; i < MAXTABLE; i++) {
        Pt1 = Table[i].next;
        while (Pt1 != NULL) {
            Pt2 = Pt1;
            Pt1 = Pt1->next;
            delete Pt2;
        }
    }
}

int main(){
    HashList test;
    test.Insert(5); test.Insert(60); test.Insert(38);
    test.Display(); cout << endl;
    test.Insert(9); test.Insert(42);
    test.Display(); cout << endl;
    test.Insert(72); test.Insert(50); test.Insert(6); test.Insert(28);
    test.Display(); cout << endl;
    test.Insert(25); test.Insert(80); test.Insert(3);
    test.Display(); cout << endl;
    test.Insert(40); test.Insert(7);
    test.Display(); cout << endl;
    test.Insert(19); test.Insert(41); test.Insert(8);
    test.Display(); cout << endl;
    test.Insert(67);
    test.Display(); cout << endl;
}

