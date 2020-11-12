#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>

using namespace std;

template <class key, class value>
struct AvlNode
{
	key 	element; //word
	value   details;
	AvlNode *left;
	AvlNode *right;
	int     height;

	AvlNode( const key & theWord, value(word_struct), AvlNode *lt, AvlNode *rt, int h = 0 )
		: element( theWord ), details(word_struct), left( lt ), right( rt ), height( h ) { }

};


template <class key, class value>
class AvlTree
{
public:
	explicit AvlTree( const key & notFound, const value & Val);
	const key & find( const key & x ) const;
	value *FindDet(key& a);
	void insert( const key & x, const value & y );


private:
	AvlNode<key, value> *root;
	const key ITEM_NOT_FOUND;

	const key & elementAt( AvlNode<key, value> *t ) const;
	void insert( const key & x, const value &val,AvlNode<key, value>* &t ) const;
	void printTree( AvlNode<key, value> *t ) const;
	AvlNode<key, value> * find( const key & x, AvlNode<key, value> *t ) const;
	AvlNode<key, value> * clone( AvlNode<key, value> *t ) const;

	// Avl manipulations
	int height( AvlNode<key, value> *t ) const;
	int max( int lhs, int rhs ) const;
	void rotateWithLeftChild( AvlNode<key, value> * & k2 ) const;
	void rotateWithRightChild( AvlNode<key, value> * & k1 ) const;
	void doubleWithLeftChild( AvlNode<key, value> * & k3 ) const;
	void doubleWithRightChild( AvlNode<key, value> * & k1 ) const;
};



using namespace std;

//PUBLIC FUNCTIONS OF AVL TREE
template <class key,class value>  //constructor
AvlTree<key,value>::
	AvlTree(const key & notFound,const value & Val ) :
	ITEM_NOT_FOUND( notFound ), root( NULL )
{}


template <class key, class value>
const key & AvlTree<key, value>::find( const key & x ) const // public find
{
	return elementAt( find( x, root ) );
}

template<class key,class value>
value* AvlTree<key,value>::FindDet(key & a)
{
	return &find(a,root)->details;
}

template <class key, class value>
void AvlTree<key, value>::insert( const key & x, const value & y ) //public insert
{
	insert( x, y, root );
}


//PRIVATE FUNCTIONS OF AVL TREE
template <class key, class value>
const key & AvlTree<key, value>::elementAt( AvlNode<key, value> *t ) const //element at
{
	return t == NULL ? ITEM_NOT_FOUND : t->element;
}

template <class key, class value>
void AvlTree<key, value>::insert ( const key & x, const value &vall, AvlNode<key, value>* &t) const // private insert
{
	//AvlNode<key, value>* t = root;
	if ( t == NULL )
		t = new AvlNode<key, value>( x, vall, NULL, NULL,0 );

	else if ( x < t->element ) {
		// X should be inserted to the left tree!
		insert( x, vall, t->left );
		// Check if the left tree is out of balance (left subtree grew in height!)
		if ( height( t->left ) - height( t->right ) == 2 )
		{
			if ( x < t->left->element )  // X was inserted to the left-left subtree!
				rotateWithLeftChild( t );
			else			     // X was inserted to the left-right subtree!
				doubleWithLeftChild( t );
		}
	}

	else if( t->element < x )
	{    // Otherwise X is inserted to the right subtree
		insert( x, vall,t->right );
		if ( height( t->right ) - height( t->left ) == 2 )
		{
			// height of the right subtree increased
			if ( t->right->element < x )
			{
				// X was inserted to right-right subtree
				rotateWithRightChild( t );
			}
			else // X was inserted to right-left subtree
			{doubleWithRightChild( t );}
		}
		else
		{;}  // Duplicate; do nothing

		t->height = max( height( t->left ), height( t->right ) ) + 1;
	}
}

template <class key, class value>
AvlNode<key, value> *
	AvlTree<key, value>::find( const key & x, AvlNode<key, value> * t ) const //private find
{
	if ( t == NULL )
		return NULL;
	else if( x < t->element )
		return find( x, t->left );
	else if( t->element < x )
		return find( x, t->right );
	else
		return t;    // Match
}

template <class key, class value>
AvlNode<key, value> *AvlTree<key, value>::clone( AvlNode<key, value> * t ) const //clone
{
	if ( t == NULL )
		return NULL;
	else
		return new BinaryNode<value> 
		( t->element, 
		clone( t->left ), 
		clone( t->right ) );
}



//AVL MANIPULATIONS
template <class key, class value>
int AvlTree<key, value>::max( int lhs, int rhs ) const //max
{
	if (lhs > rhs)
		return lhs;

	return rhs;            
}
template <class key, class value>
int AvlTree<key, value>::height( AvlNode<key, value> *t ) const //height
{
	if (t == NULL)
		return -1;

	return t->height;
}
template <class key, class value>
void AvlTree<key, value>::rotateWithLeftChild(  //single left rotation
											  AvlNode<key, value> * & k2 ) const
{
	AvlNode<key, value> *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
	k1->height = max( height( k1->left ), k2->height ) + 1;
	k2 = k1;
}
template <class key, class value>
void AvlTree<key, value>::doubleWithLeftChild( AvlNode<key, value> * & k3 )  //double left rotation
	const
{
	rotateWithRightChild( k3->left );
	rotateWithLeftChild( k3 );
}
template <class key, class value>
void AvlTree<key, value>::rotateWithRightChild	//single right rotation
	( AvlNode<key, value> * & k1 ) const
{
	AvlNode<key, value> *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
	k2->height = max( height( k2->right ), k1->height ) + 1;
	k1 = k2;
}
template <class key, class value>
void AvlTree<key, value>::doubleWithRightChild   //double right rotation
	( AvlNode<key, value> * & k1 ) const
{
	rotateWithLeftChild( k1->right );
	rotateWithRightChild( k1 );
}

#endif
