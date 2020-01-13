#include <iostream>
using namespace std;

struct Node {
    int Key; 
    Node *LChild, *RChild;
    Node() {};
    Node(int key) { Key = key; LChild = RChild = NULL; };
};

class BiTree {
public:
    BiTree() { Root = NULL; };
    BiTree(int keys[], int n) {
        int pos = 0;
        Root = createBiTree(keys, pos, n);
    };
    int findLCA(int key1, int key2) { return findLCA(Root, key1, key2);};
private:
    Node *createBiTree(int keys[], int &pos, int n);
    int findLCA(Node *root, int key1, int key2);
    Node *Root;
};

Node* BiTree::createBiTree(int keys[], int &pos, int n)
{
    if(pos >= n) return NULL;
    if(keys[pos] == 0) {pos++; return NULL; }
    Node *Pt = new Node(keys[pos]);
    pos++;
    Pt->LChild = createBiTree(keys, pos, n);
    Pt->RChild = createBiTree(keys, pos, n);
    return Pt;
}

int BiTree::findLCA(Node *root, int key1, int key2){
    if(root == NULL) return -1;
    if(root->Key == key1 || root->Key == key2) return root->Key;
    int l = -1, r = -1;
    l = findLCA(root->LChild, key1, key2);
    r = findLCA(root->RChild, key1, key2);
    if(l != -1 && r != -1) return root->Key;
    return l == -1 ? r : l;
}

int main(){
    /*
    BiTree T;
    cout << T.findLCA(2, 5) << endl;
    cout << T.findLCA(7, 8) << endl;
    cout << T.findLCA(2, 7) << endl;
    */
    return 0;
}
