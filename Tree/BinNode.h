// 二叉树的基本组陈实体是二叉树节点，而边则对应于节点之间的相互关系
#include <iostream>
#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p)  ((p) ? (p)->height : -1)// 节点高度，约定空树高度为-1

//BinNode 状态与性质的判断：
#define IsRoot(x) ( !( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( &(x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( &(x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) )
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) )
#define IsLeaf(x) ( ! HasChild(x) )

// 与BinNode具有特定关系的节点以及指针:
#define sibling(p) ( IsLChild(*(p)) ? (p)->parent->rc: (p)->parent->lc ) //兄弟
#define uncle(x) ( IsLChild(*((x)->parent)) ? (x)->parent->parent->rc: (x)->parent->parent->lc ) //叔叔
#define FromParentTo(x) /*来自父亲的引用*/ ( IsRoot(x) ? _root: ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) ) //含有父指针的二叉树结点，一般会定义这样的一个宏（获取从父节点指向自己的指针）


typedef enum { RE_RED, RB_BLACK} RBColor; //节点颜色

template <typename T> struct BinNode{ //二叉树节点模板类
// 成员
	T data;
	BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; // 父节点以及左右孩子
	int height; //高度
	int npl; //Null Path Length (左式堆， 也可以用height代替)
	RBColor color; //颜色 红黑树
// 构造函数
	BinNode(): parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RE_RED) {}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RE_RED): data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c){}
// 操作接口
	int size(); // 统计当前节点后代总数，亦即以其为根的子树的规模
	BinNodePosi(T) insertAsLC( T const& ); // 作为当前节点的左孩子插入新节点
	BinNodePosi(T) insertAsRC( T const& ); // 作为当前节点的右孩子插入新节点
	BinNodePosi(T) succ(); //取当前节点的直接后继
	template <typename VST> void travLevel( VST& ); //子树层次遍历
	template <typename VST> void travPre( VST& ); //子树先序遍历
	template <typename VST> void travIn( VST& ); //子树中序遍历
	template <typename VST> void travPost( VST& ); //子树后序遍历
// 比较器、判等器 
	bool operator< (BinNode const& bn) { return data < bn.data; }
	bool operator== (BinNode const& bn) { return data == bn.data; }
	bool operator> (BinNode const& bn) { return data > bn.data; }
	bool operator<= (BinNode const& bn) { return data <= bn.data; }
	bool operator>= (BinNode const& bn) { return data >= bn.data; }
	bool operator!= (BinNode const& bn) { return data != bn.data; }
};

// 插入儿子节点： 约定插入新节点之前，当前节点尚无左/右孩子
template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC( T const& e)
{
	return lc = new BinNode( e, this );
	/* 相当于：
		this->lc = new BinNode(e, this);
		return this->lc;
	*/
}

template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC( T const& e)
{
	return rc = new BinNode( e, this );
}


