#include <iostream>
#include <queue>
using namespace std;

template < typename T >
struct TreeNode
{
	TreeNode(T s): data(s), left(NULL), right(NULL) {}
	T data;
	TreeNode* left;
	TreeNode* right;
};

template < typename T >
class Tree {
private:
	int size;
	TreeNode<T>* root;
public:
	Tree(): size(0), root(NULL){};
	Tree( T x ){
		size = 1;
		root = new TreeNode<T>(x);
	}
	~Tree(){
		if(size > 0){
			queue<TreeNode<T>*> delq;
			delq.push(root);
			while(!delq.empty()){
				TreeNode<T>* x = delq.front();
				delq.pop();
				if(x->left) delq.push(x->left);
				if(x->right) delq.push(x->right);
				delete( x );
			}
		}
	}
	Tree<T>& operator= (Tree<T>& t){
		if(this->root != t.root)
		{
			this->root = t.root;
		}
		return *this;
	}
	int getsize()const { return this->size; }
	TreeNode<T>* getroot() const { return this->root; }
	TreeNode<T>* insertasleft( TreeNode<T>* x, T data ){
		x->left = new TreeNode<T>(data);
		size++;
		return x;
	}
	TreeNode<T>* insertasright( TreeNode<T>* x, T data ){
		x->right = new TreeNode<T>(data);
		size++;
		return x;
	}
	void preorder( TreeNode<T>* root){
		cout << root->data << " ";
		if(root->left) preorder(root->left);
		if(root->right) preorder(root->right);
	}
	void inorder( TreeNode<T>* root){
		if(root->left) inorder(root->left);
		cout << root->data << " ";
		if(root->right) inorder(root->right);
	}
	void postorder( TreeNode<T>* root){
		if(root->left) postorder(root->left);
		if(root->right) postorder(root->right);
		cout << root->data << " ";
	}
	void levelorder( TreeNode<T>* root){
		queue<TreeNode<T>*> Q;
		Q.push(root);
		int levelcur = 0;
		while(!Q.empty())
		{
			levelcur ++;
			cout << "level " << levelcur << " : ";
			queue<TreeNode<T>*> rem;
			while(!Q.empty())
			{
				TreeNode<T>* x = Q.front();
				Q.pop();
				if(x->left) rem.push(x->left);
				if(x->right) rem.push(x->right);
				cout << x->data << " ";
			}
			queue<TreeNode<T>*> temp = Q;
			Q = rem;
			rem = temp;
			cout << endl;
		}
	}
	int find_leaf_size( TreeNode<T>* leaf ){
		if( !leaf ) return 0;
		if( leaf->left == NULL && leaf->right == NULL ) return 1;
		return find_leaf_size( leaf->left ) + find_leaf_size( leaf->right );
	}
	int find_leaf_depth( TreeNode<T>* leaf){
		if(!leaf) return 0;
		int size_left = find_leaf_depth( leaf->left );
		int size_right = find_leaf_depth( leaf->right );
		if( size_left > size_right )
			return size_left + 1;
		else
			return size_right + 1;
	}
	TreeNode<T>* find_x_leaf( TreeNode<T>* root, const T& x){
		if( !root ) return NULL;
		if( root->data == x )  return root;
		TreeNode<T>* find_left = find_x_leaf ( root->left, x );
		if( find_left )
			return find_left;
		else
			return find_x_leaf ( root->right, x );
	}
	int find_x_level_size( TreeNode<T>* root, const T& x){
		if( !root ) return 0;
		if( x == 1 ) return 1;
		else return find_x_level_size( root->left, x-1 ) +  find_x_level_size( root->right, x-1 );
	} 
};


int main(){
	Tree<int> test(1);
	cout << "getsize: " << test.getsize() << endl;
	test.insertasleft( test.getroot(), 2);
	test.insertasright( test.getroot(), 3);
	cout << "getsize: " << test.getsize() << endl;
	cout << "preorder: ";
	test.preorder( test.getroot() );
	cout << endl;
	cout << "inorder: ";
	test.inorder( test.getroot() );
	cout << endl;
	cout << "postorder: ";
	test.postorder( test.getroot() );
	cout << endl;
	Tree<int> test1;
	test1 = test;
	cout << "test1 after = : test1.root->data = " << test.getroot()->data << endl;
	cout << "leveltravel: " << endl;
	test.levelorder( test.getroot() );
	cout << endl;
	cout << "find_leaf_size : " << endl;
	cout << " test.root : " << test.find_leaf_size( test.getroot() ) << endl;
	cout << " test.root->left : " << test.find_leaf_size( test.getroot()->left ) << endl;
	cout << " test.root->right : " << test.find_leaf_size( test.getroot()->right ) << endl;
	cout << "find_leaf_depth : " << endl;
	cout << " test.root : " << test.find_leaf_depth( test.getroot() ) << endl;
	cout << " test.root->left : " << test.find_leaf_depth( test.getroot()->left ) << endl;
	cout << " test.root->right : " << test.find_leaf_depth( test.getroot()->right ) << endl;
	cout << "find_x_leaf : " << endl;
	cout << " 1 : " << test.find_x_leaf( test.getroot(), 1 )->data << endl;
	cout << "find_x_level_size : " << endl;
	cout << " level-2 : " << test.find_x_level_size( test.getroot(), 2 ) << endl;
	return 0;
}
