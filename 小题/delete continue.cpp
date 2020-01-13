#include <iostream>
using namespace std;

struct Node{
    int val;
    Node* next;
    Node(int val){
        this->val = val;
        this->next = NULL;
    }
};

Node* insert(Node* root, int val){
    Node* cur = root;
    while(cur->next!=NULL){
        cur = cur->next;
    }
    cur->next = new Node(val);
    return root;
}

void print(Node* root){
    Node* cur = root;
    while(cur != NULL){
        cout << cur->val << " ";
        cur = cur->next;
    }
}

Node* deleteM(Node* root){
    Node* cur = root;
    while(cur != NULL && cur->next != NULL){
        Node* next = cur->next;
        if(next->val == cur->val){
            cur->next = next->next;
            delete next;
        }else{
            cur = cur->next;
        }
    }
    return root;
}

int main(){
    Node* head = new Node(1);
    head = insert(head, 2);
    head = insert(head, 2);
    head = insert(head, 3);
    head = insert(head, 2);
    head = insert(head, 4);
    head = insert(head, 4);
    head = insert(head, 4);
    head = insert(head, 5);
    head = insert(head, 6);
    head = insert(head, 8);
    head = insert(head, 8);
    head = insert(head, 2);
    head = insert(head, 8);
    head = insert(head, 2);
    head = insert(head, 2);
    print(head);
    cout << endl;
    head = deleteM(head);
    print(head);
}
