#include "BinNode.h"
#include <queue>
template <typename T> class BinTree{
protected:
	int _size; //规模
	BinNodePosi(T) _root; //根节点
	virtual int updateHeight ( BinNodePosi(T) x ); //更新节点x的高度
	void updateHeightAbove ( BinNodePosi(T) x ); //更新节点x及其祖先的高度
public:
	BinTree(): _size(0), _root(NULL) {}
	~BinTree() {
		if(0 < _size)
			remove( _root );
	}
	int size() const { return _size; }
	bool empty() const { return !_root; }
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsRoot ( T const& e );
	BinNodePosi(T) insertAsLC ( BinNodePosi(T) x, T const& e);
	BinNodePosi(T) insertAsRC ( BinNodePosi(T) x, T const& e);
	BinNodePosi(T) attachAsLC ( BinNodePosi(T) x, BinTree<T>* &S);//T作为x左子树插入
	BinNodePosi(T) attachAsRC ( BinNodePosi(T) x, BinTree<T>* &S);
	int remove ( BinNodePosi(T) x); //删除以位置x处节点为根的子树，返回该子树原先的规模
	BinTree<T>* secede ( BinNodePosi(T) x ); // 将子树x从当前树中摘除，并将其转换为一颗独立的子树
	template <typename VST> void travLevel( VST& visit) { if(_root) _root->travLevel(visit); } // 层次遍历
	template <typename VST> void travPre (VST& visit) { if(_root) _root->travPre(visit); }
	template <typename VST> void travIn (VST& visit) { if(_root) _root->travIn(visit); }
	template <typename VST> void travPost (VST& visit) { if(_root) _root->travPost(visit); }
	bool operator< (BinTree<T> const& t) { return _root && t._root && (_root->data < t._root->data); }
	bool operator== (BinTree<T> const& t) { return _root && t._root && (_root->data == t._root->data); }
	bool operator!= (BinTree<T> const& t) { return _root && t._root && (_root->data != t._root->data); }
	bool operator> (BinTree<T> const& t) { return _root && t._root && (_root->data > t._root->data); }
	bool operator<= (BinTree<T> const& t) { return _root && t._root && (_root->data <= t._root->data); }
	bool operator>= (BinTree<T> const& t) { return _root && t._root && (_root->data >= t._root->data); }
};

// 一旦有节点加入/离开二叉树，则更新其所有祖先的高度
int max(int a,int b)
{
	return a > b ? a : b;
}

template <typename T> int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while(x)
	{
		updateHeight(x); 
		x = x->parent;
	}
} // 在某些种类的二叉树（红黑树）中，高度的定义有所不同，因此这里updateHeight()定义为保护级的虚函数，以便派生类在必要时重写(override)

//节点插入：
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot( T const& e){
	_size = 1;
	return _root = new BinNode<T>(e);
}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(  BinNodePosi(T) x, T const& e){
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lc;
}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC(  BinNodePosi(T) x, T const& e){
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->lc;
}

//子树接入：
//指针是一个存放地址的变量，而指针引用指的是这个变量的引用，众所周知C++中如果参数不是引用的话会调用参数对象的拷贝构造函数，所以如果有需求想改变指针所指的对象（换句话说，就是要改变指针里面存的地址），就要使用指针引用
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC( BinNodePosi(T) x, BinTree<T>* &S){
	if(x->lc = S->_root) x->lc->parent = x;
	_size += S->_size;
	updateHeightAbove(x);
	S->root = NULL;
	S->_size = 0;
	release( S );
	S = NULL;
	return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC( BinNodePosi(T) x, BinTree<T>* &S){
	if(x->rc = S->_root) x->rc->parent = x;
	_size += S->_size;
	updateHeightAbove(x);
	S->root = NULL;
	S->_size = 0;
	release( S );
	S = NULL;
	return x;
}

//子树删除
template <typename T>
int BinTree<T>::remove( BinNodePosi(T) x )
{
	FromParentTo(*x) = NULL; //切断来自父节点的指针
	updateHeightAbove(x->parent);//更新祖先高度
	int n = removeAt(x);
	_size -= n;
	return n; // 删除子树x，更新规模，返回删除节点总数
}

template <typename T> 
static int removeAt( BinNodePosi(T) x )
{
	if( !x ) return 0;
	int n = 1 + removeAt( x->lc ) + removeAt( x->rc );
//	release( x->data );
//	release( x );
	delete x;
	return n;  
}

// 子树分离
template <typename T>
BinTree<T>* BinTree<T>::secede( BinNodePosi(T) x ){
	FromParentTo ( *x ) = NULL;
	updateHeightAbove( x->parent );
	BinTree<T>* S = new BinTree<T>;
	S->root = x;
	x->parent = NULL;
	S->_size = x->size();
	_size -= S->_size;
	return S;
}

// 遍历：
template <typename T, typename VST>
void travPre ( BinNodePosi(T) x, VST& visit ){
	if( !x ) return;
	visit (x->data);
	travPre (x->lc, visit);
	travPre (x->rc, visit);
} 

template <typename T, typename VST>
void travPost ( BinNodePosi(T) x, VST& visit ){
	if( !x ) return;
	travPre (x->lc, visit);
	travPre (x->rc, visit);
	visit (x->data);
} 

template <typename T, typename VST>
void travIn ( BinNodePosi(T) x, VST& visit ){
	if( !x ) return;
	travPre (x->lc, visit);
	visit (x->data);
	travPre (x->rc, visit);
} 

// 直接后继及其定位 (中序遍历)
template <typename T> BinNodePosi(T) BinNode<T>::succ(){
	BinNodePosi(T) s = this;
	if(rc) //若有右孩子，则直接后继必在右子树中
	{
		s = rc;
		while(HasLChild(*s)) s = s->lc;
	}
	else // 否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”
	{
		while(IsRChild(*s)) s = s->parent;
		s = s->parent;
	}
	return s;
}

// 层次遍历
template <typename T> template <typename VST>
void BinNode<T>::travLevel(VST& visit)
{
	std::queue<BinNodePosi(T)> Q;
	Q.push (this);
	while( !Q.empty() ){
		BinNodePosi(T) x = Q.front(); Q.pop(); visit(x->data);
		if(HasLChild(*x)) Q.push(x->lc);
		if(HasRChild(*x)) Q.push(x->rc);
	}
}
