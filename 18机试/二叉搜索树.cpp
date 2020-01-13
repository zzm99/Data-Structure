#include <iostream>
using namespace std;

void Visit(int key, int count)
{
    cout << key << ":" << count << endl;
}

struct BSTNode {
    int Key;
    int Count;
    BSTNode *LChild, *RChild;
    BSTNode(){};
    BSTNode(int key) { Key = key; Count = 1; LChild = RChild = NULL; };
};

class BSTree {
public:
    BSTree() { Root = NULL; };
    void Insert(int key) { Rec_Insert(Root, key); };
    void PostOrder(void visit(int, int)) { Rec_PostOrder(Root, visit); };
    bool Remove(int key){ return remove_root(Root, key) != NULL;}
    int Search(int key);
    int findLCA(int key1, int key2){findLCA(Root, key1, key2);}
private:
    BSTNode* remove_root(BSTNode* root, int key);
    void Rec_Insert(BSTNode* &root, int key);
    void Rec_PostOrder(BSTNode *root, void visit(int, int));
    BSTNode *Root;
    int findLCA(BSTNode *root, int key1, int key2);
};

BSTNode* BSTree::remove_root(BSTNode* root, int key){
    if(root == NULL) return root;
    if(key < root->Key) root->LChild = remove_root(root->LChild, key);
    else if(key > root->Key) root->RChild = remove_root(root->RChild, key);
    else{
        if(root->LChild == NULL){
            BSTNode* tmp = root->RChild;
            delete root;
            return tmp;
        }
        else if(root->RChild == NULL){
            BSTNode* tmp = root->LChild;
            delete root;
            return tmp;
        }
        BSTNode* tmp = root->LChild;
        while(tmp->RChild!=NULL){
            tmp = tmp->RChild;
        }
        root->Key = tmp->Key;
        root->Count = tmp->Count;
        root->LChild = remove_root(root->LChild, tmp->Key);
    }
    return root;
}

void BSTree::Rec_Insert(BSTNode* &root, int key){
    if(root == NULL) {root =  new BSTNode(key); return;}
    if(root->Key == key) root->Count++;
    else if(root->Key > key) Rec_Insert(root->LChild, key);
    else Rec_Insert(root->RChild, key);
}

void BSTree::Rec_PostOrder(BSTNode *root, void visit(int, int)){
    if(root == NULL) return;
    Rec_PostOrder(root->LChild, visit);
    Rec_PostOrder(root->RChild, visit);
    visit(root->Key, root->Count);
}

int BSTree::Search(int key){
    BSTNode* cur = Root;
    while(cur != NULL){
        if(cur->Key == key) return cur->Count;
        if(cur->Key < key) cur = cur->RChild;
        else cur = cur->LChild;
    }
    return 0;
}

int BSTree::findLCA(BSTNode *root, int key1, int key2){
    if(root == NULL) return -1;
    if(root->Key == key1 || root->Key == key2) return root->Key;
    int l = -1, r = -1;
    l = findLCA(root->LChild, key1, key2);
    r = findLCA(root->RChild, key1, key2);
    if(l != -1 && r != -1) return root->Key;
    return l == -1 ? r : l;
}

int main(){
    BSTree T1;
    T1.Insert(20); T1.Insert(20);
    T1.Insert(15); T1.Insert(15); T1.Insert(15);
    T1.Insert(33);
    for(int i=0; i<10; i++) T1.Insert(8);
    for(int i=0; i<5; i++) T1.Insert(18);
    for(int i=0; i<4; i++) T1.Insert(45);
    T1.PostOrder(Visit);
    cout << "Search: " << endl;
    cout << T1.Search(45) << endl;
    cout << T1.Search(145) << endl;
    cout << "LCA: " <<endl;
    cout << T1.findLCA(15, 33) << endl;
    cout << T1.findLCA(8, 15) << endl;
    cout << T1.findLCA(8, 18) << endl;
    cout << T1.findLCA(45, 18) << endl;
    cout << "Remove: " <<endl;
    T1.Remove(33);
    T1.PostOrder(Visit);
    cout <<endl;
    T1.Remove(15);
    T1.PostOrder(Visit);
    cout <<endl;
    T1.Remove(18);
    T1.PostOrder(Visit);
    cout <<endl;
    return 0;
}
